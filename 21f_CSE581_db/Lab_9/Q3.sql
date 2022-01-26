USE AP;

GO

CREATE PROC spDataRange
	@DataMin varchar(20) = NULL,
	@DataMax varchar(20) = NULL

AS
IF @DataMax IS NULL OR @DataMin IS NULL
	THROW 50002, 'DataMax or DataMin is NULL!',1;
IF (ISDATE(@DataMin) = 0) OR (ISDATE(@DataMax) = 0)
	THROW 50002, 'DataMax or DataMin is not in valid data type!',1;
IF CAST(@DataMin AS datetime) > CAST(@DataMax AS datetime)
	THROW 50002, 'DataMin must be later than DataMax!',1;

SELECT InvoiceNumber, InvoiceDate, InvoiceTotal, InvoiceTotal - CreditTotal - PaymentTotal AS Balance
FROM Invoices
WHERE InvoiceDate BETWEEN @DataMin AND @DataMax
ORDER BY InvoiceDate DESC;