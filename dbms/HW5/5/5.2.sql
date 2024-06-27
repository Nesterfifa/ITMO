select
    StudentName, CourseName
from 
    (
        select
            distinct StudentId, CourseId
        from
            (
                select 
                    StudentId, StudentName, GroupId, CourseId, LecturerId, CourseName
                from 
                    Students
                    natural join Plan
                    natural join Courses
                except
                select 
                    StudentId, StudentName, GroupId, CourseId, LecturerId, CourseName
                from 
                    Students
                    natural join Plan
                    natural join Courses
                    natural join Marks
            ) X
    ) Y
    natural join Students
    natural join Courses;
    