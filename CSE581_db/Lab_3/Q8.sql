-- SELECT statement that returns the id, city, state, and zip-code of each vendor
SELECT VendorID, VendorCity, VendorState, VendorZipCode
FROM AP.dbo.Vendors
-- select vendor doesn't belong to the vendors below
WHERE VendorID NOT IN
	-- Subquery select vendors that have a both state and city in common with another vendor
	(SELECT DISTINCT b1.VendorID
	FROM AP.dbo.Vendors AS b1 JOIN AP.dbo.Vendors AS b2 
	ON (b1.VendorCity = b2.VendorCity) AND (b1.VendorState = b2.VendorState)
	WHERE NOT b1.VendorID = b2.VendorID
	)
ORDER BY VendorState DESC;
