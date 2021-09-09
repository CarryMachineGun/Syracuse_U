
INSERT INTO InvoiceCopy
          (VendorID, InvoiceNumber, InvoiceTotal, PaymentTotal, CreditTotal, TermsID, 
		  InvoiceDate, InvoiceDueDate)
VALUES (2, 'CM-007-700', 401.40, 2.99, 5.99, 3, '08/24/15', '09/01/15');

SELECT *
FROM InvoiceCopy
WHERE InvoiceNumber = 'CM-007-700';
