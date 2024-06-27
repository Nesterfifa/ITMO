-- ДЗ-5.3.3. Информация о студентах с :Mark по своему предмету 
-- :LecturerId
-- ДЗ-5.3.5. Информация о студентах с :Mark по предмету :LecturerId
-- ДЗ-6.5.1. StudentId имеющих хотя бы одну оценку у :LecturerName
-- Индекс по primary key
create unique index IndexLecturerId on Lecturers using hash (LecturerId);

-- ДЗ-6.5.1. StudentId имеющих хотя бы одну оценку у :LecturerName 
-- ДЗ-6.5.2. StudentId не имеющих оценок у :LecturerName
-- ДЗ-6.5.3. StudentId имеющих оценки по всем предметам :LecturerName
-- Упорядоченный индекс для ускорения поиска по имени преподавателя
create unique index IndexLecturerNameLecturerId on Lecturers using btree (LecturerName, LecturerId);