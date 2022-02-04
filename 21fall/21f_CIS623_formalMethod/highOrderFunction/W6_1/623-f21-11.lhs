 ----------------------------------------------------------------------

CIS 623
Lecture 11  haskell script: 623-f21-11.lhs

----------------------------------------------------------------------

> import Prelude hiding (until, iterate, foldr, foldl)
> import Data.Char

Examples of higher functions 

   a. Provide *patterns* of iteration (programming) 

   i. (iteration) describe an iteration digrammatically

      The until function (bird, page 52)

> until       :: (a -> Bool) -> (a -> a) -> a -> a
> until p f x = if p x then x else until p f (f x)

      f: a function to *update*   
      p: a test, check if the current iterate is *good enough*
      x: initially set to the value used to start the 
         iteration


Discussions: using binary search to implement floor
      

   ii.   (fixed point computation) describe via diagrams
                        
 
> iterate     :: (a -> a) -> a -> [a]
> iterate f x = x : iterate f (f x) -- iterate.1

          Note: iterate.1 defines an infinite list

 
   b.   Provide *patterns* for recursion (programming)

   i.   (The foldr function: scaled down version) 

        describe foldr 
        i.   as algebraic operations 
        ii.  a template for primitive recursion

> foldr        :: (a -> b -> b) -> b -> [a] -> b
> foldr f i []     = i
> foldr f i (x:xs) = f x (foldr f i xs)


Discussions of using foldr: sum, product etc.

   ii.  (foldr: variant of foldl: scaled down version)


> foldl        :: (b -> a -> b) -> b -> [a] -> b
> foldl g j []     = j
> foldl g j (y:ys) = foldl g (g j y) ys                    
 


          