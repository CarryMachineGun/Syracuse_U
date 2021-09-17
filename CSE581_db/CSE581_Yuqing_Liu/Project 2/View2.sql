USE [States MD Urgent Care Center]
GO
CREATE VIEW Cost
AS
SELECT Patients.PatientID, Patients.PatientName, SUM(Tests.Cost) AS Total
FROM Patients JOIN Tests
ON Patients.PatientID = Tests.PatientID
GROUP BY Patients.PatientID, PatientName
GO

SELECT * FROM Cost