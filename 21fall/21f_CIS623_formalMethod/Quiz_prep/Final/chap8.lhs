> type MyType a = (a,a)

> f1 :: Int -> MyType Int 
> f1 x = (x,x)

> type MyType2 = (Int, Int)

> type MyType3 = (MyType2, MyType2)

> f2 :: MyType2 -> MyType3
> f2 (x,y) = ((x,x),(y,y))

> data Answer = YES | NO | UNKNOWN

> flips1 :: Answer -> Answer
> flips1 YES = NO
> flips1 NO = YES
> flips1 _ = UNKNOWN

> data Shape1 = Rect Float Float | Circle Float 

> area1 :: Shape1 -> Float 
> area1 (Circle r) = r^2
> area1 (Rect a b) = a * b

> data Nat = Zero | Succ Nat

> nat2int :: Nat -> Int
> nat2int Zero = 0
> nat2int (Succ x) = 1 + (nat2int x)

> int2nat :: Int -> Nat
> int2nat 0 = Zero
> int2nat x = Succ (int2nat (x-1))

> natAdd :: Nat -> Nat -> Nat
> natAdd x y = int2nat ((nat2int x) + (nat2int y))

> countCir :: [Shape1] -> Int
> countCir [] = 0
> countCir ((Circle _) : xs) = 1 + countCir xs
> countCir ((Rect _ _) : xs) = countCir xs

> addShape :: [Shape1] -> Int
> addShape [] = 0
> addShape ((Circle _) : xs) = 1 + addShape xs
> addShape ((Rect _ _) : xs) = 1 + countCir xs

> test1 = countCir [(Circle 2), (Circle 3)]


> data Tree a = Leaf a | Node (Tree a) a (Tree a)

> occur1 :: Int -> Tree Int -> Int 
> occur1 x (Leaf y) = if x == y then 1 else 0
> occur1 x (Node l y r) = 
>  if x == y then 1 + (occur1 x l) + (occur1 x r)
>  else (occur1 x l) + (occur1 x r)

> occur2 :: Int -> Tree Int -> Bool
> occur2 x (Leaf y) = x == y
> occur2 x (Node l y r) = 
>  if x == y then True
>  else (occur2 x l) || (occur2 x r)

> add2 :: Nat -> Nat -> Nat
> add2 Zero x = x 
> add2 x Zero = x 
> add2 (Succ x) y = Succ (add2 x y)

> mult1 :: Nat -> Nat -> Nat
> mult1 Zero _ = Zero
> mult1 _ Zero = Zero
> mult1 (Succ x) y = add2 y (mult1 x y)

> f3 :: Int
> f3 = x 
>  where 
>   (x,y,z) = (a+b,2,3)
>   a = 3 
>   b = 3 