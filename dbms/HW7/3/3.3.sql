update
    Students
set
    Marks = Marks +
        (
            select
                count(CourseId)
            from
                NewMarks
            where
                NewMarks.StudentId = Students.StudentId
        )
where
    1 = 1;