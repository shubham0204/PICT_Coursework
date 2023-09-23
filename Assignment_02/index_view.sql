-- Simple index
create index index_students_name
on students(name) ; 

-- Composite index
create index index_training_company_nane
on training(company_name,training_year);

-- Unique index
create unique index index_placement_drive_package
on placement_drives(package);

-- Text-search index
create index index_text_students_name
on students(name(10))

-- Create views
create view comp_students as
select * from students
where branch = 'CE';

create view pune_placement_drives as
select * from placement_drives
where location = 'pune';

-- Display views
select * from comp_students;

select * from pune_placement_drives;
