
-- Derived from the tautology.hs example from chapter 8 
-- of Programming in Haskell,
-- Graham Hutton, Cambridge University Press, 2016.


-- part a
-- Based on definition from HR Ch.1 formula (1.3)

data Formula = Var Char
             | Not Formula
             | And Formula Formula 
             | Or Formula Formula 
             | Imply Formula Formula 
               deriving (Show)  -- not required for answers

---------------------------------------------------------------------

-- part b
-- Base on HR Ch.1, section 5

implfree         :: Formula -> Formula 
implfree (Var x) = (Var x)
implfree (Not f)   = Not (implfree f)
implfree (And f g) = And (implfree f) (implfree g) 
implfree (Or f g)    = Or (implfree f) (implfree g) 
implfree (Imply f g) = Or (Not (implfree f)) (implfree g) 


---------------------------------------------------------------------

-- part c

nnf         :: Formula -> Formula
nnf (Var x)       = (Var x)
nnf (Not (Var x)) = Not (Var x) 
nnf (Not (Not f)) = nnf f
nnf (And f g)     = And (nnf f) (nnf g) 
nnf (Or f g)        = Or (nnf f) (nnf g) 
nnf (Not (And f g)) = Or (nnf (Not f)) (nnf (Not g)) 
nnf (Not (Or f g))  = And (nnf (Not f)) (nnf (Not g)) 

---------------------------------------------------------------------

-- part d

distr               :: Formula -> Formula -> Formula
distr (And p1 p2) q = (And (distr p1 q) (distr p2 q))
distr p (And q1 q2) = (And (distr p q1) (distr p q2))
distr p q           = (Or p q)

cnf :: Formula -> Formula  
cnf (Var x)       = (Var x)
cnf (Not (Var x)) = (Not (Var x)) 
cnf (And p q)     = (And (cnf p) (cnf q))
cnf (Or p q)      = distr (cnf p) (cnf q)
cnf p             = p

---------------------------------------------------------------------

p0 :: Formula
p0 = Or ((And (Var 'A') (Var 'B'))) (Not (Or (Var 'A') (Var 'B')))

p1 :: Formula
p1 = And (Var 'A') (Not (Var 'A'))

p2 :: Formula
p2 = Imply (And (Var 'A') (Var 'B')) (Var 'A')

p3 :: Formula
p3 = Imply (Var 'A') (And (Var 'A') (Var 'B'))

p4 :: Formula
p4 = Imply (And (Var 'A') (Imply (Var 'A') (Var 'B'))) (Var 'B')

