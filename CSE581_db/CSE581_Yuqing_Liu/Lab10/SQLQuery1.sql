USE AP
GO
 
SELECT *
FROM Vendors
WHERE¡¡VendorName = 'The Drawing Board';

BEGIN TRAN;
 UPDATE Vendors
 SET VendorName = 'ComputerBoard'
 WHERE¡¡VendorID = 65;
 DELETE Vendors
 WHERE VendorID!=65;
 COMMIT TRAN;

SELECT *
FROM Vendors
WHERE¡¡VendorName = 'ComputerBoard';
