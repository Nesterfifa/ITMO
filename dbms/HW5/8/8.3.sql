select
    GroupName,
    SumMark
from
    Groups
    left join
        (
            select
                GroupId, sum(Mark) as SumMark
            from
                Students
                natural join Marks
            group by GroupId
        ) X
        on Groups.GroupId = X.GroupId;