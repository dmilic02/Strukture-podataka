#include<stdio.h>
#include<stdlib.h>
#define duljinaReda 128
#define najduza 1024

typedef struct{
    char ime[duljinaReda];
    char prezime[duljinaReda];
    double bodovi;
} student;

int brojRedaka(char* nazivDatoteke)
{
    int br = 0;
    FILE* datoteka = NULL;
    char buffer[najduza] = {0};

    datoteka = fopen(nazivDatoteke, "r");
    if(datoteka == NULL)
        return -1;

    while(!feof(datoteka))
    {
        fgets(buffer, najduza, datoteka);
        br++;
    }
    fclose(datoteka);
    return br;
}

student* alociraj(int br, char* nazivDatoteke)
{
    int i = 0;
    FILE* datoteka = NULL;
    student* s = NULL;

    s = (student*)malloc(br * sizeof(student));
    datoteka = fopen(nazivDatoteke, "r");
    if(datoteka == NULL)
    {
        printf("Greska pri alociranju"),
        free(s);
        return NULL;
    }
    while(!feof(datoteka))
    {
        fscanf(datoteka, " %s %s %lf", s[i].ime, s[i].prezime, &s[i].bodovi);
        i++;
    }

    fclose(datoteka);
    return s;
}



int main(void)
{
    FILE* f = NULL;
    int i, br;
    student *s = NULL;
    double max = 0;

    br = brojRedaka("studenti.txt");
    //printf("%d", br);
    s = alociraj(br, "studenti.txt");

    for(i = 0; i < br; i++)
        if(s[i].bodovi > max)
            max = s[i].bodovi;

    for(i = 0; i < br; i++)
        printf("%-20s %-20s %lf  %lf\n", s[i].ime, s[i].prezime, s[i].bodovi, s[i].bodovi/max*100);


    return 0;
}
