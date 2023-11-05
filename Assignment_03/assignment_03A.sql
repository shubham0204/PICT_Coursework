create table employees(
	emp_id			    int			auto_increment,
	dept_id			    int						,
	emp_fname			varchar(20)				,
	emp_lname			varchar(20)				,
	emp_position		varchar(20)				,
	emp_salary			int			check( emp_salary > 0 ),
	emp_joindate		year						,
	primary key( emp_id )	,
	foreign key( dept_id ) references depts( dept_id ) on delete cascade
);

create table depts(
	dept_id			    int			auto_increment,
	dept_name			varchar(20)				,
	dept_location		varchar(20)				,
	primary key( dept_id )
);

create table projects(
	proj_id			    int			auto_increment,
	dept_id			    int						,
	proj_name			varchar(20)				,
	proj_cost			int			check( proj_cost > 0 ),
	proj_year			year						,
	primary key( proj_id ),
	foreign key( dept_id ) references depts( dept_id ) on delete cascade
);

insert into depts( dept_name , dept_location ) values
( 'Marketing' , 'Pune' ) , 
( 'Accounts' , 'Mumbai' ) , 
( 'Development' , 'Hyderabad' ) , 
( 'Legal' , 'Chennai' ) , 
( 'HR' , 'Mumbai' ) ; 

insert into employees( dept_id , emp_fname , emp_lname , emp_position , emp_salary , emp_joindate ) values
( 1 , 'p1' , 'q1' , 'Manager' , 30000 , '2009' ),
( 2 , 'p2' , 'q2' , 'Developer' , 50000 , '2010' ),
( 3 , 'p3' , 'q3' , 'HR Manager' , 20000 , '2015' ),
( 1 , 'p4' , 'q4' , 'CA' , 10000 , '2003' ),
( 2 , 'p5' , 'q5' , 'Tester' , 60000 , '2015' ),
( 4 , 'p6' , 'q6' , 'Manager' , 70000 , '2009' ),
( 4 , 'p7' , 'q7' , 'Developer' , 80000 , '2013' ),
( 3 , 'p8' , 'q8' , 'HR Manager' , 10000 , '2015' ),
( 1 , 'p9' , 'q9' , 'CA' , 10000 , '2004' ),
( 2 , 'p10' , 'q10' , 'Tester' , 60000 , '2012' ) ;

insert into projects( dept_id , proj_name , proj_cost , proj_year ) values
( 1 , 'proj1' , 10000 , 2020 ) , 
( 2 , 'proj2' , 20000 , 2015 ) , 
( 3 , 'proj3' , 50000 , 2021 ) , 
( 1 , 'proj4' , 60000 , 2014 ) , 
( 3 , 'proj5' , 90000 , 2022 ) ;

// Queries

select * from employees natural join depts;

select e.dept_id , e.emp_fname , e.emp_position , d.dept_location , e.emp_joindate from 
employees e inner join depts d on e.dept_id = d.dept_id
order by e.dept_id;

select e.* , p.proj_id , p.proj_cost , d.dept_location from
employees e inner join projects p on e.dept_id = p.dept_id
inner join depts d on p.dept_id = d.dept_id
where d.dept_location != 'Hyderabad';

select e.emp_fname , e.emp_lname , e.emp_position , d.dept_name from
employees e inner join depts d on e.dept_id = d.dept_id
where d.dept_id not in (select dept_id from projects where proj_year = '2020');

select e.emp_position , d.dept_name , p.proj_cost from
employees e inner join depts d on e.dept_id = d.dept_id
inner join projects p on d.dept_id = p.dept_id 
where p.proj_cost > 30000;

select proj_name from projects where proj_year = '2015';

select d.dept_id , d.dept_name , count( e.dept_id ) as dept_count from
employees e right join depts d on e.dept_id = d.dept_id
group by e.dept_id
having dept_count = 3;

select count( * ) from
employees e inner join projects p on e.dept_id = p.dept_id
where e.emp_joindate < '2009';

// Views - Insertion, Updation and Deletion

create view emp_dept_details as
select * from employees e natural join depts d;

create view proj_details as 
select proj_name , proj_year from projects;

insert into proj_details values( 'proj8' , '2010' );

update proj_details
set proj_year = '2023'
where proj_name = 'proj1';

delete from proj_details
where proj_name = 'proj8';

drop view proj_details;



