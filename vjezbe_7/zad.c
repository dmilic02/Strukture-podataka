#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct direktorij;
typedef struct direktorij* poz;
struct direktorij
{
    char ime[50];
    poz sibling;
    poz child;
};

struct stog;
typedef struct stog* pos;
struct stog
{
    poz el;
    pos next;
};

int ispis(pos p);
int napraviDirektorij(char* ime, poz p);
poz cd(char* ime, poz p);
int izlistajDirektorije(poz p);
int pushStog(poz p, pos s);
pos popStog(pos p);
int brisiSve(poz p, pos s);

int main(void)
{
    struct direktorij head = {.ime = "C", .sibling = NULL, .child = NULL};
    pos trenutni = NULL;
    poz trenutniDir = NULL;
    poz provjera = NULL;
    pos zamjena = NULL;
    char naredba[20];
    char imeNovi[50];

    trenutniDir = &head;
    trenutni = (pos)malloc(sizeof(struct stog));
    if(trenutni == NULL)
    {
        perror("Greska pri alokaciji memorije!\n");
        return -1;
    }
    trenutni->el = &head;
    trenutni->next = NULL;

    while(1)
    {
        ispis(trenutni);
        scanf("%s", naredba);
        if(strcmp(naredba, "exit") == 0)
        {
            break;
        }
        else if(strcmp(naredba, "md") == 0)
        {
            scanf("%s", imeNovi);
            napraviDirektorij(imeNovi, trenutniDir);
        }
        else if(strcmp(naredba, "cd") == 0)
        {
            scanf("%s", imeNovi);
            provjera = trenutniDir;
            trenutniDir = cd(imeNovi, trenutniDir);
            if(provjera != trenutniDir)
                pushStog(trenutniDir, trenutni);
        }
        else if(strcmp(naredba, "dir") == 0)
        {
            izlistajDirektorije(trenutniDir);
        }
        else if(strcmp(naredba, "cd..") == 0)
        {
            if(trenutniDir == &head)
                continue;
            zamjena = popStog(trenutni);
            trenutniDir = zamjena->el;
        }
        else
        {
            printf("Ne postoji ta naredba!\n");
        }
    }



    return 0;
}

int ispis(pos p)
{
    while(p != NULL)
    {
        printf("%s:", p->el->ime);
        p = p->next;
    }
    return 0;
}

int napraviDirektorij(char* ime, poz p)
{
    poz q = NULL;
    q = (poz)malloc(sizeof(struct direktorij));
    if(q == NULL)
    {
        perror("Greska pri alokaciji memorije!\n");
        return -1;
    }
    strcpy(q->ime, ime);
    q->child = NULL;
    q->sibling = NULL;

    if(p->child == NULL)
    {
        p->child = q;
        return 0;
    }

    p = p->child;
    while(p != NULL)
    {
        if(strcmp(ime, p->ime) == 0)
        {
            printf("Vec postoji direktorij s tim imenom!\n");
            return 0;
        }
        if(p->sibling == NULL)
        {
            p->sibling = q;
            break;
        }
        p = p->sibling;
    }
    return 0;
}

poz cd(char* ime, poz p)
{
    poz q = p;
    p = p->child;
    while(p != NULL)
    {
        if(strcmp(p->ime, ime) == 0)
            return p;
        p = p->sibling;
    }
    if(p == NULL)
    {
        printf("Nema tog direktorija!\n");
        return q;
    }
}

int izlistajDirektorije(poz p)
{
    p = p->child;
    if(p == NULL)
    {
        printf("Nema nijednog direktorija!\n");
        return 0;
    }
    while(p != NULL)
    {
        printf("\t%s\n", p->ime);
        p = p->sibling;
    }
    return 0;
}

int pushStog(poz p, pos s)
{
    pos q = NULL;
    q = (pos)malloc(sizeof(struct stog));
    if(q == NULL)
    {
        perror("Greska pri alokaciji memorije!\n");
        return -1;
    }
    q->el = p;

    while(s->next != NULL)
        s = s->next;
    q->next = s->next;
    s->next = q;
    return 0;
}

pos popStog(pos p)
{
    pos prev = p;
    pos t = NULL;
    while(p->next != NULL)
    {
        prev = p;
        p = p->next;
    }
    t = p;
    prev->next = NULL;
    free(t);
    return prev;
}

int brisiSve(poz p, pos s)
{
    pos q = NULL;
    poz t = NULL;

    while(s != NULL)
    {
        q = s;
        s = s->next;
        free(q);
    }

    while(p != NULL)
    {
        while(p->sibling != NULL)
        {
            t = p;
            p = p->sibling;
            free(t);
        }
        p = p->child;
    }
    return 0;
}









