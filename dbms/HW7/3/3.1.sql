update
    Students
set
    Marks =
        (
            select
                count(CourseId)
            from
                Marks
            where
                StudentId = :StudentId
        )
where
    1 = 1;