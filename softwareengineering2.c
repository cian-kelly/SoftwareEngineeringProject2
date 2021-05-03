#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 20

struct board {
  char board[8][8];
  char player1[20];
  char player2[20];
  int player1score;
  int player2score;
  char turn;
};

int start(struct board game);
int gametracker(struct board game);
int xconverter(char xcoordinate, int xcoordinateconverted);
int movechecker(struct board game, int xcoordinateconverted, int ycoordinate);

int main(void)
{
  struct board game;
  game.player1score=2;
  game.player2score=2;
  //char player1[20];
  //char player2[20];
  //char board[8][8];
  //int player1score=2;
  //int player2score=2;
  //int i=0;
  //int j=0;
  //int count=1;
  //char letter[8]={'a','b','c','d','e','f','g','h'};

  start(game);
}

int start(struct board game)
{
  int i=0;
  int j=0;
  int counter=1;

  for (i=0;i<8;i++)
  {
    for(j=0;j<8;j++)
    {
      game.board[i][j]='-';
    }
  }

  game.board[3][3]='W';
  game.board[3][4]='B';
  game.board[4][3]='B';
  game.board[4][4]='W';
  printf("-------------------------\n   Welcome to Othello !\n-------------------------\n");
  printf("\nEnter name of Player 1 (Black):\n");
  scanf("%s", game.player1);
  printf("\nEnter name of Player 2 (White):\n");
  scanf("%s", game.player2);
  printf("\n\nPlayer 1 : %s\nPlayer 2 : %s", game.player1, game.player2);
  //printf("\n\nScore: %s (Black) %d:%d %s (White)\n", player1, player1score, player2, player2score);
  printf("\n\n\t   Score: %s (Black) %d : %d %s (White)\n\n", game.player1, game.player1score, game.player2score, game.player2);


  for (i=0;i<8;i++)
  {
    printf("\t\t      %d ", counter);
    for(j=0;j<8;j++)
    {
      printf("%c ", game.board[i][j]);
    }
    printf("\n");
    counter++;
  }
  printf("\t\t        a b c d e f g h\n");
}

int gametracker(struct board game)
{
  bool started=false;
  char userinput;
  char xcoordinate;
  int ycoordinate;
  int xcoordinateconverted=10;
  // 0 is black
  game.turn='B';


  if (game.turn == 'B')
  {
    if (!started)
    {
      printf("%s (Black) will start\n", game.player1);
    }
     else
     {
       printf("%s is up next\n", game.playerone);
     }

    while (!valid)
    {
      printf("Would you like to play or hold  ? [P|H]");
      scanf("%c", &userinput);

      if (userinput == 'h' || userinput == 'H')
      {
        printf("%s has chosen to hold !\n");
        game.turn='W';
      }
        else if (userinput == 'p' || userinput == 'P')
        {
          while (!found)
          {
            printf("Please enter an x coordinate (letter A-H)");
            scanf("%c", &xcoordinate);
            if (userinput >= 65 || userinput <= 72 )
            {
              userinput -= 32;
              found=true;
            }
              else if ( (userinput < 65 && userinput > 72) && (userinput > 97 && userinput < 122) )
              {
                found=true;
              }
                else
                {
                  printf("Invalid input. Please enter a letter A-H\n\n");
                }
          }
          found=false;
          while (!found)
          {
            printf("Please enter a y coordinate (number 1-8)");
            scanf("%d", &ycoordinate);

            if ( ycoordinate >= 1 && ycoordinate <= 8 )
            {
              found=true;
            }
              else
              {
                printf("Invalid input. Please enter a number 1-8\n\n");
              }
          }
          xconverter(xcoordinate, xcoordinateconverted);
          movechecker(game, xcoordinateconverted, ycoordinate);
        }
          else
          {
            printf("Invalid input. Please enter the letter P to Pass or H to Hold\n\n");
          }
    }
  }
    else if (game.turn == 'W')
}

int xconverter(char xcoordinate, int xcoordinateconverted)
{
  char converterstring[8]={a,b,c,d,e,f,g,h};
  int i=0;
  bool found=false;

  while (!found)
  {
    if (xcoordinate == converterstring[i])
    {
      xcoordinateconverted=i;
      xcoordinateconverted++;
      found=true
    }
    i++;
  }
}

int movechecker(struct board game, char xcoordinateconverted, int ycoordinate)
{
  int i=0;
  int j=0;
  int k=0;
  bool found=false;
  int count=0;

  if (boardgame[i][xcoordinateconverted]='-')
  {
    count += 10;
  }

  for (i=0;i<8;i++)
  {
    if (game.turn == boardgame[i][xcoordinateconverted])
    {
      
      count++;
      //vertical
    }
  }

  for (j=0;j<8;j++)
  {
    if (game.turn == boardgame[ycoordinate][j])
    {
      count++;
      //horizontal
    }
  }

  //bottom-right diagonal
  for (i=ycoordinate+1;i<8;i++)
  {
    for (j=xcoordinateconverted+1;j<8;j++)
    {
      if (game.turn == boardgame[i][j])
      {
        count++;
      }
    }
  }

  //bottom-left diagonal
  for (i=ycoordinate+1;i<8;i++)
  {
    for (j=xcoordinateconverted-1;j<8;j--)
    {
      if (game.turn == boardgame[i][j])
      {
        count++;
      }
    }
  }

  //top-left diagonal
  for (i=ycoordinate-1;i<8;i--)
  {
    for (j=xcoordinateconverted-1;j<8;j--)
    {
      if (game.turn == boardgame[i][j])
      {
        count++;
      }
    }
  }

  //top-right diagonal
  for (i=ycoordinate-1;i<8;i--)
  {
    for (j=xcoordinateconverted+1;j<8;j++)
    {
      if (game.turn == boardgame[i][j])
      {
        count++;
      }
    }
  }
}
