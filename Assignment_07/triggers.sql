create trigger audit_deleted_trigger 
before delete on library 
for each row 
insert into audit values(old.id, old.name, old.price);

create trigger audit_updated_trigger 
before update on library 
for each row 
insert into audit values(old.id, old.name, old.price);