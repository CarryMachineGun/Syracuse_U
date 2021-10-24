---------------------------------------------------------------------------
Fall 2021 CIS 623
Activity 6
---------------------------------------------------------------------------

Lastname :  < Wang >
Firstname:  < Yuchen > 
Stud. num:  < 530 >

---------------------------------------------------------------------------

> import Data.List

Datatypes 

1. Prop (propositional formulas, from Hutton's Ch.8)

> data Prop = Const Bool       -- not included in BNF form 
>          | Var Char
>          | Not Prop
>          | And Prop Prop          
>          | Imply Prop Prop
>            deriving (Eq, Show)

a. Create objects of type Prop

Constants:

> ct :: Prop
> ct = Const True

> cf :: Prop
> cf = Const True

Variables:

> va :: Prop
> va = Var 'A'

> vb :: Prop
> vb = Var 'B'

> vc :: Prop
> vc = Var 'C'

> vd :: Prop
> vd = Var 'D'

Propositions with logical connectives:

> p1 :: Prop
> p1 = And va (Not vb)

> p2 :: Prop
> p2 = Imply (And vb vc) va

> p3 :: Prop
> p3 = Imply va (And va vb)
  
> p4 :: Prop
> p4 = Imply (And vc (Imply vd vb)) va

b. The function that count the number of distinct variables

In the space below, implement a function that will count the 
number of distinct variables in a proposition. Helper functions
can be used to support your implementation.

> numvarlst :: Prop -> [Prop]
> numvarlst (Const a) = []
> numvarlst (Var v) = [Var v]
> numvarlst (Not p) = numvarlst p
> numvarlst (And p q) = numvarlst p ++ numvarlst q
> numvarlst (Imply p q) = numvarlst p ++ numvarlst q
>
> rmduplicate :: Eq a => [a] -> [a]
> rmduplicate [] = []
> rmduplicate (x:xs) = x : filter (/=x) (rmduplicate xs)
>
> numdistvar :: Prop -> Int
> numdistvar p = (length . rmduplicate . numvarlst) p

--------------------------------------------------------------------------------

c. The function implfree

In the space below, implement a function that will take a proposition 
as input, return a proposition that is implication free.

> implfree  :: Prop -> Prop
> implfree  (Const a) = (Const a)
> implfree  (Var v) = (Var v)
> implfree  (Not p) = (Not (implfree p))
> implfree  (And p q) = (And (implfree p)(implfree q))
> implfree  (Imply p q) = (Not (And(implfree p)(Not (implfree q))))


--------------------------------------------------------------------------------


2. BTree (binary trees)

> data BTree a = Nil | Node (BTree a) a (BTree a) 
>                deriving (Eq, Show)

a. Create objects of type BTree Int

> nt :: BTree Int
> nt = Nil

> n1 :: BTree Int
> n1 = Node nt 1 nt

> n2 :: BTree Int
> n2 = Node nt 2 nt

> n3 :: BTree Int
> n3= Node nt 3 nt

> t4 :: BTree Int
> t4 = Node n1 4 n2

> t5 :: BTree Int
> t5 = Node n2 5 n3

> t6 :: BTree Int
> t6 = Node t4 6 t5


b. Compute the height of a  BTree

In the space below, compose a function height that will compute
the height of a BTree.

> height :: BTree a -> Int
> height Nil   = -1
> height (Node l x r) = 1 + max (height l) (height r)





--------------------------------------------------------------------------------

c. Compute an inorder listing of the data in a BTree

In the space below, compose a function inorder that will compute
an inorder listing of a BTree.


> inorder  :: BTree a -> [a]
> inorder Nil = []
> inorder (Node l x r) = (inorder l) ++ [x] ++ (inorder r)





--------------------------------------------------------------------------------


3. RTree (rooted trees)

> data RTree a = Vertex a [RTree a]

a. Create objects of type RTree Int

> rvtx1 :: RTree Int 
> rvtx1 = (Vertex 1 [])


> rvtx2 :: RTree Int 
> rvtx2 = (Vertex 2 [])


> rvtx3 :: RTree Int 
> rvtx3 = (Vertex 3 [])


> rvtx4 :: RTree Int 
> rvtx4 = (Vertex 4 [])


> rtr5 :: RTree Int 
> rtr5 = (Vertex 5 [rvtx1, rvtx2, rvtx3])


> rtr6 :: RTree Int 
> rtr6 = (Vertex 6 [rvtx2, rvtx3])


> rtr7 :: RTree Int 
> rtr7 = (Vertex 7 [rtr5, rtr6])


> rtr8 :: RTree Int 
> rtr8 = (Vertex 8 [rtr7, rtr7])


b. countvertex: count the number of vertices in a rooted tree

In the space below, compose a function countvertex that will find 
the number of vertices in a RTree.


> countvertex   :: RTree a -> Int
> countvertex (Vertex x []) = 1
> countvertex (Vertex x ts) = 1 + sum (map countvertex ts)



--------------------------------------------------------------------------------

c. Find the height of a RTree

In the space below, compose a function rheight that will find 
the number of vertices in a RTree.

> rheight :: RTree a -> Int
> rheight (Vertex x []) = 1
> rheight (Vertex x ts) = 1 + maximum(map rheight ts)



--------------------------------------------------------------------------------

Appendix

In the space below, append the test runs (and results) you had created while 
testing the above functions.

> test1 = numdistvar p1

2

> test2 = implfree p2

Not (And (And (Var 'B') (Var 'C')) (Not (Var 'A')))

> test3 = height t6

2

> test4 = inorder t4

[1,4,2]

> test5 = countvertex rtr6

3

> test6 = rheight rtr6

2