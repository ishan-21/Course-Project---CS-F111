#include<stdio.h>
#include<stdlib.h>

struct quest{
  char ques[400];
  char correctAns;
};

typedef struct quest question;

void fillArray ( int n , question array[15] );

void updateCurrentWorth( int reward , int * current );

int checkQuestion( char ans , char correctAns );

void updateDefiniteWorth( int i , int * current , int * definite );

int main()
{
  char  start;
  printf("WELCOME TO KAUN BANEGA CROREPATI!\n");
  printf("THIS GAME HAS 15 QUESTIONS\nEACH QUESTION HAS 4 CHOICES OUT OF WHICH ONLY ONE IS CORRECT\n");
  printf("WRONG ANSWER TO ANY OF THE QUESTIONS LEADS TO IMMEDIATE TERMINATION\n");
  printf("WE ALSO PROVIDE 2 LIFE-LINES: 50-50 AND FLIP THE QUESTION\n");
  printf("50-50: THIS WILL LEAD TO REMOVAL OF 2 WRONG CHOICES OUT OF THE TOTAL 4\n");
  printf("FLIP THE QUESTION: THIS WILL CHANGE THE CURRENT QUESTION ENTIRELY\n");
  printf("PRIZE MONEY DISTRIBUTION:-\n");
  printf("PRESS ANY KEY ON YOUR KEYBOARD TO CONTINUE\n");
  scanf("%c", &start);
  while( 1 )
  {
    if ( &start != NULL )
      break;
    else
      return 0;
  }

  question list[15];
  fillArray( 15 ,  list );

  int prize[15]={1000,1000,1000,2000,5000,10000,20000,40000,80000,160000,320000,610000,1250000,2500000,5000000};

  int * currentWorth = malloc(sizeof(int));

  int * definiteWorth = malloc(sizeof(int));

  *currentWorth = 0 ;
  *definiteWorth = 0 ;

  for ( int i = 0 ; i < 15 ; i++ ) {
    char ans;
    printf("Question %d:\n",i+1);
    printf("A> option a\tB> option b\nC> option c\tD> option d\n");
    printf("Enter your Answer Sir/Ma'am:");
    scanf("\n");
    scanf("%c",&ans);
    if ( checkQuestion( ans , (list+i)->correctAns )){
      updateCurrentWorth( prize[i] , currentWorth );
      updateDefiniteWorth( i , currentWorth , definiteWorth );
      printf("Congratulations!!!,You have won %d rupees for this question\n" , prize[i]);
      printf("You currently have %d rupees in your pocket\n" , *currentWorth );
      if ( i > 3 )
      printf("Even if you get the next question wrong, you will take %d rupees home\n" , *definiteWorth);
    }
    else{
      printf("Sorry!!! But your answer is wrong , you will take %d rupees home\n" , *definiteWorth);
      if ( i <= 4 )
      printf("Even if you have lost here today, you have won hearts all over the world my friend!\n");
      if ( i >4 && i<= 9)
      printf("You have won something and something is not nothing so REJOICE!\n");
      if ( i > 9 )
      printf("Even if you are not a CROREPATI you still leave a LAHKPATI from this stage\n");
      return 0;
    }
  }
  printf("MUBARAK HO!!! AAP CROREPATI BAN GAYE!!!");

}

void updateCurrentWorth( int reward , int * current ){
  *current = *current + reward ;
}

int checkQuestion( char ans , char correctAns){
  if ( ans == correctAns || ans == correctAns + 'a' - 'A'){
  return 1;}
  else{
  return 0;}
}

void updateDefiniteWorth( int i , int * current , int * definite ){
  if ( i == 4 || i==9 || i == 13 ){
    * definite = * current ;
  }
}

void fillArray ( int n , question array[n] ){

  for ( int i = 0 ; i < n ; i++ ){

    switch ( i % 4 ){
      case ( 0 ):
      ( array + i )->correctAns = 'A' ;
      break;
      case ( 1 ):
      ( array + i )->correctAns = 'B' ;
      break;
      case ( 2 ):
      ( array + i )->correctAns = 'C' ;
      break;
      case ( 3 ):
      ( array + i )->correctAns = 'D' ;
      break;
    }
  }
}
// 1st version 6/13/2020
 

