select distinct
    StudentId
from
    Students
except
select distinct
    StudentId
from
    (
        select distinct
            StudentId, 
            CourseId
        from
            Students,
            (
                select distinct
                    CourseId, GroupId
                from
                    Plan,
                    Lecturers
                where
                    Lecturers.LecturerId = Plan.LecturerId
                    and LecturerName = :LecturerName
            ) X
        where Students.GroupId = X.GroupId
        except
        select distinct
            StudentId,
            CourseId
        from
            Marks
    ) Y;