select
    GroupName,
    AvgMark
from
    Groups
    left join
        (
            select
                GroupId, avg(cast(Mark as float)) as AvgMark
            from
                Students
                natural join Marks
            group by GroupId
        ) X
        on Groups.GroupId = X.GroupId;