/*
 * Yonathan Dessalene
 * CS262, Lab section 203
 * Project 1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define KEYWORD_LENGTH 21
#define TABULA_LENGTH 44
#define MESSAGE_LENGTH 251
const char CHARSET[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 .,;!-'?";

int Menu();
int NumberSeed();
char* Generate(int seed);
char* GetKeyword();
char* GetMessage();
void Encrypt(char* keyword, char* Tabula);
void Decrypt(char* keyword, char* Tabula);
int GetPosition(const char* str, const char c);

int main()
{
	int keywordInserted = 0;
	int tabulaInserted = 0;
	int finished = 0;
	int choice;
	int seed;
	char* keyword;
	char* Tabula;
	
	do
	{
		choice = Menu();
		printf("\n");
		switch(choice)
		{
			case 1: seed = NumberSeed();
					srandom(seed);
					Tabula = Generate(seed);
					tabulaInserted = 1;
					break;
			case 2: keyword = GetKeyword();
					keywordInserted = 1;
					break;
			case 3: if(keywordInserted == 1 && tabulaInserted == 1)
					{
						Encrypt(keyword, Tabula);
					}
					else if(keywordInserted == 1 && tabulaInserted == 0)
					{
						printf("The Tabula Recta has not been generated\n\n");
					}
					else if(keywordInserted == 0 && tabulaInserted == 1)
					{
						printf("No keyword has not been entered\n\n");
					}
					else
					{
						printf("The Tabula Recta has not been generated, and no keyword has been entered\n\n");
					}
					break;
			case 4: if(keywordInserted == 1 && tabulaInserted == 1)
					{
						Decrypt(keyword, Tabula);
					}
					else if(keywordInserted == 1 && tabulaInserted == 0)
					{
						printf("The Tabula Recta has not been generated\n\n");
					}
					else if(keywordInserted == 0 && tabulaInserted == 1)
					{
						printf("No keyword has not been entered\n\n");
					}
					else
					{
						printf("The Tabula Recta has not been generated, and no keyword has been entered\n\n");
					}
					break;
			case 5: printf("Exiting...\n\n");
					exit(0);
					break;
		}
	}while(finished == 0);

	return 0;	
}

int Menu()
{
	char buffer[3];
	int x = 0;

	printf("1. Enter a random number seed to generate the Tabula Recta\n");
	printf("2. Enter the Keyword\n");
	printf("3. Enter a message to encrypt\n");
	printf("4. Enter a message to decrypt\n");
	printf("5. Exit the program\n\n");
	
	printf("Choose an option --> ");
	fgets(buffer,3,stdin);
	sscanf(buffer, "%d", &x);
	
	return x;
}

int NumberSeed()
{
	char Buffer[100];
	int seed = 0;
	printf("Enter a random number seed: ");
	fgets(Buffer, 100, stdin);
	sscanf(Buffer, "%d", &seed);
	return seed;
}

char* Generate(int seed)
{
	srandom(seed);
	char* Tabula;
	Tabula = (char*) malloc(TABULA_LENGTH*TABULA_LENGTH * sizeof(char));
	
	int i,idx;
	
	i = 0;
	
	while(i < 44)
	{
		Tabula[i] = CHARSET[i];
		i++;
	}
	
	for (i = 43; i > 0; i--)
	{
		char temp;
		idx = random()%(i+1);
		temp = Tabula[idx];
		Tabula[idx] = Tabula[i];
		Tabula[i] = temp;
	}
	
	i = 44;
	int begin = 0;
	int end = 43+44;
	while(i < TABULA_LENGTH*TABULA_LENGTH)
	{
		if(i != end)
		{
			Tabula[i] = Tabula[i-43];
		}
		else
		{
			Tabula[i] = Tabula[begin];
			begin+=44;
			end+=44;
		}
		i++;
	}
	printf("\n");
	/*int index = 0;
	i = 0;
	while(i != strlen(Tabula))
	{
		printf("%c", Tabula[index]);
		index++;i++;
		
		if(i % 44 == 0)
		{
			printf("\n");
		}
	}
	printf("\n\n");*/
	return Tabula;
}

char* GetKeyword()
{
	char Buffer[KEYWORD_LENGTH];
	char* keyword;
	keyword = (char*) malloc(KEYWORD_LENGTH * sizeof(char));
	printf("Enter a keyword --> ");
	fgets(Buffer, KEYWORD_LENGTH, stdin);
	
	int i = 0;	
	while(i < strlen(Buffer)-1)
	{
		keyword[i] = Buffer[i];
		i++;
	}
	
	i = 0;
	while(i < strlen(keyword))
	{
		keyword[i] = toupper(keyword[i]);
		i++;
	}
	printf("Keyword Entered --> %s", keyword);
	printf("\n\n");
	return keyword;
}

char* GetMessage()
{
	char Buffer[MESSAGE_LENGTH];
	char* message;
	message = (char*) malloc(MESSAGE_LENGTH * sizeof(char));
	printf("Enter your message --> ");
	fgets(Buffer, MESSAGE_LENGTH, stdin);
	
	int i = 0;
	while(i < strlen(Buffer)-1)
	{
		message[i] = Buffer[i];
		i++;
	}
	
	i = 0;
	while(i < strlen(message))
	{
		message[i] = toupper(message[i]);
		i++;
	}
	printf("Message Entered --> %s", message);
	printf("\n");
	return message;
}

void Encrypt(char* keyword, char* Tabula)
{
	char* message = GetMessage();
	char encrypted[strlen(message)];
	int x,y;
	
	int i = 0;
	int k = 0;
	while(i < strlen(message))
	{
		x = GetPosition(CHARSET, keyword[k]);
		y = GetPosition(CHARSET, message[i]);
		encrypted[i] = Tabula[x+(44*y)];
		i++;k++;
		if(k == strlen(keyword))
		{
			k = 0;
		}
	}
	printf("\n");
	printf("Encrypted Message --> %s", encrypted);
	printf("\n\n");
}

void Decrypt(char* keyword, char* Tabula)
{
	char* message = GetMessage();
	char decrypted[strlen(message)];
	int x, y;
	char temp;
	
	int i = 0;
	int k = 0;
	int j;
	while(i < strlen(message))
	{
		temp = message[i];
		y = GetPosition(CHARSET, keyword[k]);
		for(j = 0; j < TABULA_LENGTH; j++)
		{
			if(Tabula[(j+(44*y))] == temp)
			{
				x = j;
			}
		}
		decrypted[i] = CHARSET[x];
		i++;k++;
		if(k == strlen(keyword))
		{
			k = 0;
		}
	}
	printf("Decrypted Message --> %s", decrypted);
	printf("\n\n");
}

/*
 *  Function: GetPosition
 *
 *  Description: Finds the position of the first instance of a given character within a given cstring.
 *
 *  Parameters: const char *str   - Pointer to the first element of the cstring in which to search
 *              const char c      - The character to find within the input cstring
 *
 *  Returns: Non-negative position value of the first instance of c in str
 *           If c is not found in str, returns -1 
 */
int GetPosition(const char* str, const char c)
{
	int retVal = -1;
	char *pos = strchr(str, c);
	
	if (pos != NULL)
	{
		retVal = pos - str;
	}
	
	return retVal;
}
