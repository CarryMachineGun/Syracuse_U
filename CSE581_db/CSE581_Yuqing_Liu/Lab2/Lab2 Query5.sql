SELECT  VendorName, VendorCity AS 'city', VendorZipCode AS 'zipcode' , DefaultAccountNo AS 'account number', AccountDescription AS 'account description'
FROM Vendors LEFT JOIN GLAccounts 
ON Vendors.DefaultAccountNo = GLAccounts.AccountNo
WHERE AccountDescription = 'Other Equipment'
ORDER BY VendorCity DESC;
