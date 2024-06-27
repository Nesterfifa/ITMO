insert into groups (group_id, group_name) values
    (1, 'M3137'),
    (2, 'M3138'),
    (3, 'M3139');

insert into courses (course_id, course_name) values
    (1, 'Математический анализ'),
    (2, 'Дискретная математика'),
    (3, 'Алгоритмы и структуры данных');

insert into lecturers (lecturer_id, lecturer_name) values
    (1, 'First lecturer'),
    (2, 'Second lecturer'),
    (3, 'Third lecturer');

insert into lecturers_in_groups (lecturer_id, group_id, course_id) values
    (1, 2, 3),
    (1, 3, 1),
    (3, 1, 2);

insert into courses_in_plan (course_id, group_id) values
    (1, 1),
    (1, 2),
    (3, 3);

insert into students (student_id, group_id, student_name) values
    (1, 3, 'First Student'),
    (2, 1, 'Second Student'),
    (3, 2, 'First Student');

insert into marks (student_id, course_id, mark) values
    (1, 3, 0),
    (2, 2, 100),
    (3, 1, 59.99);
