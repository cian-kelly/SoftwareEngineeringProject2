#include <stdio.h>                                                              
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 20

int start(char player1[MAX_SIZE], char player2[MAX_SIZE], int player1score, int player2score);

int main(void)
{
  char player1[20];
  char player2[20];
  char board[17][33];
  int player1score=2;
  int player2score=2;
  int i=0;
  int j=0;
  int count=1;
  char letter[8]={'a','b','c','d','e','f','g','h'};
  //printf("%c", letter[0]);

  start(player1, player2, player1score, player2score);

  for (i=0;i<17;i++)
  {
    if (i%2 == 0)
    {
      for (j=0;j<33;j++)
      {
        board[i][j] = '-';
      }
    }
      else
      {
        for(j=0;j<33;j++)
        {
          if (j == 0 || j%4==0)
          {
            board[i][j] = '|';
          }
            else
            {
              board[i][j] = ' ';
            }
        }
      }
  }
  board[7][14]='W';
  board[7][18]='B';
  board[9][14]='B';
  board[9][18]='W';
  printf("\n\n");
  for (i=0;i<17;i++)
  {
    printf("\t ");
    if (i % 2 != 0)
    {
      printf(" %d ", count);
      count++;
    }
      else
      {
        printf("   ");
      }
    for (j=0;j<33;j++)
    {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
  printf("\t      a   b   c   d   e   f   g   h");
}

int start(char player1[MAX_SIZE], char player2[MAX_SIZE], int player1score, int player2score)
{
  printf("-------------------------\n   Welcome to Othello !\n-------------------------\n");
  printf("\nEnter name of Player 1 (Black):\n");
  scanf("%s", player1);
  printf("\nEnter name of Player 2 (White):\n");
  scanf("%s", player2);
  printf("\n\nPlayer 1 : %s\nPlayer 2 : %s", player1, player2);
  //printf("\n\nScore: %s (Black) %d:%d %s (White)\n", player1, player1score, player2, player2score);
  printf("\n\n\t   Score: %s (Black) %d : %d %s (White)", player1, player1score, player2score, player2);
}
