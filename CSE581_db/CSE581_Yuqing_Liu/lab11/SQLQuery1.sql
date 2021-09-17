USE AP
GO

CREATE ROLE PaymentEntry;

GRANT UPDATE
ON Vendors TO PaymentEntry
GRANT UPDATE
ON Invoices TO PaymentEntry
GRANT UPDATE,INSERT
ON InvoiceLineItems TO PaymentEntry

ALTER ROLE db_datareader ADD MEMBER PaymentEntry;
