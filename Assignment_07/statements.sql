create table books(
	id		int			auto_increment		                ,
	name	varchar(20)	not null	    unique	            ,
	price	int			not null	    check( price > 0 )  ,
	primary key( id )
);

create table audit(
	id 		int			not null,
	name    varchar(20)	not null,
	price	int			not null,
    ts      datetime    default     current_timestamp()
);

insert into books( name , price ) values
( 'DBMS' , 1000 ) , 
( 'SPOS' , 6000 ) , 
( 'CN' , 5000 ) , 
( 'DS' , 2000 ) , 
( 'TOC' , 3000 ) ;


create trigger trigger_book_update
before update on books
for each row
insert into audit values( old.id , old.name , old.price , current_timestamp() );

create trigger trigger_book_delete
before delete on books
for each row
insert into audit( id , name , price) values( old.id , old.name , old.price );

update books
set price = 100
where name = 'CN';

delete from books
where name = 'TOC';
	
