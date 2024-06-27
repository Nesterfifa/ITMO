select StudentName, CourseName
from Students 
    natural join
        (select distinct StudentId, CourseId
            from Students natural join Plan) X
    natural join Courses;