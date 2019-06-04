#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_WORD_LEN 20
#define MAX_MEANING_LEN 100

typedef struct node {
	char *word;
	char *meaning;
	struct node *next;
} Node;

// protypes
void InitializeDictionary(Node **head);
void SaveDictionary(Node *head);
Node* getNewNode(char* word, char *meaning);
void InsertLexi(Node **head, char *word, char *meaning, int info_flag);
void UpdateMeaning(Node **head, char *word, char *meaning);
void Search(Node *head, char *data);
void Delete(Node **head, char *data);
void Print(Node *head);
int IsEmpty(Node *head);
int Size(Node *head);


// function definitions

void InitializeDictionary(Node **head){
	char file_addr[100] = "./res/dict_db.txt";
	int total_words;
	char ch;
	char *word = (char *) calloc(MAX_WORD_LEN, sizeof(char));
	char *meaning = (char *) calloc(MAX_MEANING_LEN, sizeof(char));

	FILE *fp = fopen(file_addr, "r");
	if(fp){
		fscanf(fp, "words:%d\n", &total_words);
		for (int i = 0; i < total_words; ++i){
			fscanf(fp, "%[^:]s", word);
			ch = getc(fp);		// to remove the : character between word and meaning
			fscanf(fp, "%[^\nEOF]s", meaning);
			ch = getc(fp);
			InsertLexi(head,word,meaning,0);
		}
		fclose(fp);
	} else {
		printf("\t<%s>\n", "Fatal: Dictionary Database Not Found! Exiting..");
		exit(1);
	}
}

void SaveDictionary(Node *head){
	char file_addr[100] = "./res/dict_db.txt";
	FILE *fp = fopen(file_addr, "w");
	Node *temp = head;
	fprintf(fp, "%s:%d\n", "words",Size(head));
	while(temp->next != NULL) {
		fprintf(fp, "%s:%s\n", temp->word, temp->meaning);
		temp = temp->next;
	}
	fprintf(fp, "%s:%s", temp->word, temp->meaning);

	fclose(fp);
}

Node* getNewNode(char *word, char *meaning) {
	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->word = (char *) malloc(sizeof(word));
	newNode->meaning = (char *) malloc(sizeof(meaning));
	strcpy(newNode->word,word);
	strcpy(newNode->meaning,meaning);
	newNode->next = NULL;

	return newNode;
}


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

void Delete(Node **head, char *word) {
	if(IsEmpty(*head)){
		printf("\t<%s>\n", "Error: Dictionary Empty !");
		return;
	}

	Node *current = *head;
	Node *pre;

	if(strcmp((*head)->word,word)==0){
		(*head) = (*head)->next;
		free(current);
		printf("\t<%s%s%s>\n", "Success: ", word, " Deleted !");
		return;
	}

	while(current->next != NULL) {
		if(strcmp((*head)->word,word)==0)
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

int IsEmpty(Node *head) {
	return (head == NULL);
}

int Size(Node *head) {
	int size = 0;

	Node *temp = head;

	while(temp != NULL){
		temp = temp->next;
		size++;
	}

	return size;
}