USE AP
EXEC spBalanceRange @VendorVar = 'C%'
GO

EXEC spBalanceRange @BalanceMin = 300, @BalanceMax = 600
GO

EXEC spBalanceRange @BalanceMin = 50, @BalanceMax = 250, @VendorVar = '[AB]%'
GO
    