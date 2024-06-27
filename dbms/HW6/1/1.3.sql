select
    Students.StudentId,
    Students.StudentName,
    Students.GroupId
from
    Students, Marks
where
    Students.StudentId = Marks.StudentId and CourseId = :CourseId and Mark = :Mark;