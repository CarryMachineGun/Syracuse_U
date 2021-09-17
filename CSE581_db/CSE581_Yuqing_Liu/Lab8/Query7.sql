USE AP
IF OBJECT_ID('EarliestInvoice') IS NOT NULL
DROP VIEW EarliestInvoice;
IF OBJECT_ID('invoicetotal') IS NOT NULL
DROP VIEW invoietotal

CREATE VIEW EarliestInvoice AS 
SELECT VendorID, MIN(InvoiceDate) AS EarliestDate
FROM Invoices
GROUP BY VendorID;

CREATE VIEW invoicetotal AS
SELECT VendorName, EarliestDate, InvoiceTotal
FROM Invoices JOiN EarliestInvoice ON (Invoices.VendorID = EarliestInvoice.VendorID 
                                  AND Invoices.InvoiceDate = EarliestInvoice.EarliestDate)
			  JOIN Vendors ON Vendors.VendorID = EarliestInvoice.VendorID;

SELECT * FROM¡¡invoicetotal


