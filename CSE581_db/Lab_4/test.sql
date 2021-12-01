SELECT 
CAST(PaymentTotal AS decimal(17,4)) AS CastASDecimal,
CAST(PaymentTotal AS VARCHAR) AS CastAsVarchar,
CONVERT(DECIMAL(17, 4), PaymentTotal) AS ConvertToDecimal,
CONVERT(VARCHAR,PaymentTotal, 5) AS ConvertToVarchar
FROM AP.dbo.Invoices;