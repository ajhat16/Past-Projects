# Name: Alex Hatoum
# Spring 2023 CSci4211: Introduction to Computer Networks
# File name: B.py
# This program serves as the receiver for a TCP protocol
# Written in Python v3.

from pj2.simulator import to_layer_five
from pj2.packet import send_ack


class B:
    # The initialization of the B class. This function initializes the expected
    # sequence number of B.
    def __init__(self):
        self.expected_seq = 0
        return

    # This function does nothing since B's only purpose is to send ACKs and
    # receive packets from A.
    def output(self, m):
        return

    # This function allows B to receive a packet, determine if the packet was
    # corrupted, and send an ACK or NACK message if it was not properly
    # received. In this case, ACK is sending the same sequence number that it
    # received, and NACK is sending the last successful sequence number that it
    # received.
    def B_input(self, pkt):
        # If the checksums do not match, send NACK and exit the function
        if pkt.checksum != pkt.get_checksum():
            send_ack("B", self.expected_seq - 1)
            return

        # If the packet's sequence number matches our expected sequence number
        # send an ACK and increment our expected sequence number
        if pkt.seqnum == self.expected_seq:
            to_layer_five("B", pkt.payload.data)
            send_ack("B", self.expected_seq)
            self.expected_seq += 1
        else:
            # Otherwise, send NACK with the last successful sequence number
            send_ack("B", self.expected_seq - 1)

    # B does not need any timer, so this function does nothing.
    def B_handle_timer(self):
        return


b = B()
