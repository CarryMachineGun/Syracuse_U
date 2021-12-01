-- select salsYear and sum of salesToal
SELECT SalesTotals.SalesYear, SUM(SalesTotals.SalesTotal) AS [sum of sales]
FROM Examples.dbo.SalesTotals
-- Group sum of salesTotal by salesYears with rollUp
GROUP BY SalesTotals.SalesYear WITH ROLLUP;
