delimiter $$
create procedure add_employee( in employee_id int )
begin

declare empid_2 int;
declare exit_loop boolean;

declare cursor c1 for select eid from old_employees where eid > employee_id;
declare continue handler for not found set exit_loop = true;

open c1;
emp_loop: loop
fetch c1 into empid_2;
if not exists (select * from new_employees where eid = empid_2) then
insert into new_employees select * from old_employees where eid = empid_2;
end if;

if exit_loop then
close c1;
leave emp_loop;
end if;
end loop emp_loop;

end 
$$
delimiter ;