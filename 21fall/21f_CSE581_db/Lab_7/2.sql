USE TutoringCenter;

CREATE TABLE Students
(StudentID int NOT NULL IDENTITY PRIMARY KEY,
StudentName varchar(50) NOT NULL,
StudentPhone varchar(50) NULL,
StudentEmail varchar(50) NULL,
StudentAddress varchar(50) NULL);

CREATE TABLE Courses
(CourseID int NOT NULL IDENTITY PRIMARY KEY,
CourseTitle varchar(50) NOT NULL,
CoursePrice money NOT NULL DEFAULT 0 CHECK (CoursePrice >= 0),
CourseTime datetime NULL,
CourseRoom varchar(50) NULL);

CREATE TABLE StudyGroups
(CourseID int REFERENCES Courses(CourseID),
StudentID int REFERENCES Students(StudentID));