
#include<stdio.h>		//imporitng standard input and output header file
#include<stdlib.h>		//importing standard library header file
#include<string.h>		//importing string header file

#define NUMBER_OF_QUESTIONS 15	//setting NUMBER_OF_QUESTIONS constant at 15
#define NUMBER_OF_LINES_PER_QUESTION 6	//setting NUMBER_OF_LINES_PER_QUESTION constant at 6
#define NUMBER_OF_CHARACTERS_PER_LINE 400	//setting NUMBER_OF_CHARACTERS_PER_LINE constant at 400

/*
defining a structure 'quest' with many variables related to the questions and their answers and lifelines
*/

struct quest
{
  char originalCorrectAns;	//variable to store answer of the original question
  char originalQues[NUMBER_OF_LINES_PER_QUESTION][NUMBER_OF_CHARACTERS_PER_LINE];	//multidimensional string type array to store the original question
  char originalFiftyFiftyQues[NUMBER_OF_LINES_PER_QUESTION][NUMBER_OF_CHARACTERS_PER_LINE];	//multidimensional string type array to store the question after 50-50 has been applied
  char replacementCorrectAns;	//variable to store answer of the replaced question
  char replacementQues[NUMBER_OF_LINES_PER_QUESTION][NUMBER_OF_CHARACTERS_PER_LINE];	//multidimensional string type array to store the new swapped question
  char replacementFiftyFiftyQues[NUMBER_OF_LINES_PER_QUESTION][NUMBER_OF_CHARACTERS_PER_LINE];	//multidimensional string type array to store the question after 50-50 is applied to the swapped question
};

typedef struct quest question;	//using typedef to create a new name 'question' for the structure 'quest' also known as aliasing

/*
defining function prototypes
*/

void fillOriginalAns (question array[]); // to store answers to original questions in structure element originalCorrectAns

void fillReplacementAns (question array[]); // to store answers to replacement questions in structure replacementCorrectAns

void updateCurrentWorth (int reward, int *current);	//to update current worth, the amount that contestant has won till that time

void updateDefiniteWorth (int i, int *current, int *definite);	//to update definite worth, the amount that contestant will definitely take home

int checkQuestion (char ans, char correctAns); // to check the question answered

void fillOriginalQuestions (question array[], FILE * fp); // to assign original questions to multidimensional string array originalQues

void fillOriginalFiftyFiftyQuestions (question array[], FILE * fp);// to assign 50-50 version of original questions to multidimensional string array originalFiftyFiftyQues

void fillReplacementQuestions (question array[], FILE * fp);// to assign replacement questions to multidimensional string array replacementQues

void fillReplacementFiftyFiftyQuestions (question array[], FILE * fp);// to assign 50-50 version of replacement questions to multidimensional string array replacementFiftyFiftyQues

int prize[15] = { 1000, 1000, 1000, 2000, 5000, 10000, 20000, 40000, 80000, 160000, 320000, 610000, 1250000, 2500000, 5000000 };	//array 'prize' stores the additional prize money that a person wins after answering the question correctly



int main ()				//defining main function
{
  int countFiftyFifty = 1;	//setting countFiftyFifty to 1 so that it could be used only once
  int countSwap = 1;		//setting countSwap to 1 so that it could be used only once
  int typeOfQuesUsed = 0;	//setting typeOfQuesUsed to 0, used to signify original question

/*
malloc reserves a block of memory of the specified number of bytes and returns it's address
*/

  int *currentWorth = malloc (sizeof (int));	//currentWorth is used to represent the total amount that the person has won
  int *definiteWorth = malloc (sizeof (int));	//definiteWorth is the minimum amount the person takes home even if he answers the question wrong

  *currentWorth = 0;		//setting *currentWorth to 0
  *definiteWorth = 0;		//setting *definiteWorth to 0

/*
opening file which has the questions in it
*/

  FILE *fp = NULL;
  fp = fopen ("question.txt", "r");

/*
giving error message if file not represent
*/

  if (fp == NULL)
    {
      printf ("Error opening file\n");
      return 0;
    }

/*
printing general information and instructions about the game
*/

  printf ("WELCOME TO KAUN BANEGA CROREPATI!\n\n");
  printf("THIS GAME HAS 15 QUESTIONS\nEACH QUESTION HAS 4 CHOICES OUT OF WHICH ONLY ONE IS CORRECT\n\n");
  printf("WRONG ANSWER TO ANY OF THE QUESTIONS LEADS TO IMMEDIATE TERMINATION\n\n");
  printf("WE ALSO PROVIDE 2 LIFE-LINES: 50-50 AND FLIP THE QUESTION\n\n");
  printf("50-50: THIS WILL LEAD TO REMOVAL OF 2 WRONG CHOICES OUT OF THE TOTAL 4\n\n");
  printf("SWAP THE QUESTION: THIS WILL CHANGE THE CURRENT QUESTION ENTIRELY\n\n");
  printf ("PRIZE MONEY DISTRIBUTION:-\n\n");
  printf("QUESTION NUMBER\t   PRIZE MONEY FOR THAT QUESTION\t   NET PRIZE MONEY UPTO THAT QUESTION\n");

/*
displaying prizes
*/

  for (int i = 0; i < 15; i++)
    {
      *(currentWorth) = *(currentWorth) + *(prize + i);
      printf ("%d\t\t\t%d\t\t\t\t\t%d", i + 1, *(prize + i), *(currentWorth));
      if (i == 4 || i == 9 || i == 13){	//printing definite take home level to indicate that this is the minimum amount they take home if they answer correctly in that round
	       printf ("\t\tDEFINITE TAKE HOME LEVEL");
     }
      printf ("\n\n");
    }

  *currentWorth = 0;		// note that the pointer reference value was changed during display of prizes, naturally we had to initialize it to 0 here

  char start;
  printf("PRESS ANY KEY ON YOUR KEYBOARD TO CONTINUE ( and then press \" ENTER \" if you haven't pressed ENTER ):");
  start = getchar ();		// here I did not use system("pause") because it's a window command and would not work in MAC or LINUX

/*
starting game if character entered
*/

  while (1)
    {
      if (&start != NULL)
	     break;
      else
	     return 0;
    }
  printf ("\nLET US PLAY!!!!\n\n");

  question list[NUMBER_OF_QUESTIONS];	//creating an array of structure of question type named 'list', with 15 elements for representing the 15 questions separately

/*
function declaration
*/

  fillOriginalAns (list);
  fillReplacementAns (list);
  fillOriginalQuestions (list, fp);
  fillOriginalFiftyFiftyQuestions (list, fp);
  fillReplacementQuestions (list, fp);
  fillReplacementFiftyFiftyQuestions (list, fp);

/*
loop to actually run the game
*/

  for (int i = 0; i < NUMBER_OF_QUESTIONS; i++)
    {
      char promptLifeLine; // to ask if contestant wants to use a life-line
      char promptWhichLfeLine; // if yes then variable to ask which life-line?
      char prompt; // to ask for instruction to use another life-line or not
      char ans;  // to store tentative answer before actually locking it
      char finalAns; // to store the final answer to be evaluated against the correct one
      char c;

/*
printing original question
*/

  for (int j = 0; j < NUMBER_OF_LINES_PER_QUESTION; j++)
	{
	  printf ("%s\n", (list + i)->originalQues[j]);
	}




  while (1)
	{
	  if (countSwap == 0 && countSwap == 0) // this ensures that this loop is not executed further if no life-lines left
	    {
	      break;
	    }
	  printf ("\nDo you want to use a life-line (Press \'Y\' for Yes and \'N\' for No): ");	//asking if contestant wants to use lifeline
	  scanf ("\n");		//taking input over multiple lines in case of invalid input or otherwise
	  scanf ("%c", &promptLifeLine);	// taking input
	  printf ("\n");	//new line
	  /* if contestant wants to use lifeline */
	  if (promptLifeLine == 'Y' || promptLifeLine == 'y')
	    {
	      printf ("Which life line ( Press \'F\' for 50-50 and \'S\' for swapping the question): ");	//asking contestant which lifeline do they want to use
	      while (1)
		{
		  scanf ("\n");
		  scanf ("%c", &promptWhichLfeLine);	//accepting contestant's response to which lifeline they want to choose
		  printf ("\n");
		  if ((promptWhichLfeLine == 'F' || promptWhichLfeLine == 'f'))
		    {
		      /* checking if contestant has used 50-50 */
		      if (countFiftyFifty == 0)
			{
			  printf ("\nYou've already used 50-50\n");
			  printf ("\nPlease enter an available life-line: ");
			  continue;
			}
		      countFiftyFifty--;	//decrementing to make sure 50-50 is not used again
		      printf ("50-50 USED\n\n");
		      /* eliminating 2 options by printing question with 2 wrong options eliminated */
		      for (int j = 0; j < NUMBER_OF_LINES_PER_QUESTION; j++)
			{
			  printf ("%s\n",(list + i)->originalFiftyFiftyQues[j]);
			}
		      /* checking if the lifeline to swap the question is used */
		      if (countSwap == 0)
			{
			  printf("\nYou've already used Swap the Question.\n\n");
			  break;
			}
		      printf ("Do you want to use another life-line (Press \'Y\' for Yes and \'N\' for No): ");	//asking if the contestant wants to use another lifeline

		      while (1)
			{
			  scanf ("\n");
			  scanf ("%c", &prompt);	//accepting response
			  if (prompt == 'Y' || prompt == 'y')
			    {
			      countSwap--;	//ensuring the lifeline is not used again
			      printf("\nYour only option now is swapping the ques.\n\n");
			      printf ("SWAP THE QUESTION USED\n\n");
			      typeOfQuesUsed = 1;	//used to signify the swapped question is used
			      /* displaying new question */
			      for (int j = 0; j < NUMBER_OF_LINES_PER_QUESTION; j++)
				{
				  printf ("%s\n", (list + i)->replacementQues[j]);
				}
			      break; // breaking the loop as both life-lines used
			    }
			  /* breaking the loop if contestant says that he does not want to use another lifeline */
			  else if (prompt == 'N' || prompt == 'n')
			    {
			      break;
			    }
			  /* asking for a valid response if Y/y or N/n is not entered */
			  else
			    {
			      printf ("Please Enter a valid response: ");
			    }
			}
		      break;
		    }
		  /* case where contestant wants to swap the question */
		  else if ((promptWhichLfeLine == 'S'|| promptWhichLfeLine == 's'))
		    {
		      /* checking if lifeline had already been used */
		      if (countSwap == 0)
			{
			  printf ("You've already used Swap the Question\n");
			  printf ("Please enter an available life-line: ");
			  continue;
			}
		      countSwap--;	//making sure the lifeline 'swap the question' is not used again
		      printf ("SWAP THE QUESTION USED\n\n");
		      typeOfQuesUsed = 1;	//used to signify swapped question is used
		      /* swpping the question */
		      for (int j = 0; j < NUMBER_OF_LINES_PER_QUESTION; j++)
			{
			  printf ("%s\n", (list + i)->replacementQues[j]);
			}
		      /* checking if 50-50 has been used */
		      if (countFiftyFifty == 0)
			{
			  printf ("You've already used 50-50.\n\n");
			  break;
			}
		      printf ("\nDo you want to use another life-line (Press \'Y\' for Yes and \'N\' for No): ");	//asking if contestant wants to use 50-50

		      while (1)
			{
			  scanf ("\n");
			  scanf ("%c", &prompt);	//accepting response
			  if (prompt == 'Y' || prompt == 'y')
			    {
			      countFiftyFifty--;	//decrementing to make sure lifeline is not used again
			      printf("\nYour only option now is using 50-50.\n\n");
			      printf ("50-50 USED\n\n");
			      typeOfQuesUsed = 1;	//signifying that the swapped question is used
			      /* applying 50-50 to the swapped question */
			      for (int j = 0; j < NUMBER_OF_LINES_PER_QUESTION; j++)
				{
				  printf ("%s\n", (list +i)->replacementFiftyFiftyQues[j]);
				}
			      break; // exiting the loop as both life-lines already used
			    }
			  /* breaking out of the loop if second lifeline is not used by contestant */
			  else if (prompt == 'N' || prompt == 'n')
			    {
			      break;
			    }
			  /* asking for a valid response if Y/y or N/n is not entered */
			  else
			    {
			      printf ("Please enter a valid Response: ");
			    }
			}
		      break; // breaking out of the second innermost while loop
		    }
		}
	      break; // breaking out of the innermost while loop
	    }
/* breaking out of the loop if contestant does not want to use lifeline */
	  else if (promptLifeLine == 'N' || promptLifeLine == 'n')
	    {
	      break;
	    }
/* asking for a valid response if Y/y or N/n is not entered */
	  else
	    {
	      printf ("Please enter a valid Response\n\n");
	    }
	}

/* displaying if both lifelines used */
      if (countSwap == 0 && countFiftyFifty == 0)
	{
	  printf ("YOU HAVE ALREADY USED BOTH THE LIFELINES\n\n");
	}


      printf ("\nWhat do you think is the answer:");	//asking for user to enter answer for the question
      while (1)
	{
	  scanf ("\n");
	  scanf ("%c", &ans);	//accepting response and storing it
	  printf ("\n");
	  /* breaking out of the loop if valid answer is entered */
	  if (ans == 'a' || ans == 'A' || ans == 'b' || ans == 'B'|| ans == 'c' || ans == 'C' || ans == 'd' || ans == 'D')
	    {
	      break;
	    }
	  /* asking for a valid response if answer not valid */
	  else
	    {
	      printf("Enter a valid response (\"A\" , \"B\" , \"C\" or \"D\"):");
	    }

	}

      printf ("Do you want to lock it ( Press 'Y' for Yes and 'N' for No):");	//asking contestant whether or not to finalize their answer for evaluation
      while (1)
	{
	  char prompt;
	  scanf ("\n");
	  scanf ("%c", &prompt);	//accepting response
	  printf ("\n");
	  /* break loop if answer confirmed */
	  if (prompt == 'Y' || prompt == 'y')
	    {
	      finalAns = ans;
	      break;
	    }
	  /* asking for another answer to lock if contestant does not confirm */
	  else if (prompt == 'N' || prompt == 'n')
	    {
	      printf("Take your time and Enter the answer you want to lock:");
	      scanf ("\n");
	      scanf ("%c", &finalAns);	//accepting final locked answer
	      break;
	    }
	  /* asking for a valid response if Y/y or N/n is not entered */
	  else
	    {
	      printf("Y and N are the only valid choices. Please Enter a valid Choice:");
	    }

	}

      /*
         checking if question is original without swapping
       */

      if (typeOfQuesUsed == 0)
	{
	  if (checkQuestion (finalAns, (list + i)->originalCorrectAns))
	    {			//checking if answer is correct
	      updateCurrentWorth (prize[i], currentWorth);	//updating the total amount won
	      updateDefiniteWorth (i, currentWorth, definiteWorth);	//updating the minimum amount that the contestant takes home
	      printf ("Congratulations!!!,You have won %d rupees for this question\n", prize[i]);	//displaying incremental amount won after answeing the question
	      printf ("\nYou currently have %d rupees in your pocket\n\n", *currentWorth);	//displaying total amount won after answering question
	      if (i > 3){
		      printf ("\nEven if you get the next question wrong, you will take %d rupees home\n", *definiteWorth);	//displaying minimum amount the person takes home
        }
	    }
	  else
	    {			//if answer wrong
	      printf ("\nSorry!!! But your answer is wrong , the correct ans was %c. You will take %d rupees home\n", (list + i)->originalCorrectAns, *definiteWorth);	//displaying correct answer and the amount they take home
	      if (i < 5){
		      printf ("\nEven if you have lost here today, you have won hearts all over the world my friend!\n");	//displaying this if did not win anything
        }
	      else if (i > 4 && i < 10){
		      printf ("\nYou have won something and something is not nothing so REJOICE!\n");	//displaying this if they won something
        }
	      else if( i > 9 ){
		      printf ("\nEven if you are not a CROREPATI you still leave a LAHKPATI from this stage\n");	//displaying this if they had atleast won a lakh
        }

	      return 0;		//ending program
	    }
	}
      else // if in case replacement question used
	{
	  if (checkQuestion (finalAns, (list + i)->replacementCorrectAns))
	    {			//checking if answer is correct
	      updateCurrentWorth (prize[i], currentWorth);	//updating the total amount won
	      updateDefiniteWorth (i, currentWorth, definiteWorth);	//updating the minimum amount that the contestant takes home
	      printf ("Congratulations!!!,You have won %d rupees for this question\n", prize[i]);	//displaying incremental amount won after answeing the question
	      printf ("\nYou currently have %d rupees in your pocket\n\n", *currentWorth);	//displaying total amount won after answering question
	      if (i > 3){
        printf ("\nEven if you get the next question wrong, you will take %d rupees home\n", *definiteWorth);	//displaying minimum amount the person takes home
      }
	    }
	  else
	    {			//if answer wrong
	      printf ("\nSorry!!! But your answer is wrong , the correct ans was %c. You will take %d rupees home\n", (list + i)->replacementCorrectAns, *definiteWorth);	//displaying correct answer and the amount they take home
	      if (i < 5){
		      printf ("\nEven if you have lost here today, you have won hearts all over the world my friend!\n");	//displaying this if did not win anything
        }
	      else if (i > 4 && i < 10){
		      printf ("\nYou have won something and something is not nothing so REJOICE!\n");	//displaying this if they won something
        }
	      else if (i > 9 ){
		      printf ("\nEven if you are not a CROREPATI you still leave a LAHKPATI from this stage\n");	//displaying this if they had atleast won a lakh
        }
	      return 0;		//ending program
	    }
	}
    }
  printf ("\nMUBARAK HO!!! AAP CROREPATI BAN GAYE!!!\n\n");	//displaying message if they answer all questions right!!!, truly an amazing feat if you ask us :)

}

/* funtion to update the toal amount person has won */
void updateCurrentWorth (int reward, int *current)
{
  *current = *current + reward;	//updating *current
}

/* function to check if answer is correct */
int checkQuestion (char ans, char correctAns)
{
  if (ans == correctAns || ans == correctAns + 'a' - 'A')	//or is to make sure both upper and lower cases work
    return 1;			//returning 1 if answer correct
  else
    return 0;			//returning 0 if answer wrong
}

/* function to update minimum amount contestant takes home */
void updateDefiniteWorth (int i, int *current, int *definite)
{
  if (i == 4 || i == 9 || i == 13)
    (*definite) = (*current);	//updating *definite at definite take home levels
}

void fillOriginalQuestions (question array[], FILE * fp)
{
  for (int i = 0; i < NUMBER_OF_QUESTIONS; i++)
    {
      for (int j = 0; j < NUMBER_OF_LINES_PER_QUESTION; j++)
	{
	  fgets ((array + i)->originalQues[j], 400, fp);
	  (array + i)->originalQues[j][strlen ((array + i)->originalQues[j]) -
				       1] = '\0';
	}
    }
}

void fillOriginalFiftyFiftyQuestions (question array[], FILE * fp)
{
  for (int i = 0; i < NUMBER_OF_QUESTIONS; i++)
    {
      for (int j = 0; j < NUMBER_OF_LINES_PER_QUESTION; j++)
	{
	  fgets ((array + i)->originalFiftyFiftyQues[j], 400, fp);
	  (array +
	   i)->originalFiftyFiftyQues[j][strlen ((array + i)->
						 originalFiftyFiftyQues[j]) -
					 1] = '\0';
	}
    }
}

void fillReplacementQuestions (question array[], FILE * fp)
{
  for (int i = 0; i < NUMBER_OF_QUESTIONS; i++)
    {
      for (int j = 0; j < NUMBER_OF_LINES_PER_QUESTION; j++)
	{
	  fgets ((array + i)->replacementQues[j], 400, fp);
	  (array +
	   i)->replacementQues[j][strlen ((array + i)->replacementQues[j]) -
				  1] = '\0';
	}
    }
}

void fillReplacementFiftyFiftyQuestions (question array[], FILE * fp)
{
  for (int i = 0; i < NUMBER_OF_QUESTIONS; i++)
    {
      for (int j = 0; j < NUMBER_OF_LINES_PER_QUESTION; j++)
	{
	  fgets ((array + i)->replacementFiftyFiftyQues[j], 400, fp);
	  (array +
	   i)->replacementFiftyFiftyQues[j][strlen ((array + i)->
						    replacementFiftyFiftyQues
						    [j]) - 1] = '\0';
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

void fillReplacementAns ( question array[] )
{
  for( int i = 0 ; i < NUMBER_OF_QUESTIONS ; i++ )
  {
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
