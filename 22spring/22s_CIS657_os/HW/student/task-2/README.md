# README

Build command: 

    $ make

Run command: 

    $ ./prog

Clean command: 

    $ make clean


## How to test your program?

You are provided with the expected output `sample.ex`. 

**Option 1**:
You can compare the output of your program with `sample.ex` manually.


**Option 2**:
You can utilize the `diff` utility program available in Linux as
follows:

    $ ./prog > out.log
    $ diff out.log sample.ex    

If `out.log` and `sample.ex` is identical, then `diff` will produce no
output. Otherwise, `diff` will show the discrepancies between `out.log` 
and `sample.ex`.



**Option 3**:
Alternatively, you can utilize `Makefile` which includes a similar
`diff` command to compare your program's output with `sample.ex`. 
You can use the following command to test your program

    $ make test

This will first clean, build and run your program on the sample input.
The generated output is stored in `test.out`, which is compared against 
the `sample.ex` file.
If test outcome displays `Passed`, then your program passes the given test case.
Otherwise, it displays the diff results.

