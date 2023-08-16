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