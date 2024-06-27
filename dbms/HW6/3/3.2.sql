select
    StudentName,
    CourseName
from
    Students,
    Courses,
    (
        select
            StudentId,
            CourseId
        from
            Students,
            Plan
        where Students.GroupId = Plan.GroupId
        union
        select 
            StudentId,
            CourseId
        from
            Marks
    ) X
where
    Students.StudentId = X.StudentId
    and Courses.Courseid = X.CourseId;