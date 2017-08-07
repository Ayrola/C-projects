#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#pragma warning (disable : 4996  )
#include "struct.h"
void addingNewLeague()
{
	League league;
	FILE *fp;
	fp = fopen("Storage.bin", "ab+");
	printf("Insert leagues countey name:\n");
	fseek(stdin, 0, SEEK_END);
	fgets(league.Countryname, 50, stdin);
	league.Countryname[strcspn(league.Countryname, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert league coeficient:\n");
	scanf("%lf", &league.coeficient);
	fseek(stdin, 0, SEEK_END);
	printf("Insert number of professional teams:\n");
	scanf("%d", &league.numberOfProTeams);
	fseek(stdin, 0, SEEK_END);
	printf("Insert tv auditory\n");
	scanf("%d", &league.tvAuditory);
	fseek(stdin, 0, SEEK_END);
	printf("Insert  average audition:\n");
	scanf("%d", &league.averageAudition);
	fseek(stdin, 0, SEEK_END);
	fwrite(&league, sizeof(League), 1, fp);
	fclose(fp);
}
void menu()
{
	printf("Choose one of the following options:\n"
		"1.Add new league.\n"
		"2.Change the data about a league.\n"
		"3.Show all with a current auditory.\n"
		"4.Show the league with lowest coeficient\n"
		"5.Exit.\n");
}
League *GetList()
{
	FILE *fp;
	fp = fopen("Storage.bin", "rb");
	League *head = NULL;
	head = malloc(sizeof(League));  head->next = NULL;

	League *current = head;
	League *last = head;

	while (1)
	{
		if (fread(current, sizeof(League), 1, fp) != 1)
		{
			current = NULL;
			last->next = NULL;
			break;
		}
		last = current;
		current->next = malloc(sizeof(League));
		current = current->next;
	}
	free(current);
	free(last->next);
	fclose(fp);
	return head;
}
void showAll(League*head)
{
	printf("Enter a television auditory:\n");
	int auditory;
	scanf("%d", &auditory);
	League*current = head;
	while (current)
	{
		if (current->tvAuditory >= auditory)
		{
			printf("||Country:%s    Leagues coeficient:%lf    Number of professional teams:%d    \nTV auditory:%d    Average audition:%d || \n   ", current->Countryname, current->coeficient, current->numberOfProTeams, current->tvAuditory, current->averageAudition);
		}
		current = current->next;
	}
}
void LowestCoeficient(League*head)
{
	League*current = head;
	League*next = head;
	next = current->next;
	char name[50];
	double coeficient;
	int proTeams;
	int tvAuditory;
	int averageAudition;
	while (next)
	{
		if (next->coeficient < current->coeficient)
		{
			strcpy(name, next->Countryname);
			coeficient = next->coeficient;
			proTeams = next->numberOfProTeams;
			tvAuditory = next->tvAuditory;
			averageAudition = next->averageAudition;
		}
		next = next->next;
		current = current->next;
	}
	printf("\n||Country:%s    Leagues coeficient:%lf    Number of professional teams:%d    \nTV auditory:%d    Average audition:%d ||\n", name, coeficient, proTeams, tvAuditory, averageAudition);
}
League *modify(League*head)
{
	FILE *fp;
	fp = fopen("Storage.bin", "wb");
	fclose(fp);
	fp = fopen("Storage.bin", "ab+");
	League*current = head;
	League*prev = NULL;
	League*temp = NULL;
	printf("Insert Country name:\n");
	char name[50];
	fseek(stdin, 0, SEEK_END);
	fgets(name, 50, stdin);
	name[strcspn(name, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert coeficient\n");
	double coeficient;
	scanf("%lf", &coeficient);
	fseek(stdin, 0, SEEK_END);
	while (current)
	{
		if (strcmp(current->Countryname, name) == 0)
		{
			if (current->coeficient == coeficient)
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
				else {
					printf("Insert leagues countey name:\n");
					fseek(stdin, 0, SEEK_END);
					fgets(current->Countryname, 50, stdin);
					current->Countryname[strcspn(current->Countryname, "\n")] = 0;
					fseek(stdin, 0, SEEK_END);
					printf("Insert league coeficient:\n");
					scanf("%lf", &current->coeficient);
					fseek(stdin, 0, SEEK_END);
					printf("Insert number of professional teams:\n");
					scanf("%d", &current->numberOfProTeams);
					fseek(stdin, 0, SEEK_END);
					printf("Insert tv auditory\n");
					scanf("%d", &current->tvAuditory);
					fseek(stdin, 0, SEEK_END);
					printf("Insert  average audition:\n");
					scanf("%d", &current->averageAudition);
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
		fwrite(current, 1, sizeof(League), fp);
		current = current->next;
	}
	fclose(fp);
	return head;
}