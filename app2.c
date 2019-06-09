/* 
DRIVER PROGRAM OR APPLICATION FOR DICTIONARY 
	By 		: VIKAS KUMAR
	Roll 	: 43
	Enroll	: 2017BCSE052
	Project	: Dictionary Simulation
*/

#include "./res/BST.h"


// Function Protypes
void Menu(void);
void CommandFormats(void);


// Main Function
int main()
{
	Node *head = NULL;
	InitializeDictionary(&head);
	char command[10];
	char word[MAX_WORD_LEN];
	char meaning[MAX_MEANING_LEN];
	int found;

	printf("%s\n", "==============DICTIONARY SIMULATION==============");
	Menu();  // show menu
	while(1)
	{
		printf("\n%s", "command > ");
		scanf("%s", command);

		if(strncmp(command, "search-all", strlen("search-all")) == 0){
			scanf("%s", word);
			Search(head, word, 0);

		} else if(strncmp(command, "find", strlen("find")) == 0){
			scanf("%s", word);
			found = FindExact(head, word, 0);
			if(!found)
				printf("\t<%s%s%s>\n", "Failure: ", word, " Not Found !");

		} else if(strncmp(command, "show", strlen("show")) == 0){
			Print(head, 0);

		} else if(strncmp(command, "add", strlen("add")) == 0){
			scanf("%s %[^\n]s", word, meaning);
			InsertLexi(&head, word, meaning, 1, 0);

		} else if(strncmp(command, "update", strlen("update")) == 0){
			scanf("%s %[^\n]s", word, meaning);
			// UpdateMeaning(&head, word, meaning);

		} else if(strncmp(command, "delete", strlen("delete")) == 0){
			scanf("%s", word);
			// Delete(&head, word);

		} else if(strncmp(command, "menu", strlen("menu")) == 0){
			Menu();

		} else if(strncmp(command, "format", strlen("format")) == 0) {
			CommandFormats();

		} else if(strncmp(command, "save", strlen("save")) == 0){
			SaveDictionary(head, 0);
			printf("%s\n", "<Info: Dictionary Database Updated>");

		}  else if(strncmp(command, "quit", strlen("quit")) == 0) {
			break;

		} else {
			printf("%s\n", "< Error : Command Invalid ! Try Again... >");
			Menu();
		}
	}

	printf("%s\n", "======================END=======================");
	return 0;
}



// Function Definitions

/*
	This Functions shows the options Menu	
*/
void Menu(void){
	printf("%s\n", "Commands : ");
	printf("\t%s\n", "find       -   Find Exact Word");
	printf("\t%s\n", "search-all -   Seach All Words");
	printf("\t%s\n", "show       -   Show Complete Dictionary");
	printf("\t%s\n", "add 	   -   Add New Word");
	printf("\t%s\n", "update     -   Update Existing Word");
	printf("\t%s\n", "delete     -   Delete Word");
	printf("\t%s\n", "menu       -   Show Menu Again");
	printf("\t%s\n", "format     -   Show Format of Each Command **");
	printf("\t%s\n", "save       -   Save Dictionary (DB) *");
	printf("\t%s\n", "quit       -   Quit *");
}

void CommandFormats(void){
	printf("%s\n", "Command Formats : ");
	printf("\t%s\n", "find        -   find <space> <word>");
	printf("\t%s\n", "search-all  -   search-all <space> <word>");
	printf("\t%s\n", "show        -   show");
	printf("\t%s\n", "add 	    -   add <space> <word> <space> <meaning>");
	printf("\t%s\n", "update      -   update <space> <word> <space> <new meaning>");
	printf("\t%s\n", "delete      -   delete <space> <word>");
	printf("\t%s\n", "menu        -   menu");
	printf("\t%s\n", "save        -   save");
	printf("\t%s\n", "quit        -   quit");	
}
