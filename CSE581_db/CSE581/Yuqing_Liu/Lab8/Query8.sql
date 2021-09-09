USE AP
DECLARE @TableName VARCHAR(120)
DECLARE @DynmicSQL VARCHAR(8000)

SET @TableName = (SELECT TOP 1 sys.tables.name 
                  FROM sys.tables WHERE sys.tables.name NOT IN ('dtproperties' , 'sysdiagrams')
				  ORDER BY sys.tables.name)
SET @DynmicSQL= ' SELECT COUNT(*) AS CountOfTable FROM ' + @TableName + ';'
PRINT @TableName;
EXEC(@DynmicSQL)
