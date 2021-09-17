SELECT  InvoiceNumber AS Number, InvoiceTotal AS Total, PaymentTotal+CreditTotal AS Credits
FROM Invoices
WHERE InvoiceTotal <= 300;