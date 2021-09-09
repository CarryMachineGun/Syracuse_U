SELECT Customer.EmailAddress, OrderID, MAX(OrderDate)
FROM Customer , Orders
WHERE Customer.CustomerID = Orders.CustomerID;
