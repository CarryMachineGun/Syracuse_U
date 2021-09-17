USE [States MD Urgent Care Center]
GO

CREATE FUNCTION fn2()
RETURNS  INT
BEGIN
RETURN (SELECT DoctorID
FROM Doctor
WHERE DoctorName = (SELECT MIN(DoctorName)
FROM Doctor
))
END
GO

SELECT TestID, TestDate, Result, Tests.CenterID, Tests.Cost, DoctorName, Telephone
FROM Doctor JOIN Tests
ON Tests.DoctorID = Doctor.DoctorID
WHERE Doctor.DoctorID = dbo.fn2();