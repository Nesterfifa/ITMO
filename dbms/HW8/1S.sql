-- ДЗ-5.1.1. Информация о студентах по :StudentId
-- ДЗ-5.2.1. Полная информация о студентах по :StudentId
-- ДЗ-7.2.1. Изменение имени студента
-- Хеш-индекс на primary key
create unique index IndexStudentId on Students using hash (StudentId);

-- ДЗ-5.2.1. Полная информация о студентах по :StudentId
-- ДЗ-5.2.2. Полная информация о студентах по :StudentName
-- ДЗ-5.3.3. Информация о студентах с :Mark по предмету :LecturerId
-- Хеш-индекс на внешний ключ GroupId
create index IndexGroupId on Students using hash (GroupId);

-- ДЗ-5.1.2. Информация о студентах по :StudentName
-- ДЗ-5.2.2. Полная информация о студентах по :StudentName
-- Упорядоченный индекс для ускорения поиска студентов по имени
create unique index IndexStudentNameStudentId on Students using btree (StudentName, StudentId);