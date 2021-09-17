SELECT EmailAddress, MAX(OrderTotalAmount) AS LargestOrder
FROM (SELECT EmailAddress, Orders.OrderID, SUM(ItemPrice*Quantity-DiscountAmount*Quantity) AS OrderTotalAmount
      FROM Customers JOIN Orders ON Customers.CustomerID = Orders.CustomerID
          JOIN OrderItems ON OrderItems.OrderID = Orders.OrderID
      GROUP BY EmailAddress, Orders.OrderID) AS Customers
GROUP BY Customers.EmailAddress;

