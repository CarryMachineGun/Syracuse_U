USE AP;

GO

CREATE FUNCTION fnPaidInvoiceID()
RETURNS INT
	BEGIN
	RETURN
	(SELECT MAX(InvoiceID)
	FROM Invoices
	WHERE InvoiceTotal - CreditTotal - PaymentTotal = 0 AND
	InvoiceDueDate =
		(SELECT MAX(InvoiceDueDate)
		FROM Invoices
		WHERE InvoiceTotal - CreditTotal - PaymentTotal = 0));
END;
