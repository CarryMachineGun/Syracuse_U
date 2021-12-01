USE MyGuitarShop;

SELECT LastName + ' ' + FirstName AS FullName
FROM Customers
WHERE LEFT(LastName,1) BETWEEN 'A' AND 'E'
ORDER BY LastName