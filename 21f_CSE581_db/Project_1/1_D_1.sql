USE MyGuitarShop;

GO

CREATE VIEW OrderItemProductsDetails
AS
SELECT 
Orders.OrderID, Orders.OrderDate, Orders.TaxAmount, Orders.ShipDate,
OrderItems.ItemPrice, OrderItems.DiscountAmount, (OrderItems.ItemPrice - OrderItems.DiscountAmount) AS FinalPrice, OrderItems.Quantity, (OrderItems.ItemPrice * OrderItems.Quantity) AS ItemTotal,
Products.ProductName,Products.Description
FROM Orders JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID
JOIN Products ON Products.ProductID = OrderItems.ProductID

GO 

SELECT * FROM OrderItemProductsDetails;
