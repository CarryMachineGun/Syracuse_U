USE MyGuitarShop
IF OBJECT_ID('spUpdateProductDiscount') IS NOT NULL
 DROP PROC spUpdateProductDiscount
GO

CREATE PROC spUpdateProductDiscount 
@ProductID INT , @DiscountPercent FLOAT
AS
BEGIN 
 IF EXISTS(SELECT*FROM Products WHERE ProductID=@ProductID) AND @DiscountPercent >= 0
   Update Products
   SET DiscountPercent = @DiscountPercent;
 ELSE
   THROW 50001, 'The value DiscountPercent must be a postive number.',1;
END
GO


USE MyGuitarShop
EXEC spUpdateProductDiscount @ProductID=1, @DiscountPercent = '15';
GO

USE MyGuitarShop
EXEC spUpdateProductDiscount @ProductID=5, @DiscountPercent = '-20';
GO
