SELECT VendorName, COUNT(DISTINCT InvoiceLineItems.AccountNo) AS Accounts
FROM Vendors JOIN Invoices ON Vendors.VendorID = Invoices.VendorID
 JOIN InvoiceLineItems ON Invoices.InvoiceID = InvoiceLineItems.InvoiceID
 GROUP BY Vendors.VendorName
 HAVING COUNT(DISTINCT InvoiceLineItems.AccountNo) > 2;