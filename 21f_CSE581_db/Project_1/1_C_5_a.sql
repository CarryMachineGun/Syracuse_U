USE MyGuitarShop;

SELECT EmailAddress, Orders.OrderID, SUM((ItemPrice - DiscountAmount) * Quantity) AS TotalAmount
FROM Customers
JOIN Orders ON Customers.CustomerID = Orders.CustomerID
JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID
GROUP BY EmailAddress, Orders.OrderID
ORDER BY EmailAddress