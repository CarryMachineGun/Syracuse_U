SELECT AccountDescription, COUNT(*) AS LineItemCount, SUM(InvoiceLineItemAmount) AS LineItemSum
FROM InvoiceLineItems JOIN GLAccounts
ON InvoiceLineItems.AccountNo = GLAccounts.AccountNo
GROUP BY AccountDescription
HAVING COUNT(*)>2
ORDER BY LineItemSum DESC;