USE MyGuitarShop;

GO

PRINT 'Item Total:$' + CONVERT(VARCHAR, dbo.fnItemTotal(7), 1);