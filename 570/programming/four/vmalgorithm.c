/*
 *  Implementation of FIFO and LRU page replacement algorithm
 *  Please add appropriate level of comments in this file 
 */

#include "vmalgorithm.h"
#include <stdbool.h>

/* Generate an access pattern
 * Example: 3, 2, 2, 1, 1  indicates the page 3, 2, 2, 1, 1 in order
 */

//node declaration
struct node {
   int data;
	
   struct node *next;
   struct node *prev;
};

//global head node
struct node *head = NULL;
//global tail node
struct node *tail = NULL;
//global current node
struct node *current = NULL;

//checks if the list is empty
bool isEmpty() {
   return head == NULL;
}
void insertFirst(int data) {

   //create a link
   struct node *link = (struct node*) malloc(sizeof(struct node));
   link->data = data;
	
   if(isEmpty()) {
      //make it the last link
      tail = link;
   } else {
      //update first prev link
      head->prev = link;
   }

   //point it to old first link
   link->next = head;
	
   //point first to new first link
   head = link;
}

struct node* deleteLast() {
   //makes temp for cur tail
   struct node *tempLink = tail;
	
   //deletes head if there is only one link
   if(head->next == NULL) {
      head = NULL;
   } else {
      //deletes tail link
      tail->prev->next = NULL;
   }
   //makes prev link to tail new tail
   tail = tail->prev;
	
   //return the deleted link
   return tempLink;
}
//deletes a node if it contains that data
struct node* delete(int data) {

   //start from the first link
   current = head;
   struct node* previous = NULL;
	
   //if list is empty
   if(head == NULL) {
      return NULL;
   }

   //parses list
   while(current->data != data) {
      //if does not contain data	
      if(current->next == NULL) {
         return NULL;
      } else {
         //stores the link
         previous = current;
			
         //move to next link
         current = current->next;             
      }
   }

   //if found the it updates the list to delete the node
   if(current == head) {
      //deletes head if its the head
      head = head->next;
   } else {
      //deletes the link from the list otherwise
      current->prev->next = current->next;
   }    

   if(current == tail) {
      //updeates the prev data category
      tail = current->prev;
   } else {
      current->next->prev = current->prev;
   }
	
   return current;
}
void updateList(int data){
    //inserts at head and deletes the tail to update the list
    insertFirst(data);
    deleteLast();
}

void generateAccessPattern()
{
   int i;
   srand(time(0));
   accessPattern = (int *)malloc( sizeof(int) * AccessPatternLength);   
   printf("The randomized Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++)
   {
		     accessPattern[i] = rand() % ReferenceSZ;
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");
}

/*
 * Initialize the parameters of simulated memory
 */
void initializePageFrame()
{
   int i;
   memory.PageFrameList = (int *)malloc( sizeof(int)* FrameNR );    // dynamic allocated FrameNR frames to be used in memory
   memory.nextToReplaced =0;          // indicate the new frame to be replaced as 0
   for(i=0; i< FrameNR; i++)
   {
			memory.PageFrameList[i] = -1;  // initialization to -1 indicating all frames are unused 
   }

}

// Print the pages loaded in memory
void printPageFrame()
{
   int i;
   for(i=0; i< FrameNR; i++)
   {
			printf("%2d ",memory.PageFrameList[i]);       
   }
   printf("\n");
}


/*
 *  Print the access pattern in order
 */
void printAccessPattern()
{
   int i;
   printf("The Same Access Pattern: ");
   for(i=0; i< AccessPatternLength; i++)
   {
        printf("%d ", accessPattern[i]);       
   }
   printf("\n");

}


/*
 * Return: number of the page fault using FIFO page replacement algorithm
 */

//searches the aray for a given num, if it is in the array return the position, otherwize return -1
int searchArray(int *array,int num, int size){
    for(int i = 0; i < size; i++){
        if(array[i] == num){
            return i;
        }
    }
    return -1;
}
//prints pageframe list
void print(){
    for(int i = 0; i < FrameNR; i++){
        printf("%d ", memory.PageFrameList[i]);
    }
    printf("\n");
}
//updates the pageframe with the linkedlist data
void update(){
    current = head;
    for(int i = 0; i < FrameNR; i++){
        if(current == NULL){
            return;
        }
        memory.PageFrameList[i] = current->data;
        current = current->next;
    }
}
int FIFO()
{
    int place = FrameNR; //where to start after the first for loop 
    int replace = FrameNR;  //number which will be modded by FrameNR to find the first in
    int pnum = 0;  //page fault num
    memory.nextToReplaced = 0;
    int track = 0;  //tracks if the page frame list is full

    //attempts to fill the pageframe list
    for(int i = 0; i < FrameNR; i++){

        //if the list does not contain the accesspattern current number add it to it,print otherwise

        if(searchArray(memory.PageFrameList,accessPattern[i],FrameNR)==-1){
            memory.PageFrameList[track] = accessPattern[i];
            pnum++;
            track++;
        }
    print();
    }
    //while the pageframelist is not full
    while(track < FrameNR){

       //if the list does not contain the accesspattern current number add it to it,print otherwise

       if(searchArray(memory.PageFrameList,accessPattern[place],FrameNR)==-1){
            memory.PageFrameList[track] = accessPattern[place];
            pnum++;
            track++;
        }
        place++;
        print();
    }  
    while(place < AccessPatternLength){

        //if the list does not contain the accesspattern current number add it to it,print otherwise

        if(searchArray(memory.PageFrameList,accessPattern[place],FrameNR)==-1){
            memory.PageFrameList[replace%FrameNR] = accessPattern[place];
            replace++; //replace is incremented to keep track of the current first in
            pnum++;
        }
        place++;
        print();
    }
    return pnum;
}



/*
 * Return: number of the page fault using LRU page replacement algorithm
 */

int LRU()
{
    int place = FrameNR; //where to start after the first for loop 
    int pnum = 0;  //page fault num
    memory.nextToReplaced = 0;
    int track = 0;

    //attempts to fill the linked list
    for(int i = 0; i < FrameNR; i++){

        //if the list does not contain the accesspattern current number inserts to head,print otherwise
        if(searchArray(memory.PageFrameList,accessPattern[i],FrameNR)==-1){
            memory.PageFrameList[track] = accessPattern[i];
            pnum++;
            insertFirst(accessPattern[i]);
            track++;
        }else{
            //if it does contain it deletes its current position and places it at the head of hte list
            delete(accessPattern[i]);
            insertFirst(accessPattern[i]);
	}
        update(); //update pageframelist
        print(); //prints pageframelist
    }
    //runs until the list is full
    while(track < FrameNR){
       //if the list does not contain the accesspattern current number inserts to head,print otherwise
       if(searchArray(memory.PageFrameList,accessPattern[place],FrameNR)==-1){
            memory.PageFrameList[track] = accessPattern[place];
            pnum++;
            insertFirst(accessPattern[place]);
            track++;
        //if it does contain it deletes its current position and places it at the head of hte list
        }else{
	    delete(accessPattern[place]);
            insertFirst(accessPattern[place]);
        }
        update();
        print();
        place++; //updates current position at accesspattern
    }  
        while(place < AccessPatternLength){
        //if the list does not contain the accesspattern current number inserts to head,print otherwise
        if(searchArray(memory.PageFrameList,accessPattern[place],FrameNR)==-1){
            memory.PageFrameList[searchArray(memory.PageFrameList,tail->data,FrameNR)] = accessPattern[place];
            updateList(accessPattern[place]);
            pnum++; //increment fault
        //if it does contain it deletes its current position and places it at the head of hte list
        }else{
	    delete(accessPattern[place]);
            insertFirst(accessPattern[place]);
        }
        update();
        print();
        place++;
    }
    return pnum; //returns amount of faults

}

