#include <stdio.h>
#include <stdlib.h>
#pragma warning (disable: 4996)
void printingFile(int *idr, char *typer, double *arear, double *pricer, char **adresr, int counter);
int main()
{
	FILE *fp;
	if (!(fp = fopen("DoublePointer.bin", "ab")))
	{
		printf("Error why opening the file!");
	}
	int id = 1;
	if (fwrite(&id, sizeof(int), 1, fp) != 1)
	{
		printf("error while writing id");
	}
	char type = 'H';
	if (fwrite(&type, 1, 1, fp) != 1)
	{
		printf("error while writing type");
		
	}
	double area = 123.6;
	if (fwrite(&area, 8, 1, fp) != 1)
	{
		printf("error while writing area");
		
	}
	double price = 600;
	if (fwrite(&price, 8, 1, fp) != 1)
	{
		printf("error while writing price");
		
	}
	int len = 7;
	if (fwrite(&len, sizeof(int), 1, fp) != 1)
	{
		printf("error while writing len");
		
	}
	char adres[50] = { "mladost" };
	if (fwrite(adres, 1, len, fp) != len)
	{
		printf("error while writing adres");
		
	}
	fclose(fp);
	if (!(fp = fopen("DoublePointer.bin", "rb")))
	{
		printf("Error why readint the file the file!");
		
	}
	int counter = 0;
	int *idr;
	char *typer;
	double *arear;
	double *pricer;
	int lenr=0;
	char **adresr;
	idr = malloc(sizeof(int) * 5);
	typer = malloc(1 * 5);
	arear= malloc(8 * 5);
	pricer = malloc(8 * 5);
	adresr = malloc(sizeof(int) * 5);
	int i=0;
	for (i; i < 5; i++)
	{
		adresr[i] = (char*)malloc(20);
	}
	
	while (1)
	{
		if (fread(&idr[counter], sizeof(int), 1, fp) != 1)
		{
			printf("error while reading idr!");
			break;
		}
		if (fread(&typer[counter], 1, 1, fp) != 1)
		{
			printf("error while reading typer!");
			break;
		}
		if (fread(&arear[counter], 8, 1, fp) != 1)
		{
			printf("error while reading arear!");
			break;
		}
		if (fread(&pricer[counter], 8, 1, fp) != 1)
		{
			printf("error while reading pricer!");
			break;
		}
		if (fread(&lenr, sizeof(int), 1, fp) != 1)
		{
			printf("error while reading len!");
			break;
		}
		if (fread(adresr[counter], 1, len, fp) != len)
		{
			printf("error while reading idr!");
			break;
		}
		counter++;
	}
	printingFile(idr, typer, arear, pricer, adresr,counter);

}
void printingFile(int *idr, char *typer, double *arear, double *pricer, char **adresr,int counter)
{
	int i = 0;
	for (i; i < counter; i++)
	{
		printf("%d. ", idr[i]);
		double price = arear[i] * pricer[i];
		printf("%lf ", price);
		printf("%s. ", adresr[i]);
	}

}