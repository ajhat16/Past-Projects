# Name: Alex Hatoum
# Spring 2023 CSci4211: Introduction to Computer Networks
# File name: A.py
# This program serves as the sender for the TCP protocol
# Written in Python v3.

from pj2.simulator import sim
from pj2.simulator import to_layer_three
from pj2.event_list import evl
from pj2.packet import *
from pj2.circular_buffer import circular_buffer


class A:
    # Initialization of the A class. This function initializes the sequence
    # number, circular buffer, and the estimated RTT for A.
    def __init__(self):
        self.base = 0
        self.seq = 0
        self.circ_buf = circular_buffer(20)
        self.estimated_rtt = 30
        self.N = 8
        return

    # This is a helper function that searches for any existing timers
    def search_for_timer(self):
        # Start at head of linked list
        q = evl.head

        # Loop until either a timer is found, or the end of the list is reached
        while (q.evtype != "TIMER_INTERRUPT" and q.next != None):
            q = q.next

        # Return True if there is a timer, False if no timer exists
        return q.evtype == "TIMER_INTERRUPT"

    # This function sends a message to B (layer three). Before sending the
    # message, it pushes the message into our circular buffer. It then starts
    # a timer and increments the sequence number.
    def A_output(self, m):

        if self.seq < self.base + self.N:

            # If buffer is full, end execution
            if self.circ_buf.isfull():
                print("circular buffer is full, message dropped: ", m.data)
                return

            # Create our packet for the message
            pkt = packet(seqnum=self.seq, payload=m)

            # Insert the packet into the circular buffer
            self.circ_buf.push(pkt)

            # Send the message to layer three so B can receive it
            to_layer_three("A", pkt)

            # Start a timer if no timer exists
            if not self.search_for_timer():
                evl.start_timer("A", self.estimated_rtt)

            # Increment the sequence number
            self.seq += 1
            return
        else:
            print("window size is full, dropping packet: ", m.data)
            return

    # This function is used to receive messages from B (layer three). It checks
    # attributes of the packet, the checksum and the ACK number, to determine
    # whether or not the packet was poperly received.
    def A_input(self, pkt):
        # If checksums do not match, exit the function
        if pkt.checksum != pkt.get_checksum():
            return
        
        self.base = pkt.acknum + 1

        # If the ACK number matches the sequence number, remove the sequence
        # number from the circular buffer to show that it was properly received
        if self.seq == self.base:
            evl.remove_timer()
            self.circ_buf.pop()
        else:
            if not self.search_for_timer():
                evl.start_timer("A", self.estimated_rtt)

        return

    # This function is used to handle any finished timers when they occur in the
    # program execution. If a timer expires, the function resends any packets
    # that were lost or corrupted.
    def A_handle_timer(self):
        # Loop through the circular buffer, and resend every packet in the
        # buffer to B (layer three)
        i = 0
        for pkt in self.circ_buf.read_all():
            if i == 8:
                break
            to_layer_three("A", pkt)
            i += 1

        # If the buffer is not empty and no timer exists, start a new timer
        if self.circ_buf.count != 0 and not self.search_for_timer() == None:
            evl.start_timer("A", self.estimated_rtt)

        return


a = A()
