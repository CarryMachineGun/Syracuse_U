USE MyGuitarShop;

GO

CREATE FUNCTION fnDiscountPrice(@ItemID int)
	RETURNS MONEY

	BEGIN 
		RETURN(
			SELECT ItemPrice - DiscountAmount AS DiscountPrice
			FROM OrderItems
			WHERE ItemID = @ItemID);
	END;

GO

PRINT 'Discount Price is $' + CAST(dbo.fnDiscountPrice(5) AS varchar);

