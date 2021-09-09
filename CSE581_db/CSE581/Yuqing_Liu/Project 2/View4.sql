USE [States MD Urgent Care Center]
GO

CREATE VIEW HealthHistoryAfter2020
AS
SELECT Patients.PatientID, Patients.PatientName, HealthHistory.CheckInDate
FROM Patients JOIN HealthHistory
ON Patients.PatientID = HealthHistory.PatientID¡¡
WHERE HealthHistory.CheckInDate > '2020-01-01'
GO

SELECT * FROM HealthHistoryAfter2020
