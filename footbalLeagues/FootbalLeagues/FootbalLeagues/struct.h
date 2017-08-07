#pragma once

typedef struct League {
	char Countryname[50];
	double coeficient;
	int numberOfProTeams;
	int tvAuditory;
	int averageAudition;
	struct League*next;
}League;
void addingNewLeague();
void menu();
League *GetList();
void showAll(League*head);
void LowestCoeficient(League*head);
League *modify(League*head);

