USE [States MD Urgent Care Center]
GO
CREATE PROC spDateRange
@DateMin varchar(50)=NULL,
@DateMax varchar(50)=NULL
AS 
IF @DateMax IS NULL OR @DateMin IS NULL
   THROW 50001, 'Parameter DateMax and DateMin cannot be null.',1;
IF NOT (ISDATE(@DateMax)=1 AND ISDATE(@DateMin)=1 )
   THROW 50001, 'Please enter valid date.',1;
IF CAST(@DateMin AS datetime) > CAST (@DateMax AS datetime)
   THROW 50001, 'Parameter DateMin must be earlier than DateMax.',1;

SELECT PaymentID, Price,PaymentDate
FROM [States MD Urgent Care Center].dbo.Payment
WHERE PaymentDate Between @DateMin AND @DateMax
ORDER BY PaymentDate
BEGIN TRY
  EXEC spDateRange '2020-10-10', '2020-12-01';
END TRY
BEGIN CATCH 
   PRINT 'Error Number:' + CONVERT(varchar(50), ERROR_NUMBER());
   PRINT 'Error Message:' + CONVERT(varchar(50), ERROR_NUMBER());
END CATCH;