SELECT
CAST ( InvoiceTotal AS decimal(10,4)) AS¡¡DecimalTotal1,
CAST ( InvoiceTotal AS varchar) AS¡¡VarcharTotal1,
CONVERT ( decimal(10,4), InvoiceTotal ) AS DecimalTotal2,
CONVERT ( varchar, InvoiceTotal,10) As VarcharTotal2
FROM Invoices;