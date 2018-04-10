# Bst
Bst is a program that creates a binary search tree of integers based on information from a file.  The possible commands include insert, search, print, and delete.  The program will read the commands, and take the necessary actions.

Included are two folders: /bst and /data. /bst contains the relevant C file, bst.c, and a makefile. /data contains several instances of data that can be used to display the program at work.

In the data folder, there are two types of files: test files, and output files. After compiling, the program is passed a test file containing a set of instructions. The data that the program outputs can be checked against the associated output file for correctness. Test files are of the form "test.X.Y", and output files are of the form "test.X.Y.out", with X and Y being the ID numbers of the associated test.

Example: "/bst test.1.2" from the command line will produce output equivalent to the text file "test.1.2.out".
