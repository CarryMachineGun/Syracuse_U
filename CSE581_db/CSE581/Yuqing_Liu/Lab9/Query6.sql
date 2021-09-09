USE AP 
GO
CREATE FUNCTION  fnDateRange(@DateMin smalldatetime, @DateMax smalldatetime)
 RETURNS @OutTable table ( InvoiceNumber varchar(50), InvoiceDate smalldatetime, InvoiceTotal money, Balance money)
BEGIN
  INSERT @OutTable
     SELECT  InvoiceNumber, InvoiceDate, InvoiceTotal, InvoiceTotal-CreditTotal-PaymentTotal AS Balance 
	 FROM Invoices
	 WHERE InvoiceDate < @DateMax AND InvoiceDate > @DateMin
  RETURN;
END;
GO
SELECT* FROM 
dbo.fnDateRange('2016-1-10','2016-1-15')