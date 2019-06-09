/* 
Implementation of dictionary using Binary Search Tree
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
FILE *fp;
const char db_addr[100] = "./res/dict_min.txt";

typedef struct node {
	char *word;
	char *meaning;
	struct node *left;
	struct node *right;
} Node;

// protypes
void InitializeDictionary(Node **root);
void SaveDictionary(Node *root, int status);
Node* getNewNode(char* word, char *meaning);
void InsertLexi(Node **root, char *word, char *meaning, int info_flag, int init_flag);
int UpdateMeaning(Node **root, char *word, char *meaning, int status);
void Search(Node *root, char *data, int init_flag);
int FindExact(Node *root, char *word, int init_flag);
// void Delete(Node **root, char *data);
void Print(Node *root, int count);
int IsEmpty(Node *root);
int Size(Node *root);


// function definitions

void InitializeDictionary(Node **root){
	int total_words;
	char ch;

	char *word = (char *) malloc(MAX_WORD_LEN * sizeof(char));
	char *meaning = (char *) malloc(MAX_MEANING_LEN * sizeof(char));

	fp = fopen(db_addr, "r");
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

			InsertLexi(root,word,meaning,0,0);
		}

		fclose(fp);
	} else {
		printf("\t<%s>\n", "Fatal: Dictionary Database Not Found! Exiting..");
		exit(1);
	}
}

void SaveDictionary(Node *root, int init_flag){
	if(init_flag == 0) {
		fp = fopen(db_addr, "w");
		fprintf(fp, "%s:%d", "words",Size(root));
	}
	if (root == NULL)
		return;

	fprintf(fp, "\n%s:%s", root->word, root->meaning);
	SaveDictionary(root->left, 1);
	SaveDictionary(root->right, 1);

	if(init_flag == 0)
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


void InsertLexi(Node **root, char *word, char *meaning, int info_flag, int init_flag) {
	// get new node
	Node *newNode = getNewNode(word,meaning);

	if(IsEmpty(*root)) {
		*root = newNode;
		if(info_flag)
			printf("\t<%s%s%s>\n", "Success: ", word, " Added !");
		return;
	}

	if(strcmp(word, (*root)->word) < 0) {
		// printf("comparing: %s | %s : %d\n", word, (*root)->word, strcmp(word, (*root)->word));
		InsertLexi(&((*root)->left), word, meaning, info_flag, 1);
	} else if(strcmp(word, (*root)->word) > 0) {
		// printf("comparing: %s | %s : %d\n", word, (*root)->word, strcmp(word, (*root)->word));
		InsertLexi(&((*root)->right), word, meaning, info_flag, 1);
	} else {
		if(info_flag)
			printf("\t<%s%s%s>\n", "Failure: ", word, " Already Exists !");
		return;
	}


}

int UpdateMeaning(Node **root, char *word, char *meaning, int init_flag) {
	if(IsEmpty(*root)){
		if(init_flag == 0)
			printf("\t<%s>\n", " Error: Dictionary Empty !");
		return 0;
	}

	if(strcmp(word,(*root)->word) == 0)
	{
		(*root)->meaning = realloc((*root)->meaning, sizeof(strlen(meaning)));
		strcpy((*root)->meaning, meaning);
		printf("\t<%s%s%s>\n", "Success: ", word, " Updated !");
		return 1;
	}

	return UpdateMeaning(&((*root)->left), word, meaning, 1) || UpdateMeaning(&((*root)->right), word, meaning, 1);
}


void Search(Node *root, char *word, int init_flag) {
	if(IsEmpty(root)){
		if (init_flag == 0) {
			printf("\t<%s>\n", " Error: Dictionary Empty !");
		}
		return;
	}
	static int result_count;

	if(init_flag == 0){
		result_count = 0;
		printf("%s\n", "-----------------Search Results----------------");
	}


	if(strncmp(word,root->word,strlen(word)) == 0)
	{
		printf("\t%-15s : %s\n", root->word, root->meaning);
		result_count++;
	}
	Search(root->left, word, 1);
	Search(root->right, word, 1);

	if(init_flag == 0)
		printf("%s%d%s\n", "----------------Found ",result_count," Results---------------");
}


int FindExact(Node *root, char *word, int init_flag) {
	if(IsEmpty(root)){
		if (init_flag == 0) {
			printf("\t<%s>\n", " Error: Dictionary Empty !");
		}
		return 0;
	}

	if(strcmp(word, root->word) == 0)
	{
		printf("\t%-10s : %s\n", root->word, root->meaning);
		return 1;
	}
	
	return FindExact(root->left, word, 1) || FindExact(root->right, word, 1);

}

// void Delete(Node **root, char *word, int init_flag) {
// 	if(IsEmpty(*root)){
// 		if(init_flag == 0)
// 			printf("\t<%s>\n", "Error: Dictionary Empty !");
// 		return;
// 	}

// 	if(strcmp((*root)->word,word)==0){
// 		(*root) = (*root)->next;
// 		free(current);
// 		printf("\t<%s%s%s>\n", "Success: ", word, " Deleted !");
// 		return;
// 	}

// 	while(current->next != NULL) {
// 		if(strcmp((*root)->word,word)==0)
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


void Print(Node *root, int init_flag) {
	if(IsEmpty(root)){
		if(init_flag == 0)
			printf("\t<%s>\n", "Error: Dictionary Empty !");
		return;
	}
	static int count;

	if (init_flag == 0) {
		count = 0;
		printf("%s\n", "-----------------------------------------------");
		printf("%-5s%6s%20s\n", "Sr.", "WORD", "MEANING");
		printf("%s\n", "-----------------------------------------------");
	}

	printf("%-5d %-15s : %s\n", ++count, root->word, root->meaning);
	Print(root->left, 1);
	Print(root->right, 1);

	if (init_flag == 0) {
		printf("%s\n", "-----------------------------------------------");
	}
}

int IsEmpty(Node *root) {
	return (root == NULL);
}

int Size(Node *root) {
	if (root == NULL)
		return 0;

	return (Size(root->left) + 1 + Size(root->right));
}