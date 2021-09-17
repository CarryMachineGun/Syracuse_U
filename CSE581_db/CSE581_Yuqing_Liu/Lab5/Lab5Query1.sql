SELECT¡¡VendorContactLName + ' ' + LEFT (VendorContactFName, 2) +'.' AS Contact,
RIGHT(VendorPhone, 8) AS Phone
FROM Vendors
WHERE SUBSTRING ( VendorPhone, 2, 3) = 209
ORDER BY VendorContactFName, VendorContactLName;
