create view StudentDebts(StudentId, Debts) as
select
    Students.StudentId,
    count(CourseId) as Debts
from
    Students
    left join
        (
            select distinct
                StudentId, CourseId
            from
                Students
                natural join Plan
            except
            select distinct
                StudentId, CourseId
            from
                Marks
        ) X
        on
            X.StudentId = Students.StudentId
group by
    Students.StudentId;