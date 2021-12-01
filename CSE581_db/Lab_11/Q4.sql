USE AP;

GO
CREATE SCHEMA Yuchen_Wang;

GO
ALTER SCHEMA Yuchen_Wang TRANSFER dbo.ContactUpdates;

ALTER USER Mark WITH DEFAULT_SCHEMA = Yuchen_Wang;

GRANT SELECT, UPDATE, DELETE, EXECUTE, INSERT ON SCHEMA :: Yuchen_Wang TO Mark;