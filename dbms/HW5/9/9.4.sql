select
    GroupName,
    AvgAvgMark
from
    Groups
    left join
        (
            select
                GroupId, avg(cast(AvgMark as float)) as AvgAvgMark
            from
                (
                    select
                        StudentId, avg(cast(Mark as float)) as AvgMark
                    from
                        Students
                        natural join Marks
                    group by 
                        StudentId
                ) Y
                natural join Students
            group by
                GroupId
        ) X
        on Groups.GroupId = X.GroupId;