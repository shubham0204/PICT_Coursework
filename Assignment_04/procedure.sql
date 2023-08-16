delimiter $$
create procedure calculate_area(in radius INT)
begin
declare r INT;
declare a FLOAT;
set r = radius;
if r >= 5 and r <= 9 then
    set a = 3.14 * r *r;
    insert into area(radius,area) values(r,a);
end
$$
delimiter ;