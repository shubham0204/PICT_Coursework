-- create database
CREATE DATABASE development;

-- drop database
DROP DATABASE development;

-- create table
-- add primary key (entity integrity)
-- add foreign key (referential integrity)
-- add NOT NULL, UNIQUE (domain integrity)
-- add CHECK (business constraints)
CREATE TABLE IF NOT EXISTS students(
    id                  INT             AUTO_INCREMENT,
    name                VARCHAR(20)     UNIQUE,
    department          VARCHAR(10)     NOT NULL,
    age                 INT             CHECK (age > 0),
    PRIMARY KEY(id)                                    ,
    FOREIGN KEY(department) REFERENCES departments.name
);

-- rename table
RENAME TABLE students to new_students;

-- drop table
DROP TABLE students;

-- add column to table
ALTER TABLE students
ADD department VARCHAR(10);

-- rename column in table
ALTER TABLE students
RENAME COLUMN name TO first_name;

-- change column data-type in table
ALTER TABLE students
MODIFY name VARCHAR(50);

-- drop column from table
ALTER TABLE students
DROP COLUMN name;

-- add primary key
ALTER TABLE students
ADD PRIMARY KEY(id);

-- add foreign key
ALTER TABLE students
ADD FOREIGN KEY(department) REFERENCES departments.name;