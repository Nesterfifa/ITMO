select 
    distinct StudentId
from 
    (
        select distinct
            MarksStudentId, StudentId
        from
            (
                select distinct
                    StudentId as MarksStudentId
                from
                    Marks
            ) MarksStudents
        cross join
            (
                select distinct
                    StudentId
                from
                    Students
                    natural join Lecturers
                    natural join Plan
                where LecturerName = :LecturerName
            ) StudentsLecturers
        except
        select distinct
            MarksStudentId, StudentId
        from
            (
                select distinct
                    MarksStudentId, StudentId, CourseId
                from
                    (
                        select distinct
                            StudentId as MarksStudentId
                        from
                            Marks
                    ) MarksStudents2
                cross join
                    (
                        select distinct
                            StudentId, CourseId
                        from
                            Students
                            natural join Lecturers
                            natural join Plan
                        where LecturerName = :LecturerName
                    ) StudentsLecturers2
                except
                select distinct
                    MarksStudentId, StudentId, CourseId
                from
                    (
                        select distinct
                            StudentId as MarksStudentId, CourseId
                        from
                            Marks
                    ) MarksStudents3
                natural join
                    (
                        select distinct
                            StudentId, CourseId
                        from
                            Students
                            natural join Lecturers
                            natural join Plan
                        where LecturerName = :LecturerName
                    ) StudentsLecturers3
            ) StudentsCourses
    ) StudentsStudents
where
    MarksStudentId = StudentId