DECLARE @CURR int = 1;
DECLARE @A int = 32; 
DECLARE @B int = 4;

PRINT 'Common factors of ' + CAST(@A AS char(2)) + ' and ' + CAST(@B AS char(2));
WHILE(@CURR <= @A AND @CURR <=@B)
BEGIN
	IF(@A % @CURR = 0 AND @B % @CURR = 0)
		PRINT @CURR;
	SET @CURR = @CURR + 1;
END
