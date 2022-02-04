----------------------------------------------------------------------

CIS 623
Lecture 11  haskell script: 623-f21-13.lhs

----------------------------------------------------------------------

The Shape datatype (Hutton, Chapter 8)

1. Shape revisited

a. Join the typeclass Show using the deriving keyword

> data Shape = Circle Float | Rect Float Float
>              deriving (Show)

b. Creating data of type Shape

> c1 :: Shape
> c1 = Circle 1.0

> r1 :: Shape
> r1 = Rect 1.0 2.0

c. Store data as a Collection of shapes

> lstshape :: [Shape]
> lstshape = [c1, r1]

d. Compute functions for data of the Shape type

> area :: Shape -> Float
> area  (Circle x) = pi*x*x
> area  (Rect x y) = x*y

> countrect    :: [Shape] -> Int
> countrect []            = 0
> countrect ((Circle a):xs) = countrect xs
> countrect ((Rect a b):xs) = 1+ countrect xs

