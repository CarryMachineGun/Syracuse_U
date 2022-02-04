SELECT InvoiceCopy.InvoiceID, Vendors.DefaultTermsID, InvoiceCopy.TermsID
FROM AP.dbo.InvoiceCopy JOIN AP.dbo.Vendors ON InvoiceCopy.VendorID = Vendors.VendorID
ORDER BY InvoiceCopy.TermsID DESC;

/*UPDATE AP.dbo.InvoiceCopy
SET TermsID = 25
WHERE VendorID IN 
	(SELECT VendorID
	FROM AP.dbo.Vendors
	WHERE DefaultTermsID = 2)*/