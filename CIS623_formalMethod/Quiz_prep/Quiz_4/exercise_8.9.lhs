> -- Q1

> data Nat = Zero | Succ Nat deriving Show 

> add1 :: Nat -> Nat -> Nat
> add1 Zero x = x
> add1 (Succ x) y = Succ (add1 x y)

> mult1 :: Nat -> Nat -> Nat
> mult1 Zero _ = Zero
> mult1 (Succ x) y = add1 y (mult1 x y)

> test1 = add1 (Succ (Succ Zero)) (Succ Zero)
> test2 = mult1 (Succ (Succ Zero)) (Succ Zero)


> -- Q3

> data Tree a = Leaf a | Node (Tree a) (Tree a)

> countLeaf :: Tree a -> Int
> countLeaf (Leaf a) = 1
> countLeaf (Node l r) = (countLeaf l) + (countLeaf r)


> balanced :: Tree a -> Bool
> balanced (Leaf a) = True
> balanced (Node l r) = 
>  if abs ((countLeaf l) - (countLeaf r)) <= 1 && balanced l && balanced r then True
>  else False 

> -- Q4

> split1 xs = splitAt (div (length xs) 2) xs

> balanceTree :: [a] -> Tree a
> balanceTree [x] = (Leaf x)
> balanceTree xs = Node (balanceTree l) (balanceTree r)
>  where (l,r) = split1 xs




