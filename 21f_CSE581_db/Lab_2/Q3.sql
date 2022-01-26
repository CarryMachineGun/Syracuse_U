-- select customer last name and first name as 'Full Name'
SELECT CustomerFirst + ' ' + CustomerLast AS [Full Name]
-- from Customers table
FROM Examples.dbo.Customers
-- 'Full Name' is ordered by first character
ORDER BY CustomerFirst;