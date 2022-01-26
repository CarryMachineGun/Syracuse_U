> second xs = head (tail xs)

> swap :: (Int,Int) -> (Int,Int)
> swap (x,y) = (y,x)

> pair :: Int -> Int -> (Int, Int)
> pair x y = (x,y)

> tail1 :: [a] -> a
> tail1 as = head (reverse as) 

-- | > pal2 :: Num a => [a] -> a 
-- |> pal2 as = reverse as == as
