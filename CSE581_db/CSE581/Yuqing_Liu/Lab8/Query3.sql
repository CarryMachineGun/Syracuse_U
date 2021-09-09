CREATE VIEW  VendorAddress
AS
SELECT VendorID, VendorAddress1+' '+VendorAddress2 AS 'Address', VendorCity AS 'City', VendorState AS 'State', VendorZipCode AS 'Zipcode'
FROM Vendors;

SELECT * FROM VendorAddress
WHERE VendorID = 7;