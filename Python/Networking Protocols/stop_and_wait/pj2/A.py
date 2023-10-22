# Name: Alex Hatoum
# Spring 2023 CSci4211: Introduction to Computer Networks
# File name: A.py
# This program serves as the sender for a TCP protocol
# Written in Python v3.

from pj2.simulator import sim
from pj2.simulator import to_layer_three
from pj2.event_list import evl
from pj2.packet import *


class A:
    # Initialization of the A class. This function initializes the sequence
    # number, the estimated RTT for A, a tracker for the previously sent packet,
    # and a state tracker to tell the program if A is waiting for a message from
    # the layer, or if it is waiting for an ACK.
    def __init__(self):
        self.state = "WAIT_LAYERS"
        self.estimated_rtt = 30
        self.prev_pkt = packet()
        self.seq = 0
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

    # This function sends a message to B (layer three). After sending the
    # message, it starts a timer if one does not already exist. Additionally,
    # the program updates the state from WAIT_LAYERS to WAIT_ACK.
    def A_output(self, m):
        # Create our packet for the message
        if self.state == "WAIT_ACK":
            print("waiting for ack, dropping the packet: ", m.data)
            return

        pkt = packet(seqnum=self.seq, payload=m)

        # Send message to layer three so B can receive it
        to_layer_three("A", pkt)
        self.prev_pkt = pkt

        # If a timer does not exist, start a new timer
        if not self.search_for_timer():
            evl.start_timer("A", self.estimated_rtt)

        # Update state and sequence number
        self.state = "WAIT_ACK"
        self.seq += 1

        return

    # This function is used to receive messages from B (layer three). It checks
    # attributes of the packet, the checksum and the ACK number, to determine
    # whether or not the packet was poperly received.
    def A_input(self, pkt):
        # If checksums do not match, exit the function
        if pkt.checksum != pkt.get_checksum():
            return

        # If the ACK number matches the sequence number, update the state to
        # WAIT_LAYERS
        if self.seq == pkt.acknum + 1:
            evl.remove_timer()
            self.state = "WAIT_LAYERS"

        return

    # This function is used to handle any finished timers when they occur in the
    # program execution. If a timer expires, the function resends the packet
    # stored in our previous packet variable.
    def A_handle_timer(self):
        # Send the last packet to layer three so B can receive it
        to_layer_three("A", self.prev_pkt)

        # Start a new timer if one does not already exist
        if not self.search_for_timer():
            evl.start_timer("A", self.estimated_rtt)


a = A()
