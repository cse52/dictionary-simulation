#include "./res/linkedlist.c"



// function protypes
void Menu();


int main()
{
	Node *head = NULL;
	InitializeDictionary(&head);
	int choice;
	char word[MAX_WORD_LEN];
	char meaning[MAX_MEANING_LEN];

	printf("%s\n", "==============DICTIONARY SIMULATION==============");
	Menu();
	printf("%s", "Choice > ");
	scanf("%d", &choice);
	while(choice)
	{
		if(choice == 1){
			printf("%s", "Enter Word (search): ");
			scanf("%s", word);
			Search(head,word);
		} else if(choice == 2){
			Print(head);
		} else if(choice == 3){
			printf("%s", "Add (Format: Word<space>Meaning): ");
			scanf("%s", word);
			scanf("%[^\n]s", meaning);
			InsertLexi(&head,word,meaning,1);
		} else if(choice == 4){
			printf("%s", "Update (Formate : Word<space>NewMeaning) : ");
			scanf("%s", word);
			scanf("%[^\n]s", meaning);
			UpdateMeaning(&head,word,meaning);
		} else if(choice == 5){
			printf("%s", "Enter Word (delete): ");
			scanf("%s", word);
			Delete(&head, word);
		} else if(choice == 9){
			Menu();
		} else if(choice == 0) {
			break;
		} else {
			printf("%s\n", "< Choice Invalid ! Try Again... >");
			break;
		}
		printf("%s", "Choice > ");
		scanf("%d", &choice);
	}
	SaveDictionary(head);
	printf("%s\n", "<Info: Dictionary Database Updated>");
	printf("%s\n", "======================END=======================");
	return 0;
}



void Menu(){
	printf("%s\n", "Options : ");
	printf("\t%s\n", "1. Search Word *");
	printf("\t%s\n", "2. Show Complete Dictionary");
	printf("\t%s\n", "3. Add New Word");
	printf("\t%s\n", "4. Update Existing Word");
	printf("\t%s\n", "5. Delete Word");
	printf("\t%s\n", "9. Show Menu Again *");
	printf("\t%s\n", "0. Quit");
}
