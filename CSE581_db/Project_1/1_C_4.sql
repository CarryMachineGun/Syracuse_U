USE MyGuitarShop;

SELECT EmailAddress, COUNT(Orders.OrderID) AS NumberOfOrder, SUM((ItemPrice - DiscountAmount) * Quantity) AS TotalAmount
FROM Customers
JOIN Orders ON Customers.CustomerID = Orders.CustomerID
JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID
GROUP BY EmailAddress
HAVING SUM((ItemPrice - DiscountAmount) * Quantity) > 600
ORDER BY EmailAddress