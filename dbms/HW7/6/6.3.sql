-- PostgreSQL 15.4

create or replace function processPreserveMarks() returns trigger
as $preserveMarks$
begin
    if 
        new.Mark < old.Mark
    then
        return old;
    else
        return new;
    end if;
end;
$preserveMarks$ language plpgsql;

create trigger PreserveMarks
before update
on Marks
for each row
execute procedure processPreserveMarks();   
