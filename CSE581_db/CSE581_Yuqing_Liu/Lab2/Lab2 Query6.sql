SELECT DISTINCT ContactUpdates1.FirstName, ContactUpdates1.FirstName + ',' + ContactUpdates1.LastName AS 'Full Name'
FROM ContactUpdates AS ContactUpdates1 JOIN ContactUpdates AS ContactUpdates2
ON (ContactUpdates1.LastName = ContactUpdates2.LastName)
AND (ContactUpdates1.VendorID <> ContactUpdates2.VendorID)
ORDER BY ContactUpdates1.FirstName;