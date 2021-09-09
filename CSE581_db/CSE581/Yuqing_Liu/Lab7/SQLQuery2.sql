USE Shopping
CREATE TABLE Customers
(CustomerID INT PRIMARY KEY¡¡IDENTITY,
FirstName VARCHAR(50) NOT NULL,
LastName VARCHAR(50) NOT NULL,
Phone VARCHAR(50) NOT NULL)

CREATE TABLE Products
(ProductID INT PRIMARY KEY IDENTITY,
ProductsName VARCHAR(50) NOT NULL,
ProductCost MONEY NOT NULL DEFAULT 0 CHECK (ProductCost>=0))

CREATE TABLE CustomerGroups
(CustomerID INT REFERENCES Customers(CustomerID),
ProductID INT REFERENCES Products(ProductID));


