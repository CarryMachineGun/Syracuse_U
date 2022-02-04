--SELECT *

SELECT InvoiceNumber, (InvoiceTotal - PaymentTotal -CreditTotal) AS [Balance Due], InvoiceDueDate, 
RANK() OVER (ORDER BY InvoiceTotal - PaymentTotal - CreditTotal DESC) AS BalanceRank
FROM AP.dbo.Invoices
WHERE ((InvoiceTotal - PaymentTotal - CreditTotal) <> 0) AND (InvoiceDueDate < GETDATE() + 10);