USE AP 
GO 
SELECT VendorCity, CreditTable.InvoiceNumber, CreditTable.InvoiceDate, CreditTable.InvoiceTotal, Balance
FROM Vendors JOIN Invoices ON Vendors.VendorID = Invoices.VendorID
             JOIN dbo.fnDateRange('2016-1-10','2016-1-15') AS CreditTable
			 ON Invoices.InvoiceNumber = CreditTable.InvoiceNumber;
