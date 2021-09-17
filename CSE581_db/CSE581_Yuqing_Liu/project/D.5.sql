USE MyGuitarShop
GO

IF OBJECT_ID('fnDiscountPrice') IS NOT NULL
 DROP FUNCTION fnDiscountPrice
GO

CREATE FUNCTION fnDiscountPrice (@ItemID INT)
RETURNS MONEY
BEGIN
RETURN ( SELECT SUM(ItemPrice-DiscountAmount) AS 'DiscountPrice'
         FROM OrderItems
         WHERE @ItemID = ItemID
		 GROUP BY ItemID)
END
GO

PRINT 'Total value:$'+ CONVERT(varchar,dbo.fnDiscountPrice(2),1);


