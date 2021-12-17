---- Question 1 
-- a)
keep :: [a] -> [a]
keep []    = []
keep [x]   = [x]
keep (x:_:zs) = x: keep zs

-- b)
keepLess ::[a] -> [a]
keepLess []     = []
keepLess xs     = keep (keep xs)


---- Question 2
-- a)
factors :: Integer -> [Integer]
factors n = [x |x <- [1..n], n `mod` x == 0]

-- b)
-- Define a helper function to test if it is a prime number 
isPrime :: Integer -> Bool 
isPrime n = (factors n == [1,n])

-- We could find all prime factors of x first and then test if the product of factors is x
pseudoprime :: Integer -> [Integer]
pseudoprime n =  [x | x <- [1..n], y <- factors x, z <- factors x, isPrime y, isPrime z, y<=z, y*z==x]

-- c)
selectRange :: Int -> Int -> [a] -> [a]
selectRange i j xs = [y| (x,y) <- (zip [1..] xs),1<=i, i<=j,x>=i,x<=j,j<=length xs]


---- Question 3
-- a)
helper :: [a->a] -> (a->a)
helper [] = id
helper (y:ys) = (helper ys ).y

mapThem :: [a -> a] -> [a] -> [a]
mapThem [] xs = xs
mapThem _ [] = []
mapThem f xs = map (helper f) xs
 
-- b)
combine :: Num a => (a->a) -> (a->a) -> (a -> a)
combine f g = \x -> 2*(f x) + 3*(g x)

---- Question 4
data Tree a =  Empty | Node a (Tree a) (Tree a) deriving (Show)
-- a)
tree1 = Node 1 (Node 4 Empty Empty) (Node 5 Empty Empty )
tree2 =  Node 4 (Node 3 (Node 3 Empty Empty) (Node 5 Empty (Node 6 Empty Empty ))) Empty 
{-
According to the definition of the almost balanced, we can find that tree1 is almost balanced because it is a banlanced tree.
But for tree2, the left tree of the root has 4 nodes while it is 0 in the right tree, so it isn't.
-}

-- b)
noOfNodes :: Tree a -> Int
noOfNodes Empty  = 0
noOfNodes (Node _ left right)  = 1 + (noOfNodes left) + (noOfNodes right)

-- c)s = 
abalanced :: Tree a -> Bool
abalanced Empty  = True
abalanced (Node _ Empty Empty) = True
abalanced (Node _ left right) = abs (noOfNodes left - noOfNodes right) <= 2 && (abalanced left) && (abalanced right)


-- Question 5
fun  = (\x ys -> x: (map (+x) ys) )

prefixsum :: [Integer] -> [Integer]
prefixsum xs = foldr (\y ys -> y:(map (+y) ys)) [] xs


---- Question 6
-- a)
suffixsum :: [Int] -> [Int]
suffixsum [] =[]
suffixsum xs = map (\x -> sum (drop x xs)) [0..(length xs)-1]


-- b)
printSufSum :: [Int] -> IO ()
printSufSum xs  = sequence_ [putStrLn (show(x)) | x <- suffixsum xs]

---- Question 7
data Prop = Const Bool
            | Var Char
            | Not Prop
            | And Prop Prop
            | Or Prop Prop
            | Imply Prop Prop
            deriving (Show)

-- a)
pa = Imply (Or (Const True) (Const False)) (And (Not (Const False)) (Const True))

-- b)
countSym :: Prop -> Int
countSym (Const _) = 0
countSym (Var _) = 0
countSym (Not p) = 1 + countSym p
countSym (And p1 p2) = 1 + countSym p1 + countSym p2
countSym (Or p1 p2) = 1 + countSym p1 + countSym p2
countSym (Imply p1 p2) = 1 + countSym p1 + countSym p2


