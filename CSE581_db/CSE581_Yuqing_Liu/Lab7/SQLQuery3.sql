USE Shopping
CREATE CLUSTERED INDEX IndexofProductID
ON CustomerGroups(ProductID)
CREATE INDEX IndexofCustomerID
ON CustomerGroups(CustomerID);
