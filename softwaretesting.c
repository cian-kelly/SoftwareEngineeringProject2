#include <stdio.h>                                                                /* including libraries */
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct board {                                                                    /* structure for storing board */
  char board[8][8];                                                               /* stores the board placement */
  char player1[20];                                                               /* stores player one's name */
  char player2[20];                                                               /* stores player two's name */
  int player1score;                                                               /* stores player one's score */
  int player2score;                                                               /* stores player two's score */
  char turn;                                                                      /* stores a character to show whos turn it is (ie B for black and W for white) */
  char turnopposite;                                                              /* stores the opposite character to the one stored in char turn */
};

struct board game[1];                                                             /* globally declaring one struct of type board called game */
void start(struct board *);                                                       /* function for the start of the game - prints intro, scans in names etc */
int gametracker(struct board *);                                                  /* tracks game progress */
int xconverter(char xcoordinate);                                                 /* converts xcoordinate from a letter to a number */
int movechecker(struct board *, int xcoordinateconverted, int ycoordinate);       /* checks if a move is valid */
int validmovechecker(struct board *ptr);                                          /* checks if there are any valid moves */
void boardprinter(struct board *);                                                /* prints the board */
void playerscoreupdater(struct board *);                                          /* updates the player scores */
void finished(struct board *);                                                    /* prints the final result to CLI and appends results with info onto file */

int main(void)
{
  start(game);                                                                    /* calls function start. passes the structure game as an argument */
  gametracker(game);                                                              /* calls function gametracker. passes the structure game as an argument */
  finished(game);                                                                 /* calls function to print the final results */
}

void start(struct board *ptr)                                                     /* the function start is used to initialise the board */
{
  int i=0;                                                                        /* counter for array positioning (row) */
  int j=0;                                                                        /* counter for array positioning (column) */
  int counter=1;                                                                  /* counter for printing board */

  game->player1score=2;                                                           /* When the game starts, black already has two pieces on the board. Therefore their score is set to two */
  game->player2score=2;                                                           /* When the game starts, white already has two pieces on the board. Therefore their score is set to two */

  for (i=0;i<8;i++)                                                               /* set i to zero, loop while i is less than 8 and increment i each loop */
  {
    for(j=0;j<8;j++)                                                              /* set j to zero, loop while j is less than 8 and incrememt j each loop */
    {
      game->board[i][j]='-';                                                      /* set every piece on the board equal to hyphen */
    }
  }

  game->board[3][3]='W';                                                          /* setting up board for the start of game - initialise position [3][3] in array to char value W */
  game->board[3][4]='B';                                                          /* setting up board for the start of game - initialise position [3][4] in array to char value B */
  game->board[4][3]='B';                                                          /* setting up board for the start of game - initialise position [4][3] in array to char value B*/
  game->board[4][4]='W';                                                          /* setting up board for the start of game - initialise position [4][4] in array to char value W */
  printf("-------------------------\n   Welcome to Othello !\n-------------------------\n"); /* print welcome message*/
  printf("\nEnter name of Player 1 (Black):\n");                                  /* prompt user to enter the name of player 1 (black) */
  scanf("%s", game->player1);                                                     /* scan in the string and store in the player one part of struct */
  printf("\nEnter name of Player 2 (White):\n");                                  /* prompt user to enter the name of player 2 (white)*/
  scanf("%s", game->player2);                                                     /* scan in the string and store in the player two part of struct */
  printf("\n\nPlayer 1 : %s\nPlayer 2 : %s", game->player1, game->player2);       /* Print the assigned names of the players */
  printf("\n\n\t   Score: %s (Black) %d : %d %s (White)\n\n", game->player1, game->player1score, game->player2score, game->player2);  /* Print the initial score */
  boardprinter(game);                                                             /* calls function board printer to print the board */
}

int gametracker(struct board *ptr)                                                /* function to keep track of the game */
{
  bool started=false;                                                             /* boolean variable to keep track of whether or not the game has just started */
  bool found=false;                                                               /* boolean variable which will be used as an input checker for x and y coords */
  char userinput;                                                                 /* stores the value entered by user when passing */
  char xcoordinate;                                                               /* stores x-coordinate entered */
  int ycoordinate;                                                                /* stores y-coordinate entered */
  int xcoordinateconverted=0;                                                     /* stores the integer value of the xcoord */
  bool validmove=false;                                                           /* boolean variable which checks input and ensures move is valid */
  int correct=0;                                                                  /* stores value returned by move checker */
  char temp;                                                                      /* temporarily stores the turn char */
  int passorhold;                                                                 /* stores value returned by the validmovechecker function */
  bool passed=false;                                                              /* loops until player passes */
  int bothpass=0;                                                                 /* stores the number of passes made. if a black and a white player both pass one after another games stops */
  game->turn='B';                                                                 /* set turn to black as black starts */
  game->turnopposite='W';                                                         /* set turn opposite to white as black starts and white goes second */

  while ( ((game->player1score + game->player2score) < 64) && (bothpass != 2) )   /* loop while all squares arent filled and both people havent passed in a row*/
  {
    if (game->turn == 'B')                                                        /* if its blacks turn, reset the bothpass variable */
    {
      bothpass=0;                                                                 /* set both pass to zero */
    }

    if (!started)                                                                 /* if game not started */
    {
      printf("\n\n%s (Black) will start\n", game->player1);                       /* print info */
      started=true;                                                               /* now started so change started to true */
    }
     else                                                                         /* if started */
     {
       if (game->turn == 'B')                                                     /* if blacks turn */
       {
         printf("%s is up next\n", game->player1);                                /* print player 1 name */
       }
        else                                                                      /* if whites turn */
        {
          printf("%s is up next\n", game->player2);                               /* print player twos name */
        }
      }
    passorhold=validmovechecker(game);                                            /* calls function to check if there is valid move. stores answer as an int */
    if (passorhold == 0)                                                          /* if passorhold is 0 (if no moves) */
    {
      passed=false;                                                               /* set passed to false */
      while (!passed)                                                             /* while not passed */
      {
        printf("There are no valid moves\nPlease press P to pass\n");             /* inform user no valid moves */
        scanf("%c", &userinput);                                                  /* scan user input */
        if (userinput == 'P' || userinput == 'p')                                 /* if user entered p */
        {
          passed=true;                                                            /* valid input. set passed to true */
          bothpass++;                                                             /* player passed so add one to bothpass */
        }
          else                                                                    /* otherwise (user didnt enter p) */
          {
            printf("Invalid input. Please enter P to pass\n\n");                  /* inform user invalid input */
            getchar();
          }
      }
      temp=game->turn;                                                            /* transfer character in turn to temp */
      game->turn=game->turnopposite;                                              /* transfer character in turnopposite to turn */
      game->turnopposite=temp;                                                    /* transfer character in temp to turnopposite */
    }
      else if (passorhold == 1)                                                   /* if there is a validmove */
      {
        validmove=false;                                                          /* set validmove to false */
        while (!validmove)                                                        /* while validmove is false */
        {
          found=false;                                                            /* set found to false */
          while (!found)                                                          /* while correct input not entered */
          {
            getchar();                                                            /* remove char from stream*/
            printf("Please enter an x coordinate (letter A-H)\n");                /* prompt user */
            scanf("%c", &xcoordinate);                                            /* scan in xcoord */
            if (xcoordinate >= 65 && xcoordinate <= 72 )                          /* if uppercase */
            {
              xcoordinate += 32;                                                  /* change to lowercase */
              found=true;                                                         /* set found to true - correct input found */
            }
              else if (xcoordinate >= 97 && xcoordinate <= 122)                   /* if letter is lowercase */
              {
                found=true;                                                       /* set found to true - correct input found */
              }
                else                                                              /* otherwise (invalid input) */
                {
                  printf("Invalid input. Please enter a letter A-H\n\n");         /* prompt user to enter a correct letter */
                }
              }
          found=false;                                                            /* set found to false */
          while (!found)                                                          /* while correct input not entered */
          {
            getchar();                                                            /* get character from stream */
            printf("Please enter a y coordinate (number 1-8)\n");                 /* prompt user */
            scanf("%d", &ycoordinate);                                            /* scan in y coord */
            ycoordinate--;                                                        /* subtract one for indexing */
            if ( ycoordinate >= 0 && ycoordinate <= 7 )                           /* if number between zero and seven inclusive */
            {
              found=true;                                                         /* set found to true - valid input */
            }
            else                                                                  /* else - invalid input */
            {
              printf("Invalid input. Please enter a number 1-8\n\n");             /* prompt user to enter correct input */
            }
          }
          xcoordinateconverted=xconverter(xcoordinate);                           /* call xconverter to convert the xcoord and store returned value in xcoordinateconverted */
          correct=movechecker(game, xcoordinateconverted, ycoordinate);           /* check the move entered */
          if (correct == 1)                                                       /* if correct is one */
          {
            printf("\nMove is valid.\n");                                         /* inform user that its valid */
            validmove=true;                                                       /* set valid move to true */
            boardprinter(game);                                                   /* print board */
            playerscoreupdater(game);                                             /* print scoreboard */
            //prepare for next player
            temp=game->turn;                                                      /* transfer character in turn to temp */
            game->turn=game->turnopposite;                                        /* transfer character in turnopposite to turn */
            game->turnopposite=temp;                                              /* transfer character in temp to turnopposite */
          }
            else                                                                  /* otherwise move invalid */
            {
              printf("Move is invalid. Please enter another move\n\n");           /* prompt user to enter another move */
            }
        }
      }
  }

}

int xconverter(char xcoordinate)                                                  /* function to convert xcoordinate from letter to number */
{
  char converterstring[8]={'a','b','c','d','e','f','g','h'};                      /* string used for comparing */
  int i=0;                                                                        /* counter for array positioning */
  int xcoord=0;                                                                   /* stores location of xcoordinate in array converterstring */
  bool found=false;                                                               /* boolean variable to be used as a checker */
  while (!found)                                                                  /* while we havent found the letter */
  {
    if (xcoordinate == converterstring[i])                                        /* if letter in ith position of converterstring equals xcoordinate */
    {
      xcoord=i;                                                                   /* set xcoord to i */
      found=true;                                                                 /* set found to true so loop can close */
    }
    i++;                                                                          /* increment i */
  }
  return xcoord;                                                                  /* return xcoord integer */
}

int movechecker(struct board *ptr, int xcoordinateconverted, int ycoordinate)     /* function to check if a move is valid */
{
  int i=0;                                                                        /* counter for array positioning */
  int j=0;                                                                        /* counter for array positioning*/
  int k=0;                                                                        /* counter for array positioning */
  int l=0;                                                                        /* counter for array positioning */
  int count=0;                                                                    /* counts the number of directions in which move is valid */

  if (game->board[ycoordinate][xcoordinateconverted]='-')                         /* if the chosen space is free */
  {
    //vertical down
    for (i=ycoordinate;i<8;i++)                                                   /* set i to ycoordinate, loop while i is less than 8 and increment i each loop */
    {
      if (game->turn == game->board[i][xcoordinateconverted])                     /* if the current position has the same character as that of turn in struct game */
      {
        if (game->turnopposite == game->board[ycoordinate+1][xcoordinateconverted])   /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
        {
          count++;                                                                /* increment count */
          for (l=ycoordinate;l<i;l++)                                             /* set l to ycoordinate, loop while l is less than i and increment l each loop */
          {
            game->board[l][xcoordinateconverted]=game->turn;                      /* set current position to have the same character as that of turn in struct game */
          }
        }
      }
    }
    //vertical up
    for (i=ycoordinate;i>0;i--)                                                   /* set i to ycoordinate, loop while i is greater than 0 and decrement i each loop */
    {
      if (game->turn == game->board[i][xcoordinateconverted])                     /* if the current position has the same character as that of turn in struct game */
      {
        if (game->turnopposite == game->board[ycoordinate-1][xcoordinateconverted])   /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
        {
          count++;                                                                /* increment count */
          for (l=ycoordinate;l>i;l--)                                             /* set l to ycoordinate, loop while l is greater than i and decrement l each loop */
          {
            game->board[l][xcoordinateconverted]=game->turn;                      /* set current position to have the same character as that of turn in struct game */
          }
        }
      }
    }
    //horizontal left
    for (j=xcoordinateconverted;j>0;j--)                                          /* set j to xcoordinateconverted, loop while j is greater than 0 and decrement j each loop */
    {
      if (game->turn == game->board[ycoordinate][j])                              /* if the current position has the same character as that of turn in struct game */
      {
        if (game->turnopposite == game->board[ycoordinate][xcoordinateconverted-1])   /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
        {
          count++;                                                                /* increment count */
          for (k=xcoordinateconverted;k>j;k--)                                    /* set k to xcoordinateconverted, loop while k is greater than j and decrement k each loop */
          {
            game->board[ycoordinate][k]=game->turn;                               /* set current position to have the same character as that of turn in struct game */
          }
        }
      }
    }
    //horizontal right
    for (j=xcoordinateconverted;j<8;j++)                                          /* set j to xcoordinateconverted, loop while j is less than 8 and increment each loop */
    {
      if (game->turn == game->board[ycoordinate][j])                              /* if the current position has the same character as that of turn in struct game */
      {
        if (game->turnopposite == game->board[ycoordinate][xcoordinateconverted+1])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
        {
          count++;                                                                /* increment count */
          for (k=xcoordinateconverted;k<j;k++)                                    /* set k to xcoordinateconverted, loop while k is less than j iand increment k each loop */
          {
            game->board[ycoordinate][k]=game->turn;                               /* set current position to have the same character as that of turn in struct game */
          }
        }
      }
    }
    //bottom-right diagonal
    i=ycoordinate;                                                                /* set i to ycoordinate */
    j=xcoordinateconverted;                                                       /* set j to xcoordinateconverted */
    while ( (i<8) && (j<8) )                                                      /* loop while i is less than 8 and j is less than 8 */
    {
      if (game->turn == game->board[i][j])                                        /* if the current position has the same character as that of turn in struct game */
      {
        if (game->turnopposite == game->board[ycoordinate+1][xcoordinateconverted+1])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
        {
          count++;                                                                /* increment count */
          l=ycoordinate;                                                          /* set l to ycoordinate */
          k=xcoordinateconverted;                                                 /* set k to xcoordinateconverted */
          while ( (l<i) && (k<j) )                                                /* loop while l is less than i and k is less than j */
          {
            game->board[l][k]=game->turn;                                         /* set current position to have the same character as that of turn in struct game */
            l++;                                                                  /* increment l */
            k++;                                                                  /* increment k */
          }
        }
      }
      i++;                                                                        /* increment i */
      j++;                                                                        /* increment j */
    }
  //bottom-left diagonal
    i=ycoordinate;                                                                /* set i to ycoordinate */
    j=xcoordinateconverted;                                                       /* set j to xcoordinateconverted */
    while ( (i<8) && (j>0) )                                                      /* loop while i is less than 8 and j is greater than 0 */
    {
      if (game->turn == game->board[i][j])                                        /* if the current position has the same character as that of turn in struct game */
      {
        if (game->turnopposite == game->board[ycoordinate+1][xcoordinateconverted-1])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
        {
          count++;                                                                /* increment count */
          l=ycoordinate;                                                          /* set l to ycoordinate */
          k=xcoordinateconverted;                                                 /* set k to xcoordinateconverted */
          while ( (l<i) && (k>j) )                                                /* loop while l is less than i and k is greater than j */
          {
            game->board[l][k]=game->turn;                                         /* set current position to have the same character as that of turn in struct game */
            l++;                                                                  /* increment l */
            k--;                                                                  /* decrement k */
          }
        }
      }
      i++;                                                                        /* increment i */
      j--;                                                                        /* decrement j */
    }
  //top-left diagonal
    i=ycoordinate;                                                                /* set i to ycoordinate */
    j=xcoordinateconverted;                                                       /* set j to xcoordinateconverted */
    while ( (i>0) && (j>0) )                                                      /* loop while i is greater than zero and j is greater than zero */
    {
      if (game->turn == game->board[i][j])                                        /* if the current position has the same character as that of turn in struct game */
      {
        if (game->turnopposite == game->board[ycoordinate-1][xcoordinateconverted-1])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
        {
          count++;                                                                /* increment count */
          l=ycoordinate;                                                          /* set l to ycoordinate */
          k=xcoordinateconverted;                                                 /* set k to xcoordinateconverted */
          while ( (l>i) && (k>j) )                                                /* while l is greater than i and k is greater than j */
          {
            game->board[l][k]=game->turn;                                         /* set current position to have the same character as that of turn in struct game */
            l--;                                                                  /* decrement l */
            k--;                                                                  /* decrement k */
          }
        }
      }
    i--;                                                                          /* decrement i */
    j--;                                                                          /* decrement j */
   }
  //top-right diagonal
    i=ycoordinate;                                                                /* set i to ycoordinate */
    j=xcoordinateconverted;                                                       /* set j to xcoordinateconverted */
    while ( (i>0) && (j<8) )                                                      /* loop while i is greater than zero and j is less than eighth */
    {
      if (game->turn == game->board[i][j])                                        /* if the current position has the same character as that of turn in struct game */
      {
        if (game->turnopposite == game->board[ycoordinate-1][xcoordinateconverted+1])   /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
        {
          count++;                                                                /* increment count */
          l=ycoordinate;                                                          /* set l to ycoordinate */
          k=xcoordinateconverted;                                                 /* set k to xcoordinateconverted */
          while ( (l>i) && (k<j) )                                                /* loop while l is greater than i and j is less than j */
          {
            game->board[l][k]=game->turn;                                         /* set current position to have the same character as that of turn in struct game */
            k++;                                                                  /* increment k */
            l--;                                                                  /* decrement l */
          }
        }
      }
      i--;                                                                        /* decrement i*/
      j++;                                                                        /* increment j */
    }
  }
  if (count>=1)                                                                   /* if count is greater than or equal to 1 */
  {
    return 1;                                                                     /* return 1 */
  }
    else                                                                          /* otherwise - count is 0 */
    {
      return 0;                                                                   /* return 0 */
    }
}

void boardprinter(struct board *ptr)                                              /* function to print the board */
{
  int i=0;                                                                        /* counter for array positioning */
  int j=0;                                                                        /* counter for array positioning */
  int counter=1;                                                                  /* variable for board layout. this is the numbers along the left hand side of the board */

  for (i=0;i<8;i++)                                                               /* set i to zero, loop while i is less than 8 and increment i each loop */
  {
    printf("\t\t      %d ", counter);                                             /* formatting board */
    for(j=0;j<8;j++)                                                              /* set j to zero, loop while j is less than 8 and increment j each loop */
    {
      printf("%c ", game->board[i][j]);                                           /* printing [ith][jth] position of board */
    }
    printf("\n");                                                                 /* printing newline character */
    counter++;                                                                    /* incrementing counter each loop */
  }
  printf("\t\t        a b c d e f g h\n");                                        /* formatting board */
}

void playerscoreupdater(struct board *ptr)                                        /* function to update the player scores */
{
  int i=0;                                                                        /* counter for array positioning */
  int j=0;                                                                        /* counter for array positioning */

  game->player1score=0;                                                           /* reset player score to zero (dont want to double count the counters) */
  game->player2score=0;                                                           /* reset player score to zero (dont want to double count the counters) */

  for (i=0;i<8;i++)                                                               /* set i to zero, loop while i is less than 8 and increment i each loop */
  {
    for (j=0;j<8;j++)                                                             /* set j to zero, loop while j is less than 8 and increment j each loop */
    {
      if (game->board[i][j] == 'B')                                               /* if character B is found in [ith][jth] position */
      {
        game->player1score++;                                                     /* increase player one's score (black) by one */
      }
      if (game->board[i][j] == 'W')                                               /* if character W is found in [ith][jth] position */
      {
        game->player2score++;                                                     /* increase player two's score (white) by one */
      }
    }
  }
  printf("\n\n\t   Score: %s (Black) %d : %d %s (White)\n\n", game->player1, game->player1score, game->player2score, game->player2);    /* print score to screen */
}

void finished(struct board *ptr)                                                  /* function to print the end results after the game is over */
{
  FILE *output;                                                                   /* declaring a file pointer */
  time_t currenttime;                                                             /* using to print time */

  output=fopen("othello-results.txt","w");                                        /* open file stream */
  time(&currenttime);                                                             /* set current time */

  if (output==NULL)                                                               /* if file cannot be opened */
  {
    printf("File othello-results.txt could not be opened\n");                     /* inform user */
  }
    else                                                                          /* otherwise (file can be opened) */
    {
      fprintf(output,"Time of game completion:\n%s\n", ctime(&currenttime));      /* print the time the game was completed to file */
      printf("\n Final Score: \n%s (Black) %d : %d %s (White)\n\n", game->player1, game->player1score, game->player2score, game->player2);        /* print the final score to user */
      fprintf(output,"Final Score: %s (Black) %d : %d %s (White)\n\n", game->player1, game->player1score, game->player2score, game->player2);     /* print the final score to text file */

      if (game->player1score > game->player2score)                                /* if player one's score is greater than player two's score */
      {
        printf("%s is the winner !\n\n", game->player1);                          /* inform users that player one won */
        fprintf(output,"%s is the winner !\n", game->player1);                    /* print to file that player one won */
      }
        else                                                                      /* otherwise (player two's score is greater than player one's score) */
        {
          printf("%s is the winner !\n\n", game->player2);                        /* inform users that player two won */
          fprintf(output,"%s is the winner !\n", game->player2);                  /* print to file that player two won */
        }
      boardprinter(game);                                                         /* print the final board */
    }
  fclose(output);                                                                 /* close the file stream */
}

int validmovechecker(struct board *ptr)                                           /* checks if there are any valid moves */
{
  int i=0;                                                                        /* counter positioning for array */
  int j=0;                                                                        /* counter positioning for array */
  int count=0;                                                                    /* used for counting number of directions that are valid */
  int ycoordinate=0;                                                              /* set ycoordinate to zero */
  int xcoordinateconverted=0;                                                     /* set xcoordinateconverted to zero */

  while ( (count == 0) && (ycoordinate < 8) )                                     /* loop while count is 0 and ycoordinateis less than 8 */
  {
    if (game->board[ycoordinate][xcoordinateconverted]=='-')                      /* if space is free */
    {
      //vertical down
      for (i=ycoordinate;i<8;i++)                                                 /* set i to ycoordinate, loop while i is less than 8 and increment i each loop */
      {
        if (game->turn == game->board[i][xcoordinateconverted])                   /* if the current position has the same character as that of turn in struct game*/
        {
          if (game->turnopposite == game->board[ycoordinate+1][xcoordinateconverted])   /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
          {
            count++;                                                              /* increment count */
          }
        }
      }
      //vertical up
      for (i=ycoordinate;i>0;i--)                                                 /* set i to ycoordinate, loop while i is greater than 0 and increment i each loop */
      {
        if (game->turn == game->board[i][xcoordinateconverted])                   /* if the current position has the same character as that of turn in struct game */
        {
          if (game->turnopposite == game->board[ycoordinate-1][xcoordinateconverted])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
          {
            count++;                                                              /* increment count */
          }
        }
      }
      //horizontal left
      for (j=xcoordinateconverted;j>0;j--)                                        /* set j to xcoordinateconverted, loop while j is greater than 0 and decrement j each loop */
      {
        if (game->turn == game->board[ycoordinate][j])                            /* if the current position has the same character as that of turn in struct game */
        {
          if (game->turnopposite == game->board[ycoordinate][xcoordinateconverted-1])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
          {
            count++;                                                              /* increment count */
          }
        }
      }
      //horizontal right
      for (j=xcoordinateconverted;j<8;j++)                                        /* set j to xcoordinateconverted, loop while j is less than 8 and increment j each loop */
      {
        if (game->turn == game->board[ycoordinate][j])                            /* if the current position has the same character as that of turn in struct game */
        {
          if (game->turnopposite == game->board[ycoordinate][xcoordinateconverted+1])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
          {
            count++;                                                              /* increment count */
          }
        }
      }
      //bottom-right diagonal
      i=ycoordinate;                                                              /* set i to ycoordinate */
      j=xcoordinateconverted;                                                     /* set j to xcoordinateconverted*/
      while ( (i<8) && (j<8) )                                                    /* loop while i is less than 8 and j is less than 8 */
      {
        if (game->turn == game->board[i][j])                                      /* if the current position has the same character as that of turn in struct game */
        {
          if (game->turnopposite == game->board[ycoordinate+1][xcoordinateconverted+1])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
          {
            count++;                                                              /* increment count */
          }
        }
        i++;                                                                      /* increment i */
        j++;                                                                      /* increment j */
      }
      //bottom-left diagonal
      i=ycoordinate;                                                              /* set i to ycoordinate */
      j=xcoordinateconverted;                                                     /* set j to xcoordinateconverted */
      while ( (i<8) && (j>0) )                                                    /* loop while i is less than 8 and j is greater than 0 */
      {
        if (game->turn == game->board[i][j])                                      /* if the current position has the same character as that of turn in struct game */
        {
          if (game->turnopposite == game->board[ycoordinate+1][xcoordinateconverted-1])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
          {
            count++;                                                              /* increment count */
          }
        }
        i++;                                                                      /* increment i */
        j--;                                                                      /* decrement j */
      }
      //top-left diagonal
      i=ycoordinate;                                                              /* set i to ycoordinate */
      j=xcoordinateconverted;                                                     /* set j to xcoordinateconverted */
      while ( (i>0) && (j>0) )                                                    /* loop while i is greater than 0 and j is greater than 0 */
      {
        if (game->turn == game->board[i][j])                                      /* if the current position has the same character as that of turn in struct game */
        {
          if (game->turnopposite == game->board[ycoordinate-1][xcoordinateconverted-1]) /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
          {
            count++;                                                              /* increment count */
          }
        }
        i--;                                                                      /* decrement i */
        j--;                                                                      /* decrement j */
      }
      //top-right diagonal
      i=ycoordinate;                                                              /* set i to ycoordinate */
      j=xcoordinateconverted;                                                     /* set j to xcoordinateconverted */
      while ( (i>0) && (j<8) )                                                    /* loop while i is greater than zero and j is less than 8 */
      {
        if (game->turn == game->board[i][j])                                      /* if the current position has the same character as that of turn in struct game */
        {
          if (game->turnopposite == game->board[ycoordinate-1][xcoordinateconverted+1])  /* if the position to the top-right diagonal of where you want to place your character has the same character as that of turnopposite in struct game */
          {
            count++;                                                              /* increment count */
          }
        }
        i--;                                                                      /* decrement i */
        j++;                                                                      /* increment j */
      }
    }
    if (xcoordinateconverted == 7)                                                /* if xcoordinateconverted is 7 */
    {
      ycoordinate++;                                                              /* increment y coordinate */
      xcoordinateconverted=-1;                                                    /* set xcoordinateconverted to -1 */
    }
    xcoordinateconverted++;                                                       /* increment xcoordinateconverted */
  }

  if (count == 0)                                                                 /* if count is zero */
  {
    return 0;                                                                     /* return 0 */
  }
    else                                                                          /* otherwise - if count isnt 0 */
    {
      return 1;                                                                   /* return 1 */
    }
}
