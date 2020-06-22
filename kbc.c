#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NUMBER_OF_QUESTIONS 15
#define NUMBER_OF_LINES_PER_QUESTION 6
#define NUMBER_OF_CHARACTERS_PER_QUESTION 400

struct quest{
  char originalCorrectAns;
  char originalQues[NUMBER_OF_LINES_PER_QUESTION][NUMBER_OF_CHARACTERS_PER_QUESTION];
  char originalFiftyFiftyQues[NUMBER_OF_LINES_PER_QUESTION][NUMBER_OF_CHARACTERS_PER_QUESTION];
  char replacementCorrectAns;
  char replacementQues[NUMBER_OF_LINES_PER_QUESTION][NUMBER_OF_CHARACTERS_PER_QUESTION];
  char replacementFiftyFiftyQues[NUMBER_OF_LINES_PER_QUESTION][NUMBER_OF_CHARACTERS_PER_QUESTION];
};

typedef struct quest question;

void fillOriginalAns( question array[] );

void fillReplacementAns( question array[] );

void updateCurrentWorth( int reward , int * current );

void updateDefiniteWorth( int i , int * current , int * definite );

int checkQuestion( char ans , char correctAns );

void fillOriginalQuestions ( question array[] , FILE * fp );

void fillOriginalFiftyFiftyQuestions ( question array[] , FILE * fp );

void fillReplacementQuestions ( question array[] , FILE * fp );

void fillReplacementFiftyFiftyQuestions ( question array[] , FILE * fp );

int prize[15]={1000,1000,1000,2000,5000,10000,20000,40000,80000,160000,320000,610000,1250000,2500000,5000000};



int main()
{
  int countFiftyFifty = 1 ;
  int countSwap = 1 ;
  int typeOfQuesUsed = 0 ;

  int * currentWorth = malloc(sizeof(int));
  int * definiteWorth = malloc(sizeof(int));

  *currentWorth = 0 ;
  *definiteWorth = 0 ;

  FILE * fp = NULL;
  fp = fopen("question.txt","r");

  if( fp == NULL ){
    printf("Error opening file\n");
    return 0 ;
  }

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
  printf("PRESS ANY KEY ON YOUR KEYBOARD TO CONTINUE ( and then press \" ENTER \" if you haven't pressed ENTER ):");
  start = getchar(); // here I did not use system("pause") because it's a window command and would not  work in MAC or LINUX

  while( 1 )
  {
    if ( &start != NULL )
      break;
    else
      return 0;
  }
  printf("\nLETS PLAY!!!!\n\n");

  question list[NUMBER_OF_QUESTIONS];
  fillOriginalAns( list );
  fillReplacementAns( list );
  fillOriginalQuestions( list , fp );
  fillOriginalFiftyFiftyQuestions( list , fp );
  fillReplacementQuestions( list , fp );
  fillReplacementFiftyFiftyQuestions( list , fp );

  for ( int i = 0 ; i < NUMBER_OF_QUESTIONS ; i++ ) {
    char promptLifeLine ;
    char promptWhichLfeLine ;
    char prompt ;
    char ans ;
    char finalAns ;
    char c ;

    for( int j = 0 ; j < NUMBER_OF_LINES_PER_QUESTION ; j++ ){
      printf("%s\n",( list + i )->originalQues[j] );
    }




    while ( 1 )
{
      if( countSwap == 0 && countSwap == 0 ){
        break ;
      }
      printf("\nDo you want to use a life-line (Press \'Y\' for Yes and \'N\' for No): ");
      scanf("\n");
      scanf("%c" , &promptLifeLine );
      printf("\n");
      if ( promptLifeLine == 'Y' || promptLifeLine == 'y'){
        printf("Which life line ( Press \'F\' for 50-50 and \'S\' for swapping the question): ");
        while ( 1 ){
          scanf("\n");
          scanf("%c" , &promptWhichLfeLine );
          printf("\n");
          if ( ( promptWhichLfeLine == 'F' || promptWhichLfeLine == 'f' ) ){
            if( countFiftyFifty == 0 ){
              printf("\nYou've already used 50-50\n");
              printf("\nPlease enter an available life-line: ");
              continue ;
            }
            countFiftyFifty--;
            printf("50-50 USED\n\n");
              for( int j = 0 ; j < NUMBER_OF_LINES_PER_QUESTION ; j++ ){
                printf("%s\n" , (list + i )->originalFiftyFiftyQues[j]);
              }
              if( countSwap == 0){
                printf("\nYou've already used Swap the Question.\n\n");
                break;
              }
              printf("Do you want to use another life-line (Press \'Y\' for Yes and \'N\' for No): ");

              while( 1 ){
              scanf("\n");
              scanf("%c" , &prompt );
              if ( prompt == 'Y' || prompt == 'y' ){
                countSwap--;
                printf("\nYour only option now is swapping the ques.\n\n");
                printf("SWAP THE QUESTION USED\n\n");
                typeOfQuesUsed = 1 ;
                for( int j = 0 ; j < NUMBER_OF_LINES_PER_QUESTION ; j++ ){
                  printf("%s\n" , (list + i )->replacementQues[j]);
              }
                break;
          }
              else if ( prompt == 'N' || prompt == 'n' ){
                break ;
              }
              else {
                printf("Please Enter a valid response: ");
              }
        }
        break ;
      }
          else if ( ( promptWhichLfeLine == 'S' || promptWhichLfeLine == 's' )){
            if( countSwap == 0 ){
              printf("You've already used Swap the Question\n");
              printf("Please enter an available life-line: ");
              continue ;
            }
            countSwap--;
            printf("SWAP THE QUESTION USED\n\n");
            typeOfQuesUsed = 1 ;
            for( int j = 0 ; j < NUMBER_OF_LINES_PER_QUESTION ; j++ ){
              printf("%s\n" , (list + i )->replacementQues[j]);
            }
            if( countFiftyFifty == 0){
              printf("You've already used 50-50.\n\n");
              break;
            }
            printf("\nDo you want to use another life-line (Press \'Y\' for Yes and \'N\' for No): ");

            while( 1 ){
            scanf("\n");
            scanf("%c" , &prompt );
            if ( prompt == 'Y' || prompt == 'y' ){
              countFiftyFifty--;
              printf("\nYour only option now is using 50-50.\n\n");
              printf("50-50 USED\n\n");
              typeOfQuesUsed = 0 ;
              for( int j = 0 ; j < NUMBER_OF_LINES_PER_QUESTION ; j++ ){
                printf("%s\n" , (list + i )->replacementFiftyFiftyQues[j]);
            }
              break;
        }
            else if ( prompt == 'N' || prompt == 'n' ){
              break ;
        }
            else {
              printf("Please enter a valid Response: ");
        }
    }
    break ;
  }
}
break ;
}
else if ( promptLifeLine == 'N' || promptLifeLine == 'n'){
    break ;
  }
else {
  printf("Please enter a valid Response\n\n");
}
}

if( countSwap == 0 && countFiftyFifty == 0 ){
  printf("YOU HAVE ALREADY USED BOTH THE LIFELINES\n\n");
}


  printf("\nWhat do you think is the answer:");
    while ( 1 ){
      scanf("\n");
      scanf("%c",&ans );
      printf("\n");
      if ( ans == 'a' || ans == 'A' || ans == 'b' || ans == 'B' || ans == 'c' || ans == 'C' || ans == 'd' || ans == 'D'){
        break;
      }else{
        printf("Enter a valid response (\"A\" , \"B\" , \"C\" or \"D\"):");
      }

    }

  printf("Do you want to lock it ( Press 'Y' for Yes and 'N' for No):");
    while ( 1 ){
      char prompt;
      scanf("\n");
      scanf("%c" , &prompt );
      printf("\n");
      if ( prompt == 'Y' || prompt == 'y' ){
          finalAns = ans;
          break;
      }else if ( prompt == 'N' || prompt == 'n' ) {
          printf("Take your time and Enter the answer you want to lock:");
          scanf("\n");
          scanf("%c", &finalAns);
          break;
      }else {
          printf("Y and N are the only valid choices. Please Enter a valid Choice:");
        }

    }

    if( typeOfQuesUsed == 0 ){
    if ( checkQuestion( finalAns , (list+i)->originalCorrectAns )){
      updateCurrentWorth( prize[i] , currentWorth );
      updateDefiniteWorth( i , currentWorth , definiteWorth );
      printf("Congratulations!!!,You have won %d rupees for this question\n" , prize[i]);
      printf("\nYou currently have %d rupees in your pocket\n\n" , *currentWorth );
      if ( i > 3 )
      printf("\nEven if you get the next question wrong, you will take %d rupees home\n" , *definiteWorth);
    }
    else{
      printf("\nSorry!!! But your answer is wrong , the correct ans was %c. You will take %d rupees home\n" , ( list + i )->originalCorrectAns, *definiteWorth);
      if ( i < 5 )
      printf("\nEven if you have lost here today, you have won hearts all over the world my friend!\n");
      if ( i > 4 && i < 10)
      printf("\nYou have won something and something is not nothing so REJOICE!\n");
      if ( i > 9 )
      printf("\nEven if you are not a CROREPATI you still leave a LAHKPATI from this stage\n");
      return 0;
    }
  }
  else{
    if ( checkQuestion( finalAns , (list+i)->replacementCorrectAns )){
      updateCurrentWorth( prize[i] , currentWorth );
      updateDefiniteWorth( i , currentWorth , definiteWorth );
      printf("Congratulations!!!,You have won %d rupees for this question\n" , prize[i]);
      printf("\nYou currently have %d rupees in your pocket\n\n" , *currentWorth );
      if ( i > 3 )
      printf("\nEven if you get the next question wrong, you will take %d rupees home\n" , *definiteWorth);
    }
    else{
      printf("\nSorry!!! But your answer is wrong , the correct ans was %c. You will take %d rupees home\n" , ( list + i )->originalCorrectAns, *definiteWorth);
      if ( i < 5 )
      printf("\nEven if you have lost here today, you have won hearts all over the world my friend!\n");
      if ( i > 4 && i < 10)
      printf("\nYou have won something and something is not nothing so REJOICE!\n");
      if ( i > 9 )
      printf("\nEven if you are not a CROREPATI you still leave a LAHKPATI from this stage\n");
      return 0;
    }
  }
}
  printf("\nMUBARAK HO!!! AAP CROREPATI BAN GAYE!!!\n\n");

}

void updateCurrentWorth( int reward , int * current ){
  *current = *current + reward ;
}

int checkQuestion( char ans , char correctAns){
  if ( ans == correctAns || ans == correctAns + 'a' - 'A')
    return 1;
  else
    return 0;
}

void updateDefiniteWorth( int i , int * current , int * definite ){
  if ( i == 4 || i==9 || i == 13 )
    ( * definite ) = ( * current ) ;
}

void fillOriginalQuestions ( question array[] , FILE * fp){
  for( int i = 0 ; i < NUMBER_OF_QUESTIONS ; i++ ){
    for( int j = 0 ; j < NUMBER_OF_LINES_PER_QUESTION ; j++ ){
      fgets( (array+i)->originalQues[j] , 400 , fp );
      (array+i)->originalQues[j][strlen((array+i)->originalQues[j]) - 1 ]='\0';
    }
  }
}

void fillOriginalFiftyFiftyQuestions ( question array[] , FILE * fp ){
  for( int i = 0 ; i < NUMBER_OF_QUESTIONS ; i++ ){
    for( int j = 0 ; j < NUMBER_OF_LINES_PER_QUESTION ; j++ ){
      fgets( (array+i)->originalFiftyFiftyQues[j] , 400 , fp );
      (array+i)->originalFiftyFiftyQues[j][strlen((array+i)->originalFiftyFiftyQues[j]) - 1 ] = '\0';
    }
  }
}

void fillReplacementQuestions ( question array[] , FILE * fp ){
  for( int i = 0 ; i < NUMBER_OF_QUESTIONS ; i++ ){
    for( int j = 0 ; j < NUMBER_OF_LINES_PER_QUESTION ; j++ ){
      fgets( (array+i)->replacementQues[j] , 400 , fp );
      (array+i)->replacementQues[j][strlen((array+i)->replacementQues[j]) - 1 ] = '\0';
    }
  }
}

void fillReplacementFiftyFiftyQuestions ( question array[] , FILE * fp ){
  for( int i = 0 ; i < NUMBER_OF_QUESTIONS ; i++ ){
    for( int j = 0 ; j < NUMBER_OF_LINES_PER_QUESTION ; j++ ){
      fgets( (array+i)->replacementFiftyFiftyQues[j] , 400 , fp );
      (array+i)->replacementFiftyFiftyQues[j][strlen((array+i)->replacementFiftyFiftyQues[j]) - 1 ] = '\0';
    }
  }
}

void fillOriginalAns ( question array[] ){
  for( int i = 0 ; i < NUMBER_OF_QUESTIONS ; i++ ){
       if (i==4||i==11||i==12)
       ( array + i )->originalCorrectAns = 'A' ;
       else if (i==0||i==8||i==10||i==14)
       ( array + i )->originalCorrectAns = 'C' ;
       else if (i==3||i==7|i==13)
       ( array + i )->originalCorrectAns = 'D' ;
       else
       ( array + i )->originalCorrectAns = 'B' ;
  }
}

  void fillReplacementAns ( question array[] ){
    for( int i = 0 ; i < NUMBER_OF_QUESTIONS ; i++ ){
        if (i==0||i==6||i==11)
        ( array + i )->replacementCorrectAns = 'A' ;
        else if (i==1||i==7)
        ( array + i )->replacementCorrectAns = 'D' ;
        else if (i==2||i==9||i==10||i==13)
        ( array + i )->replacementCorrectAns = 'C' ;
        else
        ( array + i )->replacementCorrectAns = 'B' ;
    }
  }
