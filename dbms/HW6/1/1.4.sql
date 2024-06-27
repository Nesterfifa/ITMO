select
    Students.StudentId,
    Students.StudentName,
    Students.GroupId
from
    Students, Marks, Courses
where
    Students.StudentId = Marks.StudentId 
    and Courses.CourseId = Marks.CourseId 
    and CourseName = :CourseName 
    and Mark = :Mark;