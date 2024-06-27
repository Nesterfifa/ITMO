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
                    CourseId
                from
                    Plan,
                    Lecturers
                where
                    Lecturers.LecturerId = Plan.LecturerId
                    and LecturerName = :LecturerName
            ) X
        except
        select distinct
            StudentId,
            CourseId
        from
            Marks
    ) Y;