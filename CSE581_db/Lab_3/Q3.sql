-- select vendorName, counting invoice_ID as InvoiceCount and averaging invoice_Total as InvocieAverage
SELECT Vendors.VendorName, COUNT(Invoices.InvoiceID) AS 'InvoiceCount', AVG(Invoices.InvoiceTotal) AS 'InvoiceAverage'
FROM AP.dbo.Vendors JOIN AP.dbo.Invoices ON Vendors.VendorID = Invoices.VendorID
-- grouping the COUNT and AVG by VendorName
GROUP BY Vendors.VendorName	
HAVING COUNT(*) > 3
ORDER BY InvoiceCount
