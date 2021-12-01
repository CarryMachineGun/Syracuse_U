USE AP;

SELECT VendorName,LastInvoiceDate, InvoiceTotal
FROM Invoices
JOIN (SELECT VendorID, MAX(InvoiceDate) AS LastInvoiceDate
 FROM Invoices
 GROUP BY VendorID) AS LastInvoice
ON (Invoices.VendorID = LastInvoice.VendorID AND
 Invoices.InvoiceDate = LastInvoice.LastInvoiceDate)
JOIN Vendors ON Invoices.VendorID = Vendors.VendorID
ORDER BY VendorName, LastInvoiceDate;

--SELECT VendorID, MAX(InvoiceDate) AS LastInvoiceDate INTO #LastInvoie
--FROM Invoices
--GROUP BY VendorID;

--SELECT VendorName, LastInvoiceDate, InvoiceTotal
--FROM Invoices JOIN #LastInvoie ON Invoices.VendorID = #LastInvoie.VendorID AND Invoices.InvoiceDate = #LastInvoie.LastInvoiceDate
--	JOIN Vendors ON Invoices.VendorID = Vendors.VendorID
--ORDER BY VendorName, LastInvoiceDate;