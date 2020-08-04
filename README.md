# Fun-Sudoku-Pthreads

### Validating a Sudoku Using Multithreading with POSIX Pthreads

Fun-Sudoku-Pthreads was developed in c language to demonstrate how threads can be used to validate a Sudoku puzzle efficiently using multithreading with POSIX pthreads. Validating a single Sudoku on a main thread is a simple task for today's computers, but imagine having thousands of Sudokus to validate! If you said "Yikesy wowzer", you're right! If you got dem' threads, why you let them hang around? Create threads to run concurrently through the rows, columns and subgrids for much faster validation. This program generates a valid Sudoku on 25% of runs, only columns valid on 25% of runs, and only rows valid on 50% of runs. Run it multiple times to see all three types of validation. 

## Features!
If all threads can validate their content, then the Sudoku itself is valid. This program implements 11 fun fun threads. 
* 1 thread to validate the columns
* 1 thread to validate the rows
* 9 threads each assigned to validate one of the nine subgrids

# Example Input
```sh
$./fun-sudoku-pthreads
Generating Random Sudoku
|3||1||6||5||7||8||4||9||2|
|5||2||9||1||3||4||7||6||8|
|4||8||7||6||2||9||5||3||1|
|2||6||3||4||1||5||9||8||7|
|9||7||4||8||6||3||1||2||5|
|8||5||1||7||9||2||6||4||3|
|1||3||8||9||4||7||2||5||6|
|6||9||2||3||5||1||8||7||4|
|7||4||5||2||8||6||3||1||9|

Rows are valid.
Columns are valid.
Subgrids are valid.

***Results***

VALID SUDOKU.
```

### Tech

Tech uses the very very very advanced terminal shell and gcc compiler.

### Installation

You don't need a Makefile for this Boo, it's only one file. Don't be lazy and give it a run from gcc. Don't forget to add -pthread when compiling!

```sh
$ gcc -pthread -o fun-sudoku-pthreads fun-sudoku-pthreads.c
```
