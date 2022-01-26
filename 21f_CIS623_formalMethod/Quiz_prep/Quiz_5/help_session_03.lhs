> reverse    :: [a] -> [a]
> reverse []     = []                 -- reverse.1 
> reverse (x:xs) = reverse xs ++ [x]  -- reverse.2



> (++) :: [a] -> [a] -> [a]
> [] ++ ys     = ys                -- ++.1
> (x:xs) ++ ys = x : (xs ++ ys)    -- ++.2

---------------------------------------------------------------------------

Finite lists

1. reverse . reverse xs = xs

base case : []
> reverse . reverse []
> reverse []
> []

Induction step: Assume reverse . reverse xs = xs holds true for all finite lists xs

Induction Hypothesis: reverse . reverse (x:xs) = (x:xs)

approach 1:

> reverse . reverse (x:xs) = (x:xs)
> reverse (reverse xs ++ [x])
applying distributivity 
> reverse [x] ++ reverse (reverse xs)
> x ++ xs
> x:xs

approach 2:

reverse . reverse (x:xs) = (x:xs)

> reverse (reverse (x:xs))
> reverse (reverse xs ++ [x])
applying outer reverse using property *
> x : reverse(reverse xs)
> x : xs

reverse (ys ++ [x]) = x : reverse ys --- property *

base case : ys = []
>reverse ([] ++ [x])
>reverse [x]
> x


rhs: x : reverse []
> x :[]
> x


IH: reverse ((y:ys) ++ [x])
> reverse(y : (ys ++ [x]))
> reverse (ys ++ [x]) ++ [y]
> x : reverse ys ++ [y]

rhs = x : reverse (y:ys)
> x : reverse ys + [y]


2 . reverse (xs ++ ys) = reverse ys ++ reverse xs

Base case: xs = []

reverse ([] ++ ys)
> reverse ys


rhs: reverse ys ++ reverse []
> reverse ys


IH: reverse ((x:xs) ++ ys) = reverse ys ++ reverse (x:xs) 
> reverse (x : (xs ++ ys))
> reverse (xs ++ ys) ++ [x]
> reverse ys ++ reverse xs ++ [x]
unapplying reverse xs
> reverse ys ++ reverse (x:xs)

Functor properties of map

3 . map id = id

> map id xs = id xs
> map id xs = xs

Base case : xs = []

map id []
[] = []

IH : map id (x:xs) = x : xs

> id x : map id xs
> x : xs

4. map f . map g  = map  f . g

map (f.g) xs = map f ( map g xs)

base case xs = []

> map (f.g) []
> []

rhs : map f ( map g [])
> map f ([])
> []

IH :map (f.g) (x:xs) = map f ( map g (x:xs))

> map (f. g) (x:xs)
> (f.g) x : map (f.g) xs
> f(g x) : map f (g xs)

rhs :  map f ( map g (x:xs))

> map f ( g x : map g xs)

> f ( g x) : map f ( g xs)


Partial lists

1. xs ++ ys = xs
base case : xs = undefined

> undefined ++ ys
> undefined = undefined

IH = (x:xs) ++ ys
x :(xs ++ ys)
x : xs


2 . (xs ++ ys) ++ zs = xs ++ (ys ++ zs)

base case : xs = undefined

(undefined ++ ys) ++ zs
undefined ++ zs
undefined

RHS :  undefined ++ (ys ++ zs)
> undefined

IH :  ((x:xs) ++ ys) ++ zs
> (x : (xs ++ ys) ++ zs
> (x : xs ++ zs)
> (x : xs)

RHS : (x:xs) ++ (ys ++ zs)
> x : (xs ++ ys) ++ zs)
> x : xs ++ zs
> x : xs

3.  reverse . reverse xs = xs

base case : xs = undefined

reverse (reverse undefined)

undefined = undefined

IH : reverse (reverse (x:xs)) = (x:xs)
reverse ( reverse xs ++ [x]) which is not true for partial lists 
because reverse xs ++ [x] = x : reverse x does not hold true for partial lists

Proof:

reverse xs ++ [x] = x : reverse xs

> (reverse undefined) ++ [x]
> undefined ++ [x]
> undefined

RHS:
> x : reverse undefined
> x : undefined

Here LHS /= RHS and therefore, above mentioned property does not hold true for partial lists

















