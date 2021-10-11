/******************************************************************************************************
*   Program name: main.c,
*   Author name: NiyojOli (https://www.github.com/niyoj),
*   Created Path: /main.c,
*   Created Date: 11 Oct 2021, 07:46:29 (DD MON YYYY, HH:MM:SS),
*   Description: This  program is the main program for the game scatter and is to be compiled and executed.
*******************************************************************************************************/

#include <stdio.h>      //stdio.h contains basic i/o functions prototypes
#include <string.h>     //string.h contains necessary string related functions
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define TIMER 10        //represents the time spent in each round. Here, round means all questions
#define PLAYERS 2       //represents number of the players in each round
#define ROUNDS 2        //represents number of rounds in the game

struct Question {       //structure for storing the answers in the game
    char name[100];
    char city[100];
    char word[5];
    char drink[100];
    char event[100];
    char career[100];
    char actor[100];
    char food[100];
};

int scoreboard[PLAYERS][ROUNDS] = {};       //stores the score of each player in each round

//function prototyope section starts here
void print_logo();
int print_answers(struct Question);
//function prototype section ends here

int main(void) {
    srand(time(0)); 
    
    struct Question ques[PLAYERS];

    //printing the scatter title in terminal at start with horizontal bar
    print_logo();

    //printing the instructions
    printf("Here are the instructions for you to proceed;\n");
    printf("  - There would be total %d players playing in each game. You can change it by editing main.c line no. 13.\n", PLAYERS);
    printf("  - There would be total %d rounds of the game. You can change it by editing main.c line no. 14\n", ROUNDS);
    printf("  - In each rounds each player should write 8 words of different categories starting with the randomly generated character\n");
    printf("  - There would be time limit of 60 seconds for each round, which can be configured by editing line no. 12\n");
    printf("  - Time would not be displayed on the terminal. You are on your own.\n");
    printf("  - There would be plus point of 50 after every succesfull completion of each question.\n");
    printf("  - But if you take more than the stated time. Each second more spent decreases your point by 5.\n");

    printf("\n\nPress enter to continue...");

    char c = getchar();
    printf("\b\b");
    system("@cls||clear");

    //main program starts from here
    for (int i=0; i<ROUNDS; i++) {          //looping the entire program for specified number of rounds
        
        //generating a random alphabet
        char alpha = 'A' + (rand() % 26);

        for (int j=0; j<PLAYERS; j++) {     //looping for each of the player in each round
            //starts the timer
            time_t begin = time(NULL);

            //printing the scatter line in terminal with horizontal bar
            print_logo();
            
            //printing the insturction
            printf("PLAYER-%d Its your turn. The chosen alphabet is %c.Your time starts now..\n", j+1, alpha);

            //asking the questions and getting the answers
            printf("Boy/Girl/Neutral name:  ");
            scanf(" %s", ques[j].name);
            printf("Captial city:           ");
            scanf(" %s", ques[j].city);
            printf("Four letterd Word:      ");
            scanf(" %s", ques[j].word);
            printf("A drink:                ");
            scanf(" %s", ques[j].drink);
            printf("An event (festival):    ");
            scanf(" %s", ques[j].event);
            printf("A profession or career: ");
            scanf(" %s", ques[j].career);
            printf("An actor or actress:    ");
            scanf(" %s", ques[j].actor);
            printf("A food or recipe:       ");
            scanf(" %s", ques[j].food);

            //ends the timer and deduct the points as per rules if applicable
            time_t end = time(NULL);
            int time_spent = (int) (end-begin);
            scoreboard[j][i] = (time_spent<=TIMER)? 0: -5*abs(time_spent-TIMER);

            printf("%d %d", scoreboard[j][i], time_spent);
            //if the answer doesnot matches the criteria don't save the answer
            if(tolower(ques[j].name[0]) != tolower(alpha)) strcpy(ques[j].name, "");
            if(tolower(ques[j].city[0]) != tolower(alpha)) strcpy(ques[j].city, "");
            if(tolower(ques[j].word[0]) != tolower(alpha) || strlen(ques[j].word) > 4) strcpy(ques[j].word, "");
            if(tolower(ques[j].drink[0]) != tolower(alpha)) strcpy(ques[j].drink, "");
            if(tolower(ques[j].event[0]) != tolower(alpha)) strcpy(ques[j].event, "");
            if(tolower(ques[j].career[0]) != tolower(alpha)) strcpy(ques[j].career, "");
            if(tolower(ques[j].actor[0]) != tolower(alpha)) strcpy(ques[j].actor, "");
            if(tolower(ques[j].food[0]) != tolower(alpha)) strcpy(ques[j].food, "");

            system("@cls||clear");          //clear the screen
        }

        //scoring each players achievement
        for(int j=0; j<PLAYERS; j++) {
            //printing the scatter line in terminal with horizontal bar
            print_logo();

            //prints the instruction to the player
            printf("The answers by Player-%d are;\n", j+1);

            //if every answer is not wrong, ask the players whether the information is correct or not
            if (print_answers(ques[j])) {
                printf("How many answers are correct? ");

                int score = 0;
                scanf(" %d", &score);

                //1 correct answers = 50 points
                scoreboard[j][i] += 50*score;
            } else {
                printf("\nEvery answers given by this player was incorrect..\n");
            }

            printf("\nPress Enter to Continue ...\n");
            char c = getchar();
            system("@cls||clear");          //clear the screen
        }
    }
    
    //printing the scatter line in terminal with horizontal bar
    print_logo();

    //printing the scoreboard starts here
    printf("The final scoreboard is;\n\n");

    int winner = 0, temp_max = 0;            //winner player and maximum score in an iteration 

    printf("+------------+");
    for(int i=0; i<ROUNDS; i++) printf("-----------+");
    printf("-----------+");
    printf("\n|  Players   |");
    for(int i=0; i<ROUNDS; i++) printf("  Round %d  |", i+1);
    printf("  Total    |");

    for(int i=0; i<PLAYERS; i++) {
        int total = 0;
        printf("\n+------------+");
        for(int j=0; j<ROUNDS; j++) printf("-----------+");
        printf("-----------+");
        printf("\n|  Player%d   |", i+1);

        for(int j=0; j<ROUNDS; j++) {
            printf("  %7d  |", scoreboard[i][j]);  
            total += scoreboard[i][j];  
        }

        printf("  %7d  |", total);

        if(temp_max < total) {
            temp_max = total;
            winner = i;
        }
    }
    printf("\n+------------+");
    for(int i=0; i<ROUNDS; i++) printf("-----------+");
    printf("-----------+");

    //printing congratulations message
    printf("\n\n\nCongratulations !! The winner is PLAYER-%d!!!\n\n\n", winner+1);
    return 0;                   //keeping the compiler happy
}

//function `print_logo()` is used to print the name of the program in the terminal
void print_logo() {
    printf("\n88888888   88888888   88888888  88888888  88888888   88888888   88888888");
    printf("\n88         88    88   88    88     88        88      88         88    88");
    printf("\n88         88         88    88     88        88      88         88    88");
    printf("\n88888888   88         88888888     88        88      88888888   88888888");
    printf("\n      88   88         88    88     88        88      88         88  88  ");
    printf("\n      88   88    88   88    88     88        88      88         88   88 ");
    printf("\n88888888   88888888   88    88     88        88      88888888   88    88");
    printf("\n\n-------------------------------------------------------------------------------\n\n\n");
}

//function `print_answers()` is used to print the answers by the players
int print_answers(struct Question data) {
    int len[8] = {};
    len[0] = strlen(data.name);
    len[1] = strlen(data.city);
    len[2] = strlen(data.word);
    len[3] = strlen(data.drink);
    len[4] = strlen(data.event);
    len[5] = strlen(data.career);
    len[6] = strlen(data.actor);
    len[7] = strlen(data.food);

    //finding the answer having greatest length
    int max = len[0];
    for(int i=0; i<8; i++) {
        if(len[i] > max ) max=len[i];
    }

    //if every answers are wrong i.e. empty returns false
    if(max == 0) return 0;

    //printing the correct answers begins here
    for(int j=0; j<8; j++) {
        char prt[100] = {};
        
        //copying the content to new variable prt[]
        if(j == 0) strcpy(prt, data.name);
        if(j == 1) strcpy(prt, data.city);
        if(j == 2) strcpy(prt, data.word);
        if(j == 3) strcpy(prt, data.drink);
        if(j == 4) strcpy(prt, data.event);
        if(j == 5) strcpy(prt, data.career);
        if(j == 6) strcpy(prt, data.actor);
        if(j == 7) strcpy(prt, data.food);

        //if prt[] is empty don't print the line
        if(strcmp(prt, "") == 0) continue;
        printf("+-----------+");
        for(int i=0; i<max+4; i++) printf("-");

        if(j == 0) printf("+\n| Name      |");
        if(j == 1) printf("+\n| City      |");
        if(j == 2) printf("+\n| Word      |");
        if(j == 3) printf("+\n| Drink     |");
        if(j == 4) printf("+\n| Event     |");
        if(j == 5) printf("+\n| Career    |");
        if(j == 6) printf("+\n| Actor     |");
        if(j == 7) printf("+\n| Food      |");
        
        for(int i=0; i<(max-len[j]+4)/2; i++) printf(" ");
        printf("%s", prt);
        for(int i=0; i<((max+4)-(max-len[j]+4)/2-len[j]); i++) printf(" ");
        printf("|\n");
    }

    printf("+-----------+");
    for(int i=0; i<max+4; i++) printf("-");
    printf("+\n");    

    return 1;     
}