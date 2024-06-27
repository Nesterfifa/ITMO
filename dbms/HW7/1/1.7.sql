delete from
    Students
where
    StudentId in
        (
            select
                StudentId
            from
                (
                    select distinct
                        StudentId, CourseId
                    from
                        Students
                        natural join Plan
                    except
                    select distinct
                        StudentId, CourseId
                    from
                        Marks
                ) X
            group by
                StudentId
            having
                count(StudentId) >= 2
        );