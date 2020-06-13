#include<stdio.h>
#include<stdlib.h>
void fillarray (int * arr);
int main()
{
  int * counter;
  int prize;
  char  ch;
  int * p = &prize;
  printf("WELCOME TO KBC!\n");
  printf("PRESS 'C' ON YOUR KEYBOARD TO CONTINUE\n");
  scanf("%c", &ch);
  while( 1 )
  {
    if ( ch == 'c' || ch == 'C'){
      break;
    }else{
      return 0;
    }
  }
  printf("THIS GAME HAS 15 QUESTIONS\nEACH QUESTION HAS 4 CHOICES OUT OF WHICH ONLY ONE IS CORRECT\n");
  printf("WRONG ANSWER TO ANY OF THE QUESTIONS LEADS TO IMMEADIATE TERMINATION\n");
  printf("WE ALSO PROVIDE 2 LIFE-LINES: 50-50 AND FLIP THE QUESTION\n");
  printf("50-50: THIS WILL LEAD TO REMOVAL OF 2 WRONG CHOICES OUT OF THE TOTAL 4\n");
  printf("FLIP THE QUESTION: THIS WILL CHANGE THE CURRENT QUESTION ENTIRELY\n");
  printf("PRIZE MONEY DISTRIBUTION:-\n");
  * counter = 0;
  int * arr = malloc(15 * sizeof(int));
  fillarray(arr);
  for ( ; *(arr)<15 ; arr++)
  {
    printf("This is question %d\n",*(arr));
    scanf(" %c ", ans);
    if ( check(ans,correct_ans) ){
      incres
    };
  }
}

void fillarray ( int * arr ){
  for ( int i = 0 ; i < 15 ; i++ )
  {
    * ( arr ) = i;
  }
}
