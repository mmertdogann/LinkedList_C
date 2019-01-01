#include <stdio.h>
#include <stdlib.h>

//int nodes
struct digit {
    int num;
    struct digit *next; //Next node reference
};

//Function prototypes
struct digit * createDigit(int);
struct digit * append(struct digit * end, struct digit * newDigptr);
void printNumber(struct digit *);
void freeNumber(struct digit *);
struct digit * readNumber(void);
struct digit * searchNumber(struct digit * start, int number);
struct digit * insertAtFront(struct digit * start, struct digit * newptr);
struct digit * reverseNumber(struct digit * start);
struct digit * sortedCopy(struct digit * start);
struct digit * insertIntoSorted(struct digit *start, struct digit *newDig);

int main(void) {

    struct digit *start, *backwards, *sorted;
    printf("Please enter a number: ");
    start = readNumber(); //Read and insert int nodes
    printf("You entered: ");
    printNumber(start); //Print the original list
    printf("Backwards: ");
    backwards = reverseNumber(start); //Reverese list
    printNumber(backwards);
    printf("Sorted by digit:");
    sorted = sortedCopy(start); //The sorted original list
    printNumber(sorted);
    //Free the allocated memory
    freeNumber(start);
    freeNumber(backwards);
    freeNumber(sorted);
    return 0;
}

struct digit *createDigit(int dig) {
    struct digit *ptr;
    ptr = (struct digit *) malloc(sizeof(struct digit)); //Allocate memory whose size is sizeof struct digit
    ptr->num = dig; //dereference the node's integer value
    ptr->next = NULL; // next reference null
    return ptr;
}

struct digit * append(struct digit * end, struct digit * newDigptr) {
    end->next = newDigptr; //link nodes
    return(end->next);
}

void printNumber(struct digit *start) {
    struct digit * ptr = start;
    //Traverse whole list and print each int node while the searching node equals null
    while (ptr!=NULL) {
        printf("%d", ptr->num);
        ptr = ptr->next;
    }
    printf("\n");
}

void freeNumber(struct digit *start) {
    struct digit * ptr = start;
    struct digit * tmp;
    //Traverse each node and free the memory
    while (ptr!=NULL) {
        tmp = ptr->next;
        free(ptr);
        ptr = tmp;
    }
}

struct digit * readNumber(void) {
    char c;
    int d;
    struct digit *start, *end, *newptr;
    start = NULL;
    scanf("%c", &c); //Read as char
    while (c != '\n') {
        d = c-48; //Convert it to int by using ASCII
        newptr = createDigit(d); //Create a node with using the converted int
        //If there is no start node assign the new node as start and also end
        if (start == NULL) {
            start = newptr;
            end = start;
        } else { //else append end of the list
            end = append(end, newptr);
        }
        scanf("%c", &c); //Keep reading chars
    }
    return(start);
}

struct digit * searchNumber(struct digit * start, int number) {
    struct digit * ptr = start;
    //Search whole list while reach and of the list or reach the number
    while ((ptr!=NULL) && (ptr->num!=number)) {
        ptr = ptr->next;
    }
    return(ptr);
}

struct digit * insertAtFront(struct digit * start, struct digit * newptr) {
    newptr->next = start; //Link new digit to beginning
    return(newptr);
}

struct digit * reverseNumber(struct digit * start) {
    struct digit *ptr = start;
    struct digit *bstart = start;
    struct digit *newdigit;
    //If there is no start node assign the new node as backwards start
    if (start!=NULL) {
        bstart = createDigit(start->num);
        ptr = ptr->next;
    }
    //else insert at front the new node beginning of the list
    while (ptr != NULL) {
        newdigit = createDigit(ptr->num);
        bstart = insertAtFront(bstart, newdigit);
        ptr = ptr->next;
    }
    return(bstart);
}

struct digit * insertIntoSorted(struct digit *start, struct digit *newDig) {
    struct digit *ptr = start;
    struct digit *prev = NULL;
    //searching whole listwhile reach end of the list or the incoming digit smaller than existing digits
    while ((ptr!=NULL) && (ptr->num < newDig->num)) {
        prev = ptr;
        ptr = ptr->next;
    }
    if (prev == NULL) { //if the incoming digit smaller than existing digits insert it at the beginning of the list
        start = insertAtFront(start, newDig);
    } else {//if the incoming digit bigger than any digit in the list, link it to the bigger one
        prev->next = newDig;
        newDig->next = ptr;
    }
    return(start);
}

struct digit * sortedCopy(struct digit * start) {

    struct digit *ptr = start;
    struct digit *sortedStart = NULL;
    struct digit *newDigit;

    //If there is no node in the list create a sorted start node
    if (start!=NULL) {
        sortedStart = createDigit(start->num);
        ptr = ptr->next;
    }
    //search whole list while the searching node equals null (reach end of the list)
    while (ptr!=NULL) {
        newDigit = createDigit(ptr->num); //create new digit and assign int
        sortedStart = insertIntoSorted(sortedStart, newDigit); //call the function and make insertion operation
        ptr = ptr->next; //keep searching
    }
    return(sortedStart);
}
