#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
typedef struct
{
	long long int nomenclature;
	char  model[20];
	char manifacturer[20];
	float price;
	int prodYear;
	struct NODE* next;
}Node;
Node* head = NULL;
Node* temp = NULL;
Node* rear = NULL;
void Enqueue();
int maxPrice();
void Delete();
void Print();
void changePrice();


int main() {
	float maxP;
	int i, selector;
	printf("1.Add a TV\n");
	printf("2.Find the most expensive TV manifactured after 2007\n");
	printf("3.Delete TV`s by brand\n");
	printf("4.Change the price of a TV\n");
	printf("5.Print all the TV`s\n");
	printf("6.Exit\n");
	while (1)
	{
		printf("choose option:");
		scanf("%d", &selector);
		fflush(stdin);
		switch (selector)
		{
		case 1:Enqueue(); break;
		case 2:maxP = maxPrice(); break;
		case 3:Delete(); break;
		case 4:changePrice(); break;
		case 5:Print(); break;
		case 6:return 0;
		}
	}
}

void Enqueue()
{
	Node* temp =
		(Node*)malloc(sizeof(Node));
	printf("Enter Nomenclature(12 sign long number): ");
	scanf("%d", &temp->nomenclature);
	fflush(stdin);
	printf("Enter model of the TV: ");
	scanf("%s", temp->model);
	fflush(stdin);
	printf("Enter the brand of the manifacturer: ");
	scanf("%s", temp->manifacturer);
	fflush(stdin);
	printf("Enter year of manifacturing: ");
	scanf("%d", &temp->prodYear);
	fflush(stdin);
	printf("Enter the price: ");
	scanf("%f", &temp->price);
	fflush(stdin);
	temp->next = NULL;
	if (head == NULL && rear == NULL) {
		head = rear = temp;
		return;
	}
	rear->next = (Node*)temp;
	rear = temp;
}
int maxPrice()
{
	float  max = 0;
	Node* temp = head;
	while (temp != NULL) {
		if (temp->prodYear>2007)
		{
			if (temp->price>max)
			{
				max = temp->price;
			}
		}
		temp = (Node*)temp->next;
	}
	printf("%.2f is the maximum price of a TV\n", max);
	return max;
}
void Print()
{

	Node* temp = head;
	while (temp != NULL) {
		printf("%d ", temp->nomenclature);
		printf("%s ", temp->model);
		printf("%s ", temp->manifacturer);
		printf("%d ", temp->prodYear);
		printf("%f ", temp->price);
		temp = (Node*)temp->next;
	}
	printf("\n");
}

void Delete()
{
	Node* temp = NULL;
	Node* prev = NULL;
	Node* current = head;
	char delBrand[20];
	printf("enter brand to delete by: ");
	scanf("%s", delBrand);
	fflush(stdin);
	while (temp != NULL)
	{
		if (strcmp(temp->manifacturer, delBrand))//delete in front
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
		prev = current;
		current = current->next;
		}
	}

void changePrice()
{
	temp = head;
	long long int criteria;
	printf("select the id to change price by: ");
	scanf("%d", &criteria);
	fflush(stdin);
	while (temp != NULL)
	{
		if (criteria == temp->nomenclature)
		{
			printf("enter new price for the TV: ");
			scanf("%f", &temp->price);
			fflush(stdin);
			temp = (Node*)temp->next;
		}
		else
		{
			temp = (Node*)temp->next;
		}
	}
}

