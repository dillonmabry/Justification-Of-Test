/* Dillon Mabry 800854402 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    char* string;
    struct node *next;
}Node_t;

void readFile(FILE *filePtr, Node_t *currentPtr);
Node_t *insert(Node_t *currentPtr, char *string);
int calculateSpaces(Node_t *head);
void printUpdatedList(Node_t *head, int justify, int spaces, int numWords, int len);
void freeMemory(Node_t *head);

int main()
{

    char fileName[100];
    printf("Please enter the file to open (no spaces please): \n");
    scanf("%s", fileName);

    /* generate new file pointer */
    FILE *filePtr = NULL;
    if((filePtr = fopen(fileName, "r")) == NULL){
        printf("Error, could not open file\n");
        exit(1);
    }
 
    Node_t *head = NULL;
    readFile(filePtr, head);

    return 0;
}

/* Function to read the file and apply justification by using
the calculateSpaces function as well as freeMemory at the end */
void readFile(FILE *filePtr, Node_t *head){

    /* allocate memory for a new string pointer */
    char *word = malloc(100*sizeof(char));
    /* fgets to get each line with max buffer size of 100 chars */
    while(fgets(word, 100, filePtr)){
        /* if the first word is a new line */
        if(word[0] == '\n'){
            head = insert(head, "EMPTY");
        }
        /* tokenize each word using spaces and new
        lines as delimeters */
        char* token = strtok(word, " \n");
        while(token != NULL){
            /* insert each token into linked list */
            head = insert(head, token);
            token = strtok(NULL, " \n");
        }
    }
    /* call function for justification */
    calculateSpaces(head);
    freeMemory(head);

}

/* Function to insert a new node into the LinkedList */
Node_t *insert(Node_t *head, char *string){
    /* allocate memory for new node */
    Node_t* temp = malloc(sizeof(Node_t));
    /* if new pointer cannot be created */
    if(temp == NULL) {
        printf("Error could not allocate memory....");
        return NULL;
    }
    /* allocate memory for new data to be added */
    temp->string = malloc(100*sizeof(char));
    /* if head is empty create new strcpy */
    if(head == NULL){
        strcpy(temp->string, string);
        temp->next = NULL;
        head = temp;
    } else {
        /* save the head */
        Node_t *currPtr = head;
        /* move to the last node */
        while(currPtr->next != NULL){
            currPtr = currPtr->next;
        }
        /* copy the string */
        strcpy(temp->string, string);
        temp->next = NULL;
        currPtr->next = temp;
    }
    /* return starting node */
    return head;
}

/* Function to calculate the spaces for justification */
int calculateSpaces(Node_t *head){

    int justifyAmount;
    printf("Enter a jusitfy amount: (between 40 and 100) ");
    scanf("%d", &justifyAmount);
    printf("\n");

    int totalStrLen = 0; /* total string length of sentence */
    int tempVal = 0; /* temp var */
    Node_t *currPtr = head; /* head of list */
    Node_t *tempList = NULL; /* temp pointer */
    int spaces = 1; /* number of spaces in sentence read */
    int words = 0; /* total words in sentence */
    int tempJust = 0; /* temp justify amount */

    while(currPtr != NULL) {
        
        /* set to total length of string */
        tempVal = totalStrLen;
        
        /* if the justify amount - strlen is less than spaces needed 
        or the tempval is greater than justify amount */
        if((tempVal += strlen(currPtr->string)) >= justifyAmount || 
        (justifyAmount - (tempVal += strlen(currPtr->string))) < spaces) {
        
            /* insert the current word */
            tempList = insert(tempList, currPtr->string);
            /* print the new list justified */
            printUpdatedList(tempList, justifyAmount, spaces, words, totalStrLen);
            /* free memory */
            freeMemory(tempList);
            tempList = NULL;
            /* reset variables */
            totalStrLen = 0;
            tempVal = 0;
            spaces = 1;
            words = 0;

        /* else continue to add to strlen and count words*/
        } else {
            tempList = insert(tempList, currPtr->string);
            totalStrLen += strlen(currPtr->string);
            words++;
            spaces = words - 1;
            currPtr = currPtr->next;
        }
    }
    
    /* print final updated list */
    printUpdatedList(tempList, justifyAmount, spaces, words, totalStrLen);

}

/* Function to print the new justified list
per line in use with the calculateSpaces function */
void printUpdatedList(Node_t* head, int justify, int spaces, int numWords, int len) {

    int i = 0;
    int j = 0;

    /* initialize a pointer and the amount needed to justify
    per space */
    int justifyPerSpace;
    Node_t* currPtr = head;
    int leftOver = 0;
    int remainingJustify = 0;
    /* remaining spaces is justify - length */
    remainingJustify = justify - len;
    leftOver = remainingJustify % spaces;
    
    /* when the spaces is not equal to 0 */
    if(spaces != 0) {
        
        /* if the remaining amount of spaces / per each 
        space is less than 1 */
        if((float)(remainingJustify/spaces) < 1)
            justifyPerSpace = 1;
        /* else distribute spaces evenly */
        else
            justifyPerSpace = remainingJustify / spaces;

    } else { /* do nothing (this is the empty line) */ }

    /* print out the list */
    while(currPtr != NULL && i < numWords) {

        if(strcmp("EMPTY", currPtr->string) == 0){
            printf("\n\n");
        } else {
            printf("%s", currPtr->string);
            for(j = 0; j < justifyPerSpace; j++){
                printf(" ");
            }
            if(leftOver > 0){
                printf(" ");
                leftOver--;
            }
        }
        currPtr = currPtr->next;
        i++;
    }
    printf("\n");

}

/* Function to free memory from original head */
void freeMemory(Node_t *head) {
    while(head->next != NULL) {
        Node_t *temp = head;
        head = head->next;
        free(temp);
        temp = NULL;
    }
    free(head);
    head = NULL;
}