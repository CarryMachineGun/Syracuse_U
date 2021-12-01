USE AP;

DROP PROC spBalanceRange;

GO

CREATE PROC spBalanceRange 
	@VandorVar varchar(50) = '%',
	@BalanceMin money = 0,
	@BalanceMax money = 0
AS

IF @BalanceMax = 0
	BEGIN
		SELECT VendorName, InvoiceNumber, InvoiceTotal - CreditTotal - PaymentTotal AS Balance
		FROM Vendors JOIN Invoices ON Vendors.VendorID = Invoices.VendorID
		WHERE 
			VendorName LIKE @VandorVar
			AND (InvoiceTotal - CreditTotal - PaymentTotal) > 0
		ORDER BY Balance
	END
ELSE
	BEGIN
		SELECT VendorName, InvoiceNumber, InvoiceTotal - CreditTotal - PaymentTotal AS Balance
		FROM Vendors JOIN Invoices ON Vendors.VendorID = Invoices.VendorID
		WHERE 
			VendorName LIKE @VandorVar
			AND (InvoiceTotal - CreditTotal - PaymentTotal) BETWEEN @BalanceMin AND @BalanceMax
		ORDER BY Balance
END;
