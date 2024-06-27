create view AllMarks(StudentId, Marks) as
select
    Students.StudentId,
    count(CourseId) as Marks
from
    Students
    left join 
        (
            select
                StudentId, CourseId, Mark
            from
                Marks
            union all
            select
                StudentId, CourseId, Mark
            from
                NewMarks
        ) X
        on 
            Students.StudentId = X.StudentId
group by
    Students.StudentId;