select Students.StudentId as StudentId, Students.StudentName as StudentName, Students.GroupId as GroupId
from Students
except
select Students.StudentId as StudentId, Students.StudentName as StudentName, Students.GroupId as GroupId
from Students natural join Courses natural join Marks
where CourseName = :CourseName;