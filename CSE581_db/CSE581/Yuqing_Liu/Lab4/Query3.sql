SELECT *
FROM VendorCopy
WHERE DefaultAccountNo = 572;
UPDATE VendorCopy
SET DefaultAccountNo = 542
WHERE DefaultAccountNo = 572;
SELECT * 
FROM VendorCopy
WHERE DefaultAccountNo = 542;
