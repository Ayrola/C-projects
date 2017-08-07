#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#pragma warning (disable : 4996  )
typedef struct Picture {
	char id[50];
	char author[50];
	char name[50];
	double price;
	int year;
	struct Picture*next;
}Picture;
Picture *ShowAllPicturesByAuthor(Picture*head);
void addingNewPicture()
{
	Picture picture;
	FILE *fp;
	fp = fopen("Storage_Gallery.bin", "ab+");
	printf("Insert picture id:\n");
	fseek(stdin, 0, SEEK_END);
	fgets(picture.id, 50, stdin);
	picture.id[strcspn(picture.id, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert picture author:\n");
	fgets(picture.author, 50, stdin);
	picture.author[strcspn(picture.author, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	printf("Insert picture name:\n");
	fgets(picture.name, 50, stdin);
	fseek(stdin, 0, SEEK_END);
	picture.name[strcspn(picture.name, "\n")] = 0;
	printf("Insert price:\n");
	scanf("%lf", &picture.price);
	fseek(stdin, 0, SEEK_END);
	printf("Insert picture year:\n");
	scanf("%d", &picture.year);
	fwrite(&picture, sizeof(Picture), 1, fp);
	fclose(fp);
}
void menu()
{
	printf("Choose one of the options!\n");
	printf("1.Add a picture to the gallery.\n");
	printf("2.Delete a picture by id.\n");
	printf("3.Show information by authors.\n");
	printf("4.Update a picture info.\n");
	printf("5.Show all.\n");
	printf("6.Exit.\n");
}
Picture *GetList()
{
	FILE *fp;
	fp = fopen("Storage_Gallery.bin", "rb");
	Picture *head = NULL;
	head = malloc(sizeof(Picture));  head->next = NULL;

	Picture *current = head;
	Picture *last = head;

	while (1)
	{
		if (fread(current, sizeof(Picture), 1, fp) != 1)
		{
			current = NULL;
			last->next = NULL;
			break;
		}
		last = current;
		current->next = malloc(sizeof(Picture));
		current = current->next;
	}
	free(current);
	free(last->next);
	fclose(fp);
	return head;
}
Picture *DeletePicture(Picture*head)
{
	FILE *fp;
	fp = fopen("Storage_Gallery.bin", "wb");
	fclose(fp);
	fp = fopen("Storage_Gallery.bin", "ab+");
	Picture*current = head;
	Picture*prev = NULL;
	Picture*temp = NULL;
	printf("Insert picture code:\n");
	char code[50];
	fseek(stdin, 0, SEEK_END);
	fgets(code, 50, stdin);
	code[strcspn(code, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	while (current)
	{
		if (strcmp(current->id, code)==0)
		{
			if (head == current)
			{
				printf("%s was deleted from the gallery!\n", current->name);
				temp = head->next;
				head = temp;
				break;
			}
			printf("%s was deleted from the gallery!\n", current->name);
			temp = prev->next;
			prev->next = current->next;
			free(temp);
			break;
		
		}
		prev = current;
		current = current->next;
	}
	current = head;
	while (current)
	{
		fwrite(current, 1, sizeof(Picture), fp);
		current = current->next;
	}
	fclose(fp);
	return head;
}
Picture *ShowAllPicturesByAuthor(Picture*head)
{
	Picture *current = head;
	Picture *next = head->next;

	double tmp;

	while (next != NULL) 
	{
		while (next != current) 
		{
			if (next->price < current->price) 
			{
				tmp = current->price;
				current->price = next->price;
				next->price = tmp;
			}
			current = current->next;
		}
		current = head;
		next = next->next;
	}
	return head;
}
Picture *Modify(Picture*head)
{
	FILE *fp;
	fp = fopen("Storage_Gallery.bin", "wb");
	fclose(fp);
	fp = fopen("Storage_Gallery.bin", "ab+");
	Picture*current = head;
	Picture*prev = NULL;
	Picture*temp = NULL;
	printf("Insert picture code:\n");
	char code[50];
	fseek(stdin, 0, SEEK_END);
	fgets(code, 50, stdin);
	code[strcspn(code, "\n")] = 0;
	fseek(stdin, 0, SEEK_END);
	while (current)
	{
		if (strcmp(current->id, code) == 0)
		{
			printf("Change picture code:\n");
			fseek(stdin, 0, SEEK_END);
			fgets(current->id, 50, stdin);
			current->id[strcspn(current->id, "\n")] = 0;
			fseek(stdin, 0, SEEK_END);
			printf("Change author:\n");
			fseek(stdin, 0, SEEK_END);
			fgets(current->author, 50, stdin);
			current->author[strcspn(current->author, "\n")] = 0;
			fseek(stdin, 0, SEEK_END);
			printf("Change name:\n");
			fseek(stdin, 0, SEEK_END);
			fgets(current->name, 50, stdin);
			current->name[strcspn(current->name, "\n")] = 0;
			fseek(stdin, 0, SEEK_END);
			printf("Change price:\n");
			fseek(stdin, 0, SEEK_END);
			scanf("%lf", &current->price);
			fseek(stdin, 0, SEEK_END);
			printf("Change author:\n");
			fseek(stdin, 0, SEEK_END);
			scanf("%d", &current->year);
			fseek(stdin, 0, SEEK_END);
		}
		current = current->next;
	}
	current = head;
	while (current)
	{
		fwrite(current, 1, sizeof(Picture), fp);
		current = current->next;
	}
	fclose(fp);
	return head;

}
void ShowAll(Picture*head)
{
	Picture*current = head;
	while (current)
	{
		printf("Code:%s\nAuthor:%s\n&Picture name:%s\nPrice:%lf\nYear:%d\n-------------------------------------\n", current->id, current->author, current->name, current->price, current->year);
		current = current->next;
	}
}
int main()
{
	Picture*head=NULL;
	int choice;
	while (1)
	{
		head = GetList();
		menu();
		scanf("%d",&choice);
		if (choice == 1)
		{
			addingNewPicture();
			
		}
		else if (choice == 2)
		{
			head = DeletePicture(head);
			head = GetList();
		}
		else if (choice == 3)
		{
		    head=ShowAllPicturesByAuthor(head);
		}
		else if (choice == 4)
		{
			head = Modify(head);
			head = GetList(head);
		}
		else if (choice == 5)
		{
			ShowAll(head);
		}
		else
		{
			exit(1);
		}
	}

}