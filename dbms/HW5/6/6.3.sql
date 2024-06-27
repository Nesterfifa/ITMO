select
    StudentId
from 
    Marks
except
select 
    StudentId
from
    (
        select distinct
            StudentId, CourseId
        from
            (
                select 
                    StudentId
                from
                    Marks
            ) X
        cross join
            (
                select
                    CourseId
                from
                    Plan
                    natural join Lecturers
                where LecturerName = :LecturerName
            ) Y
        except
        select
            StudentId, CourseId
        from
            Marks
    ) Z;
