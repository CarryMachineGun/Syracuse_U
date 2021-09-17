SELECT EmailAddress,COUNT(*) AS NumberOfOrders, SUM(ItemPrice*Quantity - DiscountAmount*Quantity) AS TotalPrice
FROM Customers JOIN Orders ON Customers.CustomerID = Orders.CustomerID
     JOIN OrderItems ON OrderItems.OrderID = Orders.OrderID
GROUP BY EmailAddress
HAVING SUM(ItemPrice*Quantity - DiscountAmount*Quantity) > 500 
ORDER BY EmailAddress DESC;
