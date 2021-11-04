----------------------------------------------------------------------

CIS 623
Lecture 14  haskell script: 623-f21-14.lhs

----------------------------------------------------------------------

> import Data.Data

The Shape datatype (Hutton, Chapter 8)

1. Shape revisited

   Note that Circle and Rect are the constructors 
   for Shape

a. Join the typeclass Show using the deriving keyword

> data Shape = Circle Float | Rect Float Float
>            deriving (Eq, Show)

We may use the deriving keyword here by adding deriving Show 
in the data declaration. An alternative is to write a show 
function directly

instance Show Shape where
     show (Circle x)   = "cir " ++ show x 
     show (Rect   x y) = "rec " ++ show x ++ " , " ++ show y

b. Creating data of type Shape

> c1 :: Shape
> c1 = Circle 1.0

> c2 :: Shape
> c2 = Circle 1.0

> r1 :: Shape
> r1 = Rect 1.0 2.0

c. Store data as a Collection of shapes

> lstshape :: [Shape]
> lstshape = [c1, r1]

d. Compute functions for data of the Shape type
   Note the pattern used in the definition

> area :: Shape -> Float
> area  (Circle x) = pi*x*x
> area  (Rect x y) = x*y

> countrect    :: [Shape] -> Int
> countrect []            = 0
> countrect ((Circle a):xs) = countrect xs
> countrect ((Rect a b):xs) = 1+ countrect xs

2. Recursive data type

a. Recall the Nat example (defined Nat.lhs)

Review Nat.lhs (how to define instance; define functions on Nat)

b. The proprositional formula example (defined in tautology.hs)


A proposition is either 

1. True or False
2. P (a single propositional atom)
3. not p,     where p is a proposition
4. And p q    where p and q are propositions
5. Imply p q  where p and q are propositions


How this definition of proposition is being translated to
the code in tautology.hs


c. The binary tree example (Hutton's text)


> data BTree a = Nil | Node (BTree a) a (BTree a)
>              deriving (Eq, Show) 
> 

> t1 :: BTree Int
> t1 = Nil

> t2 :: BTree Int
> t2 = Node t1 1 t1

> t3 :: BTree Int
> t3 = Node t2 2 t1

> t4 :: BTree Int
> t4 = Node t1 2 t2

d. The Rooted tree example

> data RTree a = Vertex a [RTree a]

> rt1 :: RTree Int
> rt1 = Vertex 1 []

> rt2 :: RTree Int
> rt2 = Vertex 2 [rt1, rt1, rt1]



