______________________________________________________________________
Fall 2021  CIS 623 

Solution outline to Quiz 5 
______________________________________________________________________


> import Prelude hiding (reverse, (++)) 

______________________________________________________________________



> reverse    :: [a] -> [a]
> reverse []     = []                 -- reverse.1 
> reverse (x:xs) = reverse xs ++ [x]  -- reverse.2


> (++) :: [a] -> [a] -> [a]
> [] ++ ys     = ys                -- ++.1
> (x:xs) ++ ys = x : (xs ++ ys)    -- ++.2
 

prop.1:

(xs ++ ys) ++ zs  = xs ++ (ys ++ zs)      for all finite lists xs, ys 

prop.2:  

xs ++ []  = xs = [] ++ xs                 for all finite lists xs   


a. 

reverse [x] 
={[x] = x:[]}
reverse x:[]
={reverse.2}
reverse [] ++ [x]
={reverse.1}
[] ++ [x]
= {++.1}
[x]


-----

b. 

Given:

P:   reverse (xs ++ ys) = reverse  ys ++ reverse xs    

for any finite lists  xs, ys


We show that 

reverse (xs ++ ys) = reverse  ys ++ reverse xs    

is true for all finite lists xs by induction on xs.
Note that ys is an arbitrary finite list.


Proof (by Induction on xs)

a. Base case

Case xs = []

LHS
={def}
reverse ([] ++ ys) 
={++.1}
reverse ys


RHS
={def} 
reverse  ys ++ reverse []
={reverse.1}
reverse ys ++ []
={prop.2}
reverse ys 


Hence, LHS = RHS for the base case







b. Induction Step

Case (x:xs)


LHS
={def}
reverse((x:xs) ++ ys)
={++.2}
reverse(x:(xs ++ ys))
={reverse.2}
reverse (xs ++ ys) ++ [x]
={induction assumption}
(reverse ys ++ reverse xs) ++ [x]
={prop.1}
reverse ys ++  (reverse xs ++ [x])
={reverse.2}
reverse ys  ++ reverse (x:xs)
={def}
RHS

Hence, P is true for any finite lists xs, ys.




