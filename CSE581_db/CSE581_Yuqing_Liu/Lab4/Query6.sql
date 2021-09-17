SElECT *
FROM VendorCopy
WHERE VendorID NOT IN (SELECT DISTINCT VendorID FROM InvoiceCopy);

DELETE VendorCopy
WHERE VendorID NOT IN (SELECT DISTINCT VendorID FROM InvoiceCopy);

SElECT *
FROM VendorCopy
WHERE VendorID NOT IN (SELECT DISTINCT VendorID FROM InvoiceCopy);