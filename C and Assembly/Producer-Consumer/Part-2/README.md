# Alex Hatoum - hatou003
# CSE Lab Machines Used:
###    atlas.cselabs.umn.edu

## Assumptions
The only assumption that I made was not writing the "-1" that specifies the end of the buffer to the consumer file. I did not feel it was necessary to write the -1 to the file, and I thought it would look neater if it was not written to the file. It is still put into the buffer, but just not written to the file.

## How to run the code
Using the Makefile, type "make all" into the terminal. This will compile part2.c, producer.c, and consumer.c all with the header file part2.h. To run the program, type "./part2" or "./part2 <some integer>" into the terminal. If you do not specify any command line arguments, the number of items the producers write defaults to 100. The program's data will be written to all .log files. Note that you may need to remove the shared memory segment between executions. This can be done by first typing "ipcs -m", then typing "ipcrm -m <shmid>" into the terminal (separate commands). This will delete the shared memory segment, if any, as long as you put the segment's corresponding shmid in the second command. To remove all executables, type "make clean" into the terminal.