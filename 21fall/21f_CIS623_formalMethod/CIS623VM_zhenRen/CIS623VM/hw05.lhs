Spring 2021 
CIS 623
HW 5 

---------------
-- question 1
---------------


a. Universal property of fold states that, given:


> fold            :: (a -> b -> b) -> b -> ([a] -> b)
> fold f v []     = v
> fold f v (x:xs) = f x (fold f v xs)




    g :: [a] -> b
   

   The  conditions (I) and (II) are 
   equivalent:

   (I)          g []     = v           --  I.1
                g (x:xs) = f x (g xs)  --  I.2 

   (II)         g = fold f v           -- II.1


b. Prop:  (3*) . product = fold (*) 3

proof:  By universal property of fold, consider g be the function

        g = (3*) . product 

        It suffices to show that, for this g: 

        g []     = 3                  -- b.1
        g (x:xs) = (*) x (g xs)       -- b.2

        Note that:

        product []      = 1    
        product (x:xs)  = x * product xs 

b.1:    LHS
        =
        g [] 
        = {definition of g} 
        ((3*) . product) [] 
        = {product [] = 1} 
        (3*) 1
        = {arithmetic}
        3*1
        = {arithmetic}
        3
        =
        RHS

Hence  b.1 holds.

b.2:    LHS:

        g (x:xs) 
        = {definition of g}
        ((3*) . product) (x:xs) 
        = {product (x:xs) x * product xs}
        (3*) x * product xs
        = {arithmetic}
        3 * (x * product xs)
        
        RHS:

        (*) x (g xs)
        ={definition of (*)}
        x * (g xs)
        ={definition of g}
        x * (((3*) . product) xs)
        ={simplify}
        x * (3 * product xs)
        ={* is associative and commutative}
        3 * (x * product xs)

Hence: LHS = RHS and so b.2 holds.


--------------------------------------------------------------------------------

---------------
-- question 2
---------------

a. 

We consider the product function defined as follows:

product :: (Num a) => [a] -> a
product []     = 1                 -- product.1
product (x:xs) = x * product xs    -- product.2



We calculate a new definition of product by computing f and v so that 

product = fold f v 

1.      product [] = v
        ={product.1} 
        1  = v

We will set v = 1

2.        product (x:xs)  = f x (product xs)
      <=> {product.2}
          x * product xs  = f x (product xs)
       <= {(generalize) y = product xs} 
          x * y  = f x y
      <=> {Functions}    
          f = (*)

We will set f = (*)

By 1 and 2, we calculate the new definition for product as

product = fold (*) 1


--------------------------------------------------------------------------------


b.

We consider the and function defined as follows:

and        :: [Bool] -> Bool
and []     =  True               -- and.1
and (b:bs) =  b (&&) and bs      -- and.2


We calculate a new definition of product by computing f and v so that 

and = fold f v 


1.
                and [] = v
            <=> {and.1}
                True   = v

We will set v = True

2. 
                and (b:bs) = f b and bs
            <=> {and.2}
                b (&&) and bs = f b and bs
             <= {(generalize) c = and bs}
                b (&&) c = f b c
            <=> {Functions}     
                f = (&&)

We will set f = (&&)


By 1 and 2, we calculate the new definition for product as

and = fold (&&) True


--------------------------------------------------------------------------------

Question 3


a. (Fusion property of fold)

Given functions f, g, h and values v, w are of the following types:

      f ::  r -> s -> s
      v ::  s
      g ::  r -> s -> s
      w ::  s
      h ::  s -> s
      
Then the fusion property of fold state that:

If
          h w        = v           -- fusion.1
          h (g x y)  = f x (h y)   -- fusion.2

Then
        h . fold g w = fold f v    -- fusion 3


--------------------------------------------------------------------------------


b.      Following the suggestions given in the paper, we will use 
        the fusion property to demonstrate that

        (<+> a) . fold (<+>) b = fold (<+>) (b (<+>) a)        

        where <+> is an arbitrary infix operator that is associative.

        That is, we will consider:

        f: (<+>)        -- d.1
        v: (b (<+>) a)  -- d.2       
        g: (<+>)        -- d.3   
        w: b            -- d.4
        h: (<+> a)      -- d.5

        and it suffices to verify properties fusion 1 and 2
      
        -- verify  fusion.1

        LHS
        ={fusion.1}
        h w        
        ={d.4 and d.5}
        (<+> a) b
        ={property of the <+> operator}
        b <+> a
        ={d.2}
        v
        ={fusion.1}           
        RHS

        Hence fusion.1 holds 

        -- verify fusion.2
        
        LHS
        ={fusion.2}
        h (g x y)  
        = {d.5 and d.3}
        (<+> a) ((<+>) x y)
        ={<+> is an infix operator}
        (<+> a) (x <+> y)
        = {property of (<+> a)}
        ((x <+> y) <+> a) 


        RHS
        ={fusion.2}
        f x (h y) 
        ={d.1 and d.5}
        (<+>) x ((<+> a) y)
        ={property of (<+> a)}
        (<+>) x (y <+> a)
        ={property of (<+>)}
        x <+> (y <+> a)
        ={<+> is associative}
        ((x <+> y) <+> a) 
        = {fusion.2}
        LHS

        Hence fusion.2 holds.

By fusion property of fold, we have

          (<+> a) . fold (<+>) b = fold (<+>) (b (<+>) a)        
   
--------------------------------------------------------------------------------

c.      

We prove the following proposition:


Prop.    double . sum = foldr ((+) . double) 0


by using the fusion property of fold (Note: The fold operator in Hutton's 
paper refers to the foldr function in Haskell).


That is, we will adopt the following definition for sum and double

        sum = foldr (+) 0        -- sum.3
      
> double   :: (Num a) => a -> a 
> double d = d + d        
  
        turning the prop. we are refering as:

        double . foldr (+) 0  = foldr ((+) . double) 0

        and consider:

        f: (+) . double  -- e.1
        v: 0             -- e.2
        g: (+)           -- e.3   
        w: 0             -- e.4   
        h: double        -- e.5

        and it suffices to verify properties fusion 1 and 2

        -- verify fusion.1

        LHS
        ={fusion 1}
        h w
        ={e.1}
        double 0
        ={double.1} 
        0 + 0
        ={arithmetic}
        0
        ={e.2}
        v

        -- verify fusion.2

        LHS
        ={fusion.2}
        h (g x y)
        ={e.3 and e.5}
        double ((+) x  y)
        ={definition of (+)}
        double (x + y)
        ={definition of double}
        (x+y) + (x+y)

        
        RHS
        ={fusion.2}
        f x (h y) 
        ={e.5}
        ((+).double) x (h y)
        ={definition of ((+).double) operator}
        ((+) (x + x)) (y+y)
        ={definition of the (+) operator}  
        (y+y) + (x+x)
        ={+ is associative and commutative}
        (x+y) + (x+y)
        =
        LHS

        Hence fusion.2 holds.

By fusion property of fold, we have

        double . foldr (+) 0  = foldr ((+) . double) 0