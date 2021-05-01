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
};

int start(struct board game);

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
