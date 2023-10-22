# Alex Hatoum - hatou003
# CSE Lab Machines Used:
###    atlas.cselabs.umn.edu

## Assumptions
The only assumption that I made was not writing the "-1" that specifies the end of the buffer to the consumer file. I did not feel it was necessary to write the -1 to the file, and I thought it would look neater if it was not written to the file. It is still put into the buffer, but just not written to the file.

## How to run the code
Using the Makefile, type in the terminal, "make all", to compile the program code. To run the executable, type, "./part1", and the number of items the producers deposit will default to 100. Otherwise, you may type, "./part1 <some integer>" to specify the amount of items that you want the producers to deposit into the files. The consumer should write to consumer.log all items that it removes from the buffer. The producers write in a randomly determined order, but keep this order for the remainder of the execution. To remove all executable files, type "make clean" into the terminal.