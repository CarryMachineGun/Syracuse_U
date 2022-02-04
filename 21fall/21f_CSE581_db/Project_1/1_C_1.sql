USE MyGuitarShop;

SELECT FirstName, LastName, OrderDate, ProductName, ItemPrice, DiscountAmount, Quantity
FROM Customers AS Cu 
JOIN Orders AS Or_1 ON Cu.CustomerID = Or_1.CustomerID
JOIN OrderItems AS Or_2 ON Or_1.OrderID = Or_2.OrderID
JOIN Products AS Pr ON Or_2.ProductID = Pr.ProductID 
ORDER BY LastName DESC, OrderDate;
