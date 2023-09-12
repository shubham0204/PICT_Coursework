create table old_employees(
    eid INT AUTO_INCREMENT PRIMARY KEY,
    ename VARCHAR(20),
    salary INT
) ; 
insert into old_employees( ename , salary ) values
( 'Shubham' ,1200) , 
( 'Kaustubh' , 4561 ) , 
( 'Ayush' , 1230 ) , 
( 'Swaraj' , 9990 ) , 
( 'Advait' , 78890 ) ;

create table new_employees(
    eid INT AUTO_INCREMENT PRIMARY KEY,
    ename VARCHAR(20),
    salary INT
) ; 