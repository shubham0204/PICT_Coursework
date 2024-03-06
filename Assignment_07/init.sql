create database inventory;
use inventory;
create table items( 
    id int auto_increment primary key, 
    name varchar(30), 
    quantity int, 
    price int
);
insert into items( name , quantity , price ) values( 'milk' , 2 , 30 );