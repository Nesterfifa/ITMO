-- ДЗ-5.8.3. SumMark студентов каждой группы 
-- ДЗ-5.9.3. AvgMark каждой группы
-- ДЗ-6.2.2. Получить полную информацию о студентах, не имеющих оценки
-- по дисциплине, заданной идентификатором (StudentId, StudentName, 
-- GroupName по :CourseId)
-- Хеш-индекс на primary key
create unique index IndexGroupId on Groups using hash (GroupId);

-- ДЗ-6.1.2. Информация о студентах по :GroupName
-- Упорядоченный индекс для поиска по названию группы
create unique index IndexGroupNameGroupId on Groups using btree (GroupName, GroupId);