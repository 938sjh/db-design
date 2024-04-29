1. x64로 debug 한다.
2. 1번 X 입력시 1234567 혹은 1234568로 입력 (delivery_completion_date가 NULL), 즉 배송이
아직 되지 않은 것은 두 tuple만 만들어 놓음
3. 실행 중 잘못 입력하여 에러가 났을 경우 다시 실행하여 0번을 눌러 table을 모두 drop한 후 
다시 실행한다.
4. db명을 project로 하였다.
