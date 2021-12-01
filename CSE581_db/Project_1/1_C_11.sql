USE MyGuitarShop;

UPDATE Customers
SET Password = 'secret@1234'
WHERE EmailAddress = 'kriegerobert@gmail.com'

SELECT * FROM Customers;