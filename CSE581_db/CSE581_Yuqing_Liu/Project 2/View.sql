USE [States MD Urgent Care Center]
GO 

CREATE VIEW EquipmentDiverse
AS
SELECT Center.CenterID, Center.CenterName, Center.CenterAddress, MedicalEquipment.EquipmentType AS Totaltypes
FROM MedicalEquipment JOIN Center 
     ON Center.CenterID = MedicalEquipment.CenterID
WHERE EquipmentType > 3

GO

SELECT¡¡* FROM
EquipmentDiverse