USE MyGuitarShop;

SELECT ListPrice, 
CAST(ListPrice AS DECIMAL(10,1)) AS DecimalListPrice,
CAST(ListPrice AS REAL) AS RealListPrice,
CONVERT(int, ListPrice) AS IntListPrice 
FROM Products