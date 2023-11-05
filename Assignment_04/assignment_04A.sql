create table borrowers(
	roll_no INT,
	name VARCHAR(20),
	issue_date DATE,
	book_name VARCHAR(20),
	status CHAR(10),
	primary key( roll_no )
);

create table fines(
	roll_no INT,
	fine_date DATE,
	amt INT,
	foreign key( roll_no ) references borrowers( roll_no )
);

insert into borrowers values
( 1 , 'p1' , '2023-10-31' , 'b1' , 'I' ) , 
( 2 , 'p2' , '2023-10-17' , 'b2' , 'I' ) , 
( 3 , 'p2' , '2023-10-18' , 'b3' , 'I' ) , 
( 4 , 'p2' , '2023-10-16' , 'b1' , 'I' ) , 
( 5 , 'p2' , '2023-10-01' , 'b2' , 'I' ) , 
( 6 , 'p2' , '2023-10-10' , 'b3' , 'I' ) ; 


delimiter $$
create procedure calc_fine(in roll_no INT)
begin
declare days INT;
declare fine INT;
declare error INT;
declare issue_date DATE;

select borrowers.issue_date into issue_date from borrowers where borrowers.roll_no = roll_no;

set days = DATEDIFF( CURDATE() , issue_date );
if days <= 30 and days >= 15 then
	set fine = 5 * days;
else 
	set fine = 50 * days;
end if;

begin
declare exit handler for 1452 set error = 1;
insert into fines values( roll_no , CURDATE() , fine ) ; 
end;
if error = 1 then
	select 'Invalid Roll No';
else
	select 'Fine amount inserted in table';
end if;

end
$$
delimiter ;


