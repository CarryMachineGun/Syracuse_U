SELECT
CAST ( InvoiceDate AS varchar) AS¡¡VarcharDate,
CONVERT ( varchar, InvoiceDate, 5) AS VarcharDate_5,
CONVERT ( varchar, InvoiceDate, 9) AS VarchDate_9,
CAST ( InvoiceDate AS REAL) AS RealCast
FROM Invoices;