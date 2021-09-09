SELECT AccountNo, SUM(InvoiceLineItemAmount) AS TotalInvoiceAmount
FROM InvoiceLineItems
GROUP BY AccountNo WITH¡¡ROLLUP;
