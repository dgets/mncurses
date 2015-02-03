/*
 * by: Damon Getsman
 * started on: 19mar14 6:08am
 * finished:
 * A few ncurses routines that I've found to be useful for more than one chunk
 * o' code that I'm working wif
 */

#include <ncurses.h>
#include <string.h>
#include <unistd.h>

/*
 * defined constants
 */

#define MAX_LEN		78

/*
 * useful definitions/flags
 */

#define DEBUGGING
#define VERBOSE		1

typedef enum { FULL, HALF } pauseType;

/*
 * function definitions
 */

bool init_ncurses(WINDOW *priscr) {
  /*
   * curses setup for initialization utilizing a screen that will have a half-
   * second pause when displaying any error message regarding inability to
   * init curses mode/capability when started up
   */

  priscr = initscr();   /* init curses library */
  keypad(priscr, TRUE); /* keyboard mapping */
  (void) nonl();        /* no NL->CR/NL on output */
  (void) noecho();      /* do not echo input */
  (void) halfdelay(25); /* wait 2.5 sec before carrying on w/out input to getch */

  /* ouahful variable */
  bool guhupdown;

  #ifdef DEBUGGING
	mvaddstr(0, 0, "In init_ncurses");
  #endif

  guhupdown = has_colors();
  if (guhupdown) {
        /* init color subsystem */
        start_color();

        init_pair(0, COLOR_RED, COLOR_BLACK);
        init_pair(1, COLOR_GREEN, COLOR_BLACK);
        init_pair(2, COLOR_YELLOW, COLOR_BLACK);
        init_pair(3, COLOR_BLUE, COLOR_BLACK);
        init_pair(4, COLOR_CYAN, COLOR_BLACK);
        init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(6, COLOR_WHITE, COLOR_BLACK);

        return true;
  } else {
        mvaddstr(12, 15, "No color capability detected!");
        mvaddstr(13, 20, "Hit a key, por favor . . .");

        refresh();
        (void) getch();

        clear();
        refresh();

        return false;
  }
}

void end_ncurses(WINDOW *priscr) {
  /*
   * end curses mode and go back to standard interactive
   */

  endwin();

  #ifdef DEBUGGING
	printf("\nJust called endwin();\n");
  #endif

  /*
   * maybe set delscreen(screen identifier) later?  not sure if there is
   * a pro or con to this at all, but I want to follow good error
   * checking practice, etc
   */
}

/*
 * int ypos_for_center(int, int);
 * 
 * Determines the y position to begin printing a block of text at for 
 * vertical centering purposes.
 */

int ypos_for_center(int my, int ln) {

  #ifdef DEBUGGING
    mvaddstr(0, 0, 
	strcat("In ypos_for_center(", my, ", ", ln, ");"));
  #endif

  if (ln > my) return -1;
  else if (ln == my) return 0;
  else return (int) ((my - ln) / 2);
}

/*
 * int xpos_for_center(int, int);
 *
 * Determines the number of spaces to indent to begin printing 1 line
 * of text in the winder via ncurses.
 */

int xpos_for_center(int mx, int col) {

  #ifdef DEBUGGING
    mvaddstr(0, 1, 
	strcat("In xpos_for_center(", mx, ", ", col, ");"));
  #endif

  if (col > mx) return -1;
  else if (col == mx) return 0;
  else return (int) ((mx - col) / 2);
}

/*
 * void center_shit(int, char *);
 *
 * NOTE: This mahfah will be expecting strings terminated by '\n', come hell
 * or high water.  Do not leave it so rudimentary for long.
 */

int center_shit(char chunk[] /*, WINDOW *curscr */) {
  int	maxx, maxy, ouah, cntr, lines = 0;
  char	curLine;
  bool	flag;

  clear();

  getmaxyx(stdscr, maxy, maxx);		/* pointer, anyone? wut? :-?(beep) */

  ouah = sizeof(chunk);

  #ifdef DEBUGGING
    mvaddstr(0, 3, "In center_shit();");
  #endif

  if ((ouah < 1) || (ouah > (maxx * maxy))) {
	/* out of bounds for what we can put on the screen; we'll learn to 
	   deal with that kind of shite later */
	return -1;
  }

  for (cntr = 0; cntr < ouah; cntr++) {
	if (chunk[cntr] == '\n') {
		lines++;
	}
  }

  cntr = ypos_for_center(maxy, lines);
  for (curLine = 0; curLine <= lines; curLine++) {
	if (xpos_for_center(maxx, (int) strlen(chunk)) < 0) {
		mvaddstr(cntr, 4, "WtF-f-f");
		return -1;
	}

	mvaddstr((cntr + curLine),
		 xpos_for_center(maxx, (int) strlen(chunk[curLine]),
		 chunk[curLine]);
  }

  refresh();
  /* after this point we would be adding a pager if there were support for 
   * chunks longer than the screen length at this point */

  return 0;
}

int pause_flow(pauseType pT, char *prompt) {
	/*
	 * For now let's try always putting the pause prompt on the
	 * bottom 2 lines of the screen/window; we'll keep that open
	 * for status updates, and the like
	 */

	int maxx, maxy, ouah;

	#ifdef DEBUGGING
	  mvaddstr(0, 4, "In pause_flow();");
	#endif

	if (prompt == NULL) {
		prompt = "";
	}

	if (pT == HALF) {
		(void) halfdelay(250);
	} else { //(pT == FULL) 
		cbreak();
	}

	getmaxyx(stdscr, maxy, maxx);
	ouah = xpos_for_center(maxx, (int) strlen(prompt));
	if (ouah < 0) {
	  mvaddstr(5, 2, "Problem w/xpos_for_center");
	}

	mvaddstr((maxy - 2), 
		 xpos_for_center(maxx, (int) strlen(prompt)),
		 prompt);
	refresh();

	return (char) getch();
}

