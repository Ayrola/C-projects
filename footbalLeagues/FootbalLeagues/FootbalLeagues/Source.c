#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#pragma warning (disable : 4996  )
#include "struct.h"
int main()
{
	League*head = NULL;
	int choice;
	while (1)
	{
		head = GetList();
		menu();
		scanf("%d", &choice);
		if (choice == 1)
		{
			addingNewLeague();
		}
		else if (choice == 2)
		{
			head = modify(head);
		}
		else if (choice == 3)
		{
			showAll(head);
		}
		else if (choice == 4)
		{
			LowestCoeficient(head);
		}
		else
		{
			exit(1);
		}
		system("pause");
		system("cls");

	}
}