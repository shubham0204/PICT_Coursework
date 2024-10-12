-- insert in table
INSERT INTO students(name, department, age) VALUES
('hello', 'COMP', 23),
('hello2', 'IT', 24);

-- delete from table
DELETE FROM students
WHERE id = 24;

-- delete all entries
DELETE FROM students;

-- update in table
UPDATE students
SET name = 'new_name'
WHERE id = 24;