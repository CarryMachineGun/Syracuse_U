USE MyGuitarShop;

SELECT CardNumber,
LEN(CardNumber) AS LengOfCardNumber,
RIGHT(CardNumber, 5) AS LastFiveDigit,
'XXXX-XXXX-XXX' + SUBSTRING(CardNumber, 12, 1) + '-' + RIGHT(CardNumber, 4) AS XCardNumber
FROM Orders