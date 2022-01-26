Number:      50 
Last Name:   Andrew 
First Name:  Lee

> import Prelude hiding (exp, reverse)

----------
Question 1
----------

The natural numbers are defined in Haskell language as the data type: 

> data Nat = Zero | Succ Nat

and the exponential function exp is defined, in Haskell, as follows:

> exp        :: Num a => a -> Nat -> a
> exp x Zero     = 1       -- exp.1
> exp x (Succ n) = exp x n -- exp.2

Let P(n) be the proposition:  P(n):  exp x (m+n) = exp x m * exp x n

where x is of type a, and, m, n are natural numbers.  

Convention:  As in Bird's text, we will write 0 for Zero and n+1 for Succ n 
in the following proof. In addition, we will use the usual arithmetic 
properties of natural numbers (without proof) and for various instances of
the type class Num.


We will prove the following: 

------------------------------------------------------------
Proposition:      P(n) is true for any natural numbers n.
------------------------------------------------------------





























------------------------------------------------------------
Proposition:      P(n) is true for any natural numbers n.
------------------------------------------------------------

Proof:

Base case: We show that P(0), holds. That is:

     exp x (m+0) = exp x m + exp x 0   

holds for any x of type a and for any natural numbers m.

Case 0:  (Base Case)

LHS of P(0)
={definition}
exp x (m+0) 
={m+0=m for any natural number m}
exp x m

RHS of P(0)
={definition with n = 0}
exp x m + exp x 0
={exp.1}
exp x m * 1
={arithmetic}
exp x m

LHS of P(0) = RHS of P(0).   Therefore P(0) holds.

Case n+1:  (Induction step)

-- Note: We assume the (induction hypothesis) P(n) is true for
-- some natural number n. That is: exp x (m+n) = exp x m * exp x n

LHS of P(n+1)
={definition}
exp x (m+(n+1))
={exp.2 since Succ n = n+1} 
exp x ((m + n) + 1)
={exp.2}
x * exp x (m + n)
={induction hypothesis}
x * exp x m * exp x n

RHS of P(n+1)
={definition}
exp x m * exp x (n+1)
={exp.2}
exp x m * (x * exp x n)
={* is associative}
(exp x m * x) * exp x n
={* is commutative and associative}
x * exp x m * exp x n

Hence LHS = RHS in P(n+1). By the principle of mathematical induction, 
P(n) is true for all natural numbers n.
 






----------
Question 2
----------

We summarize, based on the presentation in section 16.6 (Hutton), the steps 
that transform the reverse function (*) 

> reverse    :: [a] -> [a]                    --- (*)
> reverse []     = []                         --- r.1 
> reverse (x:xs) = reverse xs ++ [x]          --- r.2

to a guess function (reverse' function in our text)  (**)

g       :: [a] -> [a] -> [a]  --- (**)
g [] ys     =                 --- g.1
g (x:xs) ys =                 --- g.2 

where g is going to relate to the function reverse and the append operator (++)

which will lead to an alternate implementation of the reverse function named 
as reverse2 (***)

> reverse2    :: [a] -> [a]  --- (***)
> reverse2 xs =  g xs []     --- r2.1 


1 Motivation

The function reverse, given in (*), use the append operator (++) in the 
recursion step (equation r.2) to reverse the elements in a finite list with 
elements that are of type a.
 
Since (++) use linear time in the length of its first argument xs to evaluate 
(++), the function reverse takes quadratic time in the length of its argument 
xs to compute reverse xs.


2. Guess 

We create a guess function 

g :: [a] -> [a] -> [a]

where (xs, ys are of type [a])

g xs ys = reverse xs ++ ys  (****)

to relate the function reverse (see (*)) and the append operator ++


3. Specification

Using the function g, we specify our desired solution as:

reverse2 :: [a] -> [a]
reverse2 = g xs []

4. Apply mathematical induction to construct the definition of g

Mathematical induction are employed (see text page 238-239) to obtain the 
line g.1 and g.2.  The results obtained are:

> g       :: [a] -> [a] -> [a]  --- (**)
> g [] ys     = ys                 --- g.1
> g (x:xs) ys = g xs (x:ys)        --- g.2 

g.1 produces result that is consistent with the equation (****)
g.2 will not lead to infinite loop and 
    will not use other operations (no append operation) excepts cons (:)

5.  Let P be the proposition

P(xs):    g xs ys  = reverse xs ++ ys (#)

We prove, by mathematical induction on xs, that P(xs) is true for all 
finite lists xs, ys in type [a].

Proof: (by mathematical induction on xs).

Case 0: xs is []  (Base case)

LHS                                     RHS               
= {defined in (#)}                      ={defined in (#)}                                           
g [] ys                                 reverse [] ++ ys        
= {g.1}                                 ={(++).1}         
ys                                      ys                 

As LHS = RHS when xs = [], base case hold.

Induction assumption: P(xs) is true for some xs and for any ys
That is    

          g xs ys  = reverse xs ++ ys  for any ys

Case (x:xs)

LHS                                     RHS
= {by (#), first input is (x:xs)}       = {use (#)}         
g (x:xs) ys                             reverse (x:xs) ++ ys  
= {g.2}                                 = {r.2} 
g xs (x:ys)                             (reverse xs ++ [x]) ++ ys                
= {induction assumption}                = {(++) is associative}
reverse xs ++ (x:ys)                    reverse xs  ++ ([x] ++ ys)
                                        ={[x] = x:[]}
                                        reverse xs  ++ ((x:[]) ++ ys)
                                        ={(++).2}
                                        reverse xs  ++ ((x:([] ++ ys))
                                        ={(++).1}
                                        reverse xs  ++ (x:ys)
                                                          
As LHS = RHS when the first input is (x:xs), the inductive step also hold.
By the principle of mathematical induction, P(xs) holds for all finite
lists xs.

Our proof use the definition of (++) shown in the prelude (B.8 page 286)

(++) :: [a] -> [a] -> [a]
    [] ++ ys = ys              -- (++).1
(x:xs) ++ ys = x : (xs ++ ys)  -- (++).2


5.  Using `reverse2` to reverse a list of n elements takes linear 
    (i.e. O(n)) time because total number steps 2n+2 = O(n) (see below)

    reverse2 [x1, ..., xn]
    = -- 1 step
    g [x1, ..., xn]    
    = .. n steps
    g [] (xn:(...(x2:(x1:[])) ...))     
    = .. 1 step
    (xn:(...(x2:(x1:[])) ...))     
    = .. n steps
    [xn, .., x1]


--------------------------------------------------------------------------------

