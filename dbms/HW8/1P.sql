-- ДЗ-5.5.1 ФИО студента и названия предметов которые у него есть 
-- по плану
-- ДЗ-5.5.2 ФИО студента и названия предметов которые у него есть 
-- без оценки
-- ДЗ-5.5.3 ФИО студента и названия предметов которые у него есть, 
-- но не 4 или 5
-- Упорядоченный индекс для таблицы связи
create unique index IndexGroupIdCourseId on Plan using btree (GroupId, CourseId);

-- ДЗ-5.5.1 ФИО студента и названия предметов которые у него есть 
-- по плану
-- ДЗ-5.5.2 ФИО студента и названия предметов которые у него есть 
-- без оценки
-- ДЗ-5.5.3 ФИО студента и названия предметов которые у него есть, 
-- но не 4 или 5
-- Упорядоченный индекс для таблицы связи
create unique index IndexCourseIdGroupId on Plan using btree (CourseId, GroupId);

-- ДЗ-5.3.3 Информация о студентах с :Mark по предмету, 
-- который у них был по :LecturerId
-- ДЗ-5.3.4 Информация о студентах с :Mark по предмету, 
-- который у них был по :LecturerName
-- ДЗ-5.3.6 Информация о студентах с :Mark по предмету 
-- :LecturerName
-- Покрывающий индекс для быстрого поиска по преподавателю и курсу
create unique index IndexCourseIdLecturerIdGroupId on Plan using btree (CourseId, LecturerId, GroupId);

-- ДЗ-5.3.3 Информация о студентах с :Mark по предмету, 
-- который у них был по :LecturerId
-- ДЗ-5.3.4 Информация о студентах с :Mark по предмету, 
-- который у них был по :LecturerName
-- ДЗ-5.3.6 Информация о студентах с :Mark по предмету 
-- :LecturerName
-- Покрывающий индекс для быстрого поиска по преподавателю и курсу
create unique index IndexLecturerIdCourseIdGroupId on Plan using btree (LecturerId, CourseId, GroupId);
