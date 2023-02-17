#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    // question,options,answer char
    char question[85];
    char answer[20];
    char options[85];
    struct node *next;
} node;

// maximum Number of questions you can add(buckets)
#define N 10000
node *table[N];

int ans_count = 0;
long long int h = 0;

void check(int a);
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
    while (fgets(word, 82, file) != 0)
    {
        switch (sw)
        {
        case 0:
            node *cursor = malloc(sizeof(node)); // allocate space for the node cursor
            if (cursor == NULL)
            {
                return false;
            }
            // Add question to the struct
            strcpy(cursor->question, word);
            sw = 2;
            break;
        case 2:
            // Add options to the struct
            strcpy(cursor->options, word); // copy word to cursor->options
            sw = 90;
            break;
        case 90:
            // Add answer and option
            strcpy(cursor->answer, word);
            table[h] = cursor; // save all the values assigned to cursor to table at number 'h'
            if (h == 0)
            {
                cursor->next = NULL; // for the first word next location is NULL
            }
            else
            {
                cursor->next = table[h];
            }
            h++;
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
        unload();
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
        char name[20];
        system("clear");               // Clears the terminal screen
        printf("What is your name\n"); // Name of the user
        scanf("%s", &name);
        int q = 1;               // Question Number
        int a = (rand() % (18)); // To Get a random number between 0 - 19
        for (int i = a; i < a + 10; i++)
        {
            system("clear");         // clear the terminal screen
            node *cursor = table[i]; // assign the question at number a to the cursor
            printf("Que %d ", q);
            // prints question and options
            printf("%s\n", cursor->question);
            printf("%s\n", cursor->options);
            printf("What is your Answer\n");
            check(i);                                      // check if the user answer is correct or not
            printf("your score is %d\n", ans_count);       // print the count answer
            for (long long int k = 0; k < 1784000000; k++) // wait for 5.010222 sec
            {
            }
            q++;
        }
        float score = (float)ans_count * 1000000;
        if (score > 0.00 && score < 1000000)
        {
            printf("\n\n\t\t**************** CONGRATULATION *****************");
            printf("\n\t You won $%.2f", score);
        }

        else if (score == 1000000.00)
        {
            printf("\n\n\n \t\t**************** CONGRATULATION ****************");
            printf("\n\t\t\t\t YOU ARE A MILLIONAIRE!!!!!!!!!");
            printf("\n\t\t You won $%.2f", score);
            printf("\t\t Thank You!!");
        }
        else
        {
            printf("\n\n\t******** SORRY YOU DIDN'T WIN ANY CASH ********");
            printf("\n\t\t Thanks for your participation");
            printf("\n\t\t TRY AGAIN");
        }
        printf("\n\n Press Y if you want to play next game ");
        printf("Press Any Other key to Quit");
        char ch;
        scanf("%s", &ch);
        if (ch == 'y' || ch == 'Y')
        {
            main();
        }
        else
        {
            edit_score(score, name);
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
        printf("\n\n\t*****C PROGRAM node GAME is developed by code WITH C TEAM*****\n\n\n\n");
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
void check(int i)
{
    char answer[20];
    scanf("%s", &answer);    // take answer from the user
    node *cursor = table[i]; // assign the value stored in int x to cursor
    int l = strlen(cursor->answer);
    cursor->answer[l - 1] = '\000';
    // compare the answer
    if (strcasecmp(answer, cursor->answer) == 0) // check whether the answer matches with stored answer
    {
        ans_count++; // if correct increase the count answer count
    }
    // if the answer is not correct print incorrect answer
    else
    {
        printf("\n\nINCORRECT ANSWER\n");
        printf("%s is the correct answer ", cursor->answer);
    }
}

bool unload()
{
    // iterates for every value in the table till N-1
    for (long int i = 0; i < N; i++)
    {
        node *cursor = table[i]; // assigns value of the node table's i location
        while (cursor != NULL)
        {
            node *temp = cursor; // assigns value of the node cursor
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
    char name;
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
