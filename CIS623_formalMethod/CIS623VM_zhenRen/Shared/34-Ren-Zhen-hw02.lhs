Student No:34
Last Name:Ren
First Name:Zhen

--Solution 1


>import Data.Char

if i do not put import at first, my emacs will report errors.
In Solution 2, we use standard functions on characters in the Data.Char library.So we need to import the library at the start.


>sqfactors :: Int -> Int          
>sqfactors n=length[x| x<-[2..(n `div` 2)],n `mod` (x*x)==0]

sqfactors fucntion is to judge whether n is perfect square. The first line is to define the type of sqfactors. If n is a perfect square, the length of the list comprehension will be one. In this section, we must use == rather than `div`  10 `div` 3 == 3. And 8 is not a sqfree number because 8 =2^2 *2.

>issquare :: Int-> Bool
>issquare n=(n>1) && ((sqfactors n)==0)

issqare mainly use the sqfactors function. The first line is to define the type of function. The judgement has been made in sqfactors function. So issquare function mainly return a bool value

>sqfree :: [Int]
>sqfree = [p | p<-[2..], issquare p]

sqfree function meets the required type[Int],and takes from 2 to 1000 as example to test.


-- Solution 2
-- Caeser cipher example from chapter 5 of Programming in Haskell,
-- Graham Hutton, Cambridge University Press, 2016.

-- Encoding and decoding

>let2int :: Char -> Int
>let2int c = ord c - ord 'a'

let2int function mainly transfer char into int, by subtracting 'a' value. So the integer is between 0 and 25.
 
>int2let :: Int -> Char
>int2let n = chr (ord 'a' + n)

int2let function is opposite conversion, int to char. And its' correponding is the same as let2int 0->'a'  25->'z'

>shift :: Int -> Char -> Char
>shift n c | isLower c = int2let ((let2int c + n) `mod` 26)
>          | otherwise = c

shift is a function to convert lower-case letter into corresponding integer, by adding the int number and taking the remainder when divided by twenty-six. To this function, only lower-case letter will work and other letters will return itself. 

>encode :: Int -> String -> String
>encode n xs = [shift n x | x <- xs]

encode is a function to use shift and list comprehension to convert a str into another str with n shifts.

-- Frequency analysis

>table :: [Float]
>table = [8.1, 1.5, 2.8, 4.2, 12.7, 2.2, 2.0, 6.1, 7.0,
>         0.2, 0.8, 4.0, 2.4, 6.7, 7.5, 1.9, 0.1, 6.0,
>         6.3, 9.0, 2.8, 1.0, 2.4, 0.2, 2.0, 0.1]

table is to store twenty-six letters' frequency.

>lowers :: String -> Int
>lowers xs = length [x | x <- xs, x >= 'a' && x <= 'z']

lowers is a function to count the number of a str's lower-case letters.

>count :: Char -> String -> Int
>count x xs = length [x' | x' <- xs, x == x']

count is a function to count the number of the char in the list.

>percent :: Int -> Int -> Float
>percent n m = (fromIntegral n / fromIntegral m) * 100

percent is a function to calculate the result of floating-point number n divide  floating-point number m. Using the library fromIntegral to converts the type from Int to Float.

>freqs :: String -> [Float]
>freqs xs = [percent (count x xs) n | x <- ['a'..'z']]
>           where n = lowers xs

freqs function use percent function, count function, lowers function togerther with list comprehensions to achieve calculating the frequency of each lower-case letters.

>chisqr :: [Float] -> [Float] -> Float
>chisqr os es = sum [((o-e)^2)/e | (o,e) <- zip os es]

chisqr is a function to calculate the chi-square stastic value, using list comprehensions and zip function.
Take an example to illustrate chisqr [1,2,3] [4,5,6]
=(1-4)^2/4+(2-5)^2/5+(3-6)^2/6=2.25+1.8+1.5=5.55
And it will return the same result as chisqr [1,2,3,4] [4,5,6] and chisqr [1,2,3] [4,5,6,7] beacuse of the zip function.

>rotate :: Int -> [a] -> [a]
>rotate n xs = drop n xs ++ take n xs

rotate is a function to rotate the elements of a list n places to the left. Its value should be between zero and the length of the list.

>positions :: Eq a => a -> [a] -> [Int]
>positions x xs = [i | (x',i) <- zip xs [0..n], x == x']
>                 where n = length xs - 1

positions function is to return the a's positions in the list, using list comprehensions and zip function. Using zip function we can mark each elements with a number i, which is the position. And if the element equals to the wanted value we could create a list consists of all the i.

>crack :: String -> String
>crack xs = encode (-factor) xs
>           where
>              factor = head (positions (minimum chitab) chitab)
>              chitab = [chisqr (rotate n table') table | n <- [0..25]]
>              table' = freqs xs


crack function is to decode the the encoded string. Firstly, we should know the table is the observation that some letters are used more frequently than others in Enllish text, but it is not work for each situation. So the crack function doesn't work for every situtaion, it just provides a possiblity. 
The table' means the frequency of the list elements.
The chitab is to calculate the chi-square statistic  for each rotate from 0-25.
factor is to try the minimum of chi-square statistic decode the encoded string.

>test :: String -> [Float]
>test xs = [chisqr (rotate n table') table | n<-[0..25]]
>          where
>              table' =freqs xs

test function is to help us calculate the sqi-square statistic for each decoded string, to help understand the process.

example 1:
encode 3 "haskell is fun"
encoded string: "kdvnhoo lv ixq"
crack string: "haskell is fun"
expected output:"haskell is fun"
This example is to test if my function work properly, and i calculate the chi-square. It's true that 3 is the minimum of the chi-square for each rotate.So the function could be transfer to 
encode (-3) "kdvnhoo lv ixq"

example 2:
encode 4 "I am a student"
encoded string: "i eq e wxyhirx"
crack string: "I am a student"
expected output:"I am a student"
This example is to test if my function works for I, as a larger-case letter. After using function test,i found 4 is the minimum of sqi-square. The result will be put in the testcases.
The result tells that it could work properly towards this situation.

example 3:
encode 2 "i have 2 computers"
encoded string: "k jcxg 2 eqorwvgtu"
crack string: "i have 2 computers"
expected output:"i have 2 computers"
This example is to test if my function works with the number in the list. The chitab result will put in testcases.
The result tells that crack can succeed in decoding the string with numbers 

example 4:
encode 10 "acefgh"
encoded string: "kmopqr"
crack string: "nprstu"
expected output:"acefgh"
This example is to show that crack function can decode the wrong string as output. It is because the input is just a random letters without any meaning. So the frequency of the input is pretty strange for chi-square numbers. And i will put the chitab in testcases.

example 5:
encode 6 "The abcde is 1 random string"
encoded string: "Tnk ghijk oy 1 xgtjus yzxotm"
crack string: "The abcde is 1 random string"
expected output:"The abcde is 1 random string"
This example is to show that the crack function can decode rightly even with some random letters. It shows that crack function is pretty strong.