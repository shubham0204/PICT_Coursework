-- Simple index
CREATE index index_students_name
ON students(name) ; 

-- Composite index
CREATE index index_training_company_nane
ON training(company_name,training_year);

-- Unique index
CREATE unique index index_placement_drive_package
ON placement_drives(package);

-- Text-search index
CREATE index index_text_students_name
ON students(name(10))

-- Drop index
DROP INDEX index_text_students_name ON students;