CIS 623 Spring 2021 

----------------------------------------
Solution outline to Test 2 version A
----------------------------------------

Question 1 (Total: 20 point)

a. (15 point)

-- find x which makes f(x) = x
--    | (x == f x) = x
--    | otherwise = fixedpt f (f x)

> fixedpt     :: (Eq a) => (a -> a) -> a -> a
> fixedpt f x 
>     | (x == y)  = x             --fixedpt.1
>     | otherwise = fixedpt f y   --fixedpt.2
>     where 
>       y = f x

-- minor error: 11-13 
-- major error: 8-10
-- conceptual error: 6-7
-- attempted but not making sense: 4-5 


b. (5 point)

> safetail    :: [a] -> [a]
> safetail []     = []      -- safetail.1
> safetail (x:xs) = xs      -- safetail.2

--------------------------------------------------------------------------------

fixedpt safetail [1,2,3]
={fixedpt.2 because safetail [1,2,3] = [2,3] and not equals to [1,2,3]}                 
fixedpt safetail [2,3]
={fixedpt.2 because safetail [2,3] = [3] and not equals to [2,3]}                 
fixedpt safetail [3]
={fixedpt.2 because safetail [3] = [] and not equals to [3]}
fixedpt safetail []
={fixedpt.1 because safetail [] = []}                 
[]

-- reasons missing: 3
-- wrong evaluation: 2


-- End of Question 1
---------------------------------------------------

Question 2 (Total: 20 point)

a. (10 point)

> applyfunsa      :: [a->b] -> a -> [b]
> applyfunsa []     x    = []
> applyfunsa (f:fs) x = (f x):(applyfunsa fs x)

-- minor error: 7-8 
-- major error: 5-6
-- conceptual error: 4
-- attempted but not making sense: 3 


b. (10 point)

> applyfunsb      :: [a->b] -> a -> [b]
> applyfunsb fs     x = map (\f -> f x) fs

-- minor error: 7-8 
-- major error: 5-6
-- conceptual error: 4
-- attempted but not making sense: 3 

-- End of Question 2
---------------------------------------------------

Question 3 (Total: 20 point)

> data Shapes = Circle Float | Rect Float Float | Tri Float Float Float
>               deriving  Show

a.

> dropcircle    :: [Shapes] -> [Shapes]
> dropcircle []                = []
> dropcircle ((Circle r1):ts)    = dropcircle ts
> dropcircle (z:ts)   = (z:dropcircle ts)

-- minor error: 7-8 
-- major error: 5-6
-- conceptual error: 4
-- attempted but not making sense: 3 

b.

> selectCircle    :: [Shapes] -> [Shapes]
> selectCircle [] = []
> selectCircle ((Circle r1):ts) = ((Circle r1):selectCircle ts)  
> selectCircle (_:ts)           = selectCircle ts  

-- minor error: 7-8 
-- major error: 5-6
-- conceptual error: 4
-- attempted but not making sense: 3 

-- End of Question 3
---------------------------------------------------

Question 4 (Total: 20 point)


> data LIT = Var Char | NVar Char
>          deriving Show

> type DJS = [LIT]
> type CNF = [DJS]

> type Subst     = Assoc Char Bool
> type Assoc k v = [(k,v)]

> find     :: Eq k => k -> Assoc k v -> v
> find k t = head [ v | (k',v) <- t, k == k']


a.

CNF is a list of DJS, and a list of lists of LIT

> phi1 :: CNF
> phi1 = [[(Var 'p'), (NVar 'q')], [NVar 'p', NVar 'q']]

> phi11 :: DJS
> phi11 = [(Var 'p'), (NVar 'q')]

> phi12 :: DJS
> phi12 = [NVar 'p', NVar 'q']

phi1 = [phi11, phi12]

> phi2 :: CNF
> phi2 = [[(Var 'p'), (Var 'q')], [NVar 'p', Var 'q']]

> phi21 :: DJS
> phi21 = [(Var 'p'), (Var 'q')]

> phi22 :: DJS
> phi22 = [NVar 'p', Var 'q']

phi2 = [phi21, phi22]

-- minor error: 4
-- major errot: 2



b.

> evaldnf      :: Subst -> DJS -> Bool
> evaldnf s [(Var x)]     =  find x s
> evaldnf s [(NVar x)]    =  not (find x s)
> evaldnf s (v:ds)  =  (evaldnf s [v]) || (evaldnf s ds)
> evaldnf s []           =  False

False 'or' p = p

> evalcnf      :: Subst -> CNF -> Bool
> evalcnf s [ds]     = evaldnf s ds
> evalcnf s (ds:dss) = (evaldnf s ds) && (evalcnf s dss)

-- minor error: 10-12
-- major error: 7-9
-- conceptual error: 5-6
-- attempted but not making sense: 4 

-- End of Question 4
---------------------------------------------------

> s1 = [('p', True), ('q', False)]
> s2 = [('p', False), ('q', True)]

find 'p' s1
find 'q' s2

evaldnf s1 phi11

evaldnf s2 phi11