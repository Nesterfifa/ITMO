drop table if exists marks;
drop table if exists students;
drop table if exists courses_in_plan;
drop table if exists lecturers_in_groups;
drop table if exists lecturers;
drop table if exists courses;
drop table if exists groups;

create table groups(
    group_id int,
    group_name char(6) not null,
    primary key(group_id)
);

create table courses(
    course_id int,
    course_name varchar(30) not null,
    primary key(course_id)
);

create table lecturers(
    lecturer_id int,
    lecturer_name varchar(30) not null,
    primary key(lecturer_id)
);

create table lecturers_in_groups(
    lecturer_id int,
    course_id int,
    group_id int,
    primary key(lecturer_id, course_id, group_id),
    constraint fk_lecturer
        foreign key(lecturer_id)
            references lecturers(lecturer_id),
    constraint fk_group
        foreign key(group_id)
            references groups(group_id),
    constraint fk_course
        foreign key(course_id)
            references courses(course_id)
);

create table courses_in_plan(
    group_id int,
    course_id int,
    primary key(group_id, course_id),
    constraint fk_course
        foreign key(course_id)
            references courses(course_id),
    constraint fk_group
        foreign key(group_id)
            references groups(group_id)
);

create table students(
    student_id int not null,
    group_id int not null,
    student_name varchar(30) not null,
    primary key(student_id),
    constraint fk_group
        foreign key(group_id)
            references groups(group_id)
);

create table marks(
    student_id int,
    course_id int,
    mark float not null,
    primary key(student_id, course_id),
    constraint fk_course
        foreign key(course_id)
            references courses(course_id),
    constraint fk_student
        foreign key(student_id)
            references students(student_id)
);