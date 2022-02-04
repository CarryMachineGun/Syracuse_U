SELECT 
CAST(PaymentDate AS VARCHAR) AS CastAsVarchar,
CONVERT(VARCHAR, PaymentDate, 1) AS CastAsVarchar_1,
CONVERT(VARCHAR, PaymentDate, 9) AS CastAsVarchar_9,
CAST(PaymentDate AS real) AS RealType
FROM AP.dbo.Invoices;