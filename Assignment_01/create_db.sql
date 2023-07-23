/* 
Create tables for teams, judge_allocation, judges, escorts and participants
*/

create table teams(
    id int auto_increment primary key,
    name varchar(255),
    abstract text,
    domain varchar(255),
    project_type varchar(255)
);

create table judge_allocation(
    id int auto_increment primary key,
    judge_id int,
    team_id int
);

create table judges(
    id int auto_increment primary key,
    name varchar(255),
    domain varchar(255),
    contact_number char(10)
);

create table escorts(
    id int auto_increment primary key,
    name varchar(255),
    contact_number char(10),
    judge_id int
);

create table participants(
    id int auto_increment primary key,
    name varchar(255),
    team_id int,
    contact_number char(10)
);

/*
Add referential integrity constraints to the tables
*/

alter table participants
add constraint participant_team 
foreign key(team_id) references teams(id);

alter table judge_allocation
add constraint judge_allocation_judge
foreign key(judge_id) references judges(id);

alter table judge_allocation
add constraint judge_allocation_team
foreign key(team_id) references teams(id);

alter table escorts
add constraint escort_judge 
foreign key(id) references judges(id);

