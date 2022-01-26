-- select vendorName and fullName
SELECT DISTINCT V1.VendorName, V1.VendorContactLName + ' ' + V1.VendorContactFName AS FullName
-- Innor Join two Vendors table 
FROM AP.dbo.Vendors AS V1 INNER JOIN AP.dbo.Vendors AS V2
-- To find vendors whose contact has the same first name (i.e.
-- VendorContactFName) as another vendor¡¯s contact.
ON V1.VendorContactFName = V2.VendorContactFName
-- But the another vendor surely can not be the vendor itself
WHERE NOT V1.VendorID = V2.VendorID
-- Order rows with FullNAme descendingly
ORDER BY FullName DESC;