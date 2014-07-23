/*
 * by: Damon Getsman
 * started on: 19mar14 6:08am
 * finished:
 * A few ncurses routines that I've found to be useful for more than one chunk
 * o' code that I'm working wif
 */

#include <ncurses.h>
#include <unistd.h>

/* constants */
const int MaxCols = (int)getmaxx();
const int MaxLines = (int)getmaxy();

/* macros */
#define DefaultBorder = border(0, 0, 0, 0, 0, 0, 0, 0);

/* structures & enumerations */
enum colorpairs_bb {
	RB, GB, YB, BB, CB, MB, WB
} PaintColor = BB;

/*
 * functions available:
 *
 * init_ncurses(void) - returns true when able to initialize an ncurses
 * window, false when terminal is not found to be capable for some
 * reason
 *
 * cntr_horiz(char *, int) - returns starting X position to print @ for
 * properly centering the string contained @ paramater 0
 */

/*
 * bool init_ncurses(void);
 * returns: true if able to init ncurses on terminal
 */
bool init_ncurses(void) {
  /*
   * curses setup for initialization utilizing a screen that will have a half-
   * second pause when displaying any error message regarding inability to
   * init curses mode/capability when started up
   */

  initscr();   //init curses library
  keypad(stdscr, TRUE); //keyboard mapping
  (void) nonl();        //no NL->CR/NL on output
  (void) noecho();      //do not echo input
  (void) halfdelay(25); //wait 2.5 sec before carrying on w/out input to getch

  /* ouahful variable */
  bool guhupdown;

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

/*
 * int cntr_horiz(char *text, int ln);
 * returns: starting column #
 * output: prints text @ appropriate point
 * *text: pointer to char array for text to display
 * ln: line # to print upon
 */
int cntr_horiz(char *text, int ln) {
	int xpos;

	if ((ln < 0) || (ln > MaxLines)) {
		#ifdef DEBUGGING
		  warn("line # out of bounds in cntr_horiz()\n");
		#endif
		return -1;
	}

	xpos = (int)((MaxCols - (int)strlen(text)) / 2);
	if (xpos < 0) {
		#ifdef DEBUGGING
		  warn("cntr_horiz() recv'd strlen > MaxCols\n");
		#endif
		return -2;
	}

	mvaddstr(ln, xpos, text);
	refresh();

	return xpos;
}

/*
 * void 
