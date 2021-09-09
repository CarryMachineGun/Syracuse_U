USE¡¡AP¡¡
GO

CREATE FUNCTION  fnUnpaidInvoiceID ()
  RETURNS int
BEGIN 
  RETURN ( SELECT TOP 1 InvoiceID 
           FROM Invoices
           WHERE InvoiceTotal - CreditTotal - PaymentTotal <> 0
	       ORDER BY InvoiceDate DESC)
END
GO

SELECT VendorName, InvoiceNumber, InvoiceDueDate,   InvoiceTotal - CreditTotal - PaymentTotal AS Balance  
FROM Vendors JOIN Invoices ON Vendors.VendorID = Invoices.VendorID  
WHERE InvoiceID = dbo.fnUnpaidInvoiceID(); 