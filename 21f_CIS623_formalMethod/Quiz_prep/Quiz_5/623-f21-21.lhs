----------------------------------------------------------------------

CIS 623
Lecture 21  haskell script: 623-f21-21.lhs

----------------------------------------------------------------------

> import Prelude hiding ( reverse, (++) )

----------------------------------------------------------------------


1. Induction proofs: an review

We have covered a number properties regarding known haskell functions 
(eg. map, reverse etc.) that can be proven by mathematical induction
and presented using (Feijen/equation reasoning) notations. 

For example:

(See Lecture 18)

Given:

> data Nat = Zero | Succ Nat
>            deriving Show 

> add        :: Nat -> Nat -> Nat
> add Zero m     = m                -- add.1 
> add (Succ n) m = Succ (add n m)   -- add.2

(a). The function add is associative  

Hutton: Section 16.4 (page 231 -234)

(b). length (replicate n x) = n for any n >= 0

Hutton: Section 16.4 (page 231 -234)

(c). (Bird, 6.1. Page 110 -112)
  
   exp x (m+n) = exp x m * exp x n

for all x, m and n by induction on m.


----------------------------------------------------------------------

(Lecture 19)

(d). Given

> reverse    :: [a] -> [a]
> reverse []     = []                 -- reverse.1 
> reverse (x:xs) = reverse xs ++ [x]  -- reverse.2



> (++) :: [a] -> [a] -> [a]
> [] ++ ys     = ys                -- ++.1
> (x:xs) ++ ys = x : (xs ++ ys)    -- ++.2


Prove that: 

reverse . reverse xs = xs   for any finite list xs.  ---(*)

Remarks:  There are at least two different ways to prove (*):

we needs additional facts:

Approach 1. (Bird 6.2; page 113 -115)

We need to prove the following auxilary result:

reverse (ys ++ [x]) = [x] ++ reverse ys  for all 

finite lists ys


Approach 2: (Hutton 16.5. Page 234 - 236)

This approach uses:

a. reverse [x] = [x] for any x 

b. reverse (xs ++ ys) = reverse ys ++ reverse xs

where proving part b uses the fact that (++) is associative
with [] as the identity.


----------------------------------------------------------------------

(e). Prove, by mathematical induction, that the functor laws of map 
holds for any finite lists (Hutton Section 16.5, page 234 - 237)

map id = id

map f . map g  = map  f . g

----------------------------------------------------------------------

A partial list is simply a list defined by (definition in Bird, 
Section 6.2)

1. undefined is a partial list

2. if xs is a partial list and x is an element in a
then x:xs is a partial list.

Therefore: proof rules for P(xs) is true FOR ALL
partial lists:

1. Show P(undefined) is true.
2. Assume P(xs) is true for some partial list,
   Deduce P(x:xs) is true.


> eg1 :: [Int]
> eg1 = 1:2:3:undefined

> eg2 :: [Int]
> eg2 = undefined

eg1 and eg2 are both partial lists.

(f). The concatenation operation (++) is associative, that is:

(xs ++ ys) ++ zs = xs ++ (ys ++ zs) 


for all partial list xs and for all lists ys, zs


----------------------------------------------------------------------

2. The universal property of foldr  (Hutton paper)

For any finite lists:

g []      = v
g (x:xs)  = f x (g xs)

<=> (IFF)

g = foldr f v


Remarks:  We can use The universal property of foldr as a 
proof method:


Eg. 

(+1) . sum  = foldr (+) 1


Steps: 

We want to apply the universal property of foldr 
(stated above) by setting 

g be the function (+1) . sum
f be the function additon (+)
1 be the value v


That is, we only need to show:

g [] = 1
g (x:xs) = x + g xs

(for simplicity, we omit many explanations 
and write {,,} instead. The explanations
can be found in Hutton paper).

g [] = 1 : 

g []
={..}
(+1) .sum []
={..}
(+1) 0
={..}
0 + 1
={..} 
1

g (x:xs) = x + g xs :

g (x:xs) 
={..}
(+1) . sum (x:xs)
={..}
sum (x:xs) + 1
={def. of sum}
(x + sum xs) + 1
={..}
(x + sum xs) + 1
={..}
x + (sum xs + 1)
={..}
x + (+1) . sum xs 
={..}
x + g xs 

----------------------------------------------------------------------

3. The maximum segment sum problem


Our goal is to use formal method to find an efficient solution 
O(n) to maximum segment sum problem.

In fact, maximum segment sum problem (and its variants)
is a famous example for the study of formal methods. In the
past, this class covers a dynamic programmming solution 
to it variants: 

Min sum section problem

where the tranditional formal methods are used. We will 
present this solution in class first to indicate that 
an O(n) solution is possible.


For the new approach (program calculation), 
Our final solution is (Bird, page 130)  

> mss = maximum . scanr (#) 0
>     where x # y = 0 `max` (x+y)

> mssl = scanr (#) 0
>     where x # y = 0 `max` (x+y)


> msseg = [-1,2,-3,5,-2,1,3,-2,-2,-3,5]
