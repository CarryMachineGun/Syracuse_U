SELECT *
FROM Invoices
WHERE (PaymentDate IS NULL AND (InvoiceTotal-PaymentTotal-CreditTotal > 0))
OR (PaymentDate IS NOT NULL AND (InvoiceTotal-PaymentTotal-CreditTotal <= 0));