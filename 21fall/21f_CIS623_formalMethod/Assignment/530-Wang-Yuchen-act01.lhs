---------------------------------------------------------------------------
Fall 2021 CIS 623
Activity 1
---------------------------------------------------------------------------

Lastname :  < Wang >
Firstname:  < Yuchen > 
Stud. num:  < 530 >

---------------------------------------------------------------------------

1. Please check (put a `X` within the square bracket) the description
   that indicates the way you use Haskell:

[ ] Running Haskell via the class VM within a Windows Environment, based 
    on the description 

    Using Haskell on Windows  

    in the folder

    Content > Other resources > Programming environment and instructions

[X] Running emacs in Mac, based on the description 

    Using Haskell on Mac  

    in the folder

    Content > Other resources > Programming environment and instructions


[ ] Other (Please specify)

---------------------------------------------------------------------------

2. Please indicate if you can run a literate Haskell script successfully 
   or not by checking (put a `X` within the square bracket) one of the 
   following:
   
[X] I can create, edit, load and interpret a Haskell script without any
    problems.

[ ] I attempted to follow the instructions given by the TA but I'm not
    able to run a Haskell script. 

    If you check this box, please elaborate the difficulties in the space
    provided below:

    < Fill in the blanks, if applicable >

---------------------------------------------------------------------------

Remarks:  As an experiment, you may use the following code (given in class/text) 
to test run the Haskell function qsort with this script:

> qsort    :: (Ord a) => [a] -> [a]
> qsort []     = []
> qsort (x:xs) = qsort smaller ++ [x] ++ qsort larger
>     where 
>       smaller = [a | a <- xs, a <= x]
>       larger  = [b | b <- xs, b > x ]

