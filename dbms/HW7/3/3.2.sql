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
                Marks.StudentId = Students.StudentId
        )
where
    1 = 1;