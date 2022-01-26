-- select CustomerFirst, CustState
SELECT Customers.CustomerFirst, Customers.CustState
-- from Customers table
FROM Examples.dbo.Customers
-- CustState have to be 'IL'
WHERE CustState = 'IL'
UNION
-- select CustomerFirst and make 'Not' in IL as CustState
SELECT Customers.CustomerFirst, 'Not in IL' AS CustState
-- from Customers table
FROM Examples.dbo.Customers
-- CustState can not be 'IL'
WHERE NOT CustState = 'IL'
-- Order rows with CustLastFirst descendingly
ORDER BY CustomerFirst DESC;