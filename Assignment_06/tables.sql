create table new_emp(
	emp_id INT,
	emp_name VARCHAR(20),
	emp_dept VARCHAR(10),
	emp_salary INT,
	primary key( emp_id )
);

create table old_emp(
	emp_id INT,
	emp_name VARCHAR(20),
	emp_dept VARCHAR(10),
	emp_salary INT,
	primary key( emp_id )
);

insert into old_emp values
( 1 , 'p1' , 'Sales' , 10000 ) ,
( 2 , 'p2' , 'Dev' , 20000 ) ,
( 3 , 'p3' , 'Testing' , 50000 ) ,
( 4 , 'p4' , 'Sales' , 10000 ) ,
( 5 , 'p5' , 'Marketing' , 50000 ) ,
( 6 , 'p6' , 'Sales' , 9000 ) ,
( 7 , 'p7' , 'Accounts' , 10000 ) ,
( 8 , 'p8' , 'Sales' , 7000 ) ; 