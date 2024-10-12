-- COMMIT commits the current transaction, making its changes permanent
-- ROLLBACK rolls back the current transaction, canceling its changes

-- Commit transaction
START TRANSACTION;
INSERT INTO employees (id, name, department) VALUES (1, 'Alice', 'HR');
UPDATE employees SET department = 'Finance' WHERE name = 'Bob';
COMMIT;

-- Rollback transaction
START TRANSACTION;
INSERT INTO employees (id, name, department) VALUES (3, 'David', 'Marketing');
DELETE FROM employees WHERE id = 2;
ROLLBACK;