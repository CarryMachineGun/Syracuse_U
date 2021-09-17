SELECT *
FROM InvoiceCopy
WHERE VendorID IN (SELECT VendorID FROM VendorCopy
                  WHERE DefaultTermsID = 2);
UPDATE InvoiceCopy
SET TermsID = 5
WHERE VendorID IN (SELECT VendorID FROM VendorCopy
                  WHERE DefaultTermsID = 2);
SELECT *
FROM InvoiceCopy
WHERE VendorID IN (SELECT VendorID FROM VendorCopy
                  WHERE DefaultTermsID = 2);
