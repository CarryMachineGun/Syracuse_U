USE MyGuitarShop;

SELECT EmailAddress, MIN(TotalAmount) AS SmallestOrder
FROM
	(SELECT EmailAddress, Orders.OrderID, SUM((ItemPrice - DiscountAmount) * Quantity) AS TotalAmount
	FROM Customers
	JOIN Orders ON Customers.CustomerID = Orders.CustomerID
	JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID
	GROUP BY EmailAddress, Orders.OrderID) AS Table1
GROUP BY EmailAddress