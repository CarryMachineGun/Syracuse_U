> import Prelude hiding (replicate, foldr, map, filter)

import Prelude hiding (replicate, foldr, map, (.), filter)

-----------------------------------------------------------
Q1:

> import Data.Char

> let2int :: Char -> Int
> let2int c = ord c - ord 'a'

> int2let :: Int -> Char
> int2let n = chr (ord 'a' + n)

> f       :: [Int -> Int] -> Int -> Int
> f [] a     =  a
> f (g:gs) a =  g (f gs a)

> g       :: Int -> Int 
> g x     = x + x

> h    :: [a] -> [a]
> h []  = []
> h [x]      = [x]
> h (x:y:xs) = h xs

> lst :: [Float]
> lst = [1, 2, 3]

a. f [1, 2] 3

f :: [Int -> Int] -> Int -> Int
The first input of f should be a list containing functions of type (Int -> Int), 
whose is type is [Int -> Int]. 

The type of [1,2] is [Int], therefore it is an error.

b. h [g, g.g]

type of g is Int->Int
type of g.g is still Int->Int
so, the type of [g, g.g] is [Int->Int]. 
And the type of h [g, g.g] is [Int->Int].

c. h lst

The type of lst is [Float], so the type of h lst is [Float]

d. f [int2let . let2int] let2int 'c'

f :: [Int -> Int] -> Int -> Int

The type of [int2let . let2int] is [Char -> Char]. Therefore it is an error.

e. (g . g . let2int . int2let)

consider f.g.z, where f.g.z are three fucnctions
z's output must have same type with g's input.
g's output must have same type with f's input. Otherwise, there is an error.
The type of f.g.z will be ('the type of z's input'->'the type of f's output')

(g . g . let2int . int2let)'s type is 'the type of int2let's input' -> 'the type of g's input',
which is Int -> Int


f. f [f []]

type of f [] is [Int->Int]
so, the type of f [f []] is Int->Int

-----------------------------------------------------------------------------------

Q2:


> lastpos :: (Eq a) => (a -> a) -> (a -> a) ->[a] -> Int
> lastpos f g xs = h [i|(i, x)<-zip [0..] xs, f x /= g x]
>			where
>				h :: [Int] -> Int
>				h [] = -1
>				h xs = last xs

h xs = if xs /= [] then last xs else -1
------------------------------------------------------------------------------------

Q3:

> data BTree a = Nil | Vertex (BTree a) a (BTree a) deriving Show

1. 
> t0 :: BTree Int
> t0 = Nil

> t1 :: BTree Int
> t1 = Vertex t0 1 t0

> t2 :: BTree Int
> t2 = Vertex t0 2 t0

> t3 :: BTree Int
> t3 = Vertex t0 3 t0

2.
> numinrange :: (Ord a) => BTree a -> a -> a -> Int
> numinrange Nil x y = 0
> numinrange (Vertex lt z rt) x y 
>			| (x <= z) && (z <= y)  = 1 + numinrange lt x y + numinrange rt x y
>			| otherwise             = numinrange lt x y + numinrange rt x y

------------------------------------------------------------------------------------

Q4:

1. 

> foldr        :: (a -> b -> b) -> b -> [a] -> b
> foldr f v []     = v
> foldr f v (x:xs) = f x (foldr f v xs)

foldr (+) 0 [1,2,3] --- [1,2,3] = 1 : [2,3]
= (+) 1 (foldr (+) 0 [2,3])
= (+) 1 ((+) 2 (foldr (+) 0 [3])) -- [3] = 3:[]
= (+) 1 ((+) 2 ((+) 3 (foldr (+) 0 []))) 
= (+) 1 ((+) 2 ((+) 3 0))
= (+) 1 ((+) 2 3)
= 6

(1+(2+(3+0)))

2. 

> seclargest    :: [Int] -> Int
> seclargest xs = snd (foldr fun v xs)

seclargest []
= snd (foldr fun v [])
= snd v
= 0
v = (x, 0)

foldr fun v [1,2,3]
= fun 1 (foldr fun v [2,3])
= fun 1 (fun 2 (foldr fun v [3]))
= fun 1 (fun 2 (fun 3 (foldr fun v [])))
= fun 1 (fun 2 (fun 3 v))
....
= 2

> fun :: Int -> (Int, Int) -> (Int, Int)
> fun z (x,y)
> 		| x <= z    = (z, x)
> 		| y <= z    = (x, z)
> 		| otherwise = (x, y)

> v :: (Int, Int)
> v = (0,0)
--------------------------------------------------------------------------------------

Q5:

1. 

> replicate :: Int -> a -> [a]
> replicate n x = [ x  | _ <- [1..n]]

2. 

> data Nat = One | Succ Nat
>            deriving (Show)

> data Exp a = Plus (Exp a) (Exp a) | Times (Exp a) (Exp a) | Val a
>              deriving Show

> eval :: Exp Nat -> Int 
> eval (Plus x y)  = (eval x) + (eval y)
> eval (Times x y) = (eval x) * (eval y)
> eval (Val n)     = eval_helper n
> 	where
> 		eval_helper   :: Nat -> Int
>		eval_helper One      = 1
> 		eval_helper (Succ x) = 1 + eval_helper x

------------------------------------------------------------------------------------

Q6:
P(xs): (filter p . map f) xs = (map f . filter (p . f)) xs

Base case:
when xs = []
LHS = (filter p . map f) []
	= {comp.1}
		filter p (map f [])
	= {map.1}
		filter p []
	= {filter.1}
		[]
	  
RHS = (map f . filter (p . f)) []
	= {comp.1}
		map f (filter (p . f) [])
	= {filter.1}
		map f []
	= {map.1}
		[]
	  
LHS = RHS, base case is true.

Inductice case:

Induction hypothesis: (filter p . map f) xs = (map f . filter (p . f)) xs
We need to prove: (filter p . map f) (x:xs) = (map f . filter (p . f)) (x:xs)

LHS = (filter p . map f) (x:xs)          
	= {comp.1}
		filter p (map f (x:xs))
	= {map.2}
		filter p (f x : map f xs)

case 1 - p (f x) is true                           case 2 - p (f x) is false
	= {filter.2}										= {filter.3}
		f x : filter p (map f xs)						  filter p (map f xs)
	= {comp.1}											= {comp.1}
		f x : (filter p . map f) xs						  (filter p . map f) xs
	= {hypothesis} 										= {hypothesis} 
		f x : (map f . filter (p . f)) xs				  (map f . filter (p . f)) xs
	
	
	
RHS = (map f . filter (p . f)) (x:xs)
	= {comp.1}
		map f (filter (p . f) (x:xs))

case 1 - p . f x which is p (f x) is true.         case 2 - p . f x which is p (f x) is false. 
	= {filter.2}										= {filter.3}
	map f (x : filter (p . f) xs)						map f (filter (p . f) xs)
	= {map.2}											= {comp.1}
	f x : map f (filter (p . f) xs)						map f . filter (p . f) xs
	= {comp.1}											= LHS case 2
	f x : (map f . filter (p . f)) xs
	= LHS case 1

------------------------------------------------------------------------------------

Q7：

1. 

map f = fold (\ x ys -> f x : ys)[]
   g  = fold            f         v


find what is g,v,f in the universal property

g : map f
v : []
f : (\ x ys -> f x : ys)

g [] = map f [] = [] = v => g [] = v

g (x:xs) = map f (x:xs) = f x : map xs
f x (g xs) = (\ x ys -> f x : ys) x (map f xs) = f x : (map f xs)

=> g (x:xs) = f x (g xs)

therefore, map f = fold (\ x ys -> f x : ys)[]


2. 

double . sum = fold ((+) . double) 0

> double :: Int -> Int
> double x = x + x 

we need fold in both sides, so rewrite sum function using fold

sum = fold (+) 0

double . sum = fold ((+) . double) 0 
<=> double . (fold (+) 0 ) = fold ((+).double) 0
	h .       fold  g  w   = fold     f        v
find what is h,w,v,g,f in the fusion property

h : double
w : 0
g : (+)
v : 0
f : (+).double

h w = double 0 = 0 = v => h w = v

h (g x y) = double ((+) x y) = double (x+y) = (x+y) + (x+y) = 2x + 2y

f x (h y) = (+).double x (double y) = (+).double x 2y = 2x + 2y

h (g x y) = f x (h y)

=> double . (fold (+) 0 ) = fold ((+).double) 0
