CREATE VIEW OrderItemProductsDetails
AS
SELECT Orders.OrderID, OrderDate, TaxAmount, ShipDate
       ItemPrice, DiscountAmount, Quantity,
       (ItemPrice-DiscountAmount) AS FinalPrice,
	   (ItemPrice-DiscountAmount)*Quantity AS ItemTotal,
	   ProductName, Description
FROM Orders join OrderItems ON Orders.OrderID = OrderItems.OrderID 
    JOIN Products ON Products.ProductID = OrderItems.ProductID;
