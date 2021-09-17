USE AP
GO

BEGIN TRAN;
INSERT INTO InvoiceArchive 
SELECT * FROM Invoices
WHERE Invoices.InvoiceTotal - CreditTotal - PaymentTotal > 0 
   AND InvoiceID NOT IN ( SELECT InvoiceID FROM InvoiceArchive);

DELETE Invoices
WHERE　Invoices.InvoiceTotal - CreditTotal - PaymentTotal > 0 　
　　AND InvoiceID IN ( SELECT InvoiceID FROM InvoiceArchive);

COMMIT　TRAN;

SELECT* FROM　InvoiceArchive ;

