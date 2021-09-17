DROP VIEW OrderItemProductsDetails
CREATE VIEW OrderItemProductsDetails
AS
SELECT  OrderID, OrderDate, TaxAmount, ShipDate,
        ItemPrice, DiscountAmount, 
        (ItemPrice-DiscountAmount) AS FinalPrice,
	    Quantity, (ItemPrice-DiscountAmount)*Quantity AS ItemTotal
		ProductName, Description
FROM Orders JOIN OrderItems ON Orders.OrderID = OrderItems.OrderID
      JOIN Products ON OrderItems.ProductID = Products.ProductID
