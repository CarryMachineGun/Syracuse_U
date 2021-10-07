> ---1

> a :: Int 
> a = sum [ x^2 | x <- [1..100]]

> --2
> grid1 :: Int -> Int -> [(Int, Int)]
> grid1 x y = [(a,b) | a <- [0..x], b <- [0..y]]

> --3

> square1 :: Int -> [(Int, Int)]
> square1 x = [(a,b) | a <- [0..x], b <- [0..x], a /= b]

> --4

> replicate1 :: Int -> a -> [a]
> replicate1 n x = [x | _ <- [1..n]]

> replicate2 :: Int -> a -> [a]
> replicate2 0 _ = []
> replicate2 n x = x : (replicate (n-1) x) 

> ----5

> pyths1 :: Int -> [(Int, Int, Int)]
> pyths1 n = [(x,y,z) | x <- [1..10], y <- [1..10], z<- [1..10], z^2 == x^2 + y^2]

> --6

> perfects1 :: Int -> [Int]
> perfects1 n = [x | x <- [1..n], x == sum [a | a <- [1..x-1], x `mod` a == 0]]
> --perfects1 n = [x | x <- [1..n], x == sum [s | s <- [1..x-1], x `mod` s == 0]]


> --8

> pos1 :: Char -> String -> [Int]
> pos1 n ns = find n ns


> positions1 :: Char -> String -> [Int]
> positions1 n ns = [y | (x,y) <- zip ns [0..], x==n]