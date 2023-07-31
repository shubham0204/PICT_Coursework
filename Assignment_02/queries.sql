-- Queries

-- 2. Display all students details with branch ‘Computer ‘and ‘It’ and student name
-- starting with  'a' or 'd'.  
select * from students
where (branch = 'CE' || branch = 'IT') && (name like 'A%' || name like 'D%');

-- 3. list the number of different companies.(use of distinct)  
select distinct company_name from training;

-- 4. Give 15% increase in fee of the Training  whose joining year is 2019.
select company_name, fee * 1.15, training_year from training
where training_year = '2019';

-- 5. Delete Student details having CGPA score less than 7.
delete from students
where cgpa < 7.0;

-- 6. Find the names of companies belonging to pune or Mumbai  
select company_name,location from placement_drives
where location in( 'mumbai' , 'pune' );

-- 7. Find the student name who joined training in  1-1-2019 as well as in 1-1-2021  
select s.name from
students s join training t on s.training_id = t.id
where t.training_year in( '2021' , '2019' );

-- 8. Find the student name  having maximum CGPA score and names of students 
-- having CGPA score between  7 to 9 .
select max(cgpa) from students
where cgpa between 7.0 and 9.0;

-- 9. Display all Student  name with T_id  with decreasing order of Fees
select t.id, t.fee, s.name from students s, training t
order by t.fee desc;

-- 10. Display Company name, S_name ,location and Package with Package  30K, 40K and 50k 
select pd.company_name , s.name , pd.location , pd.package from
placement_drives pd, students
where pd.package in( 30 , 40 , 50 );