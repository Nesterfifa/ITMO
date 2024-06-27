select
    avg(cast(Mark as float)) as AvgMark
from
    Groups
    natural join Students
    natural join Marks
    natural join Courses
where
    GroupName = :GroupName
    and CourseName = :CourseName;

-- Упорядоченный индекс для таблицы связи
create unique index IndexGroupNameGroupId on Groups using btree (GroupName, GroupId);

-- Упорядоченный индекс для таблицы связи
create unique index IndexCourseNameCourseId on Courses using btree (CourseName, CourseId);

-- Индекс позволит упорядоченно искать данные об оценках студентов по курсу
create unique index IndexCourseIdStudentIdMark on Marks using btree (CourseId, StudentId, Mark);

-- Индекс по внешнему ключу
create index IndexStudentId on Students using hash (GroupId);