#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct gradovi;
typedef struct gradovi* pok;
struct gradovi
{
    char ime[20];
    int stanovnici;
    pok d;
    pok l;
};

struct drzave;
typedef struct drzave* poz;
struct drzave
{
    char ime[20];
    pok grad;
    poz next;
};

int dodajDrzavu(poz p, char* ime, char* dat);
int dodajGrad(pok p, char* dat);
pok unosGrada(pok p, char* ime, int stan);
int printDrzave(poz p);
int printGradove(pok p);
poz traziDrzavu(poz p, char* ime);
int traziGrad(pok p, int broj);

int main(void)
{
    struct drzave head = {.ime = "", .grad = NULL, .next = NULL};
    FILE* f = NULL;
    char imeDrzave[20];
    char datGrad[20];
    poz p = NULL;
    int broj = 0;
    pok h = NULL;

    f = fopen("drzave.txt", "r");
    if(f == NULL)
    {
        perror("Greska pri otvaranju datoteke!\n");
        return -1;
    }
    while(!feof(f))
    {
        fscanf(f, "%s %s", imeDrzave, datGrad);
        dodajDrzavu(&head, imeDrzave, datGrad);
    }
    fclose(f);
    printDrzave(head.next);

    printf("\nUnesite ime drzavu koju zelite pregledati: ");
    scanf("%s", imeDrzave);
    p = traziDrzavu(head.next, imeDrzave);
    if(p == NULL)
    {
        printf("Nema te drzave!\n");
        return 0;
    }
    printf("Minimalan broj stanovnika: ");
    scanf("%d", &broj);
    printf("Gradovi te drzave (%s) sa vise od %d stanovnika:\n", p->ime, broj);
    traziGrad(p->grad, broj);

    return 0;
}

int dodajDrzavu(poz p, char* ime, char* dat)
{
    poz q = NULL;
    poz prev = NULL;
    pok h = NULL;
    q = (poz)malloc(sizeof(struct drzave));
    if(q == NULL)
    {
        perror("Greska pri alokaciji!\n");
        return -1;
    }
    strcpy(q->ime, ime);
    q->grad = h;

    h = (pok)malloc(sizeof(struct gradovi));
    if(h == NULL)
    {
        perror("Greska pri alokaciji!\n");
        return -1;
    }
    strcpy(h->ime, "");
    h->stanovnici = 0;
    h->d = NULL;
    h->l = NULL;
    q->grad = h;
    dodajGrad(q->grad, dat);

    prev = p;
    while(p != NULL)
    {
        if(p->next == NULL)
        {
            p->next = q;
            q->next = NULL;
            break;
        }
        if(strcmp(q->ime, prev->next->ime) < 0)
        {
            q->next = prev->next;
            prev->next = q;
            break;
        }
        p = p->next;
    }
    return 0;
}

int dodajGrad(pok p, char* dat)
{
    FILE* f = NULL;
    char ime[20];
    int stan = 0;

    f = fopen(dat, "r");
    if(f == NULL)
    {
        perror("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    while(!feof(f))
    {
        fscanf(f, "%s %d", ime, &stan);
        p = unosGrada(p, ime, stan);
    }
    fclose(f);
    return 0;
}

pok unosGrada(pok p, char* ime, int stan)
{
    pok q = NULL;
    if(p == NULL)
    {
        q = (pok)malloc(sizeof(struct gradovi));
        if(q == NULL)
        {
            perror("Greska pri alociranju!\n");
            return NULL;
        }
        strcpy(q->ime, ime);
        q->stanovnici = stan;
        q->l = NULL;
        q->d = NULL;
        return q;
    }
    if(stan >= p->stanovnici)
        p->d = unosGrada(p->d, ime, stan);
    if(stan < p->stanovnici)
        p->l = unosGrada(p->l, ime, stan);

    return p;
}

int printDrzave(poz p)
{
    printf("Lista drzava:\n");
    while(p != NULL)
    {
        printf("\t%s\n", p->ime);
        printGradove(p->grad->d);
        p = p->next;
    }
    return 0;
}

int printGradove(pok p)
{
    if(p == NULL)
        return 0;
    printGradove(p->l);
    printf("\t\t%s\n", p->ime);
    printGradove(p->d);
    return 0;
}

poz traziDrzavu(poz p, char* ime)
{
    while(p != NULL)
    {
        if(strcmp(p->ime, ime) == 0)
            return p;
        p = p->next;
    }
    return p;
}

int traziGrad(pok p, int broj)
{
    if(p == NULL)
        return 0;
    traziGrad(p->l, broj);
    if(p->stanovnici >= broj)
        printf("\t%s %d\n", p->ime, p->stanovnici);
    traziGrad(p->d, broj);
    return 0;
}














