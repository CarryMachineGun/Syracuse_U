SELECT CardNumber, LEN(CardNumber) AS LengthOfCardNumber,
SUBSTRING(CardNumber,11,6) AS LastSixDigitsOfCardNumber,
CONCAT('XXXX-XXXX-XX',SUBSTRING(CardNumber,11,2),'-',SUBSTRING(CardNumber,13,4)) AS FormatCardNumber
FROM Orders;