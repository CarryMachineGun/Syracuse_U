USE AP;

ALTER TABLE Invoices
Add 
	Check 
	((PaymentDate is NULL AND PaymentTotal = 0) OR
	(PaymentDate is NOT NULL AND PaymentTotal > 0)),

	Check 
	((PaymentTotal + CreditTotal) <= InvoiceTotal);