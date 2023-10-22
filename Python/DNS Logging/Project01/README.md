# Alex Hatoum,CSCI4211S23,02/22/2023
# Python3,main.py,main.py

## Compilation/Execution
To compile/execute the server program on a CSE Labs Machine (Linux), type "python3 DNSServerV3.py" into one terminal. After the server starts running, then in a separate terminal type "python3 DNSClientV3.py". This should connect the client to the server and begin executing the program as normal.

## Description
This program establishes a TCP connection with a client on port 9889 via sockets. This creates a server that takes in domain names from the client, and retrieves the DNS' associated IP address (if an IP address exists for the name). The retrieval process occurs through either a local cache, or by using the gethostbyname() Python function to retrieve the IP address using an API. IP addresses retrieved using the API method are then written into the local cache for future use. If no IP exists for the domain name, the program instead responds with "Host not found" as it could not find an IP address. All responses from the server, including cache responses, are logged in a .csv file for easy viewing. This file displays the domain name, IP address, and the method used to obtain the IP address. Finally, the program encodes the response message using UTF-8 (standard for TCP) and sends it back to the client. One thing to note about the cache and logger file: the cache file appends to the file (does not overwrite any previous data), whereas the .csv file is truncated when the server begins running. Both files are created upon execution if they do not already exist.
