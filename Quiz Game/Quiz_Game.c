#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct quiz
{
    // question,options,answer char
    char question[85];
    char answer[85];
    char options[46];
} quiz;

// maximum Number of questions you can add(buckets)
#define N 10000
quiz *table[N];

char answer; // longest word is of length 45 + '\n'char name;

int que_count = 0;
int ans_count = 0;
long long int h = 0;

bool check(const char *answer, int a);
bool unload();
void show_record();
void reset_score();
void edit_score(float score, char plnm[20]);

// load all the questions to ask
bool load()
{
    FILE *file = fopen("questions.txt", "r"); // open the file containing all the questions
    if (file == NULL)                         // if the file is empty end the program
    {
        return 1;
    }
    int sw = 0;
    char word[85];
    // Read the file till the End Of File(EOF)
    int h = 0;
    quiz *cursor = malloc(sizeof(quiz)); // allocate space for the quiz cursor
    while (fgets(word, 82, file) != 0)
    {
        if (cursor == NULL)
        {
            return false;
        }
        switch (sw)
        {
        case 0:
            // Add question to the struct
            strcpy(cursor->question, word);
            sw = 2;
            break;
        case 2:
            // Add answer and option
            strcpy(cursor->answer, word);
            sw = 90;
            break;
        case 90:
            // Add options to the struct
            strcpy(cursor->options, word); // copy word to cursor->options
            table[h] = cursor;             // save all the values assigned to cursor to table at number 'h'
            h++;
            quiz *cursor = malloc(sizeof(quiz)); // allocate space for the quiz cursor
        default:
            sw = 0;
            break;
        }
    }
    fclose(file);
    return true;
}

int main()
{
    char ch;
    system("clear");
    bool loaded = load();
    if (!loaded)
    {
        printf("Could not load\n");
        return 1;
    }
    printf("\t\t\tC PROGRAM QUIZ GAME\n");
    printf("\n\t\t________________________________________");

    printf("\n\t\t\t    WELCOME ");
    printf("\n\t\t\t      to ");
    printf("\n\t\t\t   THE GAME ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t   BECOME A MILLIONAIRE!!!!!!!!!!!    ");
    printf("\n\t\t________________________________________");
    printf("\n\t\t________________________________________");
    printf("\n\t\t > Press S to start the game");
    printf("\n\t\t > Press V to view the highest score  ");
    printf("\n\t\t > Press R to reset score");
    printf("\n\t\t > press H for help            ");
    printf("\n\t\t > press Q to quit             ");
    printf("\n\t\t________________________________________\n\n");

    scanf("%s", &ch);

    if (ch == 'S' || ch == 's')
    {
        char name;
        system("clear");               // Clears the terminal screen
        printf("What is your name\n"); // Name of the user
        scanf("%s", &name);
        int a = (rand() % (19)); // To Get a random number between 0 - 19
        for (int i = a; i <= a + 10; i++)
        {
            int q = 1;               // Question Number
            system("clear");         // clear the terminal screen
            quiz *cursor = table[i]; // assign the question at number a to the cursor
            printf("Que %d", q);
            // prints question and options
            printf("%s ", cursor->question);
            printf("%s ", cursor->options);
            printf("What is your Answer\n");
            scanf("%s", &answer); // take answer from the user

            bool corn = check(answer, a);          // check if the user answer is correct or not
            printf("your score is %i", ans_count); // print the count answer

            for (long long int k = 0; k < 1784000000; k++) // wait for 5.010222
            {
            }
        }
    }
    else if (ch == 'v' || ch == 'V')
    {
        show_record();
    }
    else if (ch == 'r' || ch == 'R')
    {
        reset_score();
    }
    else if (ch == 'h' || ch == 'H')
    {
        system("clear");
        printf("\n\n                              HELP");
        printf("\n -------------------------------------------------------------------------");
        printf("\n ......................... C program Quiz Game............................");
        printf("\n >> There are two rounds in the game, WARMUP ROUND & CHALLANGE ROUND");
        printf("\n >> In warmup round you will be asked a total of 3 questions to test your general");
        printf("\n    knowledge. You will be eligible to play the game if you can give atleast 2");
        printf("\n    right answers otherwise you can't play the Game...........");
        printf("\n >> Your game starts with the CHALLANGE ROUND. In this round you will be asked");
        printf("\n    total 10 questions each right answer will be awarded $100,000.");
        printf("\n    By this way you can win upto ONE MILLION cash prize in USD...............");
        printf("\n >> You will be given 4 options and you have to press A, B ,C or D for the");
        printf("\n    right option");
        printf("\n >> You will be asked questions continuously if you keep giving the right answers.");
        printf("\n >> No negative marking for wrong answers");

        printf("\n\n\t*********************BEST OF LUCK*********************************");
        printf("\n\n\t*****C PROGRAM QUIZ GAME is developed by code WITH C TEAM*****\n\n\n\n");
        printf("\n\n\tPress Any Key To Go Back\n\n");
        char x;
        scanf("%c", &x);
        if (x)
        {
            main();
        }
    }
    else if (ch == 'q' || ch == 'Q')
    {
        system("clear");
        printf("The Game Has ended\n");
        return 0;
    }
}

// Check if the answer is correct
bool check(const char *answer, int x)
{
    quiz *cursor = table[x]; // assign the value stored in int x to cursor
    // compare the answer
    if (strcasecmp(answer, cursor->answer) == 0) // check whether the answer matches with stored answer
    {
        ans_count++; // if correct increase the count answer count
        return true;
    }
    // if the answer is not correct print incorrect answer
    else
    {
        printf("INCORRECT ANSWER");
        printf("%s is the correct answer", cursor->answer);
    }
    return false;
}

bool unload()
{
    // iterates for every value in the table till N-1
    for (long int i = 0; i < N; i++)
    {
        quiz *cursor = table[i]; // assigns value of the quiz table's i location
        while (cursor != NULL)
        {
            quiz *temp = cursor; // assigns value of the quiz cursor
            free(temp);          // free temp
        }
        if (cursor == NULL || i == N - 1) // check if end of the list is NULL
        {
            return true;
        }
    }
    return false; // if the program failed return false
}

void show_record()
{
    system("clear");
    char name[20];
    float score;
    FILE *file = fopen("score.txt", "r");
    fscanf(file, "%s %f", &name, &score);
    printf("\n\n\t\t*************************************************************");
    printf("\n\n\t\t %s has secured the Highest Score %0.2f", name, score);
    printf("\n\n\t\t*************************************************************\n");
    fclose(file);
}

void reset_score()
{
    system("cls");
    float sc;
    char nm[20];
    FILE *f;
    f = fopen("score.txt", "r+");
    fscanf(f, "%s%f", &nm, &sc);
    sc = 0;
    fprintf(f, "%s,%.2f", nm, sc);
    fclose(f);
}
void edit_score(float score, char plnm[20])
{
    system("clear");
    float sc;
    char nm[20];
    FILE *f;
    f = fopen("score.txt", "r");
    fscanf(f, "%s%f", &nm, &sc);
    if (score >= sc)
    {
        sc = score;
        fclose(f);
        f = fopen("score.txt", "w");
        fprintf(f, "%s\n%.2f", plnm, sc);
        fclose(f);
    }
}
