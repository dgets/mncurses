/*
 * started: 28jan15
 * finished:
 * written by: Damon Getsman
 *
 * This project is a simple test to make sure that the different functions
 * available in my-nc_flashcard.h are working properly; a predecessor to the
 * flashcard program that I am writing for my son, so that he can be able
 * to practice his multiplication on anything from a text-only terminal to
 * a terminal on any machine in the house.  It seems like so many of the other
 * programs that I've used are buggy...  I figured, why not put this library
 * to use, get more familiar with C again, and code him up something simple
 * and quick that'll get the job done.
 */

#include "my-nc_flashcard.h"

WINDOW 	*mainWinder;
char 	testMsg[3][78] = { "We come for your daughter,", 
				"Chuck.  Nuh uh uh!  Nobody",
				"says the B word!" };

if (!init_ncurses(mainWinder)) {
  printf("\nHouston, we have a bad friggin' problem\n");
  exit(1);
}

if (center_shit(testMsg) != 0) {
  printf("\nHouston, we've had a problem at number 2. :|\n");
  exit(2);
} else {
  exit(0);
}


