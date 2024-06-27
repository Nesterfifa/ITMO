select 
    StudentName,
    AvgMark
from
    Students
    left join
        (
            select
                StudentId, avg(cast(Mark as float)) as AvgMark
            from
                Marks
            group by
                StudentId
        ) X
        on Students.StudentId = X.StudentId;