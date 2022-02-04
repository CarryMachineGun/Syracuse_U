-- SELECT the top ten selected record of VendorName, AVG(Invoices.PaymentTotal)
SELECT TOP 10 Vendors.VendorName, AVG(Invoices.PaymentTotal) AS 'PaymentAverage'
FROM AP.dbo.Vendors JOIN AP.dbo.Invoices ON Vendors.VendorID = Invoices.VendorID
GROUP BY VendorName
-- the records are selected by the value of PaymentAverage
ORDER BY PaymentAverage DESC;