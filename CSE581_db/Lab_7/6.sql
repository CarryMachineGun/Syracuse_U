		USE TutoringCenter;

		DROP TABLE StudyGroups;

		CREATE TABLE StudyGroups
		(CourseID int REFERENCES Courses(CourseID),
		StudentID int REFERENCES Students(StudentID),
		UNIQUE(CourseID, StudentID));
