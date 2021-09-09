SELECT VendorID, VendorCity, VendorState, VendorZipCode
FROM Vendors
WHERE VendorCity + VendorZipCode
NOT IN (SELECT VendorCity + VendorZipCode 
        FROM Vendors
		GROUP BY VendorCity,VendorZipCode
		HAVING COUNT(*)>1)
ORDER BY VendorCity DESC , VendorZipCode;
