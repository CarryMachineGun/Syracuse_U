USE MyGuitarShop;

SELECT EmailAddress, SUM(ItemPrice * OrderItems.Quantity) AS ItemPriceSum, SUM(DiscountAmount * Quantity) AS TotalSaved 
FROM Customers
JOIN Orders ON Customers.CustomerID = Orders.CustomerID
JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID
GROUP BY EmailAddress
ORDER BY ItemPriceSum