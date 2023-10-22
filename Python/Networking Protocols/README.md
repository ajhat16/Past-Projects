# Alex Hatoum,CSCI4211S23,03/18/2023
# Python3,main.py,main.py

## Compilation/Execution
To compile/execute the server program on a CSE Labs Machine (Linux), navigate to the folder containing the protocol you would like to use (either Stop-And-Wait or Go-Back-N), and type "python3 main.py" into the terminal. The program should output all successfully received packets/messages to the terminal.

## Description
This program is meant to demonstrate two of the protocols used in TCP communication. The two protocols in this case are Stop-And-Wait, and Go-Back-N. There are two classes, A and B, that allow for this to happen. A is the "sender" where is sends a message then waits for an ACK/NACK from B. B is the "receiver", so when it receives a message, it determines if the packet was corrupted/lost, then sends an ACK (the same sequence number A sent) or a NACK (the last successfully received sequence number). A sends its messages via the A_output() function. Both classes receive messages through their corresponding input functions, A_input() and B_input(). A's other functions, search_for_timer() and A_handle_timer(), work to establish a timer in program to track which packets timeout and need to be resent.

### Stop-And-Wait: A_input(), A_output(), A_handle_timer()
For the Stop-And-Wait protocol, A's methods to sending and receiving messages is pretty straight forward: A sends a message, waits for an ACK/NACK/timeout, and responds accordingly to what it receives. As said in the previous section, A_output() sends messages to B. In this protocol, A simply sends a message, starts a timer if one does not already exist, changes its state to WAIT_ACK, and increments its sequence number for the next message. It also stores the packet we just sent in a variable to track the last packet that was sent. A_input() is also fairly simply: it compares the checksum of the packet to the expected checksum value to determine if the packet was corrupted, and it changes its state to WAIT_LAYERS if the ACK number is equal to A's sequence number. If the checksums do not match, A exits the function and does not update its state. Finally, A_handle_timer() simply resends the packet stored in our last saved packet variable, and starts a timer if one does not already exist.

### Stop-And-Wait: B_input()
B's only method that has any sort of functionality is B_input(). B_input() first examines the checksum to see if there is any corruption (it returns if there is corruption), then compares the sequence number of the packet to the expected sequence number, and sends a corresponding ACK/NACK.

### Go-Back-N: A_input(), A_output(), A_handle_timer()
Go-Back-N is slightly more complicated when compared to Stop-And-Wait. A_output() first checks to see if the circular buffer is full. If the buffer is full, the packet is dropped and an error message is printed to the terminal. If it is not full, the packet is stored in the circular buffer and sent to B. It then starts a timer if one does not already exist, and incrmenets its sequence number. A_input() is basically the same as A_input() in the Stop-And-Wait protocol: it simply compares the checksums and sequence numbers to see if the packet is corrupted or not. If the packet was not corrupted during transmission, we remove the message from the circular buffer. Finally, A_handle_timer() resends all packets still in the buffer (any packets not removed from the buffer previously were packets that were corrupted/lost), and starts a timer if the circular buffer still has items in it and no timer already exists.

### Go-Back-N: B_input()
B_input() works in a very similar way to the Stop-And-Wait B_input() function. First it checks our checksums to see if the packet was corrupted. If it was not corrupted, it checks the sequence number and sends a corresponding ACK/NACK back to A.

### Stop-And-Wait and Go-Back-N: search_for_timer()
Both protocols have a helper function implemented in the A class named search_for_timer(). This function simply loops through a linked list of events, including timer interrupts, that have occured in our program. If it finds an event labeled TIMER_INTERRUPT, it returns True signifying that a timer already exists. Otherwise, it returns False signifying that we are good to start a new timer since one does not already exist.

## Evaluation
### Test 1: nsimax=20, lossprob=0, corruptprob=0, lambda=1000
This first test went as smoothly as possible since it is the perfect scenario: no risk of any packets being lost or corrupted during transmission. This successfully output the 20 messages it should have.

### Test 2: nsimax=51, lossprob=0, corruptprob=0, lambda=1000 (Go-Back-N specific test)
This test also went as expected. Because the circular buffer has a max size of 50, this function successfully printed our error message on the 51 message it tried to send since the buffer was full.

### Test 3: nsimax=20, lossprob=0.3, corruptprob=0, lambda=1000
This test successfully output all 20 messages.

### Test 4: nsimax=20, lossprob=0, corruptprob=0.3, lambda=1000
This test successfully output all 20 messages.

### Test 5: nsimax=20, lossprob=0.8, corruptprob=0.8, lambda=1000
#### Go-Back-N
The Go-Back-N protocol usually outputs around half of the messages. This is likely because so many packets are in the buffer that it cannot keep up and retransmit all packets in the current window size.

#### Stop-And-Wait
This protocol loses almost every message. The outputs vary slightly, but the program usually prints between 1-7 of the 20 messages it was supposed to print. As shown by the print statements, this is because the protocol is stuck on WAIT_ACK and drops incoming packets.

### Test 6: nsimax=20, lossprob=0.8, corruptprob=0.8, lambda=100000
This test successfully output all 20 messages. This is likely because the program has more time to retransmit messages and does not get overwhelmed, causing no packets to be dropped.