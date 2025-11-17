#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MAX 256

int score = 0;

void askQuestion(char *question, char options[][MAX], char correct)
{
    char answer;
    time_t start = time(NULL);

    printf("\n%s\n", question);
    printf("A. %s", options[0]);
    printf("B. %s", options[1]);
    printf("C. %s", options[2]);
    printf("D. %s", options[3]);

    printf("\nYou have 10 seconds...\nYour Answer: ");

    // Timer + key detection
    while (!kbhit())
    {
        if (time(NULL) - start >= 10)
        {
            printf("\n⏳ Time's up! No points awarded.\n");
            return;
        }
    }

    answer = getchar();

    // 🔥 FIX: clear input buffer so next question doesn't auto-skip
    while (getchar() != '\n')
        ;

    if (answer == correct || answer == correct + 32)
    {
        printf("Correct!\n");
        score++;
    }
    else
    {
        printf("Wrong! Correct answer was %c\n", correct);
    }
}

int main()
{
    FILE *file = fopen("questions.txt", "r");
    if (!file)
    {
        printf("Error: Could not open questions.txt\n");
        return 1;
    }

    char question[MAX];
    char options[4][MAX];
    char correct;

    printf("=========== QUIZ GAME ===========\n");

    while (fgets(question, MAX, file))
    {
        if (strlen(question) <= 1)
            continue;

        fgets(options[0], MAX, file);
        fgets(options[1], MAX, file);
        fgets(options[2], MAX, file);
        fgets(options[3], MAX, file);
        fscanf(file, " %c\n", &correct);

        askQuestion(question, options, correct);
    }

    fclose(file);

    printf("\n=========== RESULT ===========\n");
    printf("Final Score: %d\n", score);

    return 0;
}