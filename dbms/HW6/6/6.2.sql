select
    GroupName, CourseName
from
    Groups,
    Courses,
    (
        select distinct
            GroupId, CourseId
        from
            Courses,
            Groups
        except
        select distinct
            GroupId, CourseId
        from
            (
                select distinct
                    StudentId, GroupId, CourseId
                from
                    Students,
                    Courses
                except
                select distinct
                            Students.StudentId, GroupId, CourseId
                        from
                            Marks,
                            Students
                        where Marks.StudentId = Students.StudentId
            ) X
    ) Y
where
    Groups.GroupId = Y.GroupId
    and Courses.CourseId = Y.CourseId;