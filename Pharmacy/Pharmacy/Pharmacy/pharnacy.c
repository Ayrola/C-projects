#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#pragma warning (disable : 4996  )
typedef struct Pharmacy {
	char id[15];
	char name[30];
	double price;
	char date[11];
	struct Pharmacy*next;
}Pharmacy;
void addNewMedicine()
{
	FILE *fp;
	fp = fopen("Storage.bin", "ab+");
	Pharmacy medicine;
	printf("Insert medicine id:\n");
	fseek(stdin, 0, SEEK_END);
	fgets(medicine.id, 15, stdin);
	medicine.id[strcspn(medicine.id, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert medicine name:\n");
	fgets(medicine.name, 30, stdin);
	medicine.name[strcspn(medicine.name, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert medicine price:\n");
	scanf("%lf", &medicine.price);
	printf("Insert medicine data:\n");
	fseek(stdin, 0, SEEK_END);
	fgets(medicine.date, 11, stdin);
	medicine.date[strcspn(medicine.date, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	fwrite(&medicine, sizeof(Pharmacy), 1, fp);
	fclose(fp);
}
Pharmacy *GetList()
{
	FILE *fp;
	fp = fopen("Storage.bin", "rb");
	Pharmacy *head = NULL;
	head = malloc(sizeof(Pharmacy));  
	head->next = NULL;
	Pharmacy *current = head;
	Pharmacy *last = head;

	while (1)
	{
		if (fread(current, sizeof(Pharmacy), 1, fp) != 1)
		{
			current = NULL;
			last->next = NULL;
			break;
		}
		last = current;
		current->next = malloc(sizeof(Pharmacy));
		current = current->next;
	}
	free(current);
	free(last->next);
	fclose(fp);
	return head;
}
void menu()
{
	printf("Choose one of the following options:\n"
	"1.Add new medicine.\n"
	"2.Change medicine price.\n"
	"3.Show all out of date.\n"
	"4.Show current medicine.\n"
	"5.Exit.\n");
}
Pharmacy*changePrice(Pharmacy*head)
{
	FILE *fp;
	fp = fopen("Storage.bin", "wb+");
	fclose(fp);
	fp = fopen("Storage.bin", "ab+");
	Pharmacy*current = head;
	printf("Insert id to change the price:\n");
	char id[15];
	fseek(stdin, 0, SEEK_END);
	fgets(id, 11, stdin);
	id[strcspn(id, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	while (current)
	{
		if (strcmp(current->id, id)==0)
		{
			printf("Change price:\n");
			scanf("%lf", &current->price);
		}
		current = current->next;
	}
	
	
	current = head;
	while (current)
	{
		fwrite(current, 1,sizeof(Pharmacy), fp);
		current = current->next;
	}
	fclose(fp);
	return head;
}
void print(Pharmacy*head)
{
	Pharmacy*current = head;
	while (current)
	{
		printf("%s , %s , %lf , %s \n", current->id, current->name, current->price, current->date);
		current = current->next;
	}
}
void printCurrent(Pharmacy*head)
{
	Pharmacy*current = head;
	printf("Insert id to show info:\n");
	char id[15];
	fseek(stdin, 0, SEEK_END);
	fgets(id, 11, stdin);
	id[strcspn(id, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	while (current)
	{
		if (strcmp(current->id, id) == 0)
		{
			printf("Id:%s  Name:%s  Price:%lf  Date:%s  \n",current->id,current->name,current->price,current->date);
			break;
		}
		current = current->next;
	}

}
void printOutOfDate(Pharmacy*head)
{
	Pharmacy*current = head;
	printf("Insert years:\n");
	int years;
	scanf("%d", &years);
	char currentDate[11];
	while (current)
	{
		strcpy(currentDate, current->date);
		int month, day, year;
		month = atoi(strtok(currentDate, "."));
		day = atoi(strtok(NULL, "."));
		year = atoi(strtok(NULL, "."));
		if (year+years <= 2017)
		{
				printf("ID:%s  Name:%s  Price:%lf  Date:%s\n", current->id, current->name, current->price, current->date);
		}
		current = current->next;
	}
}
int main()
{
	Pharmacy*head = NULL;
	int choice;
	while (1)
	{
		menu();
		head = GetList();
		scanf("%d", &choice);
		if (choice == 1)
		{
			addNewMedicine();
		}
		else if (choice == 2)
		{
			head = changePrice(head);
		}
		else if (choice == 3)
		{
			printOutOfDate(head);
		}
		else if (choice == 4)
		{
			printCurrent(head);
		}
		else if (choice == 6)
		{
			print(head);
		}
		else
		{
			exit(1);
		}
		system("pause");
		system("cls");
		
	}
}
