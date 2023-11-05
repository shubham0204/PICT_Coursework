delimiter $$
create procedure copy_emp_data()
begin
	declare curr_emp_id INT;
	declare exit_loop BOOLEAN default 0;
	declare c CURSOR for select old_emp.emp_id from old_emp ; 
	declare continue handler for not found set exit_loop = 1;

	open c;
	fetch_loop: loop

	fetch c into curr_emp_id;
	if not exists (select new_emp.emp_id from new_emp where new_emp.emp_id = curr_emp_id ) then
		insert into new_emp select * from old_emp where old_emp.emp_id = curr_emp_id;
		select curr_emp_id;
	end if;
	if exit_loop then
		close c;
		leave fetch_loop;
	end if;
	end loop fetch_loop;
end
$$
delimiter ;
