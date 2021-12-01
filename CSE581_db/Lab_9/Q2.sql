USE AP;

EXEC spBalanceRange @VandorVar = 'F%';

GO

EXEC spBalanceRange @BalanceMin = 100, @BalanceMax = 1000;

GO

EXEC spBalanceRange '[F,G,H,I]%', 400, 600;