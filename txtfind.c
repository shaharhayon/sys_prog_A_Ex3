#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE 256
#define WORD 30
#define MAX_LINES 250

typedef struct _TEXT
{
    char text[MAX_LINES][LINE][WORD];
} TEXT;

int getLine(char s[][WORD], int *fileEnd); // Reads a line from the user
int getword(char w[], int *newLine, int *fileEnd); // Reads a word from the user
int substring(char line[LINE][WORD], char *str); // Checks if a string (str) is a substring of another string (line)
int similar(char *s, char *t, int n); // Checks if string (t) can be achieved by dropping #(n) letters of string (s) 
void print_all_lines(TEXT text); // Prints the entire text, used mainly for debugging.
void print_similar_words(TEXT text, char *string); // Prints all the words in the text that are similar to (string), as defined in Ex3 
void print_line(char text[LINE][WORD]); // Prints a specific line from the text, (used for printing only lines that include a specific word)

int main()
{
    int fileEnd = 0, line = 0;
    // lines[0][][] -> line 0
    // lines[0][0][] -> word 0 in line 0
    TEXT text;
    char string[WORD];
    char option;

    printf("Enter string ");
    scanf("%s", string);

    printf("string enterd is: %s\n", string);
    printf("Enter option ");
    scanf(" %c", &option);
    //option = getchar();
    printf("\noption enterd is: %c\n", option);

    getchar();
    getchar();
    getchar();
    getchar();

    while (!fileEnd)
    {
        getLine(text.text[line++], &fileEnd);
    }

    if (option == 'a')
    {
        int i = 0;
        while (text.text[i][0][0] != '\0')
        {
            if (substring(&text.text[i], string))
                print_line(&text.text[i]);
            i++;
        }
    }

    else if (option == 'b')
    {
        print_similar_words(text, string);
    }
}

int getLine(char s[][WORD], int *fileEnd)
{
    int index = 0;
    int length = 0;

    int newLine = 0;
    while (!newLine && !*fileEnd)
    {
        length += getword(s[index++], &newLine, fileEnd);
    }
}

int getword(char w[], int *newLine, int *fileEnd)
{
    char c = getchar();
    while ((c == '\n') && (c == '\t') && (c == ' ') && (c == '\r') && (c != EOF))
    {
        c = getchar();
    }
    int index = 0;
    while ((c != '\n') && (c != '\t') && (c != ' ') && (c != '\r') && (c != EOF))
    {
        w[index++] = c;
        c = getchar();
    }

    if (c == '\n')
    {
        *newLine = 1;
    }
    else if (c == EOF)
    {
        *fileEnd = 1;
    }

    w[index] = '\0';
    return index;
}

int substring(char line[LINE][WORD], char *str)
{
    for (int i = 0; i < LINE; i++)
    {
        if (line[i][0] == '\n')
            break;
        if (strstr(&line[i], str) != NULL)
            return 1;
    }
    return 0;
}

int similar(char *s, char *t, int n)
{
    int lenS = strlen(s), lenT = strlen(t);
    int errors = 0;
    if (strcmp(s, t) == 0)
        return 1;
    else if (!((lenS - lenT == n) || (lenT - lenS == n)))
        return 0;

    for (int i = 0; i < lenS; i++)
    {
        if (s[i + errors] == t[i])
            continue;
        else
        {
            errors++;
            i--;
        }
        if (errors > n)
            return 0;
    }
    if (errors <= n)
        return 1;
    else
        return 0;
}

void print_all_lines(TEXT text)
{

    for (int i = 0; i < MAX_LINES; i++)
    {
        if (text.text[i][0][0] == '\0')
            break;
        for (int j = 0; j < LINE; j++)
        {
            if (text.text[i][j][0] == '\0')
                break;
            for (int k = 0; k < WORD; k++)
            {
                if (text.text[i][j][k] == '\0')
                    break;
                printf("%c", text.text[i][j][k]);
            }
            printf(" ");
        }
        printf("\n");
    }
}

void print_line(char text[LINE][WORD])
{
    for (int j = 0; j < LINE; j++)
    {
        if (text[j][0] == '\0')
            break;
        for (int k = 0; k < WORD; k++)
        {
            if (text[j][k] == '\0')
                break;
            printf("%c", text[j][k]);
        }
        printf(" ");
    }
    printf("\n");
}

void print_similar_words(TEXT text, char *string)
{
    for (int i = 0; i < MAX_LINES; i++)
    {
        if (text.text[i][0][0] == 0)
            break;
        for (int j = 0; j < LINE; j++)
        {
            if (text.text[i][j][0] == '\0')
                break;
            else if (similar(&text.text[i][j], string, 1))
            {
                printf("%s\n", &text.text[i][j]);
            }
        }
    }
}
