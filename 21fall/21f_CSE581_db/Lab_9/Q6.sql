USE AP;

GO

CREATE FUNCTION fnDateRange
	(@DateMin SMALLDATETIME, @DateMax SMALLDATETIME)
RETURNS TABLE

RETURN
	(SELECT InvoiceNumber, InvoiceDate, InvoiceTotal,
	InvoiceTotal - CreditTotal - PaymentTotal AS Balance
FROM Invoices
WHERE InvoiceDate BETWEEN @DateMin AND @DateMax);

GO

SELECT *
FROM dbo.fnDateRange('2016-1-11','2016-1-15');