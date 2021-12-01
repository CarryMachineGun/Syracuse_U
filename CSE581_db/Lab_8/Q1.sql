CREATE VIEW CustomerInvoices 
AS 
SELECT CustFirstName + ' ' + CustLastName AS CustName, OrderDate, ShippedDate, OrderID
FROM ProductOrders.dbo.Orders JOIN ProductOrders.dbo.Customers ON Orders.CustID = Customers.CustID;

SELECT * 
FROM CustomerInvoices
WHERE (LEFT (CustName, 1) = 'A') OR (LEFT (CustName, 1) = 'D') OR (LEFT (CustName, 1) = 'E')
ORDER BY CustName;