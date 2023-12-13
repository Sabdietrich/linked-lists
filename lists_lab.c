#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXWORD 20

struct lnode {
    struct lnode *next;
    struct lnode *counter;
    struct lnode *pLast;
    struct lnode *prev;
    struct lnode *head;
    char *word;
    int line;
    int count;
    int freq;
};

struct lnode *start = NULL;


struct lnode *createWordCounter(char *str)
{
    struct lnode *pCounter = NULL;
    pCounter = (struct lnode*)malloc(sizeof(struct lnode));
    pCounter->word = (char*)malloc(strlen(str)+1);
    strcpy(pCounter->word, str);
    pCounter->freq = 1;
    pCounter->next = NULL;
    return pCounter;
}


void addWord(char *str)
{
    struct lnode *pCounter = NULL;
    struct lnode *pLast = NULL;

    if(start == NULL)
    {
        start = createWordCounter(str);
        return;
    }

    pCounter = start;
    int temp = pCounter->freq;
    while(pCounter != NULL)
    {
        if(strcmp(str, pCounter->word) == 0)
        {
            pCounter->freq++;
            return;
        }
        pLast = pCounter;
        pCounter = pCounter->next;
    }

    pLast->next = createWordCounter(str);
}


int getNextWord(char *buf, int bufsize, FILE *input) {
    char *p = buf;
    char ch;
    do {
        ch = getc(input);
        if (ch == '\377')
            return 0;
    } while (!((ch >= 'A' && ch <= 'Z')||( ch >= 'a' && ch <= 'z')));
    do {
        if (p - buf < bufsize - 1){
            if( ch >= 97 && ch <= 122)
                *p++ = ch;
            else{ch += 32;
                *p++ = ch;}
        }//End of if
        ch = getc(input);
    } while (((ch >= 'A' && ch <= 'Z')||( ch >= 'a' && ch <= 'z')));
    *p = '\0';
    return 1;
}


void print_List(struct lnode *pWord, FILE *out)
{
    struct lnode *current_node = pWord;
    while ( current_node != NULL)
    {
        fprintf(out, "%s %d\n", current_node->word, current_node->freq);
        current_node = current_node->next;
    }
}


int main(){

    FILE *input;
    FILE *output;

    input = fopen("input_text.txt", "r");
    output = fopen("output_text.txt", "w");

    struct lnode *counter = NULL;
    int size = 1000;
    char buf[MAXWORD];

    while(getNextWord(buf, size, input) != 0 ){
        addWord(buf);
    }

    counter = start;

    fprintf(output, "\nOccurrences of all distinct words in file: \n");

    print_List(counter, output);

    counter = start;

    while(counter != NULL)
    {
        free(counter->word);
        start = counter;
        counter = counter->next;
        free(start);
    }

    fclose(input);
    fclose(output);

    return 0;
}
