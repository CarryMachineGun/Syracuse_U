-- select ¡®InvoiceTotal - PaymentTotal - CreditTotal¡¯ as 'Balance Due' and all the column on Invoices table
SELECT *, InvoiceTotal - PaymentTotal - CreditTotal AS [Balance Due]
-- from Invoices table
FROM AP.dbo.Invoices
-- PaymentDate must be a non-null value if there is no balance due
-- and a null value if there is balance due
WHERE (PaymentDate IS NOT NULL AND (InvoiceTotal - PaymentTotal - CreditTotal) = 0) 
OR (PaymentDate IS NULL AND (InvoiceTotal - PaymentTotal - CreditTotal) > 0);