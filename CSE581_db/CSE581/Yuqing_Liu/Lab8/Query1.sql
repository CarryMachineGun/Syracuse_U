CREATE VIEW InvoiceBasic 
AS
SELECT VendorName, InvoiceNumber, InvoiceTotal
FROM Vendors JOIN Invoices ON Vendors.VendorID = Invoices.VendorID;

SELECT * FROM InvoiceBasic
WHERE ( LEFT ( VendorName, 1 ) = 'A' OR¡¡LEFT ( VendorName, 1 ) = 'B' OR  LEFT ( VendorName, 1 ) = 'C' )
ORDER BY InvoiceTotal DESC;