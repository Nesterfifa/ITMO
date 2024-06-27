merge into
    Marks
using
    NewMarks
on
    NewMarks.StudentId = Marks.StudentId
    and NewMarks.CourseId = Marks.CourseId
when matched 
    and NewMarks.Mark > Marks.Mark 
then
    update set Mark = NewMarks.Mark
when not matched
then
    insert (StudentId, CourseId, Mark)
    values (NewMarks.StudentId, NewMarks.CourseId, NewMarks.Mark);