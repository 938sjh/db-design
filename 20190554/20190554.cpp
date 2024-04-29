#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "mysql.h"

#pragma comment(lib, "libmysql.lib")

const char* host = "localhost";
const char* user = "root";
const char* pw = "kjs6906";
const char* db = "project";

int main(void) {

	MYSQL* connection = NULL;
	MYSQL conn;
	MYSQL_RES* sql_result;
	MYSQL_ROW sql_row;

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");

	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}

	else
	{
		FILE* fp = fopen("20190554.txt", "r");
		char temp[1024];
		char* query;

		printf("Connection Succeed\n");
		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}

		for (int i = 0; i < 218; i++)
		{
			query = fgets(temp, 1024, fp);
			mysql_query(connection, query);
		}

		while (1)
		{
			int query_type, sub_type;
			printf("------- SELECT QUERY TYPES -------\n\n");
			printf("\t1. TYPE 1\n");
			printf("\t2. TYPE 2\n");
			printf("\t3. TYPE 3\n");
			printf("\t4. TYPE 4\n");
			printf("\t5. TYPE 5\n");
			printf("\t6. TYPE 6\n");
			printf("\t7. TYPE 7\n");
			printf("\t0. QUIT\n\n");
			printf("Enter Query type: ");
			scanf("%d", &query_type);
			printf("\n");
			int state = 0;
			char type_query[1024];
			if (query_type == 0)
			{
				break;
			}
			else if (query_type == 1)
			{
				int tracking_number;

				printf("---- TYPE 1 ----\n\n");
				printf("** Assume the package shipped by USPS with tracking number X is reported to have been destroyed in an accident.Find the contact information for the customer **\n");
				printf("Enter number X(7-digit): ");
				scanf("%d", &tracking_number);
				if (tracking_number < 1000000)
				{
					printf("invalid tracking_number\n");
					continue;
				}
				sprintf(type_query, "select phone_number from customer where customer_ID = (select customer_ID from deliver where tracking_number = '%d')", tracking_number);
				state = mysql_query(connection, type_query);
				if (state == 0)
				{
					sql_result = mysql_store_result(connection);
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("phone_number: %s\n\n", sql_row[0]);
					}
					mysql_free_result(sql_result);
				}
				printf("------ Subtypes in TYPE 1 ------\n");
				printf("\t1. TYPE 1-1\n");
				printf("\t0. QUIT\n");
				printf("Enter Subtype: ");
				scanf("%d", &sub_type);
				printf("\n");
				if (sub_type == 1)
				{
					printf("---- TYPE 1-1 ----\n\n");
					printf("** Then find the contents of that shipment and create a new shipment of replacement items **\n");
					sprintf(type_query, "select product_ID from deliver where tracking_number = '%d'", tracking_number);
					mysql_query(connection, type_query);
					sql_result = mysql_store_result(connection);
					sql_row = mysql_fetch_row(sql_result);
					sprintf(type_query, "select * from product where product_ID = %s", sql_row[0]);
					mysql_query(connection, type_query);
					sql_result = mysql_store_result(connection);
					sql_row = mysql_fetch_row(sql_result);

					int cnt1 = 1, cnt2 = 1;
					while (1)
					{
						MYSQL_ROW temp_row;
						sprintf(type_query, "select product_ID from product where product_ID = %d", atoi(sql_row[0] + cnt1));
						mysql_query(connection, type_query);
						sql_result = mysql_store_result(connection);
						temp_row = mysql_fetch_row(sql_result);
						if (temp_row)
							cnt1++;
						else
							break;
					}
					sprintf(type_query, "insert into Product (product_ID, model_name, store_ID, type, manufacturer, price, saled) values (%d, %s, %s, %s, %s, %s, %s);", atoi(sql_row[0]) + cnt1, sql_row[1], sql_row[2], sql_row[3], sql_row[4], sql_row[5], sql_row[6]);
					mysql_query(connection, type_query);
					sprintf(type_query, "select * from deliver where tracking_number = '%d'", tracking_number);
					mysql_query(connection, type_query);
					sql_result = mysql_store_result(connection);
					sql_row = mysql_fetch_row(sql_result);
					while (1)
					{
						MYSQL_ROW temp_row;
						sprintf(type_query, "select tracking_number from deliver where tracking_number = %d", atoi(sql_row[1]) + cnt2);
						mysql_query(connection, type_query);
						sql_result = mysql_store_result(connection);
						temp_row = mysql_fetch_row(sql_result);
						if (temp_row)
							cnt2++;
						else
							break;
					}
					sprintf(type_query, "insert into deliver (product_ID, tracking_number, estimated_delivery_date, delivery_completion_date, customer_ID) values ('%d', '%d', '%s', NULL, %s);", atoi(sql_row[0]) + cnt1, atoi(sql_row[1]) + cnt2, sql_row[2], sql_row[4]);
					mysql_query(connection, type_query);
					mysql_query(connection, "select * from deliver");
					sql_result = mysql_store_result(connection);
					printf("product_ID tracking_number estimated_delivery_date delivery_completion_date customer_ID\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s\t\t%s\t\t%s%22s%20s\n", sql_row[0], sql_row[1], sql_row[2], sql_row[3], sql_row[4]);
					}
				}
				else if (sub_type == 0)
				{
					continue;
				}
				else
				{
					printf("Invalid input\n");
				}
			}
			else if (query_type == 2)
			{
				printf("---- TYPE 2 ----\n\n");
				printf("**  Find the customer who has bought the most (by price) in the past year **\n");
				mysql_query(connection, "select customer_ID, sum(saled_price) as total_bill from sales group by customer_ID order by total_bill desc limit 1");
				sql_result = mysql_store_result(connection);
				sql_row = mysql_fetch_row(sql_result);
				printf("customer_ID and total_bill: %s %s\n\n", sql_row[0], sql_row[1]);
				printf("------ Subtypes in TYPE 2 ------\n");
				printf("\t1. TYPE 2-1\n");
				printf("\t0. QUIT\n");
				printf("Enter Subtype: ");
				scanf("%d", &sub_type);
				printf("\n");
				if (sub_type == 1)
				{
					printf("---- TYPE 2-1 ----\n\n");
					printf("** Then find the product that the customer bought the most **\n");
					mysql_query(connection, "select customer_ID from (select customer_ID, sum(saled_price) as total_bill from sales group by customer_ID order by total_bill desc limit 1) as t");
					sql_result = mysql_store_result(connection);
					sql_row = mysql_fetch_row(sql_result);
					sprintf(type_query, "select customer_ID, model_name, count(model_name) as unit_sale from sales, product where sales.product_ID = product.product_ID and customer_ID = %s group by model_name order by count(model_name) desc limit 1", sql_row[0]);
					mysql_query(connection, type_query);
					sql_result = mysql_store_result(connection);
					sql_row = mysql_fetch_row(sql_result);
					printf("customer_ID model_name unit_sale\n");
					printf("%s\t\t%s\t  %s\n", sql_row[0], sql_row[1], sql_row[2]);

				}
				else if (sub_type == 0)
				{
					continue;
				}
				else
				{
					printf("Invalid input\n");
				}
			}
			else if (query_type == 3)
			{
				printf("---- TYPE 3 ----\n\n");
				printf("** Find all products sold in the past year **\n");
				mysql_query(connection, "select product.product_ID, model_name from sales, product where year = 2021 and product.product_ID = sales.product_ID");
				sql_result = mysql_store_result(connection);
				printf("product_ID, model_name\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					printf("%s\t    %s\n", sql_row[0], sql_row[1]);
				}
				printf("------ Subtypes in TYPE 3 ------\n");
				printf("\t1. TYPE 3-1\n");
				printf("\t2. TYPE 3-2\n");
				printf("\t0. QUIT\n");
				printf("Enter Subtype: ");
				scanf("%d", &sub_type);
				printf("\n");
				if (sub_type == 1)
				{
					int k;
					printf("---- TYPE 3-1 ----\n\n");
					printf("** Then find the top k products by dollar-amount sold **\n");
					printf("which K?: ");
					scanf("%d", &k);
					sprintf(type_query, "select model_name, sum(saled_price) as total_sold from sales, product where year = 2021 and sales.product_ID = product.product_ID group by model_name order by total_sold desc limit %d", k);
					mysql_query(connection, type_query);
					sql_result = mysql_store_result(connection);
					printf("model_name, total_sold\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s\t     %s\n", sql_row[0], sql_row[1]);
					}
				}
				else if (sub_type == 2)
				{
					float k;

					printf("---- TYPE 3-2 ----\n\n");
					printf("** And then find the top 10%% products by dollar-amount sold **\n");
					mysql_query(connection, "select count(distinct model_name) from sales, product where year = 2021 and sales.product_ID = product.product_ID ");
					sql_result = mysql_store_result(connection);
					sql_row = mysql_fetch_row(sql_result);
					k = float(atoi(sql_row[0])) / 10;
					sprintf(type_query, "select model_name, sum(saled_price) as total_sold from sales, product where year = 2021 and sales.product_ID = product.product_ID group by model_name order by total_sold desc limit %d", (int)k);
					mysql_query(connection, type_query);
					sql_result = mysql_store_result(connection);
					printf("model_name, total_sold\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%s\t     %s\n", sql_row[0], sql_row[1]);
					}

				}
				else if (sub_type == 0)
				{
					continue;
				}
				else
				{
					printf("Invalid input\n");
				}
			}
			else if (query_type == 4)
			{
				printf("---- TYPE 4 ----\n\n");
				printf("** Find all products by unit sales in the past year **\n");
				mysql_query(connection, "select product.product_ID, model_name, count(model_name) as unit_sale from sales, product where year = 2021 and product.product_ID = sales.product_ID group by model_name order by unit_sale desc");
				sql_result = mysql_store_result(connection);
				printf("product_ID, model_name, unit_sale\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					printf("%6s    %10s%10s\n", sql_row[0], sql_row[1], sql_row[2]);
				}
				printf("------ Subtypes in TYPE 4 ------\n");
				printf("\t1. TYPE 4-1\n");
				printf("\t2. TYPE 4-2\n");
				printf("\t0. QUIT\n");
				printf("Enter Subtype: ");
				scanf("%d", &sub_type);
				printf("\n");
				if (sub_type == 1)
				{
					int k;
					printf("---- TYPE 4-1 ----\n\n");
					printf("**  Then find the top k products by unit sales **\n");
					printf("which K?: ");
					scanf("%d", &k);
					sprintf(type_query, "select product.product_ID, model_name, count(model_name) as unit_sale from sales, product where year = 2021 and product.product_ID = sales.product_ID group by model_name order by unit_sale desc limit %d", k);
					mysql_query(connection, type_query);
					sql_result = mysql_store_result(connection);
					printf("product_ID, model_name, unit_sale\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%6s    %10s%10s\n", sql_row[0], sql_row[1], sql_row[2]);
					}
				}
				else if (sub_type == 2)
				{
					float k;
					printf("---- TYPE 4-2 ----\n\n");
					printf("** And then find the top 10% products by unit sales **\n");
					mysql_query(connection, "select count(distinct model_name) from sales, product where year = 2021 and sales.product_ID = product.product_ID ");
					sql_result = mysql_store_result(connection);
					sql_row = mysql_fetch_row(sql_result);
					k = float(atoi(sql_row[0])) / 10;
					sprintf(type_query, "select product.product_ID, model_name, count(model_name) as unit_sale from sales, product where year = 2021 and product.product_ID = sales.product_ID group by model_name order by unit_sale desc limit %d", (int)k);
					mysql_query(connection, type_query);
					sql_result = mysql_store_result(connection);
					printf("product_ID, model_name, unit_sale\n");
					while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
					{
						printf("%6s    %10s%10s\n", sql_row[0], sql_row[1], sql_row[2]);
					}

				}
				else if (sub_type == 0)
				{
					continue;
				}
				else
				{
					printf("Invalid input\n");
				}
			}
			else if (query_type == 5)
			{
				printf("---- TYPE 5 ----\n\n");
				printf("** Find those products that are out-of-stock at every store in California **\n");
				mysql_query(connection, "select model_name from inventory where region = 'California' and stock = 0");
				sql_result = mysql_store_result(connection);
				printf("model_name\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					printf("%s\n", sql_row[0]);
				}
			}
			else if (query_type == 6)
			{
				printf("---- TYPE 6 ----\n\n");
				printf("** Find those packages that were not delivered within the promised time **\n");
				mysql_query(connection, "select product.product_ID from product, deliver where product.product_ID = deliver.product_ID and type = 'package' and (delivery_completion_date - estimated_delivery_date) > 0");
				sql_result = mysql_store_result(connection);
				printf("product_ID\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					printf("%s\n", sql_row[0]);
				}
			}
			else if (query_type == 7)
			{
				printf("---- TYPE 7 ----\n\n");
				printf("** Generate the bill for each customer for the past month **\n");
				mysql_query(connection, "select customer_ID, sum(saled_price) as monthly_bill from sales where year = 2022 and month = 5 group by customer_ID");
				sql_result = mysql_store_result(connection);
				printf("customer_ID, monthly_bill\n");
				while ((sql_row = mysql_fetch_row(sql_result)) != NULL)
				{
					printf("%s\t     %s\n", sql_row[0], sql_row[1]);
				}

			}
			else
			{
				printf("Invalid input\n");
			}
		}
		while (!feof(fp))
		{
			query = fgets(temp, 1024, fp);
			mysql_query(connection, query);
		}
		fclose(fp);
		mysql_close(connection);
	}

	return 0;
}


