#############################################################
ReadMe for assignment submitted by 2019B3PS0504P
Practical section number: P9
Assignment question attempted: 1 ( KBC Game )

#############################################################
Team:-

1. 2019B3PS0504P Ishan Rai
2. 2019B3PS0406P Aryan Gautam Nadkarni
3. 2019B3PS0592P Shrey Bansal

#############################################################
Important information about the code we wanted to convey:-

Our code has 600+ lines, this is mainly because:-

1. At every prompt we have taken into account the scenario in which user enters an invalid character, for example something other than 'Y' or 'N' in case of a Yes/No or a option
   other than A/B/C/D . This definitely increased the length of the code by a good margin but it is much easier to use now even if one inadverently presses an invalid key. In conclusion,
   we have tryed to keep the program as user friendly as possible.

2. We have used 10+ functions in our code, to make it as modular as possible as mentioned in the problem statement itself. This also makes the code eaiser to understand and debug for
   the user. Furthermore, we have declared function prototypes as well when we could've done without them easily because we were taught that's it's always good practice as it increases
   the readability marginally.

3. We have used extensive indentation and also have blank lines where required to separate various portions of the code from each other.

4. We have also used comments as and when required to convey our thought process.

5. We also have declared constants through #define declaration so that the user can easily understand what each constant stands for and its use in various loops and portions throughout
   the code.

6. We have tryed to keep the game very conversational, displaying messages according to the scenario the player is in at the moment. This helped in the user computer interaction
   This also took a very large portion of our code.

IMPORTANT Information about the logic of the code:-

1. We copied entire information about the questions from a single text file by carefully placing information in the file and writing useful functions to copy that information in our
   question structure. We then placed those functions sequentially in our code so that the information is read into the correct members of the structure.

2. PLEASE DO NOT TAMPER WITH THE TEXT FILE. IT MAY LEAD TO DISTORTED OUTPUT. 

############################################################
Description of how to run the code and observe the output: (This is just a sample. You are expected to write in much more detail!!!)
1. We're attaching the .c file. There are no .h files in our project.
2. The procedure to running the code is fairly simple and usual like ordinary .c file. There are no special instructions.
3. We are however, attaching the "question.txt" file which is highly important for the working of the code.
############################################################
Known limitations of the code (if you have not been able to completely/fully implement certain features that were asked):

There are NO known limitations of the code. We have implemented every feature that was asked of us. We also added several other features such as quit etc.

#############################################################
Contributions of the team members:

Like all good things, this project also took team effort and it is highly unlikely that we would've been able to write such a code individually. All of us contributed more or less
equally in the project from day-1 . We had decided the task of each team member beforehand and checked the progress regularly through google meets. Not unlike the functions in our code,
we gave our best and together made a clean, working code. At the same time not unlike the functions in our code, some errors might have inadverently crept through, In such cases feedback
will be highly appreciated.

->Ishan( 2019B3PS0504P ) envisioned the structure of the code and identified the functions to be used as well as the procedural prompts guiding the contestant throughout the run of the game.
  He implemented the functioning of both the life-lines and decided to use structures for storing the questions and their related information such as correct ans, replacement ques,etc.
  He decided to use file for these purposes and encoded all the above functionalities in the code.

->Aryan( 2019B3PS0406P ) thought of adding the option to quit after the first definite level and handled the entire functionality to do so i.e encoded it in the code. He also provided insights in the code
  at various intervals starting from the first draft itself. He handled the comments throughout the code to explain each and every line clearly to the user.
  He also wrote the messages to be displayed if the player chose to quit or lost midway during the game.

->Shrey( 2019B3PS0592P ) did the task of shortlisting and adding the 30 questions and their various versions such as 50-50 and the replacement question for each of them.
  He also thought of adding a trivia after each question related to the subject much like the original KBC. He collected trivia about these 30 subjects and added them in the text file.
  He also encoded this. He also did the very essential task of error handling after each version of the code to check for errors in the output on screen and through the code as well.

#############################################################
