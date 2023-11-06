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

delimiter $$
create procedure copy_emp_data()
begin
	declare curr_emp_id INT;
	declare exit_loop BOOLEAN default 0;
	declare c CURSOR for select old_emp.emp_id from old_emp ; 
	declare continue handler for not found set exit_loop = 1;

	open c;
	fetch_loop: loop

	fetch c into curr_emp_id;
	if not exists (select new_emp.emp_id from new_emp where new_emp.emp_id = curr_emp_id ) then
		insert into new_emp select * from old_emp where old_emp.emp_id = curr_emp_id;
		select curr_emp_id;
	end if;
	if exit_loop then
		close c;
		leave fetch_loop;
	end if;
	end loop fetch_loop;
end
$$
delimiter ;