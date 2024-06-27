select Students.StudentId as StudentId, StudentName, Students.GroupId as GroupId
from Plan natural join Marks natural join Lecturers
left join Students on Students.StudentId = Marks.StudentId
where Mark = :Mark and LecturerName = :LecturerName and Students.StudentId is not null;