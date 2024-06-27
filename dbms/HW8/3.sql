-- Средний балл по предмету :CourseName
select
    avg(cast(Mark as float)) as AvgMark
from
    Marks
where
    CourseId in
        (
            select
                CourseId
            from
                Courses
            where
                CourseName = :CourseName
        );
        
create index IndexCourseIdMark on Mark using btree (CourseId, Mark);

-- ФИО преподавателя, который вел предмет :CourseName в группе :GroupName
select
    LecturerName
from
    Lecturers
where
    LecturerId in
        (
            select
                LecturerId
            from
                Plan
            where
                GroupId in
                    (
                        select
                            GroupId
                        from
                            Groups
                        where
                            GroupName = :GroupName
                    )
                and CourseId in
                    (
                        select
                            CourseId
                        from
                            Courses
                        where
                            CourseName = :CourseName
                    )
        )
        
create unique index IndexCourseIdGroupId on Plan using hash (CourseId, GroupId);

-- Найти студента по ФИО и названию группы
select
    StudentId,
    StudentName,
    GroupId
from
    Students
where
    GroupId in
        (
            select  
                GroupId
            from
                Groups
            where
                GroupName = :GroupName
        )
    and 
        StudentName = :StudentName;

create index IndexGroupIdStudentName on Students using btree (GroupId, StudentName);



