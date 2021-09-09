SELECT * 
FROM Customers
WHERE EmailAddress = 'kriegerrobert@gmail.com';

UPDATE Customers
SET Password = 'secret@1234'
WHERE EmailAddress = 'kriegerrobert@gmail.com';

SELECT * 
FROM Customers
WHERE EmailAddress = 'kriegerrobert@gmail.com';