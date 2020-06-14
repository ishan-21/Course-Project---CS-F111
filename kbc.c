#include<stdio.h>
#include<stdlib.h>

struct quest{
  char correctAns;
};

typedef struct quest question;

void fillArray ( int n , question array[] );

void updateCurrentWorth( int reward , int * current );

int checkQuestion( char ans , char correctAns );

void updateDefiniteWorth( int i , int * current , int * definite );

int prize[15]={1000,1000,1000,2000,5000,10000,20000,40000,80000,160000,320000,610000,1250000,2500000,5000000};

int main()
{

  int * currentWorth = malloc(sizeof(int));

  int * definiteWorth = malloc(sizeof(int));

  *currentWorth = 0 ;
  *definiteWorth = 0 ;

  FILE * fp;
  fp = fopen("question.txt","r");

  printf("WELCOME TO KAUN BANEGA CROREPATI!\n\n");
  printf("THIS GAME HAS 15 QUESTIONS\nEACH QUESTION HAS 4 CHOICES OUT OF WHICH ONLY ONE IS CORRECT\n\n");
  printf("WRONG ANSWER TO ANY OF THE QUESTIONS LEADS TO IMMEDIATE TERMINATION\n\n");
  printf("WE ALSO PROVIDE 2 LIFE-LINES: 50-50 AND FLIP THE QUESTION\n\n");
  printf("50-50: THIS WILL LEAD TO REMOVAL OF 2 WRONG CHOICES OUT OF THE TOTAL 4\n\n");
  printf("FLIP THE QUESTION: THIS WILL CHANGE THE CURRENT QUESTION ENTIRELY\n\n");
  printf("PRIZE MONEY DISTRIBUTION:-\n\n");
  printf("QUESTION NUMBER\t   PRIZE MONEY FOR THAT QUESTION\t   NET PRIZE MONEY UPTO THAT QUESTION\n");
  for ( int i = 0 ; i < 15 ; i++ ){
    *( currentWorth ) = *( currentWorth ) + *( prize + i );
    printf("%d\t\t\t%d\t\t\t\t\t%d", i+1 , *( prize + i ) , *(currentWorth));
    if ( i == 4 || i == 9 || i == 13)
    printf("\t\tDEFINITE TAKE HOME LEVEL");
    printf("\n\n");
  }

  *currentWorth = 0; // note that the pointer reference value was changed during  display of prizes , naturally we had to initialize it to 0 here

  char  start;
  printf("PRESS ANY KEY ON YOUR KEYBOARD TO CONTINUE ( and then press \" ENTER \" if you haven't pressed ENTER \n");
  scanf("%c", &start); // here I did not use system("pause") because it's a window command and would not  work in MAC or LINUX

  while( 1 )
  {
    if ( &start != NULL )
      break;
    else
      return 0;
  }
  printf("\nLETS PLAY!!!!\n\n");
  question list[15];
  fillArray( 15 ,  list );

  for ( int i = 0 ; i < 15 ; i++ ) {
    char ans;
    char finalAns;
    char c;

    for ( int i = 0 ; i < 6  ; i++){
        do {
            c = fgetc(fp);
            printf("%c",c);
        } while ( c != '\n' );

    }

    printf("\n What do you think is the answer:");
    scanf("\n");
    scanf("%c",&ans );
    printf("Do you want to lock it ( Press 'Y' for Yes and 'N' for No):");

    while ( 1 ){

        char prompt;
        scanf("\n");
        scanf("%c" , &prompt );

        if ( prompt == 'Y' || prompt == 'Y' + 'a' - 'A'){
            finalAns = ans;
            break;
        } else if ( prompt == 'N' || prompt == 'N' + 'a' - 'A') {
            printf("Take your time and Enter the answer you want to lock:");
            scanf("\n");
            scanf("%c", &finalAns);
            break;
        } else {
            printf("Y and N are the only valid choices. Please Enter a valid Choice:");
        }

    }
    if ( checkQuestion( finalAns , (list+i)->correctAns )){
      updateCurrentWorth( prize[i] , currentWorth );
      updateDefiniteWorth( i , currentWorth , definiteWorth );
      printf("\nCongratulations!!!,You have won %d rupees for this question\n" , prize[i]);
      printf("\nYou currently have %d rupees in your pocket\n\n" , *currentWorth );
      if ( i > 3 )
      printf("\nEven if you get the next question wrong, you will take %d rupees home\n" , *definiteWorth);
    }
    else{
      printf("\nSorry!!! But your answer is wrong , the correct ans was %c. You will take %d rupees home\n" , ( list + i )->correctAns, *definiteWorth);
      if ( i <= 4 )
      printf("\nEven if you have lost here today, you have won hearts all over the world my friend!\n");
      if ( i >4 && i<= 9)
      printf("\nYou have won something and something is not nothing so REJOICE!\n");
      if ( i > 9 )
      printf("\nEven if you are not a CROREPATI you still leave a LAHKPATI from this stage\n");
      return 0;
    }
  }
  printf("\nMUBARAK HO!!! AAP CROREPATI BAN GAYE!!!\n\n");

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

void fillArray ( int n , question array[] ){

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
