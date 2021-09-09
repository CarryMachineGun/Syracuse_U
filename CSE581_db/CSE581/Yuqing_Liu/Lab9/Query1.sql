USE AP
IF OBJECT_ID ('spBalanceRange') IS NOT NULL
 DROP PROC spBalanceRange
GO
CREATE PROC spBalanceRange
   @VendorVar varchar(40)='%',
   @BalanceMin money=NULL,
   @BalanceMax money=NULL
AS
 IF @BalanceMax = 0
  SELECT * FROM Invoices
  WHERE InvoiceTotal - CreditTotal - PaymentTotal > 0
 ELSE 
 SELECT VendorName, InvoiceNumber, InvoiceTotal - CreditTotal - PaymentTotal AS BalanceDue
 FROM Vendors JOIN Invoices ON Vendors.VendorID = Invoices.VendorID
 WHERE (VendorName LIKE @VendorVar) AND 
       (InvoiceTotal - CreditTotal - PaymentTotal > @BalanceMin) AND
	   (InvoiceTotal - CreditTotal - PaymentTotal < @BalanceMax)
 ORDER BY InvoiceTotal - CreditTotal - PaymentTotal ASC;
