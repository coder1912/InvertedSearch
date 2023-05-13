/* 
*  Name        : AKHIL AJITH K C
*  Project     : InvertedSearch
*  Date        : 15/02/2023
*  DESCRIPTION : An inverted index is a mapping of words to their location in a set of documents. Most modern search engines utilize 
 some form of an inverted index to process user-submitted queries. In its most basic form, an inverted index is a simple hash table 
 which maps words in the documents to some sort of document identifier. 
 */


#include "inverted.h"
int main(int argc, char *argv[])
{
	//check whether there is only one CLA
	if(argc == 1)
	{
		//printing the error message
		printf("Error : Invalid number of arguments\nUsage: ./invertedIndex <file1> <file2> ...\n");
		return FAILURE;
	}
	else
	{
		//create a file structure
		file_node_t *file_head = NULL;

		//validate all the files
		validate_n_store_filenames(&file_head, argv);

		//logic to check wheteher the files are valid or not
		if(file_head == NULL)
		{
			printf("There is no valid files\nPlease enter valid files\n");
			return FAILURE;
		}

		//create a main structure
		main_node_t *HT_head[SIZE] = {NULL};

		//Variable and array declaration
		char cont;
		int choice, flagX = 0,flagY=0;
		char name[BUFF_SIZE], backup_f[BUFF_SIZE], upd_file[BUFF_SIZE];
	
		//Loop for continue the proccess 
		while(1)
		{
			//Print the content
			printf("1.create DB\n2.Display DB\n3.Search DB\n4.Save DB\n5.Update DB\n6.Exit\nPlease Enter your choice : ");
			scanf("%d", &choice);
			//switch case to do different operations
			switch(choice)
			{
				//case 1 is for creating the database
				case 1:
					if (flagX == 0)
					{
						//Function call of create database
						create_DB(file_head, HT_head);
						flagX = 1;   //flage set as 1
					}
					else
						//Print the content
						printf("Files passed through commandline already added into the Database\n");
					break;

				//case 2 is for display the database	
				case 2:
					if(flagX == 1 || flagY == 1)
					//function call of display database
					display_DB(HT_head);
					else
						printf("Can't perform display without performing create database or update database\n");
					break;
				
				//case 3 is for search the database	
				case 3:
					if(flagX == 1 || flagY == 1)
					{
						printf("Enter the word to be searched in Database : ");
						scanf("%s", name);
						//Finding the index value
						int index = tolower(name[0]) % 97;
						if (index < 0 || index > 25)
							index = 26;
						//function call of search database
						search_DB(HT_head[index], name, index);
					}
					else
						printf("Can't perform search without performing create database or update database\n");

					break;


				//case 4 for save the database to backup file
				case 4:
					printf("Enter the backup filename : ");
					scanf("%s", backup_f);
					//function call to save the database 
					save_DB(HT_head, backup_f);
					break;

				//case 5 for update the database
				case 5:
					if(flagX == 0)
					{
						printf("Enter the filename : ");
						scanf("%s", upd_file);

						//function call of update database
						update_DB(HT_head, file_head, upd_file);
						flagY=1;
					}
					else
						printf("Can't perform update operation after creating database\n");
					break;
				//default massage	
				
				case 6:
					return SUCCESS;
				default :
					printf("Error : Invalid choice\n");
			}
			printf("Do you want to continue(y/Y) ? ");
			getchar();
			scanf("%c", &cont);
			//checking the cont value
			if (cont != 'y' && cont != 'Y')
				return SUCCESS;
		}
		
	}
}
