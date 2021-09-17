USE AP
DECLARE @TotalBalanceDue money;

SET @TotalBalanceDue = (SELECT SUM(InvoiceTotal-PaymentTotal-CreditTotal) FROM Invoices)
IF @TotalBalanceDue > 45000
  PRINT 'Balance due is more than $45,000.00.'

ELSE SELECT VendorName, InvoiceNumber, InvoiceDueDate, (InvoiceTotal-PaymentTotal-CreditTotal) AS 'Balance'
     FROM Invoices JOIN Vendors ON Invoices.VendorID = Vendors.VendorID
	 WHERE InvoiceTotal-PaymentTotal-CreditTotal > 0
	 ORDER BY InvoiceDueDate
	 PRINT 'Balance due is'+ CONVERT (varchar, @TotalBalanceDue, 1);
	 