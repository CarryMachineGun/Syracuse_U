--SELECT *

SELECT (CustomerFirst + ' ' + LEFT(CustomerLast, 1) + '.') AS ContactName,
	RIGHT(CustPhone, 8) AS ContactPhone
FROM Examples.dbo.Customers
WHERE CONVERT(int, SUBSTRING(CustPhone, 2,3)) = 309
ORDER BY CustomerFirst;