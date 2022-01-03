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
    pok next;
};

struct drzave;
typedef struct drzave* poz;
struct drzave
{
    char ime[20];
    pok grad;
    poz d;
    poz l;
};

poz dodajDrzavu(poz p, char* imeDrzave, char* datGrad);
int dodajGradove(pok p, char* datGrad);
int printDrzaveInorder(poz p);
int printGradove(pok p);
int usporediGradove(pok p, pok q);
int trazi(poz p, char* imeDrzave, int stanovnici);
poz traziDrzavu(poz p, char* imeDrzave);

int main(void)
{
    poz root = NULL;
    FILE* f = NULL;
    char imeDrzave[20];
    char datGrad[20];
    int stanovnici = 0;

    f = fopen("drzave.txt", "r");
    if(f == NULL)
    {
        perror("Greska pri otvaranju datoteke!\n");
        return 0;
    }

    while(!feof(f))
    {
        fscanf(f, "%s %s", imeDrzave, datGrad);
        root = dodajDrzavu(root, imeDrzave, datGrad);
    }
    fclose(f);
    printDrzaveInorder(root);

    printf("Unesite drzavu koju zelite pregledati: ");
    scanf("%s", imeDrzave);
    printf("Minimalan broj stanovnika po gradu: ");
    scanf("%d", &stanovnici);
    trazi(root, imeDrzave, stanovnici);

    return 0;
}

int printDrzaveInorder(poz p)
{
    if(p == NULL)
        return 0;
    printDrzaveInorder(p->l);
    printf("%s\n", p->ime);
    printGradove(p->grad->next);
    printDrzaveInorder(p->d);
    return 0;
}

int printGradove(pok p)
{
    while(p != NULL)
    {
        printf("\t%s %d\n", p->ime, p->stanovnici);
        p = p->next;
    }
    return 0;
}

poz dodajDrzavu(poz p, char* imeDrzave, char* datGrad)
{
    poz q = NULL;
    pok h = NULL;
    if(p == NULL)
    {
        q = (poz)malloc(sizeof(struct drzave));
        if(q == NULL)
        {
            perror("Greska pri alokaciji!\n");
            return NULL;
        }
        strcpy(q->ime, imeDrzave);

        h = (pok)malloc(sizeof(struct gradovi));
        if(q == NULL)
        {
            perror("Greska pri alokaciji!\n");
            return NULL;
        }
        strcpy(h->ime, "");
        h->stanovnici = 0;
        h->next = NULL;
        q->grad = h;

        dodajGradove(q->grad, datGrad);
        q->l = NULL;
        q->d = NULL;

        return q;
    }
    else if(strcmp(p->ime, imeDrzave) > 0)
        p->l = dodajDrzavu(p->l, imeDrzave, datGrad);
    else if(strcmp(p->ime, imeDrzave) < 0)
        p->d = dodajDrzavu(p->d, imeDrzave, datGrad);
    return p;
}

int dodajGradove(pok p, char* datGrad)
{
    pok q = NULL;
    FILE* f = NULL;
    char ime[20];
    int stan = 0;
    pok prev = p;
    pok poc = p;

    f = fopen(datGrad, "r");
    if(f == NULL)
    {
        perror("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    while(!feof(f))
    {
        prev = poc;
        p = poc;
        fscanf(f, "%s %d", ime, &stan);
        q = (pok)malloc(sizeof(struct gradovi));
        if(q == NULL)
        {
            perror("Greska pri alokaciji!\n");
            return -1;
        }
        strcpy(q->ime, ime);
        q->stanovnici = stan;
        while(p != NULL)
        {
            if(p->next == NULL)
            {
                q->next = p->next;
                p->next = q;
                break;
            }
            if(usporediGradove(q, prev->next) == 1)
            {
                q->next = prev->next;
                prev->next = q;
                break;
            }
            prev = p;
            p = p->next;
        }
    }
    fclose(f);
    return 0;
}

int usporediGradove(pok p, pok q)
{
    if(p->stanovnici > q->stanovnici)
        return 1;
    else if(p->stanovnici < q->stanovnici)
        return -1;
    else
    {
        if(strcmp(p->ime, q->ime) > 0)
            return 1;
        else if(strcmp(p->ime, q->ime) < 0)
            return -1;
    }
    return 0;
}

int trazi(poz p, char* imeDrzave, int stanovnici)
{
    poz drzava = NULL;
    pok h = NULL;
    int x = 0;

    drzava = traziDrzavu(p, imeDrzave);
    if(drzava == NULL)
    {
        printf("Nema te drzave!\n");
        return 0;
    }
    h = drzava->grad;

    if(h == NULL)
    {
        printf("Nema nijedan grad u toj drzavi!\n");
        return 0;
    }
    h = h->next;
    while(h != NULL)
    {
        if(h->stanovnici >= stanovnici)
        {
            printf("\t%s\n", h->ime);
            x = 1;
        }
        else
            break;
        h = h->next;
    }
    if(x == 0)
        printf("Nema nijedan takav grad!\n");

    return 0;
}

poz traziDrzavu(poz p, char* imeDrzave)
{
    if(p == NULL)
        return NULL;
    if(strcmp(imeDrzave, p->ime) == 0)
        return p;
    if(strcmp(imeDrzave, p->ime) < 0)
        return traziDrzavu(p->l, imeDrzave);
    if(strcmp(imeDrzave, p->ime) > 0)
        return traziDrzavu(p->d, imeDrzave);
}





