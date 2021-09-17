SELECT  VendorName, COUNT(*) AS InvoiceCount, AVG(InvoiceTotal) AS InvoiceAverage
FROM Invoices JOIN Vendors
ON Invoices.VendorID= Vendors.VendorID 
GROUP BY VendorName
ORDER BY InvoiceCount DESC;
