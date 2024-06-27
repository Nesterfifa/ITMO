create database hw7;
\c hw7;

drop table if exists Students;
drop table if exists Groups;
drop table if exists Courses;
drop table if exists Plan;
drop table if exists Lecturers;
drop table if exists Marks;

create table Students (
    StudentId int,
    StudentName varchar(50),
    GroupId int
);

create table Groups (
    GroupId int,
    GroupName varchar(50)
);

create table Courses (
    CourseId int,
    CourseName varchar(50)
);

create table Lecturers (
    LecturerId int,
    LecturerName varchar(50)
);

create table Plan (
    GroupId int,
    CourseId int,
    LecturerId int
);

create table Marks (
    StudentId int,
    CourseId int,
    Mark real
);
