#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#pragma warning (disable : 4996  )
typedef struct Enterpise {
	double id;
	char name[50];
	char industry[30];
	double income;
	double outcome;
	int workers;
	struct Enterpise*next;
}Enterprise;
Enterprise* swap_items(Enterprise* root, Enterprise* A, Enterprise* B)
{

	Enterprise *prev_A = NULL;
	Enterprise *prev_B = NULL;
	Enterprise *curr_item = root; int f = 0;

	if (root == A)
	{ 
		f = 1;
	}
		

	else if (root == B) f = 2; 
	while (curr_item != NULL)
	{
		if (curr_item->next == A) 
			prev_A = curr_item;

		if (curr_item->next == B)
			prev_B = curr_item;
		curr_item = curr_item->next;

	}
	if ((prev_A != NULL || f == 1) && (prev_B != NULL || f == 2))
	{

		if (f != 1)
			prev_A->next = B;

		else

			root = B; if (f != 2)

			prev_B->next = A;
			else

				root = A; curr_item = A->next; A->next = B->next; B->next = curr_item;

	}
	return root;

}
void Printing(Enterprise* head)
{
	Enterprise*current = head;
	Enterprise*next = current->next;
	while (current)
	{
		next = current->next;
		while (next)
		{
			if (strcmp(current->industry, next->industry) < 0)
			{
				head = swap_items(head, current, next);
			}
			next = next->next;
		}
		current = current->next;
	}
	current = head;
	while (current)
	{
		printf("ID:%lf \nName:%s \nIndustry:%s \nIncome:%lf \nOutcome:%lf \nMembers:%d \n", current->id, current->name, current->industry, current->income, current->outcome, current->workers);
		current = current->next;
	}
}
void addingNewEnterprise()
{
	Enterprise enterprise;
	FILE *fp;
	fp = fopen("Storage_Enterprise.bin", "ab+");
	printf("Insert enterprise id:\n");
	fseek(stdin, 0, SEEK_END);
	scanf("%lf", &enterprise.id);
	fseek(stdin, 0, SEEK_END);
	printf("Insert enterprise name:\n");
	fgets(enterprise.name, 50, stdin);
	enterprise.name[strcspn(enterprise.name, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert enterprise industry:\n");
	fgets(enterprise.industry, 50, stdin);
	enterprise.industry[strcspn(enterprise.industry, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert industry income:\n");
	scanf("%lf", &enterprise.income);
	fseek(stdin, 0, SEEK_END);
	printf("Insert enterprise outcome:\n");
	fseek(stdin, 0, SEEK_END);
	scanf("%lf", &enterprise.outcome);
	printf("Insert enterprise workers:\n");
	fseek(stdin, 0, SEEK_END);
	scanf("%d", &enterprise.workers);
	fseek(stdin, 0, SEEK_END);
	fwrite(&enterprise, sizeof(enterprise), 1, fp);
	fclose(fp);
}
Enterprise *GetList()
{
	FILE *fp;
	fp = fopen("Storage_Enterprise.bin", "rb");
	Enterprise *head = NULL;
	head = malloc(sizeof(Enterprise));  head->next = NULL;

	Enterprise *current = head;
	Enterprise *last = head;

	while (1)
	{
		if (fread(current, sizeof(Enterprise), 1, fp) != 1)
		{
			current = NULL;
			last->next = NULL;
			break;
		}
		last = current;
		current->next = malloc(sizeof(Enterprise));
		current = current->next;
	}
	free(current);
	free(last->next);
	fclose(fp);
	return head;
}
void ShowAll(Enterprise*head)
{
	Enterprise *current = head;
	while (current)
	{
		printf("ID:%lf \nName:%s \nIndustry:%s \nIncome:%lf \nOutcome:%lf \nMembers:%d \n", current->id, current->name, current->industry, current->income, current->outcome, current->workers);
		current = current->next;
	}
}
Enterprise *DeleteEnterprise(Enterprise*head)
{
	FILE *fp;
	fp = fopen("Storage_Enterprise.bin", "wb");
	fclose(fp);
	fp = fopen("Storage_Enterprise.bin", "ab+");
	Enterprise*current = head;
	Enterprise*prev = NULL;
	Enterprise*temp = NULL;
	int value;
	int checker=0;
	printf("Insert value for comparison:\n");
	scanf("%d", &value);
	while (current)
	{
		if (current->outcome>=value)
		{
			if (head == current)
			{
				temp = head->next;
				head = temp;
				checker = 1;
			}
			if (checker == 0)
			{
				temp = prev->next;
				prev->next = current->next;
				free(temp);
			}

		}
		prev = current;
		current = current->next;
	}
	current = head;
	while (current)
	{
		fwrite(current, 1, sizeof(Enterprise), fp);
		current = current->next;
	}
	fclose(fp);
	return head;
}
void menu()
{
	printf("Choose one of the options!\n");
	printf("1.Add a enterprise to the system.\n");
	printf("2.Show info about enterprises.\n");
	printf("3.List of sorted enterprises.\n");
	printf("4.Delete all enterprises with huge outcomes.\n");
	printf("5.Exit.\n");
}
int main()
{
	Enterprise*head = NULL;
	int choice;
	while (1)
	{
		menu();
		head = GetList();
		scanf("%d", &choice);
		if (choice == 1)
		{
			addingNewEnterprise();
		}
		else if (choice == 2)
		{
			ShowAll(head);
		}
		else if (choice == 3)
		{
			Printing(head);
		}
		else if (choice == 4)
		{
			head = DeleteEnterprise(head);
		}
		else
		{
			exit(1);
		}
	}
}