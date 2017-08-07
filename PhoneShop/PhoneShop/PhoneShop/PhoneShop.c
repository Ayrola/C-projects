#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#pragma warning (disable : 4996  )
int uNumber;
typedef struct Phone {
	int number;
	char model[20];
	double price;
	int quantity;
	struct Phone*next;
}Phone;
Phone *Orders(Phone*head);
void addingNewPhone()
{
	Phone phone;
	FILE *fp;
	fp = fopen("Storage.bin", "ab+");
	printf("Insert phone unique number:\n");
	scanf("%d", &phone.number);
	fseek(stdin, 0, SEEK_END);
	printf("Insert phone model:\n");
	fgets(phone.model, 20, stdin);//pozicionira pointera na kraq na consolata
	phone.model[strcspn(phone.model, "\n")] = 0;//premahva \n ot kraq na string 
	fseek(stdin, 0, SEEK_END);
	printf("Insert phone price:\n");
	scanf("%lf", &phone.price);
	printf("Insert quantity:\n");
	scanf("%d", &phone.quantity);
	fwrite(&phone, sizeof(Phone), 1, fp);
	fclose(fp);
}
Phone *GetList()
{
	FILE *fp;
	fp = fopen("Storage.bin", "rb");
	Phone *head = NULL;
	head = malloc(sizeof(Phone));  head->next = NULL;

	Phone *current = head;
	Phone *last = head;

	while (1)
	{
		if (fread(current, sizeof(Phone), 1, fp) != 1)
		{
			current = NULL;
			last->next = NULL;
			break;
		}
		last = current;
		current->next = malloc(sizeof(Phone));
		current = current->next;
	}
	free(current);
	free(last->next);
	fclose(fp);
	return head;
}
Phone *Orders(Phone*head)
{
	FILE *fp;
	fp = fopen("Storage.bin", "wb");
	fclose(fp);
	fp = fopen("Storage.bin", "ab+");
	Phone*current = head;
	Phone*prev = NULL;
	Phone*temp = NULL;
	printf("Insert phone unique number:\n");
	scanf("%d", &uNumber);
	int choice;
	printf("1.Add phones.\n2.Remove phones.\n");
	scanf("%d", &choice);
	int newQuantity;
	while (current)
	{
		if (current->number == uNumber)
		{
			printf("%s quantity is %d\n", current->model, current->quantity);
			printf("Insert quantity:\n");
			scanf("%d", &newQuantity);
			if (choice == 1)
			{
				current->quantity += newQuantity;
				printf("Quantity of %s was changed to %d\n", current->model, current->quantity);
			}
			else if (choice == 2)
			{
				if (newQuantity >= current->quantity)
				{
					if (head == current)
					{
						temp = head->next;
						head = temp;
						printf("%s was deleted from the system!\n", current->model);
						break;
					}
					temp = prev->next;
					prev->next = current->next;
					free(temp);
					printf("%s was deleted from the system!\n", current->model);
					break;
				}
				else
				{
					current->quantity -= newQuantity;
					printf("Quantity of %s was changed to %d\n", current->model, current->quantity);
				}
			}
		}
	    fwrite(current, 1, sizeof(Phone), fp);	
		prev = current;
		current = current->next;
	}
	fclose(fp);
	return head;
}
void menu()
{
	printf("Choose one of the following options!\n");
	printf("1.Add new phone to the system.\n");
	printf("2.Change phones quantity.\n");
	printf("3.Show ones above the average.\n");
	printf("4.Show informtion.\n");
	printf("5.Show all phones.\n");
	printf("6.Exit.\n");
}
void clrscr()
{
	system("@cls||clear");
}
void ShowAllAboveAverige(Phone*head)
{
	Phone*current = head;
	int i = 0;
	double sum = 0;
	while (current)
	{
		i++;
		sum += current->price;
		current = current->next;
	}
	double average = sum / (double)i;
	current = head;
	while (current)
	{
		if (current->price >= average)
		{
			printf("%d %s %lf %d\n", current->number, current->model, current->price, current->quantity);
		}
		current = current->next;
	}
}
void printViaNumber(Phone*head)
{
	Phone*current = head;
	printf("Insert phone's unique number:\n");
	scanf("%d", &uNumber);
	while (current)
	{
		if (current->number == uNumber)
		{
			printf("Unique number:%d\nPhone model:%s\nPhones price:%lf\nPhones quantity:%d\n", current->number, current->model, current->price, current->quantity);
		}
		current = current->next;
	}
}
void ShowAll(Phone*head)
{
	Phone*current = head;
	while (current)
	{
		printf("Unique number:%d\nPhone model:%s\nPhones price:%lf\nPhones quantity:%d\n", current->number, current->model, current->price, current->quantity);
		current = current->next;
	}
}
int main()
{
	Phone *head = NULL;
	int mainChoice;
	while (1)
	{
		menu();
		scanf("%d", &mainChoice);
		head = GetList();
		if (mainChoice == 1)
		{
			addingNewPhone();
		}
		else if (mainChoice == 2)
		{
			head = Orders(head);
		}
		else if (mainChoice == 3)
		{
			ShowAllAboveAverige(head);
		}
		else if (mainChoice == 4)
		{
			printViaNumber(head);
		}
		else if(mainChoice==5)
		{
			ShowAll(head);
		}
		else
		{
			exit(1);
		}
		//clrscr();
	}
	
}