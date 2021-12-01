-- select AccountNo and AccountDescription
SELECT GLAccounts.AccountNo, GLAccounts.AccountDescription
-- from GLAccounts table
FROM AP.dbo.GLAccounts LEFT JOIN AP.dbo.InvoiceLineItems
ON GLAccounts.AccountNo = InvoiceLineItems.AccountNo
-- selected row's corresponding InvoiceLineItems.AccountNo have to be NULL
WHERE InvoiceLineItems.AccountNo IS NULL
-- Order rows with GLAccounts.AccountNo descendingly
ORDER BY AccountNo DESC;