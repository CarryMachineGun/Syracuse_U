-- WHY distinct?
-- WE need distinct because a Vendor can have mutiple invocie
SELECT Vendors.VendorName, COUNT(DISTINCT InvoiceLineItems.AccountNo) AS [total number of accounts]
FROM AP.dbo.Vendors 
	JOIN AP.dbo.Invoices ON Vendors.VendorID = Invoices.VendorID
	JOIN AP.dbo.InvoiceLineItems ON InvoiceLineItems.InvoiceID = Invoices.InvoiceID
-- Grouping the count of accountNo by VendorName
GROUP BY VendorName
HAVING COUNT(DISTINCT InvoiceLineItems.AccountNo) > 1
ORDER BY VendorName;	
