create table areas(
	radius		float		not null		unique,
	area			float		not null
);

delimiter $$
create procedure compute_area( in radius FLOAT )
begin
	declare area FLOAT default 0.0;
	declare exit handler for sqlstate '45000' select 'Invalid Radius';
	declare exit handler for 1062 select 'Entry exists in table';

	if radius >= 5.0 and radius <= 9.0 then
		set area = radius * radius * 3.14;
		insert into areas values( radius , area );
	else
		signal sqlstate '45000';
	end if;
end
$$
delimiter ;