-- Select sum of sumMax
SELECT SUM(sumMax) AS [sum of the largest unpaid invoices]
FROM (
-- sumMax is the max of InvoiceTotal of each vendor
	SELECT VendorID ,MAX(InvoiceTotal) AS 'sumMax'
	FROM AP.dbo.Invoices
	WHERE InvoiceTotal - CreditTotal - PaymentTotal > 0
	-- Grouping sumMax with VendorID
	GROUP BY VendorID) AS t1;
