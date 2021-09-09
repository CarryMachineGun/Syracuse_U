 DECLARE @Number1 INT = 15
 DECLARE @Number2 INT = 30
 DECLARE @Number3 INT = 1
 PRINT 'Common factors of 15 and 30'
 WHILE @Number3 <= 15
 BEGIN 
 IF (@Number1%@Number3= 0)AND( @Number2%@Number3=0)
 PRINT @Number3
 SET @Number3=@Number3+1
 END
 GO