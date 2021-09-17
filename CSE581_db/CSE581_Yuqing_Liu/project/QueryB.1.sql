SELECT LastName + ', ' + EmailAddress AS FullName
FROM Customers
WHERE LEFT(LastName,1) BETWEEN 'A' AND 'H'
ORDER¡¡BY LastName DESC;