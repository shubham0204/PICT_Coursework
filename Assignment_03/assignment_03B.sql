/* 
Create tables

Assignment No 2A  (Student Schema)
Consider the following relational Schema.  
 Student( s_id,Drive_id,T_id,s_name,CGPA,s_branch,S_dob)
 PlacementDrive( Drive_id,Pcompany_name,package,location)
 Training ( T_id,Tcompany_name,T_Fee,T_year) 
Note: Use referential integrity constraints while creating tables with on delete cascade options. 
 Create view(simple), index, sequence and synonym based on above tables.  
*/

create table placement_drives(
	id int auto_increment primary key,
	company_name varchar(255),
	package int,
	location varchar(255)
);

create table training(
	id int auto_increment primary key,
	company_name varchar(255),
	fee int,
	training_year year
) ; 

create table students(
	id int auto_increment primary key,
	drive_id int,
	training_id int,
	name varchar(255),
	cgpa float,
	branch varchar(255)	,
	foreign key( drive_id ) references placement_drives(id) on delete cascade,
	foreign key( training_id ) references training(id) on delete cascade
) ;

/*
Referencial Integrity Constraints
(Optional)

alter table students
add constraint student_drive
foreign key(drive_id) references placement_drives(id);

alter table students
add constraint student_training
foreign key(training_id) references training(id);
*/

insert into placement_drives(company_name,package,location)
values
( 'imocha' , 20 , 'pune' ) ,
( 'barclays' , 6 , 'pune' ) , 
( 'tracelink' , 50 , 'mumbai' ) , 
( 'mastercard' , 40 , 'bengaluru' ) , 
( 'google' , 30 , 'mumbai' ) ;

insert into training(company_name,fee,training_year)
values
( 'imocha' , 2000 , '2020' ) ,
( 'barclays' , 500 , '2022' ) , 
( 'tracelink' , 350 , '2021' ) , 
( 'mastercard' , 230 , '2019' ) , 
( 'google' , 5000 , '2019' ) ;

insert into students( drive_id , training_id , name , cgpa , branch )
values
( 1 , 2 , 'Shubham Panchal' , 8.7 , 'CE' ),
( 1 , 3 , 'Advait Naik' , 6.2 , 'CE' ),
( 3 , 2 , 'Kaustubh Netke' , 9.0 , 'CE' ),
( 2 , 2 , 'Anish Pawar' , 8.1 , 'IT' ),
( 1 , 4 , 'Manthan Adhav' , 8.1 , 'IT' ),
( 4 , 1 , 'Advait Nagarkar' , 8.0 , 'IT' ),
( 3 , 3 , 'Rana Vanikar' , 6.8 , 'ENTC' ),
( 2 , 5 , 'Suma Meghana' , 7.8 , 'ENTC' ),
( 5 , 5 , 'Chinmay Patil' , 7.9 , 'CE' ),
( 4 , 4 , 'Anushka Joshi' , 7.6 , 'CE' );

-- Queries

-- 1. Find the Student details and Placement details using NATURAL JOIN.  
select * from
students natural join placement_drives;

-- 2. Find all the student details with company_name who have conducted in same drive
select s.*, pd.company_name from 
students s inner join placement_drives pd on s.drive_id = pd.id;

-- 3. List all the Student name and Student branch of Student having package 5 LPA
select s.name,s.branch from
students s inner join placement_drives pd on s.drive_id = pd.id
where pd.package = 5;

-- 4.List all the student names ,company_name having T_fee more than 20000
select s.name,t.company_name from
students s inner join training t on s.training_id = t.id
where t.fee > 500;

-- 5. Display all training details attended by “shantanu” in year 2011  
select t.* from
students s inner join training t on s.training_id = t.id
where s.name = 'Chinmay Patil' && t.training_year = '2019'; 

-- 6. list the total number of companies who conduct training before 2015
select count(company_name) from training
where training.training_year < 2019;

-- 7. List the students name with company ‘Microsoft’ and  location ’Thane’
select s.* from
students s inner join placement_drives pd on s.drive_id = pd.id
where pd.location in( 'Mumbai' , 'Pune' ) ;

-- 8. Find the names of all Students who have joined ‘Microsoft ‘ training  in 2015 .
select s.name from 
students s inner join training t on s.training_id = t.id
where t.company_name = 'google' ;

-- 9. Create a view showing the Student and Training details.  
create view student_training_view as 
select s.*, t.company_name, t.fee, t.training_year from students s inner join training t on
s.training_id = t.id;

-- 10. Perform Manipulation on simple view-Insert, update, delete, drop view.  
-- 10.a. Insert in view
insert into student_training_view(drive_id, training_id, name, cgpa, branch ) 
values( 2 , 2 , 'Advait Naik' , 8.5 , 'CE' ) ; 
insert into student_training_view( company_name, fee, training_year ) 
values( 'bny mellon' , 20 , '2019' ) ;