USE MyGuitarShop;

SELECT OrderID, OrderDate, ShipDate
FROM Orders
WHERE ShipDate IS NOT NULL
