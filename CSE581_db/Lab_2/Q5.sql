-- select CustLastName, CustCity, CustState, OrderDate and ShippedDate
SELECT Customers.CustLastName, Customers.CustCity AS 'City', Customers.CustState, Orders.OrderDate AS [Order Date], 
Orders.ShippedDate AS [Shipped Date]
-- from Customers and Orders table
FROM ProductOrders.dbo.Orders
FULL outer join ProductOrders.dbo.Customers
ON Customers.CustID = Orders.CustID
-- CustState can only be 'CA' and ShippedDate can only be NULL
WHERE CustState = 'CA' AND ShippedDate IS NULL
-- Order rows with CustLastName descendingly
ORDER BY CustLastName DESC;