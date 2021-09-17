SELECT VendorName,VendorState 
FROM Vendors 
WHERE VendorState IN('CA')
UNION
SELECT VendorName,'Not in CA' AS VendorState 
FROM Vendors 
WHERE VendorState<>('CA')
ORDER BY VendorName;