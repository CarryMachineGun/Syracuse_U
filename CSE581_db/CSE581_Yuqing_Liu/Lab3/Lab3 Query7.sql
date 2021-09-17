SELECT SUM(MinInvoice) AS 'Sum of the Smallest Unpaid Invoices'
FROM (SELECT VendorID, MIN(InvoiceTotal) AS MinInvoice
      FROM Invoices
	  WHERE InvoiceTotal - CreditTotal - PaymentTotal > 0
	  GROUP BY VendorID)
AS MinInvoice


