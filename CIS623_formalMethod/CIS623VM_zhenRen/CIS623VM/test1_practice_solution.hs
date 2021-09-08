--Q1
remove3np1 :: [Int] -> [Int]
remove3np1 (x:y:z:ws) = y:z:remove3np1 ws
remove3np1 [y,z] = [z]
remove3np1   _   = []

--Q2
myCountDown :: Int -> [(Int,Int)]
myCountDown k
    |  k <= 0    =[]
    | otherwise = helper 1
    where 
      helper          :: Int -> [(Int,Int)]
      helper r
          | r > k     = []
          | r == k    = [(0,0)]
          | otherwise = (2*(k-r), (k-r)):helper (r+1)  
		  
--Q3
remove3np1' :: [Int] -> [Int]
remove3np1' xs = [x | (index, x) <- zip [1..] xs, mod index 3 /= 1]

myCountDown' :: Int -> [(Int,Int)]
myCountDown' k = [ (2*(k-i), k-i) | i <- [1..k]]

--Q4
psums::[Int] -> [Int]
psums [] = []
psums (x:xs) = x:(map(+x) (psums xs))


psums2::[Int] -> [Int]
psums2 [] = []
psums2 (x:xs) = helper 1 (x:xs)
      where 
	  helper::Int -> [Int] -> [Int]
	  helper n xs 
	      | n>length(xs) = []
		  |otherwise = sum(take n xs) :helper (n+1) xs

--Q5
factor::Int -> [Int]
factor n = [k|k<-[1..n],  mod n k ==0]

isComposite::Int->Bool
isComposite x = (x>1) && (length (factor x) >2)

composites::[Int]
composites = [i | i<-[2..],isComposite i]

kthComposite:: Int -> Int
kthComposite k = head [c|(i,c) <- zip [1..] composites, (i==k)]

--Q6
altMap :: (a -> b) -> (a -> b) -> [a] -> [b]
altMap f g [] = []
altMap f g (x:xs) = (f x) : altMap g f xs 

--Q7
combine :: Num a => (a -> a) -> (a -> a) -> (a -> a) 
combine f g = \ x -> 2 * (f x) + 3 * (g x)   

--Q8(a)
-- move ([5,4,3],[2,1])
-- ={move.2; [2,1]=2:[1]}
-- move (2:[5,4,3],[1])
-- ={move.2; [1]=1:[]}
-- move (1:2:[5,4,3],[])
-- ={move.1; 1:2:[5,4,3]=[1,2,5,4,3]}
-- ([1,2,5,4,3],[])

--Q8(b)
move :: ([a],[a]) -> ([a],[a])
move (xs,[]) = (xs, []) -- move.1
move (xs,(y:ys)) = move ((y:xs),ys) -- move.2

reverse2 :: [a] -> [a]
reverse2 xs = f (move ([], xs))
			where 
				f :: (a,b) -> a
				f (u,v) = u
				
--Q9
split :: [Int] -> [([Int],[Int])]
split [] = [] -- return [] if input is empty list
split [_] = [] -- return [] if input is singleton
split (x:xs) = ([x],xs) : [(x:rs,ts)|(rs,ts) <- split xs]

--Q10
bqfour :: [String] -> [String]
bqfour xs = filter (\ s -> test s) xs
		where
			test :: String -> Bool
			test [] = True -- our convention
			test xs = (head xs /= 'a') && (head xs /= 'A')
			
--Q11
ite :: (a -> a) -> a -> Int -> a
ite f x n 
	| n<=0 = x
	| otherwise = f (ite f x (n-1))
	