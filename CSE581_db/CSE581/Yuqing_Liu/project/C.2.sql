SELECT CategoryName,ProductID 
FROM Categories LEFT JOIN Products ON Categories.CategoryID = Products.CategoryID
WHERE ProductID IS NULL;