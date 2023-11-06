create table stud_marks(
	rollno			int				auto_increment,
	name			varchar(20)		not null,
	total_marks		int				not null			check( total_marks > 0 ),
	primary key( rollno )
) ;

create table results(
	rollno			int,
	name			varchar(20)		not null,
	class 			varchar(20)		not null,
	foreign key( rollno ) references stud_marks( rollno ) on delete cascade
) ;

insert into stud_marks( name , total_marks ) values 
( 'p1' , 1000 ) , 
( 'p2' , 945 ) , 
( 'p3' , 830 ) , 
( 'p4' , 960 ) , 
( 'p5' , 1200 ) ; 

delimiter $$
create or replace procedure grade( in rollno INT , out category VARCHAR(20) )
begin
	declare marks INT ; 
	declare name VARCHAR(20) ;

	select stud_marks.name , stud_marks.total_marks 
	into name , marks from stud_marks 
	where stud_marks.rollno = rollno;

	if marks >= 990 and marks <= 1500 then
		set category = 'Distinction';
	elseif marks >= 900 and marks <= 989 then
		set category = 'First Class';
	elseif marks >= 825 and marks <= 899 then
		set category = 'Higher Second Class';
     end if;

	insert into results values( rollno , name , category ) ;
end
$$
delimiter ;