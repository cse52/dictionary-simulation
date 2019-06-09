/* Implementation of dictionary using Binary Search Tree
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
const char db_addr[100] = "./res/dict_min.txt";

typedef struct node {
	char *word;
	char *meaning;
	struct node *left;
	struct node *right;
} Node;

// protypes
void InitializeDictionary(Node **head);
void SaveDictionary(Node *head, int status);
Node* getNewNode(char* word, char *meaning);
void InsertLexi(Node **head, char *word, char *meaning, int info_flag);
void UpdateMeaning(Node **head, char *word, char *meaning, int status);
void Search(Node *head, char *data, int result_count);
void Delete(Node **head, char *data);
void Print(Node *head, int count);
int IsEmpty(Node *head);
int Size(Node *head);


// function definitions

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

void SaveDictionary(Node *head, int count){
	FILE *fp;
	if(count == 0) {
		fp = fopen(db_addr, "w");
		fprintf(fp, "%s:%d", "words",Size(head));
	}
	if (head == NULL)
		return;

	fprintf(fp, "\n%s:%s", head->word, head->meaning);
	SaveDictionary(head->left, count+1);
	SaveDictionary(head->right, count+1);

	if(count == 0)
		fclose(fp);
}

Node* getNewNode(char *word, char *meaning) {
	Node *newNode = (Node *) malloc(sizeof(Node));
	newNode->word = (char *) malloc(sizeof(char)*strlen(word) + 1);
	newNode->meaning = (char *) malloc(sizeof(char)*strlen(meaning) + 1);
	strcpy(newNode->word,word);
	strcpy(newNode->meaning,meaning);
	newNode->left = newNode->right = NULL;

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

	if(strcmp(word, (*head)->word) < 0) {
		InsertLexi(&((*head)->left), word, meaning, info_flag);
	} else if(strcmp(word, (*head)->word) > 0) {
		InsertLexi(&((*head)->right), word, meaning, info_flag);
	} else {
		if(info_flag)
			printf("\t<%s%s%s>\n", "Failure: ", word, " Already Exists !");
		return;
	}

	if(info_flag)
		printf("\t<%s%s%s>\n", "Success: ", word, " Added !");

}

void UpdateMeaning(Node **head, char *word, char *meaning, int count) {
	if(IsEmpty(*head)){
		if(count == 0)
			printf("\t<%s>\n", " Error: Dictionary Empty !");
		return;
	}

	if(strcmp(word,(*head)->word) == 0)
	{
		(*head)->meaning = realloc((*head)->meaning, sizeof(strlen(meaning)));
		strcpy((*head)->meaning, meaning);
		printf("\t<%s%s%s>\n", "Success: ", word, " Updated !");
		return;
	}
	UpdateMeaning(&((*head)->left), word, meaning, count+1);
	UpdateMeaning(&((*head)->right), word, meaning, count+1);

	if(count == 0)
		printf("\t<%s%s%s>\n", "Failure: ", word, " Not Found !");

}


void Search(Node *head, char *word, int result_count) {
	if(IsEmpty(head)){
		if (result_count == 0) {
			printf("\t<%s>\n", " Error: Dictionary Empty !");
		}
		return;
	}
	if(result_count == 0)
		printf("%s\n", "-----------------Search Results----------------");


	if(strncmp(word,head->word,strlen(word)) == 0)
	{
		printf("\t%-15s : %s\n", head->word, head->meaning);
		result_count++;
	}
	Search(head->left, word, result_count);
	Search(head->right, word, result_count);

	if(result_count == 0)
		printf("%s%d%s\n", "----------------Found ",result_count," Results---------------");
}

// void Delete(Node **head, char *word) {
// 	if(IsEmpty(*head)){
// 		printf("\t<%s>\n", "Error: Dictionary Empty !");
// 		return;
// 	}

// 	Node *current = *head;
// 	Node *pre;

// 	if(strcmp((*head)->word,word)==0){
// 		(*head) = (*head)->next;
// 		free(current);
// 		printf("\t<%s%s%s>\n", "Success: ", word, " Deleted !");
// 		return;
// 	}

// 	while(current->next != NULL) {
// 		if(strcmp((*head)->word,word)==0)
// 			break;

// 		pre = current;
// 		current = current->next;
// 	}


// 	if(strcmp(current->word,word)==0){
// 		pre->next = current->next;
// 		free(current);
// 		printf("\t<%s%s%s>\n", "Success: ", word, " Deleted !");
// 	} else {
// 		printf("\t<%s%s%s>\n", "Failure: ", word, " Not Found !");
// 	}
// }


void Print(Node *head, int count) {
	if(IsEmpty(head)){
		if(count == 0)
			printf("\t<%s>\n", "Error: Dictionary Empty !");
		return;
	}

	if (count == 0) {
		printf("%s\n", "-----------------------------------------------");
		printf("%-5s%6s%20s\n", "Sr.", "WORD", "MEANING");
		printf("%s\n", "-----------------------------------------------");
	}

	printf("%-5d %-15s : %s\n", count+1, head->word, head->meaning);
	Print(head->left, count+1);
	Print(head->right, count+1);

	if (count == 0) {
		printf("%s\n", "-----------------------------------------------");
	}
}

int IsEmpty(Node *head) {
	return (head == NULL);
}

int Size(Node *root) {
	if (root == NULL)
		return 0;

	return (Size(root->left) + 1 + Size(root->right));
}