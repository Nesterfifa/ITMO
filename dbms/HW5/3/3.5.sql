select Students.StudentId as StudentId, StudentName, Students.GroupId as GroupId
from Plan natural join Marks 
left join Students on Students.StudentId = Marks.StudentId
where Mark = :Mark and LecturerId = :LecturerId and Students.StudentId is not null;