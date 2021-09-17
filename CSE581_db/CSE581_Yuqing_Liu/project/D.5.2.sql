USE MyGuitarShop
GO

IF OBJECT_ID('fnItemTotal') IS NOT NULL
 DROP FUNCTION fnItemTotal
GO

CREATE FUNCTION fnItemTotal (@ItemID INT)
RETURNS money
BEGIN
RETURN ( SELECT SUM(ItemPrice*Quantity-DiscountAmount*Quantity) AS TotalAmountofItem
         FROM OrderItems
         WHERE @ItemID = ItemID
         GROUP BY ItemID,Quantity)
END
GO

PRINT 'Total value:$'+ CONVERT(varchar,dbo.fnItemTotal(3),1);