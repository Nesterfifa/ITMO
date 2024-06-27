delete from
    Students
where
    StudentId in
        (
            select distinct
                StudentId
            from
                (
                    select
                        StudentId,
                        count (CourseId) as MarksCount
                    from
                        Marks
                    group by StudentId
                ) X
            where MarksCount >= 3
        );