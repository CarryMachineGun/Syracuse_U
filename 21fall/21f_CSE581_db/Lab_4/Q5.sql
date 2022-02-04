SELECT VendorID, VendorState
FROM AP.dbo.VendorCopy
ORDER BY VendorState;

--DELETE AP.dbo.VendorCopy
--WHERE VendorState = 'NY';