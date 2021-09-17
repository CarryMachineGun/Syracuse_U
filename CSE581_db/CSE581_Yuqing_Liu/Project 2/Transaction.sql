USE [States MD Urgent Care Center]
GO

IF EXISTS ( SELECT*FROM sys.triggers
    WHERE object_id = OBJECT_ID ('Insurance_UPDATE_company'))
DROP TRIGGER [dbo].[Insurance_UPDATE_company];
GO

BEGIN TRAN
UPDATE Insurance
SET PatientID = 1008
WHERE PatientID = 1005;

DELETE Insurance
WHERE PatientID = 1005;

UPDATE Insurance
SET Company = 'OMT'
WHERE PatientID = 1008;
COMMIT TRAN;

SELECT * FROM Insurance WHERE¡¡PatientID = 1008