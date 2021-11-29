Steps of induction?
1. Determine the statment P(n) that you are going to prove
2. Base case: demonstrate that P(0) is true
3. Inductive case:
	3.1 state the assumption - P(n) is true
	3.2 Based on the assumption, we need to prove that P(n+1) is true
4. State P(n) is true for any 'n'

--------------------------------------------
Example 1:
Given
> data Nat = Zero | Succ Nat
>            deriving Show 

> add        :: Nat -> Nat -> Nat
> add Zero m     = m                -- add.1 
> add (Succ n) m = Succ (add n m)   -- add.2

Show that 'add' function is associative using induction. That is, show 'add x (add y z) = add (add x y) z'.

solution:
P(n): 'add n (add y z) = add (add n y) z' is true for any n

Base case:
when n = Zero
LHS = add Zero (add y z)   RHS = add (add Zero y) z
	= {apply add.1}			   = {apply add.1}
	  add y z				     add y z
	  
	  LHS = RHS, so the base case is true
	  
Inductive case:
Assume that 'add n (add y z) = add (add n y) z' is true for any n -- hypothesis

now, we need to prove that 'add (Succ n) (add y z) = add (add (Succ n) y) z' is true

LHS = add (Succ n) (add y z)
    = {apply add.2}
	  Succ (add n (add y z)) 
	= {induction hypothesis} -- this is a must, if you didnt use the hypothesis during the proof, there must be some error
	  Succ (add (add n y) z) -- in RHS of add.2, 'n' is (add n y), 'm' is z
	= {apply add.2}
	  add (Succ (add n y)) z -- in (Succ (add n y)), we apply add.2
	= {apply add.2}         
	  add (add (Succ n) y) z
	= RHS
	so, the inductive case is true
	
Therefore, 'add n (add y z) = add (add n y) z' is true for any n

------------------------------------------------------------------------
Example 2:

Given 
replicate :: Int -> a -> [a]
replicate 0 _ = []                    -- replicate.1
replicate n x = x : replicate (n-1) x -- replicate.2

length :: [a] -> Int
length [] = 0					-- length.1
length (x:xs) = 1 + length xs   -- length.2

Prove that 'length (replicate n x) = n for any n >= 0' by induction.

solution:

P(n): 'length (replicate n x) = n for any n >= 0' is true

Base case:
when n = 0
LHS = length (replicate 0 x)
	= {apply replicate.1}
	  length []
	= {apply length.1}
	   0
	= RHS
	so, the base case is true
	
Inductive case:

Assume 'length (replicate n x) = n for any n >= 0' is true -- hypothesis
We need to prove 'length (replicate (n+1) x) = n+1' 

-- make P(n) appears in P(n+1)

LHS = length (replicate (n+1) x)
	= {replicate.2}
	  length (x : replicate n x)
	= {length.2}
	  1 + length (replicate n x)
	= {induction hypothesis}
	  1 + n
	= RHS
	so, the inductive case is true
	
Therefore, 'length (replicate n x) = n for any n >= 0' is true

--------------------------------------------------------------------
Example 3:
Given
exp :: Num a => a -> Int -> a
exp x 0 = 1                -- exp.1
exp x (n+1) = x * exp x n  -- exp.2

Prove 'exp x (m+n) = exp x m * exp x n' using induction.

solution:
P(m): 'exp x (m+n) = exp x m * exp x n' is true for any 'm'

Base case:
when m = 0
LHS = exp x (0+n)    RHS = exp x 0 * exp x n
	= {0+n = n}			 = {exp.1}
	  exp x n			   1 * exp x n
						 = {1*x = x}
						   exp x n
						   
	so, LHS = RHS, the base case is true
	
Inductive case:
Assume that 'exp x (m+n) = exp x m * exp x n' is true for any 'm' -- hypothesis

we need to prove 'exp x ((m+1)+n) = exp x (m+1) * exp x n'

LHS = exp x ((m+1)+n)
	= {(m+1)+n = (m+n)+1}
	  exp x ((m+n)+1)
	= {exp.2}
	  x * exp x (m+n)
	= {induction hypothesis}
	  x * exp x m * exp x n
	= {exp.2}
	  exp x (m+1) * exp x n
	= RHS
	so, the inductive case is true
	
therefore......


