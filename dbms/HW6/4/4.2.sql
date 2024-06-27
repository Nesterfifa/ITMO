select
    StudentName,
    CourseName
from
    Students,
    Courses,
    (
        select distinct
            Students.StudentId as StudentId, Plan.CourseId as CourseId
        from
            Marks,
            Plan,
            Students
        where
            Marks.CourseId = Plan.CourseId
            and Students.StudentId = Marks.StudentId
            and Students.GroupId = Plan.GroupId
            and Mark <= 2
    ) X
where
    X.CourseId = Courses.CourseId
    and Students.StudentId = X.StudentId;