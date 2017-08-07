#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#pragma warning (disable : 4996  )
int uNumber;
typedef struct Song {
	char title[50];
	char artist[50];
	char album[50];
	int length;
	struct Song*next;
}Song;
void addingNewSong()//dobavq nova pesen vuv faila i lista
{
	Song song;
	FILE *fp;
	fp = fopen("Storage.bin", "ab+");
	fseek(stdin, 0, SEEK_END);
	printf("Insert song title:\n");
	fgets(song.title, 500, stdin);//pozicionira pointera na kraq na consolata
	song.title[strcspn(song.title, "\n")] = 0;//premahva \n ot kraq na string 
	fseek(stdin, 0, SEEK_END);
	printf("Insert song artist:\n");
	fgets(song.artist, 500, stdin);//pozicionira pointera na kraq na consolata
	song.artist[strcspn(song.artist, "\n")] = 0;//premahva \n ot kraq na string 
	fseek(stdin, 0, SEEK_END);
	printf("Insert song album:\n");
	fgets(song.album, 500, stdin);//pozicionira pointera na kraq na consolata
	song.album[strcspn(song.album, "\n")] = 0;//premahva \n ot kraq na string 
	fseek(stdin, 0, SEEK_END);
	printf("Insert song length:\n");
	scanf("%d", &song.length);
	fseek(stdin, 0, SEEK_END);
	fwrite(&song, sizeof(Song), 1, fp);
	fclose(fp);
}
Song *GetList()//vzima vsichki pesni ot faila i gi zapisva v lista
{
	FILE *fp;
	fp = fopen("Storage.bin", "rb");
	Song *head = NULL;
	head = malloc(sizeof(Song));  head->next = NULL;

	Song *current = head;
	Song *last = head;

	while (1)
	{
		if (fread(current, sizeof(Song), 1, fp) != 1)
		{
			current = NULL;
			last->next = NULL;
			break;
		}
		last = current;
		current->next = malloc(sizeof(Song));
		current = current->next;
	}
	free(current);
	free(last->next);
	fclose(fp);
	return head;
}
int count(Song*head)//prebroqva elementite v lista
{
	Song*current = head;
	int count = 0;
	while (current)
	{
		count++;
		current = current->next;
	}
	return count;
}

struct Song *sortAlbum(struct Song *head)//funkciq koqto sortira lista po metoda na buble
{//funkciqta vrushta headura na list//funkciqta priema headura na lista i zapochva obrabotkata
	int num_nodes = count(head);
	int counter;

	for (counter = 0; counter < num_nodes; counter++) {
		struct Song* current = head;
		struct Song* next = current->next;
		struct Song* previous = NULL;

		while (next != NULL) {
			int compare = strcmp(current->album, next->album);
			if (compare > 0) {
				if (current == head) {
					head = next;
				}
				else {
					previous->next = next;
				}
				current->next = next->next;
				next->next = current;

				previous = next;
				next = current->next;
			}
			else {
				previous = current;
				current = current->next;
				next = current->next;
			}
		}
	}
	Song*newS = head;
	while (newS)
	{
		printf("%s   %s   %s  %d  \n", newS->title, newS->artist, newS->album, newS->length);
		newS = newS->next;
	}
	return head;
}
struct Song *sortTitle(struct Song *head)//funkciq koqto sortira lista po metoda na buble
{//funkciqta vrushta headura na list//funkciqta priema headura na lista i zapochva obrabotkata
	int num_nodes = count(head);
	int counter;

	for (counter = 0; counter < num_nodes; counter++) {
		struct Song* current = head;
		struct Song* next = current->next;
		struct Song* previous = NULL;

		while (next != NULL) {
			int compare = strcmp(current->title, next->title);
			if (compare > 0) {
				if (current == head) {
					head = next;
				}
				else {
					previous->next = next;
				}
				current->next = next->next;
				next->next = current;

				previous = next;
				next = current->next;
			}
			else {
				previous = current;
				current = current->next;
				next = current->next;
			}
		}
	}
	Song*newS = head;
	while (newS)
	{
		printf("%s   %s   %s  %d  \n", newS->title, newS->artist, newS->album, newS->length);
		newS = newS->next;
	}
	return head;
}
void menu()
{
	printf("Choose one of the following options!\n");
	printf("1.Sort by album.\n");
	printf("2.Sort by artist.\n");
	printf("3.Sort by title.\n");
	printf("4.Show all informtion.\n"
	"5.Add new song\n");
	printf("6.Exit.\n");
}
void printAll(Song*head)//printi vsichko za vsichki elementi na lista
{
	Song*current = head;
	while (current)
	{
		printf("%s   %s   %s  %d  \n", current->title, current->artist, current->album, current->length);
		current = current->next;
	}
}
struct Song *sortArtist(struct Song *head)//funkciq koqto sortira lista po metoda na buble
{//funkciqta vrushta headura na list//funkciqta priema headura na lista i zapochva obrabotkata
	int num_nodes = count(head);
	int counter;

	for (counter = 0; counter < num_nodes; counter++) {
		struct Song* current = head;
		struct Song* next = current->next;
		struct Song* previous = NULL;

		while (next != NULL) {
			int compare = strcmp(current->artist, next->artist);
			if (compare > 0) {
				if (current == head) {
					head = next;
				}
				else {
					previous->next = next;
				}
				current->next = next->next;
				next->next = current;

				previous = next;
				next = current->next;
			}
			else {
				previous = current;
				current = current->next;
				next = current->next;
			}
		}
	}
	Song*newS = head;
	while (newS)
	{
		printf("%s   %s   %s  %d  \n", newS->title, newS->artist, newS->album, newS->length);
		newS = newS->next;
	}
	return head;
}
int main()
{
	Song *head = NULL;
	int choice;
	while (1)
	{
		menu();
		scanf("%d", &choice);
		head = GetList();
		if (choice == 6)
		{
			addingNewSong();
			
		}
		else if (choice == 3)
		{
			head = sortTitle(head);
		}
		else if (choice == 2)
		{
			head = sortArtist(head);
		}
		else if (choice == 1)
		{
			head=sortAlbum(head);
		}
		else if (choice == 4)
		{
			printAll(head);
		}
		else
		{
			exit(1);
		}
	}
}