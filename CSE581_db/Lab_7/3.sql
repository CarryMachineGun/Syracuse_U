USE TutoringCenter;

CREATE INDEX IX_StudyGroups_StudentID ON StudyGroups(StudentID)
CREATE CLUSTERED INDEX IX_StudyGroups_CourseID ON StudyGroups(CourseID);