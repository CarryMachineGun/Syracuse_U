--DROP VIEW Top13Orders

--CREATE VIEW Top13Orders
--AS 
--SELECT TOP 13 CustomerInvoices.CustName, MIN(CustomerInvoices.OrderDate) AS FirstOrderDate, SUM(OrderDetails.Quantity) AS SumOfQuantity
--FROM CustomerInvoices JOIN ProductOrders.dbo.OrderDetails 
--ON CustomerInvoices.OrderID = OrderDetails.OrderID
--GROUP BY CustomerInvoices.CustName
--ORDER BY SumOfQuantity DESC;

SELECT * FROM Top13Orders;
