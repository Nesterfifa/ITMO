update
    Students
set
    Debts =
        (
            select
                count(distinct CourseId)
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
            where
                X.StudentId = Students.StudentId
        )
where
    GroupId = 
        (
            select 
                GroupId
            from
                Groups
            where
                GroupName = :GroupName
        );