 SELECT LastName, ShipDate, ProductName, Description, ItemPrice,DiscountAmount, Quantity
 FROM Customers JOIN Orders ON Customers.CustomerID = Orders.CustomerID
      JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID 
      JOIN Products ON Products.ProductID = OrderItems.ProductID
 ORDER BY LastName ASC, ShipDate DESC, ProductName DESC;
	 