USE MyGuitarShop;

SELECT EmailAddress, OrderID, OrderDate
FROM Customers AS c1
JOIN Orders ON c1.CustomerID = Orders.CustomerID 
WHERE OrderDate =
	(SELECT MAX(OrderDate)
	FROM Customers AS c2
	JOIN Orders ON c2.CustomerID = Orders.CustomerID
	WHERE c1.EmailAddress = c2.EmailAddress)
ORDER BY EmailAddress
