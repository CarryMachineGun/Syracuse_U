USE¡¡Shopping
CREATE TABLE CustomerGroups
(CustomerID INT REFERENCES Customers(CustomerID),
ProductID INT REFERENCES Products(ProductID),
UNIQUE(CustomerID,ProductID))
