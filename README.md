<h2>mySQL vendor company RDBMS design project</h2>

<h3>ER Model을 설계한 뒤 BCNF로 정규화</h3>

<h3>Requirements</h3>

+ Some customers have a contract with the company and bill their purchases to an account number.
+ They are billed monthly. Other customers are infrequent customers and pay with a credit or debit card. Card information may be stored for online customers, but not for in-store customers.
+ Online sales must be sent to a shipper. The company needs to store the tracking number for the shipping company so it can respond to customer inquiries.
+ Inventory must be accurate both in stores and in warehouses used to replenish stores and to ship to online customers.
+ When inventory is low, a reorder should be sent to the manufacturer and listed in the database. When goods arrive, inventory should be updated and reorders marked as having been filled.
+ Sales data are important for corporate planning. Marketers may want to look at sales data by time period, product, product grouping, season, region (for stores), etc.

- Project Requirements 

1. E-R Model
+ Construct an E-R diagram representing the conceptual design of the database.
+ At minimum you must include all the entity and relationship sets implied by this description. You may go beyond the minimum. Remember that the manager who defined the specifications is not computer literate so the specifications should not be viewed as necessarily being precise and complete.
+ Be sure to identify primary keys, relationship cardinalities, etc.

2. Relational Schema Diagram
 
+ After creating an E-R model, reducing it into Schema diagram
+ Create the schema diagram in ERwin Data Modeler we discussed in practice session.
+ Be sure to allow us to store information without unnecessary redundancy.
+ Be sure to identify primary keys, foreign keys, relationship cardinalities, relationship type, allowing nulls and so far.
+ Every entities should have name and primary key(s).
  
3. Queries
   
The queries listed below are those that your client (the manager from the package delivery company) wants turned in. 

They may provide further hints about database design, so think about them at the outset of the project.

+ AssumethepackageshippedbyUSPSwithtrackingnumber123456isreported to have been destroyed in an accident. Find the contact information for the customer. Also, find the contents of that shipment and create a new shipment of replacement items.
+ Find the customer who has bought the most (by price) in the past year. • Find the top 2 products by dollar-amount sold in the past year.
+ Find the top 2 products by unit sales in the past year.
+ Find those products that are out-of-stock at every store in California. • Find those packages that were not delivered within the promised time. • Generate the bill for each customer for the past month.
