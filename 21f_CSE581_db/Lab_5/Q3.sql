--SELECT CONVERT(datetime, CONVERT(char(4), YEAR(GETDATE())) + '-' + CONVERT(char(2),(MONTH(GETDATE()) + 1)) + '-01') -1 
--, CONVERT(datetime, YEAR(GETDATE())),  CONVERT(datetime,InvoiceDueDate),*
--FROM AP.dbo.Invoices

SELECT InvoiceNumber, (InvoiceTotal - PaymentTotal - CreditTotal) AS [Balance Due]
FROM AP.dbo.Invoices
WHERE ((InvoiceTotal - PaymentTotal - CreditTotal) <> 0) AND 
(InvoiceDueDate < CONVERT(datetime, CONVERT(char(4), YEAR(GETDATE())) + '-' + CONVERT(char(2),(MONTH(GETDATE()) + 1)) + '-01') -1);