SELECT DISTINCT GLAccounts.AccountNo
FROM GLAccounts JOIN InvoiceLineItems
ON GLAccounts.AccountNo = InvoiceLineItems.AccountNo 
WHERE InvoiceLineItems.InvoiceLineItemAmount >
(SELECT AVG(InvoiceLineItems.InvoiceLineItemAmount) FROM InvoiceLineItems );