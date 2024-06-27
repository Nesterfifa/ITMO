-- PostgreSQL 15.4

create or replace function processNoExtraMarks() returns trigger
as $NoExtraMarks$
begin
    if
        exists
            (
                select 
                    *
                from
                    Marks
                where
                    not exists
                        (
                            select
                                *
                            from
                                Students
                                natural join Plan
                            where 
                                Marks.StudentId = Students.StudentId
                                and Marks.CourseId = Plan.CourseId
                        )
            )
    then
        raise exception 'NoExtraMarks constraint failed';
    end if;
    return null;
end;
$NoExtraMarks$ language plpgsql;

create or replace trigger NoExtraMarksMarks
after update or insert
on Marks
for each row
execute procedure processNoExtraMarks();

create or replace trigger NoExtraMarksPlan
after update or delete
on Plan
for each row
execute procedure processNoExtraMarks();

create or replace trigger NoExtraMarksStudents
after update or delete
on Students
for each row
execute procedure processNoExtraMarks();
