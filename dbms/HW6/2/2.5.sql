select
    StudentId,
    StudentName,
    GroupName
from 
    Students, 
    Groups
where 
    Students.GroupId = Groups.GroupId 
    and Students.GroupId in
        (
            select 
                GroupId
            from 
                Plan, 
                Courses
            where
                CourseName = :CourseName 
                and Plan.CourseId = Courses.CourseId
        )
    and StudentId not in 
        (
            select 
                StudentId
            from
                Marks, 
                Courses
            where 
                CourseName = :CourseName
                and Marks.CourseId = Courses.CourseId
        );