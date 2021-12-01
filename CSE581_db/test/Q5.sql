-- select CustLastName, CustCity, CustState, OrderDate and ShippedDate
SELECT Customers.CustLastName, Customers.CustCity AS 'City', Customers.CustState, Orders.OrderDate AS [Order Date], 
Orders.ShippedDate AS [Shipped Date]
-- from Customers and Orders table
FROM ProductOrders.dbo.Orders
inner join ProductOrders.dbo.Customers
ON Customers.CustID = Orders.CustID
-- Order rows with CustLastName descendingly
ORDER BY CustLastName DESC;