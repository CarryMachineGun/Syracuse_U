hw03
Student No:34
Last Name:Ren
First Name:Zhen


>data Formula=  Var Char
>             | Not Formula
>             | And Formula Formula
>             | Or Formula Formula
>             | Imply Formula Formula

>instance Show Formula 
>    where
>      show (Var a)="'"++a:""++"'"
>      show (Not a)="~"++"("++(show a)++")"
>      show (And p q)="("++(show p)++")"++"A"++"("++(show q)++ ")"
>      show (Or p q)="("++(show p)++")"++"V"++"("++(show q)++")"
>      show (Imply p q)="("++(show p)++")"++"->"++"("++(show q)++")"

test for expression

>testcase1::Formula
>testcase1=And (Var 'p') (Var 'q')

>testcase2::Formula
>testcase2=Or (Var 'p') (Var 'q')

>testcase3::Formula
>testcase3=Imply (Var 'p') (Var 'q')


>implfree::Formula->Formula
>implfree (Not a)=(Not (implfree a))
>implfree (And a b)=(And (implfree a) (implfree b))
>implfree (Or a b)=(Or (implfree a) (implfree b))
>implfree (Imply a b)=(Or (Not (implfree a)) (implfree b))
>implfree a=a

testfor implfree


>testcase4::Formula
>testcase4=Imply (And (Var 'p') (Var 'q')) (Or (Var 'p') (Var 'q'))

explain: ('p' A 'q')-> ('p' V 'q')
expected result:(~(('p')A('q')))V(('p')V('q'))
output:
*Main> implfree testcase4
(~(('p')A('q')))V(('p')V('q'))

>testcase5::Formula
>testcase5=Imply (Imply (Var 'p') (Var 'q')) (Var 'r')

explain:('p'->'q')->'r'
expected result:(~((~('p'))V('q')))V('r')
output:
*Main> implfree testcase5
(~((~('p'))V('q')))V('r')

>nnf::Formula->Formula
>nnf (Not (Not a))=a
>nnf (And p q)=(And (nnf p) (nnf q))
>nnf (Or p q)=(Or (nnf p) (nnf q))
>nnf (Not (And p q))=(Or (nnf (Not p)) (nnf (Not q)))
>nnf (Not (Or p q))=(And (nnf (Not p)) (nnf (Not q)))
>nnf a=a

>testcase6::Formula
>testcase6= (Not (Not (Var 'p')))

explain: ~ ~'p'
expected result:'p'
output:
*Main> nnf testcase6
'p'

>testcase7::Formula
>testcase7= (Not (Not (Not (And (Var 'p') (Var 'q')))))

explain: ~ ~ ~ ('p' A 'q')
expect result:~(('p')A('q'))
output:
*Main> nnf testcase7
~(('p')A('q'))


>distr::Formula->Formula->Formula
>distr (And p q) r=And (distr p r) (distr q r)
>distr p (And q r)=And (distr p q) (distr p r)
>distr p q=(Or p q)

>cnf::Formula->Formula
>cnf (And p q)=And (cnf p) (cnf q)
>cnf (Or p q)=distr (cnf p) (cnf q)
>cnf a=a

>testcase8::Formula
>testcase8=Not (And (Var 'p') (Var 'q'))

explain: ~ ('p' A 'q')
expect result:~(('p')A('q'))
output:
*Main> cnf testcase8
~(('p')A('q'))


>testcase9::Formula
>testcase9=Or (Var 'p') (And (Var 'q') (Var 'r'))

explain: 'p' V ('q' A 'r')
expected result:(('p')V('q'))A(('p')V('r'))
output:
*Main> cnf testcase9
(('p')V('q'))A(('p')V('r'))