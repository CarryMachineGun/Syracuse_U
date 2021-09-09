SELECT InvoiceNumber, (InvoiceTotal-PaymentTotal-CreditTotal) AS Balance, InvoiceDueDate
FROM Invoices
WHERE InvoiceDueDate < DATEADD(DAY,-1,DATEADD(MONTH,DATEDIFF(MONTH,0,GETDATE())+1,0)) 
AND (InvoiceTotal-PaymentTotal-CreditTotal) <> 0;