SELECT TOP 5 Artist , SUM(UnitPrice) AS TotalEarnings
FROM Items
GROUP BY Artist
ORDER BY TotalEarnings;
