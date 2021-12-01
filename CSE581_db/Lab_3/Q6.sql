-- Select distinct VendorName
SELECT DISTINCT Vendors.VendorName
FROM AP.dbo.Vendors JOIN AP.dbo.Invoices ON Vendors.VendorID = Invoices.VendorID
WHERE Invoices.PaymentTotal > 
-- PaymentTotal can not be 0
	 (SELECT AVG(Invoices.PaymentTotal) FROM AP.dbo.Invoices WHERE Invoices.PaymentTotal > 0)
ORDER BY VendorName;
