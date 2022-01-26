CIS 623 
Spring 2021
Student No:34
Last Name:Ren
First Name:Zhen


(a):
First of all, we use prune is to make the solver much efficient, by removing any choices from a cell c that already occur as singleton entries in the row, column and box containing c.
Then, pruneRow is a function to deal with the elements of a list of rows. The ones choices are the singleton entries in each row. The ones uses a list comprehension invoving pattern to discard the elements of rows are not singletons.
The remove function removes that the fixed choices from any choice that is not fixed.
Based on the two functions and the helper function pruneBy, we could finish the prune function. 
Take two examples to illustrate why pruneBy can deal with rows, columns and boxes. 

pruneRow [[6],[1,2],[3],[1,3,4],[5,6]]
[[6],[1,2],[3],[1,4],[5]]
pruneRow [[6],[3,6],[3],[1,3,4],[4]]
[[6],[],[3],[1],[4]]
The first example,[6] and [3] are the fixed choices; removing these chocies from other entries. In the second example, removing the fixed choices reduces the second entry to the empty list of choices.
And we already know that 
filter p.f={second definiation of filter}
concat. map (test p) . map f={functor property of map}
concat .map (test p . f)={since test p. f=map f .test (p.f)}
concat.map (map f. test (p.f))={functor property of map}
concat.map (map f). map (test (p.f))={naturaltiy of concat}
map f. concat . map (test (p.f))={second definition of filter} 
map f .filter (p.f)

filter (p.f)=map f .filter p . map f
filter (p.f).map f= map f . filter p

map f. filter p . map f
={we have proved previous that filter p . map f = filter (p.f)}
map f. map f .filter (p.f)
={functor law of map and f.f=id}
filter (p.f)

For the main calculation.
filter valid. expand
=filter (all nodups.boxs).
filter (all nodups .cols).
filter (all nodups.rows).expand

filter (all no dups .boxs).expand
={above law of filter, since boxs.boxs=id}
map boxs.filter (all nodups).map boxs . expand
={since map boxs. expand=expand. boxs}
map boxs. filter (all nodups). expand. boxs
={definition of expand}
map boxs. filter (all nodups) . cp . map cp .boxs
={since filter (all p) . cp  = cp .map (filter p)}
map boxs.cp .map (filter nodups). map cp . boxs
={functor law of map}
map boxs. cp .map (filter nodups. cp). boxs

Using filter nodeps. cp =filter nodups. cp .pruneRow
Rewrite map boxs. cp . map (filter nodups.cp. pruneRow).boxs

So the remaing part is:
map boxs. cp .map (filter nodups. cp . pruneRow). boxs
={functor law of map}
map boxs.cp .map (filter nodups). map (cp. pruneRow). boxs
={since cp.map (filter p)=filter (all p) .cp}
map boxs.filter (all nodups) . cp . map (cp. pruneRow). boxs
={functor law of map}
map boxs .filter (all nodups). cp . map cp .map pruneRow. boxs
={defintion of expand}
map boxs . filter (all nodups). expand .map pruneRow. boxs
={law of filter since boxs.boxs =id}
filter (all nodups .boxs). map boxs. expand. map pruneRow . boxs
={since map boxs. expand = expand .boxs}
filter (all nodups . boxs) . expand . boxs . map pruneRow . boxs
={introducing pruneBy f=f.pruneRow. f}
filter (all nodups. boxs). expand. pruneBy boxs.
So the prune holds.
solver2=filter valid. expand .prune. choices

(b):
The many function is mainly help us use many prunes as we like. It is worked because after one round of pruning some choices may be resolved into singleton choices and another round of pruning may remove still more imporssible choices.
Using pruning strategy and many prunes, we try each choice for Sudoku. And then repeatedly expand and try it until the matrix is completed.  The Sudoku problems are solved by repeatedly pruning the matrix of choices until only singleton choices are left.

(c):
For the example51, we can solve it in the reasonable time for solver2.
But for the examplealt, we can not solve it in the reasonable time for solver2.
For the solver1, it is the brute-force result. I think the running time is not reasonable.
I have tested two cases, and both are only a solution.
And even i delete some elements of example51, the running time is still reasonable. So there must something wrong with pruning
The result of many prune . choices is a matrix of choices that can be put into three classes:
1.A complete matrix in which every entry is a singleton choice. In this case expand will extract a single grid that can be checked for validity.
2.A martix that contains the empty choice somewhere. In this case expand will produce the empty list.
3.A matrix that does not conatin the empty choice but does conatin some enrty with two or choices.

I think maybe the many prune. choices meet the third case, leading time consuming much larger.


Modify from the following source for test 2 part 2
_________________________________________________________

A Simple Sudoku Solver
27th September, 2007
In Chapter 05


The Sudoku game: an introduction

The game of Sudoku is played on a 9 by 9 grid, though 
other sizes are also possible. Given a matrix, such as 
that in Bird Figure 5.1 (refer as *example51* in 
section 0 below):

the idea is to fill in the empty cells (represented by 
the 0's) with the digits 1 to 9 so that for each 
row, column and 3 × 3 box contains the numbers 1 to 9.

In general there may be any number of solutions, though 
in a good Sudoku puzzle there should always be a unique 
solution.

_________________________________________________________
0. Basic data types and two examples of Sudoku puzzle:

a. Basic data types

> type Matrix a = [Row a]
> type Row a    = [a]

> type Grid     = Matrix Digit
> type Digit    = Char

> digits  :: [Digit]
> digits  =  ['1'..'9']

> blank   :: Digit -> Bool
> blank   =  (== '0')


b. Examples of sudoku puzzle

i. The Sudoku puzzle given in Figure 5.1 (Bird) and its 
   solution: 

> example51 :: Grid
> example51 = 
>     ["004005700",
>      "000009400",
>      "360000008",
>      "720060000",
>      "000402000",
>      "000080093",
>      "400000056",
>      "005300000",
>      "006100900"]

> solexample51 :: Grid
> solexample51 = 
>     ["184625739",
>      "572839461",
>      "369741528",
>      "728963145",
>      "953412687",
>      "641587293",
>      "417298356",
>      "295376814",
>      "836154972"]


ii. An alternate example of a Sudoku puzzle and its 
    solution: 

> examplealt :: Grid
> examplealt = 
>     ["020000000",
>      "000600003",
>      "074080000",
>      "000003002",
>      "080040010",
>      "600500000",
>      "000010780",
>      "500009000",
>      "000000040"]

> solexamplealt :: Grid
> solexamplealt =
>     ["126437958",
>      "895621473",
>      "374985126",
>      "457193862",
>      "983246517",
>      "612578394",
>      "269314785",
>      "548769231",
>      "731852649"]

_________________________________________________________
1. Specification

> solve1 :: Grid -> [Grid]
> solve1 = filter valid . completions

> completions :: Grid -> [Grid]
> completions = expand . choices

> type Choices = [Digit]

> choices :: Grid -> Matrix Choices
> choices = map (map choice)
>  where choice d | blank d   = digits
>                 | otherwise = [d]

> expand :: Matrix Choices -> [Grid]
> expand = cp . map cp

> cp :: [[a]] -> [[a]]
> cp []       = [[]]
> cp (xs:xss) = [x:ys | x <- xs, ys <- cp xss]

> valid  :: Grid -> Bool
> valid g = all nodups (rows g) &&
>           all nodups (cols g) &&
>           all nodups (boxs g)

> nodups       :: Eq a => [a] -> Bool
> nodups []     = True
> nodups (x:xs) = x `notElem` xs && nodups xs

> rows :: Matrix a -> [Row a]
> rows = id

> cols          :: Matrix a -> [Row a]
> cols [xs]     = [[x] | x <- xs]
> cols (xs:xss) = zipWith (:) xs (cols xss)

> boxs :: Matrix a -> [Row a]
> boxs = map ungroup . ungroup . map cols .
>        group . map group

> ungroup          = concat
> group []         = []
> group (x:y:z:xs) = [x,y,z]:group xs

_________________________________________________________
2. Pruning

> prune :: Matrix Choices -> Matrix Choices
> prune =
>  pruneBy boxs . pruneBy cols . pruneBy rows
>  where pruneBy f = f . map pruneRow . f

> pruneRow :: Row Choices -> Row Choices
> pruneRow row = map (remove ones) row
>  where ones = [d | [d] <- row]

> remove :: Choices -> Choices -> Choices
> remove xs [d] = [d]
> remove xs ds  = filter (`notElem` xs) ds


> many     :: (Eq a) => (a -> a) -> a -> a
> many f x = if x == y then x else many f y
>     where y = f x

> solve2 :: Grid -> [Grid]
> solve2 = filter valid . expand . many prune . choices

_________________________________________________________

 