USE AP;

GO

SELECT VendorCity, FunctionTable.*
FROM Vendors JOIN Invoices
ON Vendors.VendorID = Invoices.VendorID
	JOIN dbo.fnDateRange('16-1-11','16-1-15') AS FunctionTable
	ON Invoices.InvoiceNumber = FunctionTable.InvoiceNumber;