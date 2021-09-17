SELECT ListPrice,
    CAST (ListPrice AS DECIMAL(7,2) ) AS ListPriceDecimal,
	CAST (ListPrice AS REAL ) AS ListPriceReal,
	CONVERT (INT, ListPrice ) AS ListPriceInt
	FROM Products;