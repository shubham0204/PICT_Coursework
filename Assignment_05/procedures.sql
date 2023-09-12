delimiter $$
create procedure proc_grade(in name varchar(20))
begin

declare n varchar(20);
declare m int;
declare category varchar(20) ;

set n = name;
select marks into m from student_marks where student_marks.name = n;

if m >= 990 and m <= 1500 then
    set category = 'distinction';
elseif m >= 989 and m < 990 then
    set category = 'first_class';
elseif m >= 825 and m <= 899 then
    set category = 'high second class';
end if;

update result set class = category where result.name = n;

end
$$
delimiter ;