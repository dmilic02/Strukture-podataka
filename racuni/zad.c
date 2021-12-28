#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct artikal;
typedef struct artikal* pok;
struct artikal
{
    char ime[20];
    int kolicina;
    double cijena;
    pok next;
};

struct racun;
typedef struct racun* poz;
struct racun
{
    char ime[20];
    char datum[10];
    pok h;
    poz next;
};

int dodajRacun(poz p, char* ime, char* datum);
int usporediDatume(char* t1, char* t2);
int printRacune(poz p);
int dodajArtikle(poz p);
int artikalNaKraj(pok p, char* ime, int kol, double cijena);
int printArtikle(pok p);
int trazi(poz p, char* ime, char* d1, char* d2);
pok traziArtikal(pok p, char* ime);
char dat1[10];
char dat2[10];

int main(void)
{
    FILE* f = NULL;
    FILE* fRacun = NULL;
    char imeRacuna[20];
    char racunZaOtvaranje[20];
    char datum[10];
    struct racun head = {.ime = "", .datum = "", .h = NULL, .next = NULL};

    f = fopen("racuni.txt", "r");
    while(!feof(f))
    {
        fRacun = NULL;
        fscanf(f, "%s", imeRacuna);
        strcpy(racunZaOtvaranje, imeRacuna);
        fRacun = fopen(racunZaOtvaranje, "r");
        if(fRacun == NULL)
        {
            perror("Greska pri otvaranju datoteke!\n");
            return -1;
        }
        fscanf(fRacun, "%s", datum);
        fclose(fRacun);
        dodajRacun(&head, imeRacuna, datum);
    }
    fclose(f);

    dodajArtikle(head.next);
    printRacune(head.next);

    printf("Koji artikal zelite provjeriti: ");
    scanf("%s", imeRacuna);
    printf("Koje vremensko razdoblje zelite pregledati(DD-MM-YYYY DD-MM-YYYY): ");
    scanf("%s %s", dat1, dat2);
    trazi(head.next, imeRacuna, dat1, dat2);


    return 0;
}

int dodajRacun(poz p, char* ime, char* datum)
{
    pok art = NULL;
    poz q = NULL;
    poz prev = NULL;
    q = (poz)malloc(sizeof(struct racun));
    if(q == NULL)
    {
        perror("Greska pri alokaciji!\n");
        return -1;
    }
    strcpy(q->ime, ime);
    strcpy(q->datum, datum);
    art = (pok)malloc(sizeof(struct artikal));
    if(art == NULL)
    {
        perror("Greska pri alokaciji!\n");
        return -1;
    }
    strcpy(art->ime, "");
    art->cijena = 0;
    art->kolicina = 0;
    art->next = NULL;
    q->h = art;

    prev = p;
    while(p != NULL)
    {
        if(p->next == NULL)
        {
            p->next = q;
            q->next = NULL;
            break;
        }
        if(usporediDatume(q->datum, prev->next->datum) == 1)
        {
            q->next = prev->next;
            prev->next = q;
            break;
        }
        prev = p;
        p = p->next;
    }

    return 0;
}

int usporediDatume(char* t1, char* t2)
{
    int d1 = 0;
    int d2 = 0;

    d1 = (int)t1[6] * 1000 + (int)t1[7] * 100 + (int)t1[8] * 10 + (int)t1[9];
    d2 = (int)t2[6] * 1000 + (int)t2[7] * 100 + (int)t2[8] * 10 + (int)t2[9];
    if(d1 > d2)
        return 1;
    if(d1 < d2)
        return -1;

    d1 = 0;
    d2 = 0;
    d1 = (int)t1[3] * 10 + (int)t1[4];
    d2 = (int)t2[3] * 10 + (int)t2[4];
    if(d1 > d2)
        return 1;
    if(d1 < d2)
        return -1;

    d1 = 0;
    d2 = 0;
    d1 = (int)t1[0] * 10 + (int)t1[1];
    d2 = (int)t2[0] * 10 + (int)t2[1];
    if(d1 > d2)
        return 1;
    if(d1 < d2)
        return -1;

    return 1;
}

int printRacune(poz p)
{
    pok q = NULL;
    q = p->h;
    printf("Lista racuna:\n");
    while(p != NULL)
    {
        printf("%s %s\n", p->ime, p->datum);
        printArtikle(p->h->next);
        p = p->next;
    }
    return 0;
}

int dodajArtikle(poz p)
{
    FILE* f = NULL;
    char red[20];
    int kol = 0;
    double cijena = 0;

    while(p != NULL)
    {
        f = fopen(p->ime, "r");
        if(f == NULL)
        {
            perror("Greska pri otvaranju datoteke!\n");
            return -1;
        }
        fgets(red, 1024, f);
        while(!feof(f))
        {
            fscanf(f, "%s %d %lf", red, &kol, &cijena);
            artikalNaKraj(p->h, red, kol, cijena);
        }
        p = p->next;
        fclose(f);
    }
    return 0;
}

int artikalNaKraj(pok p, char* ime, int kol, double cijena)
{
    pok q = NULL;
    q = (pok)malloc(sizeof(struct artikal));
    if(q == NULL)
    {
        perror("Greska pri alokaciji!\n");
        return -1;
    }
    strcpy(q->ime, ime);
    q->kolicina = kol;
    q->cijena = cijena;
    if(p == NULL)
    {
        p = q;
        q->next = NULL;
        return 0;
    }
    while(p->next != NULL)
        p = p->next;

    p->next = q;
    q->next = NULL;
    return 0;
}

int printArtikle(pok p)
{
    while(p != NULL)
    {
        printf("\t%s %d %.2lf\n", p->ime, p->kolicina, p->cijena);
        p = p->next;
    }
    return 0;
}

int trazi(poz p, char* ime, char* d1, char* d2)
{
    pok t = NULL;
    int flag = 0;
    int kol = 0;
    double cijena = 0;
    while(p != NULL)
    {
        if(usporediDatume(p->datum, d1) >= 0 && usporediDatume(p->datum, d2) <= 0)
        {
            t = NULL;
            t = traziArtikal(p->h->next, ime);
            if(t != NULL)
            {
                flag = 1;
                cijena = t->cijena;
                kol += t->kolicina;
            }
        }
        p = p->next;
    }
    cijena = cijena * kol;
    if(flag == 0)
        printf("Nema trazenog artikla!\n");
    else
        printf("Trazeni element: %s %d %.2lf\n", ime, kol, cijena);

    return 0;
}

pok traziArtikal(pok p, char* ime)
{
    while(p != NULL)
    {
        if(strcmp(p->ime, ime) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}








