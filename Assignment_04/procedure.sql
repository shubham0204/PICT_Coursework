delimiter $$
create procedure calculate_area(in radius INT)
begin
declare r INT;
declare a FLOAT;
declare msg VARCHAR(20) ; 
declare exit handler for SQLSTATE '45000' select msg;
set msg = 'Invalid Radius';
set r = radius;
if r >= 5 and r <= 9 then
    set a = 3.14 * r *r;
    insert into area(radius,area) values(r,a);
else
    SIGNAL SQLSTATE '45000';
end if;
end
$$
delimiter ;