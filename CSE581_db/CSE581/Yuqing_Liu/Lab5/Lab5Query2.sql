SELECT InvoiceNumber, (InvoiceTotal-PaymentTotal-CreditTotal) AS BalanceDue, InvoiceDueDate 
FROM Invoices
WHERE InvoiceDate < GETDATE() + 12
AND (InvoiceTotal-PaymentTotal-CreditTotal) <> 0;
