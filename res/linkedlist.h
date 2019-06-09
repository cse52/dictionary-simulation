/* 
Implementation of dictionary using Linked List 
	By 		: VIKAS KUMAR
	Roll 	: 43
	Enroll	: 2017BCSE052
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LEN 300
#define MAX_MEANING_LEN 10000

// dictionary database address
const char db_addr[100] = "./res/dict_db.txt";

// linked list node structure
typedef struct node {
	char *word;
	char *meaning;
	struct node *next;
} Node;


// Function Prototypes
Node* getNewNode(char* word, char *meaning);
void InitializeDictionary(Node **head);
void SaveDictionary(Node *head);
void InsertLexi(Node **head, char *word, char *meaning, int info_flag);
void UpdateMeaning(Node **head, char *word, char *meaning);
void Search(Node *head, char *data);
void FindExact(Node *head, char *data);
void Delete(Node **head, char *data);
void Print(Node *head);
int IsEmpty(Node *head);
int TotalWords(Node *head);


// Function Definitions

/* 
	This function takes word and meaning strings
	and creates a newNode and returns the address of that node
*/
Node* getNewNode(char *word, char *meaning) {
	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->word = (char *) malloc(sizeof(char)*strlen(word));
	newNode->meaning = (char *) malloc(sizeof(char)*strlen(meaning));
	strcpy(newNode->word,word);
	strcpy(newNode->meaning,meaning);
	newNode->next = NULL;

	return newNode;
}

/* 
	This function reads data from dictionary database(a text file on db_addr)
	and creates & stores the data to a linked list denoted by head
*/
void InitializeDictionary(Node **head){
	int total_words;
	char ch;

	char *word = (char *) malloc(MAX_WORD_LEN * sizeof(char));
	char *meaning = (char *) malloc(MAX_MEANING_LEN * sizeof(char));

	FILE *fp = fopen(db_addr, "r");
	if(fp){
		fscanf(fp, "words:%d\n", &total_words);
		while(total_words--){
			word = (char *) realloc(word, MAX_WORD_LEN * sizeof(char));
			meaning = (char *) realloc(meaning, MAX_MEANING_LEN * sizeof(char));

			fscanf(fp, "%[^:]s", word);
			word = realloc(word, (sizeof(char)*strlen(word)+1));
			ch = getc(fp);		// to remove the : character between word and meaning
			fscanf(fp, "%[^\n]s", meaning);
			meaning = realloc(meaning, (sizeof(char)*strlen(meaning)+1));
			ch = getc(fp);		// to remove the \n at the end of each line

			InsertLexi(head,word,meaning,0);
		}

		fclose(fp);
	} else {
		printf("\t<%s>\n", "Fatal: Dictionary Database Not Found! Exiting..");
		exit(1);
	}
}

/* 
	This function reads data from linked list denoted by head
	and stores that data to the dictionary database(text file on db_addr)
*/
void SaveDictionary(Node *head){
	FILE *fp = fopen(db_addr, "w");
	Node *temp = head;
	fprintf(fp, "%s:%d\n", "words",TotalWords(head));
	while(temp->next != NULL) {
		fprintf(fp, "%s:%s\n", temp->word, temp->meaning);
		temp = temp->next;
	}
	fprintf(fp, "%s:%s", temp->word, temp->meaning);

	fclose(fp);
}

/* 
	This function takes word and meaning stings as arguments
	and creates a new node using them and inserts that node 
	LEXICOGRAPHICALLY into the linked list denoted by head
*/
void InsertLexi(Node **head, char *word, char *meaning, int info_flag) {
	// get new node
	Node *newNode = getNewNode(word,meaning);

	if(IsEmpty(*head)) {
		*head = newNode;
		if(info_flag)
			printf("\t<%s%s%s>\n", "Success: ", word, " Added !");
		return;
	}

	Node *temp = *head;
	Node *pre;
	// traverse list
	while(temp->next != NULL)
	{
		if(strcmp(word,temp->word)<1 || strcmp(word,temp->word)==0){
			break;
		}
		pre = temp;
		temp = temp->next;
	}
	if(strcmp(word,temp->word) == 0){
		if(info_flag)
			printf("\t<%s%s%s>\n", "Failure: ", word, " Already Exists !");
		return;
	} else if(strcmp(word,temp->word) < 1) {
		if(temp == *head){
			newNode->next = temp;
			*head = newNode;
		} else {
			newNode->next = temp;
			pre->next = newNode;	
		}
	} else if(temp->next == NULL) {
		temp->next = newNode;
	} else {
		printf("\tUnknown error\n");
		return;
	}
	if(info_flag)
		printf("\t<%s%s%s>\n", "Success: ", word, " Added !");
}


/*
	This function function finds and updates the entered
	word's meaning
*/
void UpdateMeaning(Node **head, char *word, char *meaning) {
	if(IsEmpty(*head)){
		printf("\t<%s>\n", " Error: Dictionary Empty !");
		return;
	}

	Node *temp = *head;
	while(temp != NULL)
	{
		if(strcmp(word,temp->word) == 0)
		{
			temp->meaning = realloc(temp->meaning, sizeof(strlen(meaning)));
			strcpy(temp->meaning,meaning);
			printf("\t<%s%s%s>\n", "Success: ", word, " Updated !");
			return;
		}
		temp = temp->next;
	}

	printf("\t<%s%s%s>\n", "Failure: ", word, " Not Found !");

}

/*
	This function finds all the words which 
	begin with the entered word and
	prints their meanings and number of words found
*/
void Search(Node *head, char *word) {
	if(IsEmpty(head)){
		printf("\t<%s>\n", " Error: Dictionary Empty !");
		return;
	}
	Node *temp = head;
	int result_count = 0;
	printf("%s\n", "-----------------Search Results----------------");
	while(temp != NULL)
	{
		if(strncmp(word,temp->word,strlen(word)) == 0)
		{
			printf("\t%-15s : %s\n", temp->word, temp->meaning);
			result_count++;
		}
		temp = temp->next;
	}
	printf("%s%d%s\n", "----------------Found ",result_count," Results---------------");
}


/*
	This function finds exact words and its meaning 
*/
void FindExact(Node *head, char *word) {
	if(IsEmpty(head)){
		printf("\t<%s>\n", " Error: Dictionary Empty !");
		return;
	}
	Node *temp = head;
	while(temp != NULL)
	{
		if(strcmp(word,temp->word) == 0)
		{
			printf("\t%-15s : %s\n", temp->word, temp->meaning);
			return;
		}
		temp = temp->next;
	}

	printf("\t<%s%s%s>\n", "Failure: ", word, " Not Found !");
}


/*
	This function finds and deletes the entered word
*/
void Delete(Node **head, char *word) {
	if(IsEmpty(*head)){
		printf("\t<%s>\n", "Error: Dictionary Empty !");
		return;
	}

	Node *current = *head;
	Node *pre;

	// if the word is at head node
	if(strcmp((*head)->word,word)==0){
		(*head) = (*head)->next;
		free(current);
		printf("\t<%s%s%s>\n", "Success: ", word, " Deleted !");
		return;
	}

	while(current->next != NULL) {
		if(strcmp(current->word,word)==0)
			break;

		pre = current;
		current = current->next;
	}


	if(strcmp(current->word,word)==0){
		pre->next = current->next;
		free(current);
		printf("\t<%s%s%s>\n", "Success: ", word, " Deleted !");
	} else {
		printf("\t<%s%s%s>\n", "Failure: ", word, " Not Found !");
	}
}


/*
	Print function traverses the whole list
	and prints all the words along with their meanings
*/
void Print(Node *head) {
	if(IsEmpty(head)){
		printf("\t<%s>\n", "Error: Dictionary Empty !");
		return;
	}
	Node *temp = head;
	// traverse list
	printf("%s\n", "-----------------------------------------------");
	int count = 0;
	printf("%-5s%6s%20s\n", "Sr.", "WORD", "MEANING");
	printf("%s\n", "-----------------------------------------------");
	while(temp != NULL)
	{
		printf("%-5d %-15s : %s\n", ++count, temp->word, temp->meaning);
		temp = temp->next;
	}
	printf("%s\n", "-----------------------------------------------");
	free(temp);
}

/*
	This function returns 1 if the dictionary is empty
	and returns 0 if the dictionary is not empty
*/
int IsEmpty(Node *head) {
	return (head == NULL);
}

/*
	This function returns the total words contained by 
	the dictionary
*/
int TotalWords(Node *head) {
	int size = 0;

	Node *temp = head;

	while(temp != NULL){
		temp = temp->next;
		size++;
	}

	return size;
}