SELECT ItemID
FROM OrderDetails JOIN Orders
ON OrderDetails.OrderID = Orders.OrderID
WHERE ShippedDate IS NULL;
