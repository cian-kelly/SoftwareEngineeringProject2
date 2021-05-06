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
  char turnopposite;
  int samecounterpositioning[6];
};

struct board game;

void start(struct board *);
int gametracker(struct board *);
int xconverter(char xcoordinate);
int movechecker(struct board *, int xcoordinateconverted, int ycoordinate);
void boardprinter(struct board game);
int minandmax(int x, int y, int min, int max);
//int movemaker(int board *, int xcoordinateconverted, int ycoordinate);

int main(void)
{
  struct board game[1];
  //struct board game;
  game->player1score=2;
  game->player2score=2;
  //char player1[20];
  //char player2[20];
  //char board[8][8];
  //int player1score=2;
  //int player2score=2;
  //int i=0;
  //int j=0;
  //int count=1;
  //char letter[8]={'a','b','c','d','e','f','g','h'};
  //printf("\nEnter name of Player 1 (Black):\n");
  //scanf("%s", game.player1);
  start(game);
  gametracker(game);
  boardprinter(game);
}

void start(struct board *ptr)
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

int gametracker(struct board *ptr)
{
  bool started=false;
  bool found=false;
  char userinput;
  char xcoordinate;
  int ycoordinate;
  int xcoordinateconverted=0;
  bool valid=false;
  bool validmove=false;
  int correct=0;
  char temp;
  // 0 is black
  game.turn='B';
  game.turnopposite='W';
  int temporaryfix=0;

  while (temporaryfix<=1)
  {
    temporaryfix=1;
    if (!started)
    {
      printf("\n\n%s (Black) will start\n", game.player1);
      started=true;
    }
     else
     {
       if (game.turn == 'B')
       {
         printf("%s is up next\n", game.player1);
       }
        else
        {
          printf("%s is up next\n", game.player2);
        }
      }
    valid=false;
    while (!valid)
    {
      getchar();
      printf("Would you like to play or hold  ? [P|H]\n");
      scanf("%c", &userinput);

      if (userinput == 'h' || userinput == 'H')
      {
        printf("%s has chosen to hold !\n");
        temp=game.turn;
        game.turn=game.turnopposite;
        game.turnopposite=temp;
        valid=true;
      }
        else if (userinput == 'p' || userinput == 'P')
        {
          valid=true;
          validmove=false;
          while (!validmove)
          {
            while (!found)
            {
              getchar();
              printf("Please enter an x coordinate (letter A-H)\n");
              scanf("%c", &xcoordinate);
              if (xcoordinate >= 65 && xcoordinate <= 72 )
              {
                //printf("hitting first\n");
                xcoordinate += 32;
                found=true;
              }
                else if (xcoordinate > 97 && xcoordinate < 122)
                {
                  //printf("hitting second\n");
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
              getchar();
              printf("Please enter a y coordinate (number 1-8)\n");
              scanf("%d", &ycoordinate);
              ycoordinate--;
              printf("y-coord = %d\n", ycoordinate);
              if ( ycoordinate >= 0 && ycoordinate <= 8 )
              {
                found=true;
              }
              else
              {
                printf("Invalid input. Please enter a number 1-8\n\n");
              }
            }
            xcoordinateconverted=xconverter(xcoordinate);
            //printf("%d", xcoordinateconverted);

            correct=movechecker(game, xcoordinateconverted, ycoordinate);
            //printf("\ncorrect = %d", correct);
            if (correct == 1)
            {
              printf("Move is valid.\n");
              validmove=true;
              //movemaker(game, xcoordinateconverted, ycoordinate);
            //call function to make move
            boardprinter(game);
              //prepare for next player
              temp=game.turn;
              game.turn=game.turnopposite;
              game.turnopposite=temp;
            }
              else
              {
                printf("Move is invalid. Please enter another move\n\n");
              }
          }
        }
          else
          {
            printf("Invalid input. Please enter the letter P to Pass or H to Hold\n\n");
          }
    }
  }

}

int xconverter(char xcoordinate)
{
  char converterstring[8]={'a','b','c','d','e','f','g','h'};
  int i=0;
  int xcoord=0;
  bool found=false;
  while (!found)
  {
    if (xcoordinate == converterstring[i])
    {
      xcoord=i;
      found=true;
    }
    i++;
  }
  return xcoord;
}

int movechecker(struct board *ptr, int xcoordinateconverted, int ycoordinate)
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
  bool emptyspace=false;
  //int xcoord=
  //printf("xcoord = %d\nycoord = %d", xcoordinateconverted, ycoordinate);
  for (i=0;i<6;i++)
  {
    game.samecounterpositioning[i]=0;
  }

  if (game.board[i][xcoordinateconverted]='-')
  {
    emptyspace=true;
  }


    if (emptyspace)
    {
      /* for (i=0;i<8;i++)//vertical
      {
        if (game.turn == game.board[i][xcoordinateconverted])
        {
          if (i > ycoordinate)
          {
            if (game.turnopposite == game.board[ycoordinate+1][xcoordinateconverted])
            {
              count++;
          //printf("here1\n");
          //game.samecounterpositioning[l]++;
            if (count>=11)
            {
              while (!turncolour)
              {
                for (l=ycoordinate;l<i;l++)
                {

                }
              }
            }
          }
        }
          else   //if i<ycoord
          {
            if (game.turnopposite == game.board[ycoordinate-1][xcoordinateconverted])
            {
              count++;
            //printf("here2\n");
            //game.samecounterpositioning[l]++;
            }
          }
        }
      }
  //printf("count#2 = %d\n", count);
  */
  //vertical down
  for (i=ycoordinate;i<8;i++)
  {
    if (game.turn == game.board[i][xcoordinateconverted])
    {
      if (game.turnopposite == game.board[ycoordinate+1][xcoordinateconverted])
      {
        count++;
        for (l=ycoordinate;l<i;l++)
        {
          game.board[l][xcoordinateconverted]=game.turn;
        }
      }
    }
  }
  //vertical up
  for (i=ycoordinate;i>0;i--)
  {
    if (game.turn == game.board[i][xcoordinateconverted])
    {
      if (game.turnopposite == game.board[ycoordinate-1][xcoordinateconverted])
      {
        count++;
        for (l=ycoordinate;l>i;l--)
        {
          game.board[l][xcoordinateconverted]=game.turn;
        }
      }
    }
  }

  //horizontal left
  for (j=xcoordinateconverted;j>0;j--)
  {
    if (game.turn == game.board[ycoordinate][j])
    {
      if (game.turnopposite == game.board[ycoordinate][xcoordinateconverted-1])
      {
        count++;
        for (k=xcoordinateconverted;k>j;k--)
        {
          game.board[ycoordinate][k]=game.turn;
        }
      }
    }
  }
  //horizontal right
  for (j=xcoordinateconverted;j<8;j++)
  {
    if (game.turn == game.board[ycoordinate][j])
    {
      if (game.turnopposite == game.board[ycoordinate][xcoordinateconverted+1])
      {
        count++;
        for (k=xcoordinateconverted;k<j;k++)
        {
          game.board[ycoordinate][k]=game.turn;
        }
      }
    }
  }
    printf("count#3 = %d\n", count);
  l++;
  //bottom-right diagonal
  for (i=ycoordinate+1;i<8;i++)
  {
    for (j=xcoordinateconverted+1;j<8;j++)
    {
      if (game.turn == game.board[i][j])
      {
        if (game.turnopposite == game.board[ycoordinate+1][xcoordinateconverted+1])
        {
          count++;
          for (l=ycoordinate;l<i;l++)
          {
            for (k=xcoordinateconverted;k<j;k++)
            {
              game.board[l][k]=game.turn;
            }
          }
        }
      }
    }
  }
  printf("count#4 = %d\n", count);
  printf("C4 : %c\nD4 : %c", game.board[3][2], game.board[3][3]);
  l++;
  //printf("\n\n%d\n", count);
  //bottom-left diagonal
  for (i=ycoordinate+1;i<8;i++)
  {
    for (j=xcoordinateconverted-1;j>0;j--)
    {
      if (game.turn == game.board[i][j])
      {
        if (game.turnopposite == game.board[ycoordinate+1][xcoordinateconverted-1])
        {
          count++;
          for (l=ycoordinate;l<i;l++)
          {
            for (k=xcoordinateconverted;k>j;k--)
            {
              game.board[l][k]=game.turn;
            }
          }
        }
      }
    }
  }
    printf("count#5 = %d\n", count);
    l++;
  //top-left diagonal
  for (i=ycoordinate-1;i>0;i--)
  {
    for (j=xcoordinateconverted-1;j>0;j--)
    {
      if (game.turn == game.board[i][j])
      {
        if (game.turnopposite == game.board[ycoordinate-1][xcoordinateconverted-1])
        {
          count++;
          for (l=ycoordinate;l>i;l--)
          {
            for (k=xcoordinateconverted;k>j;k--)
            {
              game.board[l][k]=game.turn;
            }
          }
        }
      }
    }
  }
  printf("count#6 = %d\n", count);
  l++;
  //top-right diagonal
  for (i=ycoordinate-1;i>0;i--)
  {
    for (j=xcoordinateconverted+1;j<8;j++)
    {
      if (game.turn == game.board[i][j])
      {
        if (game.turnopposite == game.board[ycoordinate-1][xcoordinateconverted+1])
        {
          count++;
          for (l=ycoordinate;l>i;l--)
          {
            for (k=xcoordinateconverted;k<j;k++)
            {
              game.board[l][k]=game.turn;
            }
          }
        }
      }
    }
  }
}
    printf("count#7 = %d\n", count);
  if (count>=1)
  {
    printf("greater2");
    return 1;
  }
    else
    {
      printf("greater1");
      return 0;
    }
}

void boardprinter(struct board game)
{
  int i=0;
  int j=0;
  int counter=1;

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
