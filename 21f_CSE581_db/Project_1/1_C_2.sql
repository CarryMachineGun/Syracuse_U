USE MyGuitarShop;

SELECT DISTINCT CategoryName
FROM Categories
RIGHT JOIN Products ON Products.CategoryID = Categories.CategoryID