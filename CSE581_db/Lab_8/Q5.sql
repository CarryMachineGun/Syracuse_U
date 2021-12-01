USE AP;

DECLARE @TotalInvoiceDue money;

SELECT @TotalInvoiceDue = SUM(InvoiceTotal - CreditTotal- PaymentTotal)
FROM dbo.Invoices
WHERE InvoiceTotal - CreditTotal - PaymentTotal > 0;

IF @TotalInvoiceDue < 50000
	BEGIN
	PRINT 'Balance due is' + CAST(@TotalInvoiceDue as NVARCHAR(9)) + '.'
	SELECT Vendors.VendorName, Invoices.InvoiceNumber, Invoices.InvoiceDueDate,
		Invoices.InvoiceTotal - Invoices.CreditTotal - Invoices.PaymentTotal AS Balance
	FROM Invoices JOIN Vendors
	ON Invoices.VendorID = Vendors.VendorID
	WHERE Invoices.InvoiceTotal - Invoices.CreditTotal - Invoices.PaymentTotal > 0
	ORDER BY InvoiceDueDate DESC
	END
ELSE
	PRINT 'Balance due is more than $50,000.00.'