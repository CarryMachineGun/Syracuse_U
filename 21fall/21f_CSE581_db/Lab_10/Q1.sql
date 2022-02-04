USE AP;

GO

--SELECT * FROM Vendors WHERE VendorName = 'Internal Revenue Service' OR VendorName = 'Fresno County Tax Collector'

BEGIN TRAN;
	UPDATE Invoices
	SET VendorID = 16
	WHERE VendorID = 48;

	DELETE Vendors
	WHERE VendorID = 48;

	UPDATE Vendors
	SET VendorName = 'Revenue Management Office'
	WHERE VendorID = 16
COMMIT TRAN

