USE MyGuitarShop;

GO

CREATE PROC spUpdateProductDiscount
@ProductID_in int = 0,
@DiscountPrecent_in money = 0
AS
IF @DiscountPrecent_in < 0
	THROW 50002, 'DISCOUNT PRECENT MUST BE POSITIVE!!!',1;
UPDATE Products
	SET DiscountPercent = @DiscountPrecent_in
	WHERE ProductID = @ProductID_in;

GO

EXEC spUpdateProductDiscount @ProductID_in = 1, @DiscountPrecent_in = 10;
EXEC spUpdateProductDiscount @ProductID_in = 2, @DiscountPrecent_in = -10;

GO

SELECT * FROM Products;
