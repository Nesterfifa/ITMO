select
    Students.StudentId as StudentId,
    coalesce(Total, 0) as Total,
    coalesce(Passed, 0) as Passed,
    coalesce(Total, 0) - coalesce(Passed, 0) as Failed
from
    Students
    left join
        (
            select 
                GroupId, 
                count(distinct CourseId) as Total
            from
                Students
                natural join Plan
            group by 
                GroupId
        ) X
        on X.GroupId = Students.GroupId
    left join
        (
            select
                StudentId,
                count(distinct CourseId) as Passed
            from
                Students
                natural join Plan
                natural join Marks
            group by
                StudentId
        ) Y
        on Students.StudentId = Y.StudentId;