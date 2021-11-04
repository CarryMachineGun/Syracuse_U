> data Tree a = Leaf a | Node (Tree a) a (Tree a)

> occur1 :: Int -> Tree Int -> Bool
> occur1 x (Leaf y) = x == y
> occur1 x (Node l y r) = 
>  if x == y then True
>  else  
>   if occur1 x l then True 
>   else 
>    if occur1 x r then True 
>    else False