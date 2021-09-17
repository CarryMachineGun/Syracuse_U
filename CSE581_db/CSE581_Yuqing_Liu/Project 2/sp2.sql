USE [States MD Urgent Care Center]
GO
CREATE PROC spPaymentPriceRange
@PatientVar varchar(50) = '%',
@PriceMin money = 0,
@PriceMax money = 0
AS
IF (@PriceMax = 0)
SELECT @PriceMax = MAX(Price), @PriceMin = 0
FROM Payment
SELECT PatientName, Price
FROM Patients JOIN Payment
ON Patients.PatientID = Payment.PatientID
WHERE Price > @PriceMin AND Price < @PriceMax AND PatientName LIKE @PatientVar
ORDER BY Price;
GO
EXEC spPaymentPriceRange '[M]%';