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
