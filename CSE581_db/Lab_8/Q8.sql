DECLARE @TableName VARCHAR(120)
DECLARE @DynamicSQL VARCHAR(8000)

SET @TableName = (SELECT TOP 1 sys.tables.name
				FROM sys.tables WHERE sys.tables.name NOT IN ('dtproperties', 'sysdiagrams')
				ORDER BY sys.tables.name)
SET @DynamicSQL = ' SELECT COUNT(*) AS CountOf' + @TableName + ' from ' + @TableName + ';';
EXEC(@DynamicSQL)
