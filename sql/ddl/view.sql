-- Create views
CREATE VIEW comp_students AS
SELECT * FROM students
WHERE department = 'CE';

-- Display views
SELECT * FROM comp_students;
SELECT * FROM pune_placement_drives;

-- Update view
ALTER VIEW comp_students
AS
SELECT * FROM students
WHERE department = 'CE' and cgpa > 8;

-- Delete view
DROP VIEW comp_students;