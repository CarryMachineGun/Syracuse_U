Test 3
Student No:34
Last Name:Ren
First Name:Zhen

Question1:
The maximum segement sum problem is a question tha to compute the maximum of the sums of all segments in the sequence. A segement can also be called a contiguous subsequence.
For example, [-1,2,-3,5,-2,1,3,-2,-2,-3,6] has the maximum sum 7, which is the sum of segment [5,-2,1,3].
On the other hand, the sequence [-1,-2,-3] has a maximum segement sum of zero, since the empty sequence is a segment of every list and its sum is zero. It follows that the maximum segment sum should be nonnegative.
For this problem, we should find a list of all segments of a list and count the sum one by one to find the maximum segment sum.

Question2:
Formal specification to the MSS problem
The input should a list with integers and the output should be a number

function describtion

>mss::[Int]->Int
>mss= maximum . map sum . segments

>segments=concat . map inits . tails

>inits::[a]->[[a]]
>inits []=[[]]
>inits (x:xs) =[]: map (x:) (inits xs)

>tails::[a]->[[a]]
>tails []=[[]]
>tails (x:xs)=(x:xs):tails xs

Question3
(1):

>mss1::[Int]->Int
>mss1=maximum.map (maximum . scanl (+) 0). tails

(2):
The running time of mss will take a number of step propportional to n^3 on a list of length n. There are about n^2 segments, and summing each of them will take n steps, so in total it will take n^3 steps.It is not obvious that we can do better than cubic time for mss.
We can start by installing the definition of segments:
maximum . map sum . concat . map inits . tails = {apply a law: map f . concat = concat . map (map f)  and subterm map sum. concat}
maximum . concat . map (map sum) . map inits .tails={map f .map g= map (f. g)}
maximum . concat . map (map sum . inits) .tails={ maximum. concat = maximum . map maximum}
maximum . map (maximum . map sum . inits) .tails = {use the property of scanl: map sum. inits= scanl (+) 0}
maximum . map (maximum . scanl (+) 0) .tails

The next step is to concern about maximum . scanl (+) 0. We should do about foldr1 max . scnal (+) 0
For instance, 
scanl (+) 0 [1,2,3]
=[0,0+1,(0+1)+2,((0+1)+2)+3]
=[0,1,3,6]
=0:map (1+) [0,2,5]
=0:map (1+) (scanl (+) 0 [2,3])

ghci>scanl (+) 0 [1..10]
[0,1,3,6,10,15,21,28,36,45,55]

scnal's definition is:

>scanl1::(b->a->b)->b->[a]->[b]
>scanl1 f e= map (foldl f e). inits

Then based on the scanl's property,we can make
map sum . inits= scan0l (+) 0  ->
maximum . map (maximum .scanl (+) 0) .tails
The running time is n^2 time now.


Question4:
(1):

>max1::Int->Int->Int
>x `max1` y = 0 `max` (x+y)

>infix @@
>((@@))=max1

>mss2::[Int]->Int
>mss2= maximum . (scanr (@@) 0)

(2):

scanr (+) 0 [x1,x2,...,xn]
=[...,(((0+xn)+x(n-1))+x(n-2))+x(n-3),((0+xn)+x(n-1))+x(n-2),(0+xn)+x(n-1),0+xn,0]

(3):
We mainly concern about maximum.scanl (+) 0
We can prove about foldr1 max .scanl (+) 0
This is a fusion rule, But we can use scnal (+) 0 expressed by a foldr.
scanl (+) 0 [x,y,z]
=[0,0+x,(0+x)+y,((0+x)+y)+z]
=[0,x,x+y,x+y+z]
=0:map (x+) [0,y,y+z]
=0:map (x+) (scanl (+) 0 [y,z])
This calculation exploits the associativity of (+) and the fact that 0 is the identity element of (+). The result suggests, more generally, that
scanl (@) e =foldr f [e]
      where f x xs=e:map (x@) xs
(@) is assoicative with identity e. Let us take this on trust and move on to the conditions under which
foldr1 (<>) . foldr f [e]= foldr h b
      where f x xs=e:map (x@) xs
foldr1 (<>) is strict and foldr1 (<>) [e]= e. So b=e.
foldr (<>) (e:map (x@) xs)= h x (foldr1 (<>) xs)
for all x and xs. The left-hand side simplifies to
e <> (foldr1 (<>) (map (x@) xs))
Taking the singleton case xs=[y]
h x y=e <> (x @ y)
That gives us our definition of h, but we still have to check that
foldr1 (<>) (e:map (x@) xs) = e <> (x @ foldr1 (<>) xs)
Simplifying both sides, this equation holds provided
foldr1 (<>) . map (x@)= (x@). foldr1 (<>)
This final equation holds provided (@) distributes over (<>)
x@ (t <> z) = (x @ y) <> (x @ z)
Back to the maximum segment sum . We have arrived at
maximum . map ( foldr (@) 0) .tails
     where x @ y = 0 `max` (x+y)
What we have left looks very like an instance of the scanl rule of the previous section, except that we have a foldr not a foldl and a tails not an inits. But a similar calculation to the one about scanl reveals
map (foldr f e) . tails = scnar f e

>scanr1::(a->b->b)->b->[a]->[b]
>scanr1 f e []= [e]
>scanr1 f e (x:xs)=f x (head ys):ys
>                    where ys=scanr f e xs

Finally we get
mss2=maximum .scanr (@) 0
      where x @ y = 0 `max` (x+y)
