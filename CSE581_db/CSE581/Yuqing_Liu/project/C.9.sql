USE MyGuitarShop
SELECT OrderID, OrderDate, DATEADD(MONTH,1,OrderDate) AS ApproxShipDate,
    ShipDate,DATEDIFF(DAY,OrderDate,ShipDate) AS DayToShip
FROM Orders
WHERE DATEPART(MONTH,OrderDate)='4' AND DATEPART(YEAR,OrderDate)='2016';
