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

int gametracker(struct board *ptr)                                                /* */
{
  bool started=false;                                                             /* */
  bool found=false;                                                               /* */
  char userinput;                                                                 /* */
  char xcoordinate;                                                               /* */
  int ycoordinate;                                                                /* */
  int xcoordinateconverted=0;                                                     /* */
  bool valid=false;                                                               /* */
  bool validmove=false;                                                           /* */
  int correct=0;                                                                  /* */
  char temp;                                                                      /* */
  bool needed=false;                                                              /* */
  int passorhold=1;                                       /* REMOVE ASSIGNMENT FOR REAL THING */
  bool passed=false;                                                              /* */
  int bothpass=0;                                                                 /* */
  game->turn='B';                                                                 /* */
  game->turnopposite='W';                                                         /* */

  while ( ((game->player1score + game->player2score) < 64) && (bothpass != 2) )   /* */
  {
    if (game->turn == 'B')                                                        /* */
    {
      bothpass=0;                                                                 /* */
    }
    if (!started)                                                                 /* */
    {
      printf("\n\n%s (Black) will start\n", game->player1);                       /* */
      started=true;                                                               /* */
    }
     else
     {
       if (game->turn == 'B')                                                     /* */
       {
         printf("%s is up next\n", game->player1);                                /* */
       }
        else                                                                      /* */
        {
          printf("%s is up next\n", game->player2);                               /* */
        }
      }
    valid=false;                                                                  /* */
    while (!valid)                                                                /* */
    {
      //getchar();                                                                /* */
      //getchar();
      //call my function which checks if there are any available moves
      //passorhold=validmove(game);
      if (passorhold == 0)                                   /* */
      {
        passed=false;
        while (!passed)
        {
          printf("There are no valid moves\n. Please press P to pass\n");
          scanf("%d", &userinput);

          if (userinput == 'P' || userinput == 'p')
          {
            passed=true;
            bothpass++;
          }
            else
            {
              printf("Invalid input. Please enter P to pass\n\n");
            }
        }
        printf("%s has passed !\n");                                              /* */
        temp=game->turn;                                                           /* */
        game->turn=game->turnopposite;                                              /* */
        game->turnopposite=temp;                                                   /* */
        valid=true;                                                               /* */
      }
        else if (passorhold == 1)                            /* */
        {
          valid=true;                                                             /* */
          validmove=false;                                                        /* */
          while (!validmove)                                                      /* */
          {
            found=false;
            while (!found)                                                        /* */
            {

              getchar();

              //getchar();                                                          /* */
              printf("Please enter an x coordinate (letter A-H)\n");              /* */
              scanf("%c", &xcoordinate);                                          /* */
              if (xcoordinate >= 65 && xcoordinate <= 72 )                        /* */
              {
                //printf("hitting first\n");
                xcoordinate += 32;                                                /* */
                found=true;                                                       /* */
              }
                else if (xcoordinate >= 97 && xcoordinate <= 122)                   /* */
                {
                  //printf("hitting second\n");
                  found=true;                                                     /* */
                }
                  else                                                            /* */
                  {
                    printf("Invalid input. Please enter a letter A-H\n\n");       /* */
                  }
                }
            found=false;                                                          /* */
            while (!found)                                                        /* */
            {
              getchar();                                                          /* */
              printf("Please enter a y coordinate (number 1-8)\n");               /* */
              scanf("%d", &ycoordinate);                                          /* */
              ycoordinate--;                                                      /* */
              //printf("y-coord = %d\n", ycoordinate);                              /* */
              if ( ycoordinate >= 0 && ycoordinate <= 8 )                         /* */
              {
                found=true;                                                       /* */
              }
              else                                                                /* */
              {
                printf("Invalid input. Please enter a number 1-8\n\n");           /* */
              }
            }
            xcoordinateconverted=xconverter(xcoordinate);                         /* */
            //printf("%d", xcoordinateconverted);

            correct=movechecker(game, xcoordinateconverted, ycoordinate);         /* */
            //printf("\ncorrect = %d", correct);
            if (correct == 1)                                                     /* */
            {
              printf("\nMove is valid.\n");                                         /* */
              validmove=true;                                                     /* */
              //movemaker(game, xcoordinateconverted, ycoordinate);
            //call function to make move
            boardprinter(game);                                                   /* */
            playerscoreupdater(game);
              //prepare for next player
              temp=game->turn;                                                     /* */
              game->turn=game->turnopposite;                                        /* */
              game->turnopposite=temp;                                             /* */
            }
              else                                                                /* */
              {
                printf("Move is invalid. Please enter another move\n\n");         /* */
              }
          }
        }
    }
  }

}

int xconverter(char xcoordinate)                                                  /* */
{
  char converterstring[8]={'a','b','c','d','e','f','g','h'};                      /* */
  int i=0;                                                                        /* */
  int xcoord=0;                                                                   /* */
  bool found=false;                                                               /* */
  while (!found)                                                                  /* */
  {
    if (xcoordinate == converterstring[i])                                        /* */
    {
      xcoord=i;                                                                   /* */
      found=true;                                                                 /* */
    }
    i++;                                                                          /* */
  }
  return xcoord;                                                                  /* */
}

int movechecker(struct board *ptr, int xcoordinateconverted, int ycoordinate)     /* */
{
  int i=0;
  int j=0;
  int k=0;
  int l=0;
  bool found=false;
  int count=0;
  int validmove=1;
  int invalidmove=0;
  bool turncolour=false;
  //bool emptyspace=false;

  //if (game->board[ycoordinate][xcoordinateconverted]='-')
  //{
    //emptyspace=true;
  //}

  if (game->board[ycoordinate][xcoordinateconverted]='-')
  {
    //vertical down
    for (i=ycoordinate;i<8;i++)
    {
      if (game->turn == game->board[i][xcoordinateconverted])
      {
        if (game->turnopposite == game->board[ycoordinate+1][xcoordinateconverted])
        {
          count++;
          for (l=ycoordinate;l<i;l++)
          {
            game->board[l][xcoordinateconverted]=game->turn;
          }
        }
      }
    }
    //vertical up
    for (i=ycoordinate;i>0;i--)
    {
      if (game->turn == game->board[i][xcoordinateconverted])
      {
        if (game->turnopposite == game->board[ycoordinate-1][xcoordinateconverted])
        {
          count++;
          for (l=ycoordinate;l>i;l--)
          {
            game->board[l][xcoordinateconverted]=game->turn;
          }
        }
      }
    }
    //horizontal left
    for (j=xcoordinateconverted;j>0;j--)
    {
      if (game->turn == game->board[ycoordinate][j])
      {
        if (game->turnopposite == game->board[ycoordinate][xcoordinateconverted-1])
        {
          count++;
          for (k=xcoordinateconverted;k>j;k--)
          {
            game->board[ycoordinate][k]=game->turn;
          }
        }
      }
    }
    //horizontal right
    for (j=xcoordinateconverted;j<8;j++)
    {
      if (game->turn == game->board[ycoordinate][j])
      {
        if (game->turnopposite == game->board[ycoordinate][xcoordinateconverted+1])
        {
          count++;
          for (k=xcoordinateconverted;k<j;k++)
          {
            game->board[ycoordinate][k]=game->turn;
          }
        }
      }
    }
    //bottom-right diagonal
    i=ycoordinate;
    j=xcoordinateconverted;
    while ( (i<8) && (j<8) )
    {
      if (game->turn == game->board[i][j])
      {
        if (game->turnopposite == game->board[ycoordinate+1][xcoordinateconverted+1])
        {
          //printf("Problem#5");
          count++;
          /* for (l=ycoordinate;l<i;l++)
          {
            for (k=xcoordinateconverted;k<j;k++)
            {
              game->board[l][k]=game->turn;
            }
          } */
          l=ycoordinate;
          k=xcoordinateconverted;
          while ( (l<i) && (k<j) )
          {
            game->board[l][k]=game->turn;
            l++;
            k++;
          }
        }
      }
      i++;
      j++;
    }
    //}
  //}
  //printf("count#4 = %d\n", count);
  //printf("C4 : %c\nD4 : %c", game->board[3][2], game->board[3][3]);
  //l++;
  //printf("\n\n%d\n", count);
  //bottom-left diagonal
  //for (i=ycoordinate;i<8;i++)
  //{
    //for (j=xcoordinateconverted;j>0;j--)
    //{
    i=ycoordinate;
    j=xcoordinateconverted;
    while ( (i<8) && (j>0) )
    {
      if (game->turn == game->board[i][j])
      {
        if (game->turnopposite == game->board[ycoordinate+1][xcoordinateconverted-1])
        {
          //printf("Problem#6");
          count++;
          /* for (l=ycoordinate;l<i;l++)
          {
            for (k=xcoordinateconverted;k>j;k--)
            {
              game->board[l][k]=game->turn;
            }
          } */
          l=ycoordinate;
          k=xcoordinateconverted;
          while ( (l<i) && (k>j) )
          {
            game->board[l][k]=game->turn;
            l++;
            k--;
          }
        }
      }
      i++;
      j--;
    }
    //}
  //}
    //printf("count#5 = %d\n", count);
    //l++;
  //top-left diagonal
  //for (i=ycoordinate;i>0;i--)
  //{
    //for (j=xcoordinateconverted;j>0;j--)
    //{
    i=ycoordinate;
    j=xcoordinateconverted;
    while ( (i>0) && (j>0) )
    {
      if (game->turn == game->board[i][j])
      {
        if (game->turnopposite == game->board[ycoordinate-1][xcoordinateconverted-1])
        {
          //printf("Problem#7");
          count++;
          /* for (l=ycoordinate;l>i;l--)
          {
            for (k=xcoordinateconverted;k>j;k--)
            {
              game->board[l][k]=game->turn;
            }
          } */
          l=ycoordinate;
          k=xcoordinateconverted;
          while ( (l>i) && (k>j) )
          {
            game->board[l][k]=game->turn;
            l--;
            k--;
          }
        }
      }
    i--;
    j--;
   }
    //}
  //}
  //printf("count#6 = %d\n", count);
  //l++;

  //printf("Before - \nB5: %c\nC6: %c\n", game->board[4][1], game->board[5][2]);

  //top-right diagonal
  //for (i=ycoordinate;i>0;i--)
  //{
    //for (j=xcoordinateconverted;j<8;j++)
    //{
    i=ycoordinate;
    j=xcoordinateconverted;
    while ( (i>0) && (j<8) )
    {
      if (game->turn == game->board[i][j])
      {
        if (game->turnopposite == game->board[ycoordinate-1][xcoordinateconverted+1])
        {
          //printf("Problem#8");
          count++;
          /*
          for (l=ycoordinate;l>i;l--)
          {
            //printf("[l][k] = [%d][%d]\n", (l+1), (k+1));
            for (k=xcoordinateconverted;k<j;k++)
            {
              printf("[l][k] = [%d][%d]\n", (l+1), (k+1));
              game->board[l][k]=game->turn;
            }
          }*/
          l=ycoordinate;
          k=xcoordinateconverted;
          //printf("i = %d\nj = %d\n", i, j);
          while ( (l>i) && (k<j) )
          {
            game->board[l][k]=game->turn;
            //printf("game->board[%d][%d] = %c\n", l, k, game->board[l][k]);
            k++;
            l--;
          }
        }
      }
      i--;
      j++;
    }
    //}
  //}
  //printf("After - \nB5: %c\nC6: %c\n", game->board[4][1], game->board[5][2]);

  }
    //printf("count#7 = %d\n", count);
  if (count>=1)
  {
    //printf("greater2");
    return 1;
  }
    else
    {
    //  printf("greater1");
      return 0;
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
