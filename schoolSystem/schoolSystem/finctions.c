#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#pragma warning (disable : 4996  )
#include "Header.h"


void addingNewLeague(School*head)
{
	School school;
	FILE *fp;
	School*current = head;
	fp = fopen("Storage.bin", "ab+");
	printf("Insert school name:\n");
	fseek(stdin, 0, SEEK_END);
	fgets(school.name, 50, stdin);
	school.name[strcspn(school.name, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert school unique code:\n");
	scanf("%d", &school.number);
	while (current)
	{
		if (current->number == school.number)
		{
			printf("You should insert an unique school code!");
			exit(1);
		}
		current = current->next;
	}
	fseek(stdin, 0, SEEK_END);
	printf("Insert school size:\n");
	scanf("%lf", &school.size);
	fseek(stdin, 0, SEEK_END);
	printf("Insert number of students\n");
	scanf("%d", &school.numberStudents);
	fseek(stdin, 0, SEEK_END);
	printf("Insert  director name:\n");
	fseek(stdin, 0, SEEK_END);
	fgets(school.director, 30, stdin);
	school.director[strcspn(school.director, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	fwrite(&school, sizeof(School), 1, fp);
	fclose(fp);
}
void menu()
{
	printf("Choose one of the following options:\n"
		"1.Add new school.\n"
		"2.Change the data about a school.\n"
		"3.Show all schools.\n"
		"4.Show the all schools with a a current number of students\n"
		"5.Exit.\n");
}
School *GetList()
{
	FILE *fp;
	fp = fopen("Storage.bin", "rb");
	School *head = NULL;
	head = malloc(sizeof(School));  head->next = NULL;

	School *current = head;
	School *last = head;

	while (1)
	{
		if (fread(current, sizeof(School), 1, fp) != 1)
		{
			current = NULL;
			last->next = NULL;
			break;
		}
		last = current;
		current->next = malloc(sizeof(School));
		current = current->next;
	}
	free(current);
	free(last->next);
	fclose(fp);
	return head;
}
void showAll(School*head)
{
	School*current = head;
	while (current)
	{
		printf("\nSchool name:%s  School unique number:%d  School size:%lf  \nSchool numebr of students:%d  School director:%s\n_______________________\n", current->name, current->number, current->size, current->numberStudents, current->director);
		current = current->next;
	}
}
School *modify(School*head)
{
	FILE *fp;
	fp = fopen("Storage.bin", "wb");
	fclose(fp);
	fp = fopen("Storage.bin", "ab+");
	School*current = head;
	School*prev = NULL;
	School*temp = NULL;
	printf("Insert Country name:\n");
	char name[50];
	fseek(stdin, 0, SEEK_END);
	fgets(name, 50, stdin);
	name[strcspn(name, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert code\n");
	int code;
	scanf("%d", &code);
	fseek(stdin, 0, SEEK_END);
	while (current)
	{
		if (strstr(current->name, name) != NULL)
		{
			if (current->number == code)
			{
				printf("Do you want to delete it? Y/N\n");
				char choice[1];
				scanf("%c", choice);
				if (choice[0] == 'Y')
				{
					if (head == current)
					{
						temp = head->next;
						head = temp;
						break;
					}
					temp = prev->next;
					prev->next = current->next;
					free(temp);
					break;
				}
				else
				{
					printf("Insert school name:\n");
					fseek(stdin, 0, SEEK_END);
					fgets(current->name, 50, stdin);
					current->name[strcspn(current->name, "\n")] = 0;
					fseek(stdin, 0, SEEK_END);
					printf("Insert school unique code:\n");
					scanf("%d", &current->number);
					fseek(stdin, 0, SEEK_END);
					printf("Insert school size:\n");
					scanf("%lf", &current->size);
					fseek(stdin, 0, SEEK_END);
					printf("Insert number of students\n");
					scanf("%d", &current->numberStudents);
					fseek(stdin, 0, SEEK_END);
					printf("Insert  director name:\n");
					fseek(stdin, 0, SEEK_END);
					fgets(current->director, 30, stdin);
					current->director[strcspn(current->director, "\n")] = 0;
					fseek(stdin, 0, SEEK_END);
				}

			}
		}
		prev = current;
		current = current->next;
	}
	current = head;
	while (current)
	{
		fwrite(current, 1, sizeof(School), fp);
		current = current->next;
	}
	fclose(fp);
	return head;
}
void showAllByStudents(School*head)
{
	printf("Enter a students number:\n");
	int number;
	scanf("%d", &number);
	School*current = head;
	while (current)
	{
		if (current->numberStudents >= number)
		{
			printf("\nSchool name:%s  School unique number:%d  School size:%lf  \nSchool numebr of students:%d  School director:%s\n_______________________\n", current->name, current->number, current->size, current->numberStudents, current->director);
		}
		current = current->next;
	}
}