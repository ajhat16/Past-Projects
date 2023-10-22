# Name: Alex Hatoum
# Spring 2023 CSci4211: Introduction to Computer Networks
# File name: DNSServer.py
# This program serves as the server of DNS query.
# Written in Python v3.
import csv
import os
import random
import socket
import threading
import time
from socket import *

# Global for cache file
DNS_FILE = 'DNS_mapping.txt'

# Global list for the dns-server-log.csv file
list_for_logger = []
cache_list = []

# The main function for this program. This function is responsible for opening
# the TCP socket, starting a command monitor thread, and starting the server
# thread.
def main():
    try:
        # Open the cache file to store it into a global variable
        with open(DNS_FILE, 'r') as cache:
            lines_list = cache.readlines()

            for entry in lines_list:
                # Prevents unwanted lines such as newlines from appearing in our
                # cache global list
                if len(entry) > 1:
                    # Separate the name from the IP
                    cache_list.append(entry.split(','))

    except Exception:
        with open(DNS_FILE, 'x') as cache:
            print('No cache file found. Creating cache file...')


    host = "localhost"  # Hostname. It can be changed to anything you desire.
    port = 9889  # Port number.

    # create a socket object, SOCK_STREAM for TCP
    sSock = socket(AF_INET, SOCK_STREAM)

    # bind socket to the current address on port
    sSock.bind((host, port))

    # Listen on the given socket maximum number of connections queued is 20
    sSock.listen(20)

    # Runs in a monitor in the background to check if "exit" is input to the
    # server
    monitor = threading.Thread(target=monitorQuit, args=[])
    monitor.start()

    save = threading.Thread(target=saveFile, args=[])
    save.start()

    print("Server is listening...")

    while 1:
        # blocked until a remote machine connects to the local port
        connectionSock, addr = sSock.accept()
        server = threading.Thread(target=dnsQuery, args=[connectionSock, addr[0]])
        server.start()


# This function is repsonsible for searching for the IP address of the DNS given
# by the client. The function first checks the local cache, and if the DNS is
# not present in there, it instead uses the gethostbyname() function to search
# for the IP address. Finally, it sends the domain namem, IP address, and the
# method it used to get the address back to the client.
def dnsQuery(connectionSock, srcAddress):

    # Receive data (sent by the client) from the socket
    data = connectionSock.recv(1024).decode()
    
    response_string = ''
    cache_hit = False

    # Search for the client's query in the cache
    for entry in cache_list:
        if entry[0] == data:
            cache_hit = True

            # ip_list stores just the IP(s) stored in the cache, and selects one
            # using the dnsSelection() function
            ip_list = entry[1:]
            ip = dnsSelection(ip_list)

            # Remove newline so the formatting does not get messed up
            ip = ip.rstrip('\n')

            # Log the query
            list_for_logger.append(data+','+ip+',CACHE')

            # Response message for client (used later)
            response_string = data + ':' + ip + ':CACHE'
            
            # No longer need to loop since we already found the query
            break

    # This conditional check was necessary because when the user quits by typing
    # 'q', it sends an empty string as data for the query, which may cause weird
    # messages to be printed and written to files.
    if data != '':
        if not cache_hit:
            try:
                ip = gethostbyname(data)
            except Exception:
                ip = 'Host not found'

            # Response message for client
            response_string = data + ':' + ip + ':API'

            # Log the query, then write it to the local cache for future use
            list_for_logger.append(data+','+ip+',API')

            # Append the query to the cache_list
            cache_list.append([data, ip])

        # Open the csv file for writing
        with open('dns-server-log.csv', 'w', newline='') as logger:
            # Set writing properties for the file
            writer = csv.writer(logger, delimiter='\n')

            # Write the entries from the logger list to the file
            writer.writerow(list_for_logger)

        print(response_string)

        # Encode the response with UTF-8, the standard for TCP messages, and
        # send the encoded message back to the client
        response = response_string.encode()
        connectionSock.sendall(response)

    connectionSock.close()

# Selects a random IP from the IP list. If there is only 1 IP in the list, that
# IP is selected by default.
def dnsSelection(ipList):
    return random.choice(ipList)

# Function to update the cache file every 15 seconds
def saveFile():
    while 1:
        time.sleep(15)
        with open(DNS_FILE, 'w') as cache:
            for entry in cache_list:
                entry[1] = entry[1].rstrip('\n')
                cache.write(entry[0] + ',' + entry[1] + '\n')

# Monitors commands typed into the server terminal, but only reacts if "exit"
# is typed into th terminal.
def monitorQuit():
    while 1:
        sentence = input()

        # Kill the server and write to the local cache file if exit is typed
        if sentence == "exit":
            with open(DNS_FILE, 'w') as cache:
                for entry in cache_list:
                    entry[1] = entry[1].rstrip('\n')
                    cache.write(entry[0] + ',' + entry[1] + '\n')

            os.kill(os.getpid(), 9)

# Call the main function when execution begins
main()
