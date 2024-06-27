-- PostgreSQL 15.4

create or replace function processSameMarks() returns trigger
as $SameMarks$
begin
    if exists
        (
            select
                *
            from
                Students S1
            where
                exists
                    (
                        select
                            *
                        from
                            Students S2
                        where
                            S1.GroupId = S2.GroupId
                            and exists
                                (
                                    select
                                        *
                                    from
                                        Marks M1
                                    where
                                        CourseId in
                                            (
                                                select 
                                                    CourseId
                                                from
                                                    Marks M2
                                                where
                                                    M2.StudentId = S1.StudentId
                                            )
                                        and CourseId not in
                                            (
                                                select 
                                                    CourseId
                                                from
                                                    Marks M3
                                                where
                                                    M3.StudentId = S2.StudentId
                                            )
                                )
                    )
        ) 
    then
        raise exception 'SameMarks constraint failed on mark $', mark;
    end if;
    return null;
end;
$SameMarks$ language plpgsql;

create or replace trigger SameMarksMarks
after insert or update or delete
on Marks
for each row
execute procedure processSameMarks();

create or replace trigger SameMarksStudents
after insert or update
on Students
for each row
execute procedure processSameMarks();