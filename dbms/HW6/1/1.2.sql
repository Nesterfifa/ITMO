select distinct
    Students.StudentId, 
    Students.StudentName, 
    Students.GroupId
from 
    Students, Groups
where
    Students.GroupId = Groups.GroupId and GroupName = :GroupName;