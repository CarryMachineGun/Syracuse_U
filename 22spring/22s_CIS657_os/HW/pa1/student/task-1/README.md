# README (For Tinyshell)

## Commands 

### Build command

    $ gcc -o tshell -Werror -Wall  tinyshell.c

  Alternatively you can utilize the `Makefile` by typing

    $ make

### Build command for printing (already included) debug messages (inside `tinyshell.c`)

    $ gcc -DDEBUG -o tshell -Werror -Wall  tinyshell.c

  Alternatively,

    $ make debug


### Run command (for **interactive** use)

    $ ./tshell

### Run command (with stdin or input redirection)

    $ stdbuf -i0 -o0 ./tshell < input_file

  The prefix `stdbuf -i0 -o0` ensures that your program is executed
  as if it were running interactively.

### Run command (with stdin, stdout, and stderr redirection):

    $ stdbuf -i0 -o0 ./tshell < input_file > log_file 2>&1

  The prefix `stdbuf -i0 -o0` ensures that your program is executed
  as if it were running interactively and all output (to `stdout` and
  `stderr`) will be redirected to `log_file`


### Clean command: 

    $ make clean




## How to test your program? (READ CAREFULLY)

It is **recommended** that you **manually test** your shell program 
for each feature separately and incrementally before trying out
the test cases provided in this package.

**Sample test cases**
You are provided with **three** sample inputs (`test-*.in`) 
and the corresponding expected outputs (`test-*.ex`).


You can **manually** use the provided sample inputs and check your solution
against the expected outputs. Alternatively, you can utilize the
provided `Makefile`. 


**About the make commands**
Note that the make commands listed below will first 
clean, build, and run your solution on the provided sample test
input (`test-*.in`). The generated output is stored in `test-*.out`, 
which is compared against the `test-*.ex` file.
If test outcome displays `PASSED`, then your program passes the given test case.
Otherwise, it displays the diff results. 
If your solution fails the test case, you can utilize the
**Troubleshooting tips** provided toward the end of this file.


Three sample test cases include:

(a) To test your solution for normal operations, use `test-simple.in` and
`test-simple.ex`. Alternatively, use

    $ make test-simple

(b) To test your solution for erroneous operations, use `test-error.in`
and `test-error.ex`. Alternatively, use

    $ make test-error

(c) To test your solution for output redirection, use `test-io.in` and
`test-io.ex`. Alternatively, use

    $ make test-io

  **NOTE**: This `test-io.in` test case additionally creates two log files
  (`out-1.log` and `out-2.log`). The Makefile produces a file named `test-io.log`
  that combines the content from all three files (`test-io.out`, 
  `out-1.log`, `out-2.log`) generated when you run this test. Finally
  the makefile matches the expected output `test-io.ex` with the log
  file `test-io.log` to find discrepancies.




**For testing all** of the above test cases using one command

    $ make test-all


If it prints `passed` (for each test case), then your program passes the given test cases.



## Troubleshooting if a test case failed

If your solution fails to pass any test case, the best way to
troubleshoot is to follow these steps:

  - Compile your program manually using 

        $ gcc -o tshell -Werror -Wall  tinyshell.c

  - Manually (not using `make`) run your shell program 
    and provide the test input (as shown when you use
    make to test your shell)

      E.g., 
          
        $ stdbuf -i0 -o0 ./tshell < test-simple.in > test-simple.out 2>&1

    If you're using I/O redirection like above, don't forget the prefix `stdbuf -i0 -o0` 
    which ensures that your program is executed as if it were running interactively. 
    Otherwise, you may observe some unexpected behavior of your program.

  - Manually check and debug the outcome to identify the bug/issue in
    your program




## Only for Advanced Users (OPTIONAL)

**DO IT AT YOUR OWN RISK. NO ASSISTANCE WILL BE PROVIDED 
IF YOU ARE STUCK WITH THIS ADVANCED DEBUGGING OPTION.**

If you are concerned about any memory leak in your program 
or looking forward to learn some new technology 
or willing to take additional challenges, you may check your
program for memory leak. For that, you have to compile your program 
using different options for `gcc`. 

Build command for debugging memory corruptions in `tinyshell.c`:

    $ make asan

Note that any `make test-*` will clean and re-build your program with 
default build command. So you have to **run the program manually** for 
each specific test case.
