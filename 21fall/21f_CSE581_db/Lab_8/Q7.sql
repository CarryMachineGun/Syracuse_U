USE AP;

IF OBJECT_ID('LastInvoice_view') IS NOT NULL
	DROP VIEW LastInvoice_view

CREATE VIEW LastInvoice_view
AS
SELECT VendorID, MAX(InvoiceDate) AS LastInvoiceDate, MAX(InvoiceTotal) AS LastInvoiceTotal
FROM AP.dbo.Invoices
GROUP BY VendorID;

SELECT* FROM LastInvoice_view;