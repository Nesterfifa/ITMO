select distinct
    GroupName, CourseName
from
    (
        select distinct
            CourseId, GroupId
        from
            (
                select distinct
                    CourseId
                from
                    Marks
            ) CoursesFromMarks
        cross join
            (
                select distinct
                    GroupId
                from
                    Students
            ) GroupsFromStudents
        except
        select distinct
            CourseId, GroupId
        from
            (
                select distinct
                    CourseId, GroupId, StudentId
                from
                    (
                        select distinct
                            CourseId
                        from
                            Marks
                    ) CoursesFromMarks2
                cross join
                    (
                        select distinct
                            StudentId, GroupId
                        from
                            Students
                    ) GroupsFromStudents2
                except
                select distinct
                    CourseId, GroupId, StudentId
                from
                    (
                        select distinct
                            CourseId, StudentId
                        from
                            Marks
                    ) CoursesFromMarks3
                natural join
                    (
                        select distinct
                            StudentId, GroupId
                        from
                            Students
                    ) GroupsFromStudents3
            ) X
    ) Y
    natural join Groups
    natural join Courses;