This example is revised from Bird's Text for
CIS 623 (last used in Fall 2021 Semester)

Anagrams.               
10th October, 2014
In Chapter 01
_________________________________________________
To compile this program, type

$ ghc -o anagrams anagrams.lhs

This invokes the Glasgow Haskell Compiler (ghc)
and creates an executable file anagrams.o

You can then run the program with a command like

$ ./anagrams 6 < dictionary

This reads the file dictionary and prints the 6-
letter anagrams to the terminal. If you want the
result to go to an output file called "results",
you can type

$ ./anagrams 6 < dictionary > results

________________________________________________
The functions toLower and sort are provided in
standard Haskell libraries:

> import Data.Char (toLower)
> import Data.List (sort,words)
> import System.Environment (getArgs)

We need getArgs because the ./anagrams command has
an argument, namely the number of letters in a word.

Note: The type `Words` was initially defined as `Word`, 
causing a naming conflict. We rename it to Words, as follows:

> type Words  = [Char]
> type Key    = [Char]
  

> anagrams :: Int -> [Words] -> String
> anagrams n = showResult . groupByKey . sort .
>              map addKey . getWords n

> getWords :: Int -> [Words] -> [Words]
> getWords n = filter ((==n) . length)

> addKey :: Words -> (Key,Words)
> addKey w = (sort w,w)

> groupByKey :: [(Key,Words)] -> [(Key,[Words])]
> groupByKey [] = []
> groupByKey (kw:kws) = insert kw (groupByKey kws)
>  where
>  insert (k,w) []            = [(k,[w])]
>  insert (k,w) ((k',ws):kws) = if k==k' then (k,w:ws):kws
>                               else (k,[w]):(k',ws):kws





> showResult :: [(Key,[Words])] -> String
> showResult = concat . map showLine
>  where
>  showLine (k,ws) = k ++ ": " ++ addcommas ws ++ "\n"

> addcommas :: [Words] -> String
> addcommas []     = []
> addcommas [w]    = w
> addcommas (w:ws) = w ++ "," ++ addcommas ws

> main :: IO ()
> main = do {[n] <- getArgs;
>            text <- getContents;
>            putStr (anagrams (read n) (words text)) }
