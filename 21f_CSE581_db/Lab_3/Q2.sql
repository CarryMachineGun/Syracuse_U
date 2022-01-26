-- Select AccountDescription, number counting of InvoiceLineItem as LineItemCount,
-- SUM of InvoiceLineItems.InvoiceLineItemAmount as LineItemSum
SELECT GLAccounts.AccountDescription, COUNT(InvoiceLineItems.InvoiceID) AS 'LineItemCount', 
	SUM(InvoiceLineItems.InvoiceLineItemAmount) AS 'LineItemSum'
FROM AP.dbo.InvoiceLineItems JOIN AP.dbo.GLAccounts ON InvoiceLineItems.AccountNo = GLAccounts.AccountNo
GROUP BY GLAccounts.AccountDescription
ORDER BY LineItemSum;