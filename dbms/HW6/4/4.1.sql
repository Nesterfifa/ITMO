select
    StudentName,
    CourseName
from
    Students,
    Courses,
    (
        select distinct
            StudentId, CourseId
        from
            Students,
            Plan
        where
            Students.GroupId = Plan.GroupId
        except
        select distinct
            StudentId, CourseId
        from
            Marks
    ) X
where
    X.CourseId = Courses.CourseId
    and Students.StudentId = X.StudentId;