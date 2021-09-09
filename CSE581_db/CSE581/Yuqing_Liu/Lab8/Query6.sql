USE AP

SELECT VendorID, MAX(InvoiceDate) AS LastInvoiceDate
INTO #LastInvoice
FROM Invoices
GROUP BY VendorID;

SELECT VendorName, LastInvoiceDate, InvoiceTotal
FROM Invoices JOIN #LastInvoice 
        ON Invoices.VendorID = #LastInvoice.VendorID AND Invoices.InvoiceDate = #LastInvoice.LastInvoiceDate
		JOIN Vendors ON Invoices.VendorID = Vendors.VendorID
ORDER BY VendorName, LastInvoiceDate;