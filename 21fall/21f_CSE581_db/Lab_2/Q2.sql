-- select last name, first name as 'Name'
select Employees.LastName + ',' + Employees.FirstName AS Name, 
-- Select department number as 'DeptNumber'
	Employees.DeptNo AS DeptNumber 
-- from Employees table
from Examples.dbo.Employees
-- pick up the customers who has department number of 2
where DeptNo = 2;