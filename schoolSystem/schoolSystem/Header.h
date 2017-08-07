#pragma once
typedef struct School {
	char name[50];
	int number;
	double size;
	int numberStudents;
	char director[30];
	struct School*next;
}School;
void addingNewLeague(School*head);
void menu();
School *GetList();
void showAll(School*head);
School *modify(School*head);
void showAllByStudents(School*head);
