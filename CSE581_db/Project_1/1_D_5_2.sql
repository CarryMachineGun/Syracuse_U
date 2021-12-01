USE MyGuitarShop;

GO

IF OBJECT_ID('fnItemTotal') IS NOT NULL
	DROP FUNCTION fnItemTotal;

GO

CREATE FUNCTION fnItemTotal(@ItemID int)
	RETURNS MONEY

	BEGIN 
		RETURN(
			SELECT dbo.fnDiscountPrice(@ItemID) * Quantity AS ItemTotal
			FROM OrderItems
			WHERE ItemID = @ItemID);
	END;

GO

PRINT 'Discount Price is $' + CAST(dbo.fnDiscountPrice(5) AS varchar);
PRINT 'Item Total is $' + CAST(dbo.fnItemTotal(5) AS varchar);

