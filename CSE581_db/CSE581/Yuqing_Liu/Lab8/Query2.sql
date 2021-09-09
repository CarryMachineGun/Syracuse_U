CREATE VIEW Top10PaidInvoices AS
SELECT TOP 10 VendorName, MAX(InvoiceDate) AS LastInvoiceDate, SUM(InvoiceTotal) AS SumOfInvoices
FROM Vendors JOIN Invoices ON Vendors.VendorID=Invoices.VendorID
WHERE¡¡InvoiceTotal - CreditTotal - PaymentTotal = 0
GROUP BY VendorName
ORDER BY SumOfInvoices DESC;

SELECT * FROM Top10PaidInvoices