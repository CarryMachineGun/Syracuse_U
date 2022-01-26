--SELECT *

	SELECT InvoiceNumber, (InvoiceTotal - PaymentTotal - CreditTotal) AS [Balance Due], InvoiceDueDate
	FROM AP.dbo.Invoices
	WHERE ((InvoiceTotal - PaymentTotal - CreditTotal) <> 0) AND (InvoiceDueDate < GETDATE() + 10);