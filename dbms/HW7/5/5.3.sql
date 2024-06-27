create view Debts(StudentId, Debts) as
select
    StudentId,
    count(distinct CourseId) as Debts
from
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
group by
    StudentId;