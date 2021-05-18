#include <stdio.h>                                                                /* including libraries */
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "functions.h"

int main(void)
{
  start(game);                                                                    /* calls function start. passes the structure game as an argument */
  gametracker(game);                                                              /* calls function gametracker. passes the structure game as an argument */
  finished(game);                                                                 /* calls function to print the final results */
}
