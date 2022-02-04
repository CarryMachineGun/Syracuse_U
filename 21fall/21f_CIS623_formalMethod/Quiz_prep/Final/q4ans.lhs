______________________________________________________________________
Fall 2021  CIS 623 

Quiz 4
______________________________________________________________________

1. The datatype Shape is re-defined as:

> data Shape = Circle Float | Rect Float Float | Others
>            deriving Show  -- not part of the question 


a. (3 point) Write a function `showShape` to display the specific shape of 
each Shape object declared. For example:

*Main> showShape (Circle 1.0)
"A Circle"

*Main> showShape (Rect 1.0 1.0)
"A Rectangle"

*Main> showShape Others
"Unknown"

answer:

> showShape            :: Shape -> [Char]
> showShape (Circle _) = "A Circle"
> showShape (Rect _ _) = "A Rectangle"
> showShape Others     = "Unknown"


---


b. (7 point) In class, the datatype BTree a is defined as:

> data BTree a = Nil | Node (BTree a) a (BTree a)

write a function countShapes which will take a tree (of type BTree Shape) as input, return 
the count of each Shapes in the form of an ordered triple. For example, if:

> n :: BTree Shape
> n = Nil

> c1 :: BTree Shape
> c1 = Node n (Circle 1.0) n 

> r1 :: BTree Shape
> r1 = Node n (Rect 1.0 1.0) n 

> o1 :: BTree Shape
> o1 = Node n Others n 

> eg1 :: BTree Shape
> eg1 = Node c1 Others c1 

> eg2 :: BTree Shape
> eg2 = Node eg1 Others eg1 

then:

*Main> countShapes eg1
(2,0,1)

*Main> countShapes eg2
(4,0,3)

You may write helper functions (either as local functions or otherwise) to help to build your function.

> countShapes     :: BTree Shape -> (Int, Int, Int)
> countShapes Nil                  = (0,0,0)
> countShapes (Node ltree a rtree) 
>     | showShape a == "A Circle"    = add (1,0,0) (add (countShapes ltree)  (countShapes rtree))
>     | showShape a == "A Rectangle" = add (0,1,0) (add (countShapes ltree)  (countShapes rtree))
>     | showShape a == "Unknown"     = add (0,0,1) (add (countShapes ltree)  (countShapes rtree))

> countShapes2     :: BTree Shape -> (Int, Int, Int)
> countShapes2 Nil                  = (0,0,0)
> countShapes2 (Node ltree a rtree) 
>     | showShape a == "A Circle"    = (1 + l1 + r1, l2 + r2, l3+ r3)
>     | showShape a == "A Rectangle" = (l1 + r1, l2 + r2 + 1, l3+ r3)
>     | showShape a == "Unknown"     = (l1 + r1, l2 + r2, l3+ r3 + 1)
>     where
>      (l1,l2,l3) = countShapes2 ltree
>      (r1,r2,r3) = countShapes2 rtree


 
> add                           :: (Int, Int, Int) -> (Int, Int, Int) -> (Int, Int, Int)  
> add (x1, y1, z1) (x2, y2, z2) =  (x1 + x2, y1 + y2, z1 +z2) 



---


2. In class, the datatype Prop is stated as:

> data Prop = Const Bool
>           | Var Char
>           | Not Prop
>           | And Prop Prop
>           | Imply Prop Prop
>             deriving Show

a. (3 point) State a property of propositional logic we will use

p -> q \equiv (____)

so that the function implfree can transform a propositional formula to a equivalent 
propositional formula which will not use the logical connective imply. 

Answer: 

p -> q \equiv (Not (And p (Not q)))


---
          
b. (7 point) Write a function andfree which will transform a propositional formula to an
equivalent prop formulas which will not use the logical connect and.

Answer: Note that

And p q 

\equiv 

(Not (Imply p (Not q)))

Hence:

> andfree :: Prop -> Prop
> andfree (Const a) = (Const a) 
> andfree (Var v) = (Var v)
> andfree (Not p)   = (Not (andfree p))
> andfree (And p q)   = (Not (Imply (andfree p) (Not (andfree q)))) 
> andfree (Imply p q) = (Imply (andfree p) (andfree q))



---

