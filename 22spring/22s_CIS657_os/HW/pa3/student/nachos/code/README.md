# README for NACHOS
Author: Endadul Hoque (enhoque@syr.edu)


## How to build NACHOS?

Nachos should be built from the `build.linux/` directory.

Now follow the steps to build NACHOS:

        $ cd build.linux/
        $ make depend
        $ make

  `make depend` is essential. **Don't miss this step**.

After the initial time, for incremental build, try this

    $ cd build.linux
    $ make


However, if you think the build is behaving weirdly or you observe the
executable is not reflecting your edits in the code, it's a good idea of
clean and re-build nachos. 

    $ make distclean
    $ make depend
    $ make



## How to check if the build was successful?

There may be some warnings during compilation, but that is OK. 
If you observe `nachos` executable inside `build.linux/`, that means it
compiled and built the OS. Now check if it runs:

    $ cd build.linux/ 
    $ ./nachos -K

If it runs successfully, it should print some messages. For example,
you may notice some messages like "*** thread 1 looped 0 times". After
printing the messages, `nachos` seizes to execute and becomes
unresponsive. You may have to type `ctrl+c` to quit `nachos`.
Unresponsive behavior will make sense once you understand its internals.

If you do not observe those messages, check the error message to resolve or
re-build `nachos` again. 



## How to build NACHOS (test) programs?

The programs to be executed on NACHOS are built separately. All
programs are stored in `test/`.

**Build executables of the test programs**. Executables are created in
two stages: 

   - First, the compiler creates a .coff (regular MIPS exe) file
   - Secode, the utility tool `coff2noff` (inside `nachos/coff2noff/`) is used to convert .coff file
     to an executable for NACHOS

  *Build command*: 

    $ cd test/
    $ make


  *Clean command*: to remove `*.o` and `*.coff` files

    $ cd test/
    $ make clean

  *Dist-clean command:*  to remove all files produced by `make`
  including the executables for nachos

    $ cd test/
    $ make distclean

