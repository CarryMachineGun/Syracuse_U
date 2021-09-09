SELECT InvoiceNumber, (InvoiceTotal-PaymentTotal-CreditTotal) AS Balance, InvoiceDueDate,
RANK()OVER (ORDER BY (InvoiceTotal- PaymentTotal- CreditTotal) ASC) AS BalanceRank
FROM Invoices
WHERE InvoiceDueDate < GETDATE()+12
AND (InvoiceTotal-PaymentTotal-CreditTotal) <> 0;