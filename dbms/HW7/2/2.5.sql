update
    Students
set
    GroupId = 
        (
            select 
                GroupId
            from
                Groups
            where
                GroupName = :GroupName
        )
where
    GroupId =
        (
            select
                GroupId
            from
                Groups
            where
                GroupName = :FromGroupName
        )
    and exists
        (
            select
                GroupId
            from
                Groups
            where
                GroupName = :GroupName
        );