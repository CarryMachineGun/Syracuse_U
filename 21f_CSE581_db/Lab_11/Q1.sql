USE AP;

CREATE ROLE PaymentEntry;

GRANT UPDATE, INSERT
ON Vendors TO PaymentEntry;
GRANT UPDATE, INSERT
ON Invoices TO PaymentEntry;
GRANT INSERT
ON InvoiceLineItems TO PaymentEntry;

ALTER ROLE db_datareader ADD MEMBER PaymentEntry;