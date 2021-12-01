SELECT DISTINCT b1.VendorID, b1.VendorCity, b1.VendorState, b1.VendorZipCode
	FROM AP.dbo.Vendors AS b1 JOIN AP.dbo.Vendors AS b2 
	ON (b1.VendorCity = b2.VendorCity) AND (b1.VendorState = b2.VendorState)
	WHERE NOT b1.VendorID = b2.VendorID
	ORDER BY VendorCity