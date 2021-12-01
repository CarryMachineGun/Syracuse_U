USE MyGuitarShop;

SELECT OrderID, OrderDate, DATEADD(month, 2, OrderDate) AS ApproxShipDate, ShipDate, MONTH(ShipDate - OrderDate) AS MonthsToShip
FROM Orders