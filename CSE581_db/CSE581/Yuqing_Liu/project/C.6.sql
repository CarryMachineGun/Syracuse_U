SELECT EmailAddress, OrderID, OrderDate
FROM Customers AS P1 JOIN Orders 
WHERE OrderDate = ( SELECT MAX(OrderDate) FROM Orders AS P2
                  WHERE P1.CustomerID =P2.CustomerID)

