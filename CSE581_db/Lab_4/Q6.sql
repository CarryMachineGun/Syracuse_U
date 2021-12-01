SELECT COUNT(VendorID), COUNT(DISTINCT VendorState)
FROM AP.dbo.VendorCopy;

/*DELETE AP.dbo.VendorCopy
WHERE VendorState NOT IN(
	SELECT DISTINCT VendorState
	FROM AP.dbo.Vendors JOIN AP.dbo.Invoices ON Vendors.VendorID = Invoices.VendorID);*/