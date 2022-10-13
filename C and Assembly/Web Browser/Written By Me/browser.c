/* CSCI-4061 Fall 2022
 * Group Member #1: Alex Hatoum hatou003
 * Group Member #2: chase wilson wils2538
 * Group Member #3: Abdullah Meneese menee008
 */

#include "wrapper.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <gtk/gtk.h>

/* === PROVIDED CODE === */
// Function Definitions
void new_tab_created_cb(GtkButton *button, gpointer data);
int run_control();
int on_blacklist(char *uri);
int bad_format (char *uri);
void uri_entered_cb(GtkWidget* entry, gpointer data);
void init_blacklist (char *fname);

/* === PROVIDED CODE === */
// Global Definitions
#define MAX_TAB 100                 //Maximum number of tabs allowed
#define MAX_BAD 1000                //Maximum number of URL's in blacklist allowed
#define MAX_URL 100                 //Maximum char length of a url allowed

/* === STUDENTS IMPLEMENT=== */
// HINT: What globals might you want to declare?

// Global variables for the blacklisted sites, the number of tabs,
// a pid array to kill zombies and the blacklist length
char blacklist[MAX_URL][MAX_BAD];
int num_tabs = 0;
pid_t pid_arr[100];
int blacklist_length;

/* === PROVIDED CODE === */
/*
 * Name:		          new_tab_created_cb
 *
 * Input arguments:	
 *      'button'      - whose click generated this callback
 *			'data'        - auxillary data passed along for handling
 *			                this event.
 *
 * Output arguments:   void
 * 
 * Description:        This is the callback function for the 'create_new_tab'
 *			               event which is generated when the user clicks the '+'
 *			               button in the controller-tab. The controller-tab
 *			               redirects the request to the parent (/router) process
 *			               which then creates a new child process for creating
 *			               and managing this new tab.
 */
// NO-OP for now
void new_tab_created_cb(GtkButton *button, gpointer data)
{}
 
/* === PROVIDED CODE === */
/*
 * Name:                run_control
 * Output arguments:    void
 * Function:            This function will make a CONTROLLER window and be blocked until the program terminates.
 */
int run_control()
{
	browser_window * b_window = NULL;

	// (b) Create controller window with callback function
	create_browser(CONTROLLER_TAB, 0, G_CALLBACK(new_tab_created_cb),
		       G_CALLBACK(uri_entered_cb), &b_window);

	// (c) enter the GTK infinite loop
	show_browser();
	return 0;
}

/* === STUDENTS IMPLEMENT=== */
/* 
    Function: on_blacklist  --> "Check if the provided URI is in th blacklist"
    Input:    char* uri     --> "URI to check against the blacklist"
    Returns:  True  (1) if uri in blacklist
              False (0) if uri not in blacklist
    Hints:
            (a) File I/O
            (b) Handle case with and without "www." (see writeup for details)
            (c) How should you handle "http://" and "https://" ??
*/ 
int on_blacklist (char *uri) {
  //STUDENTS IMPLEMENT
  
  // A for loop to loop through the blacklist array and remove any
  // existing "http://", "https://", and "www."" from the link
  for (int i = 0; i < blacklist_length; i++) {
    // Bools to keep track of what needs to be removed
    int http = 0;
    int https = 0;
    int www = 0;
    
    // Conditionals to check which substrings exist in the blacklist
    // link, and set the bools equal to 1 (true) if necessary
    if (strncmp(blacklist[i], "http://", 7) == 0) {
      http = 1;
    } else if (strncmp(blacklist[i], "https://", 8) == 0) {
      https = 1;
    }
    if (strstr(blacklist[i], "www.") != NULL) {
      www = 1;
    }
    
    // j is a temporary variable to tell the later conditional where to start
    int j = 0;
    if (http) {
      if (www) {
        // 11 characters is where the actual website domain would start in the string
        j = 11;
      } else {
        j = 7;
      }
    } else if (https) {
      if (www) {
          j = 12;
        } else {
          j = 8;
      }
    } else if (www) {
      j = 4;
    }

    // Variable len to store the length of blacklist[i] before
    // modifying the string
    int len = strlen(blacklist[i]) - j;

    // j != 0 means there is something that needs to be removed
    if (j != 0) {
      for (int k = 0; k < len; k++) {
        char tmp = blacklist[i][k+j];     // tmp stores the characters of the domain name
        blacklist[i][k] = tmp;            // replaces the chars at the beginning of blacklist[i][k]
      }
      blacklist[i][len] = '\0';           // add a null char to tell compiler where to stop
    }
    
  }

  // For loop to check if any of the blacklisted sites exist in the uri string
  // This is why all "http://", "https://", and "www." need to be removed
  for(int i = 0; i < blacklist_length; i++){
    // conditional to check if blacklist is in uri
    if(strstr(uri, blacklist[i]) != NULL){
      return 1;
    }
  }
  return 0;
}

/* === STUDENTS IMPLEMENT=== */
/* 
    Function: bad_format    --> "Check for a badly formatted url string"
    Input:    char* uri     --> "URI to check if it is bad"
    Returns:  True  (1) if uri is badly formatted 
              False (0) if uri is well formatted
    Hints:
              (a) String checking for http:// or https://
*/
int bad_format (char *uri) {
  // error checking
  if (uri == NULL) {
    return 1;
  }

  // if the uri is either missing the "http://" or is just "http://" 
  if (strlen(uri) < 8) {
    return 1;
  }

  // compare beginning to http://
  if((strncmp(uri,"http://", 7) == 0)) {
    return 0;
  }

  // if the uri is either missing the "https://" or is just "https://"
  if (strlen(uri) < 9) {
    return 1;
  }

  // compare beginning to "https://"
  if ((strncmp(uri,"https://", 8) == 0) ) {
    return 0;
  }
 
  // if it makes its way without going into any conditional, its bad
  return 1;
}

/* === STUDENTS IMPLEMENT=== */
/*
 * Name:                uri_entered_cb
 *
 * Input arguments:     
 *                      'entry'-address bar where the url was entered
 *			                'data'-auxiliary data sent along with the event
 *
 * Output arguments:     void
 * 
 * Function:             When the user hits the enter after entering the url
 *			                 in the address bar, 'activate' event is generated
 *			                 for the Widget Entry, for which 'uri_entered_cb'
 *			                 callback is called. Controller-tab captures this event
 *			                 and sends the browsing request to the router(/parent)
 *			                 process.
 * Hints:
 *                       (a) What happens if data is empty? No Url passed in? Handle that
 *                       (b) Get the URL from the GtkWidget (hint: look at wrapper.h)
 *                       (c) Print the URL you got, this is the intermediate submission
 *                       (d) Check for a bad url format THEN check if it is in the blacklist
 *                       (e) Check for number of tabs! Look at constraints section in lab
 *                       (f) Open the URL, this will need some 'forking' some 'execing' etc. 
 */
void uri_entered_cb(GtkWidget* entry, gpointer data)
{
  // error checking
  if (data == NULL) {
    exit(1);
  }
  // store url in char*
  char* url = get_entered_uri(entry);
  printf("URL entered is %s\n", url);

  // check format
  int retval = bad_format(url);
  if (retval) {
    alert("BAD FORMAT");
    return;
  }

  // check if on blacklist
  if (on_blacklist(url)) {
    alert("BLACKLIST");
    return;
  }
  
  // check if at tab limit
  if (num_tabs == MAX_TAB) {
    alert("TAB LIMIT REACHED");
    return;
  }

  // make child window
  pid_t pid = fork();
  
  if (pid == -1) {
    perror("Fork failed. Child not created.\n");
    exit(1);
  } else if (pid == 0) {      // in child
    char tabs_count[4];
    sprintf(tabs_count, "%d", num_tabs);    // have tab count listed at top of new tab
    execl("./render", "render", tabs_count, url, NULL);   // open the new tab
  } else {                    // in parent
    pid_arr[num_tabs] = pid;  // store pid in array in case it becomes a zombie
    num_tabs++;
  }

  return;
}

/* === STUDENTS IMPLEMENT=== */
/* 
    Function: init_blacklist --> "Open a passed in filepath to a blacklist of url's, read and parse into an array"
    Input:    char* fname    --> "file path to the blacklist file"
    Returns:  void
    Hints:
            (a) File I/O (fopen, fgets, etc.)
            (b) If we want this list of url's to be accessible elsewhere, where do we put the array?
*/
void init_blacklist (char *fname) {
  FILE* fp;
  // open file as read only
  fp = fopen(fname, "r");
  // error checking
  if (fp == NULL) {
    perror("Error opening file\n");
    exit(-1);
  }
  // a counter for storing the next file into the right place in the array
  int i = 0;
  // line 292 gets the website from blacklist and stores it in blacklist[i]
  // if it returns NULL, we have reached the end of the file
  while (fgets(blacklist[i], MAX_URL, fp) != NULL) {
    // store length
    int len = strlen(blacklist[i]);
    // if the string is bigger than 0 and its last character is a 
    // newline, replace it with a null character
    if (len > 0 && blacklist[i][len-1] == '\n') {
      blacklist[i][len-1] = '\0';
    }
    // incrememnt counter
    i++;
  }
  // set global to the counter
  blacklist_length = i;
  fclose(fp);
  return;
}

/* === STUDENTS IMPLEMENT=== */
/* 
    Function: main 
    Hints:
            (a) Check for a blacklist file as argument, fail if not there [PROVIDED]
            (b) Initialize the blacklist of url's
            (c) Create a controller process then run the controller
                (i)  What should controller do if it is exited? Look at writeup (KILL! WAIT!)
            (d) Parent should not exit until the controller process is done 
*/
int main(int argc, char **argv)
{

  //STUDENT IMPLEMENT

  // (a) Check arguments for blacklist, error and warn if no blacklist
  if (argc != 2) {
    fprintf (stderr, "browser <blacklist_file>\n");
    exit (0);
  }
  
  // initiallize global blacklist array and global blacklist array length
  init_blacklist(argv[1]);
  // open browser
  run_control();
  // kill and wait for all zombies
  for (int i = 0; i < num_tabs; i++) {
    kill(pid_arr[i], 1);
    waitpid(pid_arr[i], NULL, 0);
  }
    
  printf("KILLED\n");

  return 0;
}
