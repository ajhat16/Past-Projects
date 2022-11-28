#include "wrapper.h"
#include "util.h"
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <gtk/gtk.h>
#include <signal.h>

#define MAX_TABS 100  // this gives us 99 tabs, 0 is reserved for the controller
#define MAX_BAD 1000
#define MAX_URL 100
#define MAX_FAV 100
#define MAX_LABELS 100 


comm_channel comm[MAX_TABS];         // Communication pipes 
char favorites[MAX_FAV][MAX_URL];    // Maximum char length of a url allowed
int num_fav = 0;                     // # favorites

typedef struct tab_list {
  int free;
  int pid; // may or may not be useful
} tab_list;

// Tab bookkeeping
tab_list TABS[MAX_TABS];  
int num_tabs = 0;

/************************/
/* Simple tab functions */
/************************/

// return total number of tabs
int get_num_tabs () {
  int i;
  for (i = 1; i < MAX_TABS; i++) {
    if (TABS[i].free) {
      i--;
      break;
    }
  }
  return i;
}

// get next free tab index
int get_free_tab () {
  return get_num_tabs() + 1;
}

// init TABS data structure
void init_tabs () {
  int i;

  for (i=1; i<MAX_TABS; i++)
    TABS[i].free = 1;
  TABS[0].free = 0;
}

/***********************************/
/* Favorite manipulation functions */
/***********************************/

// return 0 if favorite is ok, -1 otherwise
// both max limit, already a favorite (Hint: see util.h) return -1
int fav_ok (char *uri) {

  // error checking
  if (num_fav == MAX_FAV) {
    alert("MAXIMUM FAVORITES REACHED");
    return -1;
  }

  // error checking
  if (on_favorites(uri)) {
    alert("FAV EXISTS");
    return -1;
  }

  return 0;
}


// Add uri to favorites file and update favorites array with the new favorite
void update_favorites_file (char *uri) {
  // open favorites for reading and writing
  FILE* fp;
  fp = fopen("./.favorites", "r+");

  if (fp == NULL) {
    perror("Error opening file");
    return;
  }
  
  // Updates favorites array and favorites file with the new favorite
  if (!(fav_ok(uri))) {
    if (!(fseek(fp, 0, SEEK_END))) {
      fprintf(fp, "%s\n", uri);
    }
    strcpy(favorites[num_fav], uri);
    num_fav++;
  }

  fclose(fp);
  return;
}

// Set up favorites array
void init_favorites (char *fname) {
  // open file
  FILE* fp;
  fp = fopen(fname, "r");

  if (fp == NULL) {
    perror("Error opening file");
    return;
  }

  int i = 0;
  // gets the next line in the favorites file
  while (fgets(favorites[i], MAX_URL, fp) != NULL) {
    // store length
    int len = strlen(favorites[i]);
    // if the string is bigger than 0 and its last character is a 
    // newline, replace it with a null character
    if (len > 0 && favorites[i][len-1] == '\n') {
      favorites[i][len-1] = '\0';
    }
    // incrememnt counter
    i++;
  }

  num_fav = i;
  fclose(fp);
  return;
}

// Make fd non-blocking just as in class!
// Return 0 if ok, -1 otherwise
// Really a util but I want you to do it :-)
int non_block_pipe (int fd) {
  int nFlags;
  
  if ((nFlags = fcntl(fd, F_GETFL, 0)) < 0)
    return -1;
  if ((fcntl(fd, F_SETFL, nFlags | O_NONBLOCK)) < 0)
    return -1;
  return 0;
}

/***********************************/
/* Functions involving commands    */
/***********************************/

// Checks if tab is bad and url violates constraints; if so, return.
// Otherwise, send NEW_URI_ENTERED command to the tab on inbound pipe
void handle_uri (char *uri, int tab_index) {
  // variable for tracking if the uri is bad format or not
  int bad = 1;

  if (uri == NULL) {
    perror("URI is NULL");
    return;
  }

  // if the uri is either missing the "http://" or is just "http://" 
  if (strlen(uri) < 8) {
    bad = 1;
  }

  // compare beginning to http://
  if((strncmp(uri,"http://", 7) == 0)) {
    bad = 0;
  }

  // if the uri is either missing the "https://" or is just "https://"
  if (strlen(uri) < 9) {
    bad = 1;
  }

  // compare beginning to "https://"
  if ((strncmp(uri,"https://", 8) == 0) ) {
    bad = 0;
  }

  // if the uri is bad, then alert with BAD FORMAT
  if (bad) {
    alert("BAD FORMAT");
    return;
  }

  // check if on blacklist
  if (on_blacklist(uri)) {
    alert("ON BLACKLIST");
    return;
  }

  // error checking
  int num = get_num_tabs();
  if (tab_index > num || tab_index < 1) {
    alert("BAD TAB");
    return;
  }
  // prepare the message for the pipe
  req_t send;
  send.type = NEW_URI_ENTERED;
  send.tab_index = tab_index;
  strcpy(send.uri, uri);
  // send the message
  write(comm[tab_index].inbound[1], &send, sizeof(req_t));
  return;
}


// A URI has been typed in, and the associated tab index is determined
// If everything checks out, a NEW_URI_ENTERED command is sent (see Hint)
// Short function
void uri_entered_cb (GtkWidget* entry, gpointer data) {
  
  if(data == NULL) {	
    return;
  }

  // Get the tab (hint: wrapper.h)
  int index = query_tab_id_for_request(entry, data);
  

  // Get the URL (hint: wrapper.h)
  char* url = get_entered_uri(entry);
  printf("URL entered is %s\n", url);
  // Hint: now you are ready to handle_the_uri
  handle_uri(url, index);
  return;
}
  

// Called when + tab is hit
// Check tab limit ... if ok then do some heavy lifting (see comments)
// Create new tab process with pipes
// Long function
void new_tab_created_cb (GtkButton *button, gpointer data) {
  
  if (data == NULL) {
    return;
  }

  // at tab limit?
  if (get_num_tabs() == MAX_TABS) {
    alert("TAB LIMIT REACHED.");
    return;
  }


  // Get a free tab
  int index = get_free_tab();

  // Create communication pipes for this tab
  if (pipe(comm[index].inbound) == -1) {
    perror("Error creating pipe (inbound)");
    return;
  }
  if (pipe(comm[index].outbound) == -1) {
    perror("Error creating pipe (outbound)");
    return;
  }

  // Make the read ends non-blocking 
  non_block_pipe(comm[index].inbound[0]);
  non_block_pipe(comm[index].outbound[0]);
  
  // fork and create new render tab
  // Note: render has different arguments now: tab_index, both pairs of pipe fd's
  // (inbound then outbound) -- this last argument will be 4 integers "a b c d"
  // Hint: stringify args
  pid_t child = fork();
  if (child == -1) {
    perror("Child not created");
  } else if (child == 0) {
    // stringify args
    char index_string[4];
    sprintf(index_string, "%d", index);

    char a[16];
    sprintf(a, "%d %d %d %d", comm[index].inbound[0], comm[index].inbound[1],
                              comm[index].outbound[0], comm[index].outbound[1]);
    // render tab
    if (execl("./render", "render", index_string, a, NULL) == -1) {
      perror("execl failed to execute");
      return;
    }
  } else {
    // tab bookkeeping
    num_tabs = index;
    TABS[index].pid = child;
    TABS[index].free = 0;
  }

  // Controller parent just does some TABS bookkeeping
  return;
}

// This is called when a favorite is selected for rendering in a tab
// Hint: you will use handle_uri ...
// However: you will need to first add "https://" to the uri so it can be rendered
// as favorites strip this off for a nicer looking menu
// Short
void menu_item_selected_cb (GtkWidget *menu_item, gpointer data) {

  if (data == NULL) {
    return;
  }
  
  // Note: For simplicity, currently we assume that the label of the menu_item is a valid url
  // get basic uri
  char *basic_uri = (char *)gtk_menu_item_get_label(GTK_MENU_ITEM(menu_item));

  // append "https://" for rendering
  char uri[MAX_URL];
  sprintf(uri, "https://%s", basic_uri);

  // Get the tab (hint: wrapper.h)
  int index = query_tab_id_for_request(menu_item, data);
  printf("URL entered is %s\n", uri);

  // Hint: now you are ready to handle_the_uri
  handle_uri(uri, index);

  return;
}


// BIG CHANGE: the controller now runs an loop so it can check all pipes
// Long function
int run_control() {
  browser_window * b_window = NULL;
  int i, nRead;
  req_t req;

  //Create controller window
  create_browser(CONTROLLER_TAB, 0, G_CALLBACK(new_tab_created_cb),
		 G_CALLBACK(uri_entered_cb), &b_window, comm[0]);
  
  // Create favorites menu
  create_browser_menu(&b_window, &favorites, num_fav);
  
  while (1) {
    process_single_gtk_event();
    

    // Read from all tab pipes including private pipe (index 0)
    // to handle commands:
    // PLEASE_DIE (controller should die, self-sent): send PLEASE_DIE to all tabs
    // From any tab:
    //    IS_FAV: add uri to favorite menu (Hint: see wrapper.h), and update .favorites
    //    TAB_IS_DEAD: tab has exited, what should you do?

    // Loop across all pipes from VALID tabs -- starting from 0
    for (i=0; i<MAX_TABS; i++) {
      if (TABS[i].free) continue;
      nRead = read(comm[i].outbound[0], &req, sizeof(req_t));
      

      // Check that nRead returned something before handling cases
      if (nRead == -1) {
        continue;
      }
      // Case 1: PLEASE_DIE
      if (req.type == PLEASE_DIE) {
        // if this was called by anything other than the controller
        if (i != 0) {
          continue;
        } else {
          // loop to go and kill all tabs
          for (int j = 1; j <= num_tabs; j++) {
            // prepare message
            req_t send;
            send.tab_index = j;
            send.type = PLEASE_DIE;
            strcpy(send.uri, req.uri);
            write(comm[j].inbound[1], &send, sizeof(req_t));
            waitpid(TABS[j].pid, NULL, 1);
          }
          // close controller
          return 0;
        }
      }

      // Case 2: TAB_IS_DEAD
       if(req.type == TAB_IS_DEAD){

        // prepare message to send to pipe
        req_t send;
        send.tab_index = i;
        send.type = PLEASE_DIE;
        strcpy(send.uri, req.uri);
        write(comm[i].inbound[1], &send, sizeof(req_t));
        // tab bookkeeping
        TABS[i].free = 1;
        num_tabs--;
        waitpid(TABS[i].pid, NULL, 1);
      }
	    
      // Case 3: IS_FAV
      if (req.type == IS_FAV) {
        // check if the tab is ok before adding to the menu or file
        if (!fav_ok(req.uri)) {
          add_uri_to_favorite_menu(b_window, req.uri);
          update_favorites_file(req.uri);
        }
      }

    }
    usleep(1000);
  }
  return 0;
}


int main(int argc, char **argv)
{

  if (argc != 1) {
    fprintf (stderr, "browser <no_args>\n");
    exit (0);
  }

  init_tabs ();
  // init blacklist (see util.h), and favorites (write this, see above)
  init_blacklist("./.blacklist");
  init_favorites("./.favorites");

  // Fork controller
  // Child creates a pipe for itself comm[0]
  // then calls run_control ()
  // Parent waits ...
  pid_t pid = fork();
  if (pid == -1) {
    perror("Child not created\n");
  } else if (pid == 0) {
    // make pipes
    pipe(comm[0].inbound);
    pipe(comm[0].outbound);
    non_block_pipe(comm[0].inbound[0]);
    non_block_pipe(comm[0].outbound[0]);
    run_control();
  } else {
    // wait in order to stop process from becoming a zombie
    if (wait(NULL) == -1) {
      perror("Error waiting\n");
      exit(1);
    }
  }


  return 0;
}
