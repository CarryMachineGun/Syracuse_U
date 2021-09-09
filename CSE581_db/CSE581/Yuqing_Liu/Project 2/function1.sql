USE [States MD Urgent Care Center]
GO
CREATE FUNCTION f1()
RETURNS INT
BEGIN
RETURN (SELECT TestID
FROM Tests
WHERE TestDate = (SELECT MAX(TestDate)
FROM Tests
WHERE Cost > 10)
)
END
GO
SELECT TestID, TestDate, PatientName, Patients.PatientID, PatientAddress, Cost, Zipcode
FROM Tests JOIN Patients
ON Tests.PatientID = Patients.PatientID
WHERE TestID = dbo.f1();