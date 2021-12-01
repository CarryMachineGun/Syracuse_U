USE MyGuitarShop;

GO

CREATE VIEW Top5BestSelling
AS
SELECT ProductName, SUM(Quantity) AS OrderTotal, COUNT(OrderID) AS OrderCount
FROM OrderItemProductsDetails
GROUP BY ProductName;

GO 

SELECT * FROM Top5BestSelling;
