USE AP
ALTER TABLE Invoices
ADD CHECK ((PaymentTotal=0 AND PaymentDate IS NULL) OR 
           (PaymentTotal>0 AND PaymentDate IS NOT NULL)),
    CHECK ((PaymentTotal + CreditTotal) <= InvoiceTotal);