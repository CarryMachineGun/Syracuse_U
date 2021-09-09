USE AP
IF OBJECT_ID ('spDateRange') IS NOT NULL
 DROP PROC spDateRange
GO
CREATE PROC spDateRange
   @DateMin varchar(50)=NULL,
   @DateMax varchar(50)=NULL
AS
 IF @DateMin IS NULL
    THROW 50001, 'The minum date should not be null.',1;
 IF @DateMax IS NULL 
    THROW 50002, 'The maximum date should not be null.',1;
 IF @DateMin > @DateMax
    THROW 50003, 'Invalid Date.',1;
 ELSE 
    SELECT InvoiceNumber, InvoiceDate, InvoiceTotal, InvoiceTotal-CreditTotal-PaymentTotal AS Balance
	FROM Invoices
	WHERE ( InvoiceDate > CONVERT (smalldatetime, @DateMin)) AND (InvoiceDate < CONVERT(smalldatetime, @DateMax))
	ORDER BY InvoiceDate ASC;

