#ifndef _REENTRANT
#define _REENTRANT
#endif

#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

int master_fd = -1;
pthread_mutex_t accept_con_mutex = PTHREAD_MUTEX_INITIALIZER;





/**********************************************
 * init
   - port is the number of the port you want the server to be
     started on
   - initializes the connection acception/handling system
   - if init encounters any errors, it will call exit().
************************************************/
void init(int port) {
   int sd;
   struct sockaddr_in addr;
   int ret_val;
   int flag;
   
   // Socket creation and error checking
   sd = socket(AF_INET, SOCK_STREAM, 0);
   if (sd == -1) {
    perror("ERROR: failure when creating socket");
    return;
   }

   // Chaning socket options
   flag = 1;
   ret_val = setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int));

   if (ret_val != 0) {
     perror("ERROR: setsockopt failed");
     return;
   }
   
   // Binding socket to provided port
   addr.sin_family = AF_INET;
   addr.sin_port = htons(port);
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   if (bind(sd, (struct sockaddr*) &addr, sizeof(addr)) == -1) {
    perror("ERROR: failure on bind");
    return;
   }

   // Marking socket as a passive socket
   if (listen(sd, 5) == -1) {
    perror("ERROR: failure when marking as a passive socket");
   }
   
   
   // Saving file descriptor to a global
   master_fd = sd;
   printf("UTILS.O: Server Started on Port %d\n",port);

}





/**********************************************
 * accept_connection - takes no parameters
   - returns a file descriptor for further request processing.
     DO NOT use the file descriptor on your own -- use
     get_request() instead.
   - if the return value is negative, the thread calling
     accept_connection must should ignore request.
***********************************************/
int accept_connection(void) {
   int newsock;
   struct sockaddr_in new_recv_addr;
   uint addr_len;
   addr_len = sizeof(new_recv_addr);
   
   // Acquire a lock
   pthread_mutex_lock(&accept_con_mutex);
   
   // Accepting the connection
   newsock = accept(master_fd, (struct sockaddr *) &new_recv_addr, &addr_len);
   if (newsock == -1) {
    perror("ERROR: failure when called accept");
    return -1;
   }

   // Unlock
   pthread_mutex_unlock(&accept_con_mutex);
   
   return newsock;
}





/**********************************************
 * get_request
   - parameters:
      - fd is the file descriptor obtained by accept_connection()
        from where you wish to get a request
      - filename is the location of a character buffer in which
        this function should store the requested filename. (Buffer
        should be of size 1024 bytes.)
   - returns 0 on success, nonzero on failure. You must account
     for failures because some connections might send faulty
     requests. This is a recoverable error - you must not exit
     inside the thread that called get_request. After an error, you
     must NOT use a return_request or return_error function for that
     specific 'connection'.
************************************************/
int get_request(int fd, char *filename) {
    
   char buf[2048];

   // Reading bytes from the connection
   ssize_t bytes_read = read(fd, buf, sizeof(buf));
   if (bytes_read < 0) {
       perror("ERROR reading from fd");
   }

   // Getting the first line of the bytes read
   char *first_line_end = strstr(buf, "\n");
   char first_line[2048];
   if (first_line_end != NULL) {
       strncpy(first_line, buf, first_line_end - buf);
       printf("%s\n", first_line);
   }

   // String manipulation to ensure the line is in the correct format
   char s[2] = " ";
   char first_line_copy[2048];
   strcpy(first_line_copy, first_line);
   char *token = strtok(first_line_copy, s);
   if (token == NULL || strcmp(token, "GET") != 0) {
     printf("t1: %s\n", token);
     perror("ERROR: Correct format is GET <file name> HTTP/1.0 or GET <file name> HTTP/1.1");
     return -1;
   }

   // Checking after the first space
   token = strtok(NULL, s);
   char *fname = malloc(sizeof(filename));
   strcpy(fname, token);
   if (token == NULL) {
     printf("t2: %s\n", token);
     perror("ERROR: Correct format is GET <file name> HTTP/1.0 or GET <file name> HTTP/1.1");
     return -1;
   }

   // Checking after the second space
   token = strtok(NULL, s);
   // Removing any characters after the HTTP/1.0 / HTTP/1.1 that we want to check
   token[8] = '\0';
   if (token == NULL || (strcmp(token, "HTTP/1.0") != 0 && strcmp(token, "HTTP/1.1") != 0)) {
     perror("ERROR: Correct format is GET <file name> HTTP/1.0 or GET <file name> HTTP/1.1");
     return -1;
   }
   
   // Making sure the name poses no security risks
   if (strstr(fname, "..") != NULL || strstr(fname, "//") != NULL) {
     perror("ERROR: Invalid filename. Filename may not contain \"..\" or \"//\"");
     return -1;
   }

   // Copying file name into the buffer
   strcpy(filename, fname);
   free(fname);

   return 0;
}





/**********************************************
 * return_result
   - returns the contents of a file to the requesting client
   - parameters:
      - fd is the file descriptor obtained by accept_connection()
        to where you wish to return the result of a request
      - content_type is a pointer to a string that indicates the
        type of content being returned. possible types include
        "text/html", "text/plain", "image/gif", "image/jpeg" cor-
        responding to .html, .txt, .gif, .jpg files.
      - buf is a pointer to a memory location where the requested
        file has been read into memory (the heap). return_result
        will use this memory location to return the result to the
        user. (remember to use -D_REENTRANT for CFLAGS.) you may
        safely deallocate the memory after the call to
        return_result (if it will not be cached).
      - numbytes is the number of bytes the file takes up in buf
   - returns 0 on success, nonzero on failure.
************************************************/
int return_result(int fd, char *content_type, char *buf, int numbytes) {

    // Preparing headers to be written to the connection
    char str[1024];
    sprintf(str, "HTTP/1.1 200 OK\nContent-Type: %s\nContent-Length: %d\nConnection: Close\n\n", content_type, numbytes);

    // Writing headers
    if (write(fd, str, strlen(str)) == -1) {
      perror("ERROR: failure on writing headers");
    }

    // Writing file contents
    if (write(fd, buf, numbytes) == -1) {
      perror("ERROR: failure on writing file contents");
    }
    
    // Closing the connection
    if (close(fd) == -1) {
      perror("ERROR: failure when closing connection");
      return -1;
    }

    return 0;
}





/**********************************************
 * return_error
   - returns an error message in response to a bad request
   - parameters:
      - fd is the file descriptor obtained by accept_connection()
        to where you wish to return the error
      - buf is a pointer to the location of the error text
   - returns 0 on success, nonzero on failure.
************************************************/
int return_error(int fd, char *buf) {

   // Preparing headers for the error message
   char str[1024];
   sprintf(str, "HTTP/1.1 404 Not Found\nContent-Length: %ld\nConnection: Close\n\n", strlen(buf));
   
   // Writing the headers to the client
    if (write(fd, str, strlen(str)) == -1) {
      perror("ERROR: failure on writing headers");
    }
    
    // Writing the actual error message to the client
    if (write(fd, buf, strlen(buf)) == -1) {
      perror("ERROR: failure on writing file contents");
    }
    
    // Closing the connection
    if (close(fd) == -1) {
      perror("ERROR: failure when closing connection");
      return -1;
    }

    return 0;
}
