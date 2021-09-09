USE [States MD Urgent Care Center]
GO
CREATE VIEW ReductionFee
AS
SELECT Patients.PatientID, Patients.PatientName, SUM(Payment.Price-Tests.Cost) AS Reduction
FROM Patients JOIN Tests
ON Patients.PatientID = Tests.PatientID
 JOIN Payment ON Tests.PaymentID = Payment.PaymentID
GROUP BY Patients.PatientID, PatientName
GO

SELECT * FROM ReductionFee