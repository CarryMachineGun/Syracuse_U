SELECT EmailAddress, SUM(ItemPrice*Quantity) AS TotalPrice, AVG(DiscountAmount*Quantity) AS Discount
FROM Customers JOIN Orders
ON Customers.CustomerID = Orders.CustomerID
JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID
GROUP BY EmailAddress
ORDER BY TotalPrice DESC;

