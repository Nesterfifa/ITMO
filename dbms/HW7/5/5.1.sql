create view StudentMarks(StudentId, Marks) as
select
    Students.StudentId,
    count(CourseId) as Marks
from
    Students
    left join Marks
on
    Students.StudentId = Marks.StudentId
group by
    Students.StudentId;