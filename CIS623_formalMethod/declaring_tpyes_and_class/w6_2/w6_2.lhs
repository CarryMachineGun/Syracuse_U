> type Pos = (Int, Int)

> -- type declaration can have parameter
> type Pair a = (a,a)

> copy :: a -> Pair a 
> copy x = (x,x)


> -- Type declaration can be nested

type Trans = Pos -> Pos


> -- Data Declarations

> data Answer = Yes | No | Unknown

> inAns :: Int -> Answer
> inAns 1 = Yes
> inAns 2 = No
> inAns 3 = Unknown
> inAns _ = Unknown

> printfAns :: Answer -> Int
> printfAns Yes = 1
> printfAns No = 2
> printfAns Unknown = 3

> answers :: [Answer]
> answers = [Yes, No, Unknown, Yes]


> flip1 :: Answer -> Answer
> flip1 Yes = No
> flip1 No = Yes
> flip1 Unknown = Unknown


> -- Constructor in data declaration with parameter

> data Shape1 = Circle Float | Rect Float Float

> square1 :: Float -> Shape1
> square1 x = Rect x x 

> area1 :: Shape1 -> Float
> area1 (Circle r) = pi * r^2
> area1 (Rect x y) = x * y


> -- recursion type

> data Nat = Zero | Succ Nat


> nat2Int :: Nat -> Int
> nat2Int Zero = 0
> nat2Int (Succ n) = 1 + nat2Int n


> int2Nat :: Int -> Nat
> int2Nat 0 = Zero
> int2Nat n = Succ (int2Nat (n-1))


> add1 :: Nat -> Nat -> Nat
> add1 Zero n = n 
> add1 (Succ m) n = Succ (add1 m n) 

> fAdd n m = nat2Int (add1 n m)

> multi1 :: Nat -> Nat -> Nat
> multi1 Zero n = Zero
> multi1 (Succ m) n = add1 n (multi1 m n) 

> countCir :: [Shape1] -> Int
> countCir [] = 0
> countCir ((Circle _) :ns) = 1 + countCir ns
> countCir ((Rect _ _) :ns) = countCir ns

> test = countCir [(Rect 1 2), (Rect 1 2), (Rect 3 5), (Circle 3), (Rect 2 5), (Circle 3)]
