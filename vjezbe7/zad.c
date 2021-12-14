#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50

struct dir;
typedef struct dir* poz;
struct dir
{
    char ime[N];
    poz sibling;
    poz child;
};

struct stog;
typedef struct stog* stpoz;
struct stog
{
    poz data;
    stpoz next;
};

poz dodajDir(poz current, poz p);
void print(poz p);
poz trazi(poz p, char* dirIme, char* trenutni, int n, stpoz red);
void brisi(poz p);
stpoz push(stpoz red, poz p);
poz pop(stpoz red);
stpoz popStog(stpoz red);


int main(void)
{
    struct dir C;
    struct stog head = {.data = &C, .next = NULL};
    char naredba[10], dirIme[N], trenutni[100];
    poz q, current = &C;
    stpoz currentStog = &head, h;
    int n = 0, i;

    strcpy(trenutni, "");

    strcpy(C.ime, "C:");
    C.sibling = NULL;
    C.child = NULL;


    while(1)
    {
        printf("%s%s", C.ime, trenutni);
        scanf("%s", naredba);
        if(strcmp(naredba, "md") == 0)
        {
            scanf("%s", dirIme);
            q = (poz)malloc(sizeof(struct dir));
            strcpy(q->ime, dirIme);
            q->sibling = NULL;
            q->child = NULL;
            current->child = dodajDir(current->child, q);
        }
        else if(strcmp(naredba, "cd") == 0)
        {
            scanf("%s", dirIme);
            n = strlen(trenutni);
            current = trazi(current, dirIme, trenutni, n, currentStog);
            currentStog = push(currentStog, current);
        }
        else if(strcmp(naredba, "cd..") == 0)
        {
            //printf("*%s*", currentStog->data->ime);
            if(current != &C)
            {
                currentStog = popStog(currentStog);
                current = pop(currentStog);
            }
            for(i = strlen(trenutni) - 2; i >= 0; i--)
            {
                if(trenutni[i] == ':')
                    break;
                trenutni[i] = '\0';
            }
        }
        else if(strcmp(naredba, "dir") == 0)
        {
            print(current->child);
        }
        else if(strcmp(naredba, "exit") == 0)
        {
            brisi(&C);
            return 0;
        }
        else
        {
            printf("Naredba nije pronadena!\n");
        }
    }

    return 0;
}

poz dodajDir(poz current, poz p)
{
    if(current == NULL)
        return p;
    if(strcmp(current->ime, p->ime) > 0)
    {
        p->sibling = current;
        return p;
    }
    else if(strcmp(current->ime, p->ime) < 0)
        current->sibling = dodajDir(current->sibling, p);
    else
    {
        printf("Vec postoji ta datoteka");
        free(p);
    }
    return current;
}

void print(poz p)
{
    if(p == NULL)
        printf("Nema nijednog direktorija\n");
    while(p != NULL)
    {
        printf(" %s\n", p->ime);
        p = p->sibling;
    }
}

poz trazi(poz p, char* dirIme, char* trenutni, int n, stpoz red)
{
    int i;
    poz c = p;
    p = p->child;
    while(p != NULL)
    {
        if(strcmp(p->ime, dirIme) == 0)
        {
            for(i = 0; i < strlen(dirIme); i++)
                trenutni[n + i] = dirIme[i];
            trenutni[n + i] = ':';
            trenutni[n + 1 + i] = '\0';
            red = push(red, p);
            return p;
        }
        p = p->sibling;
    }
    if(p == NULL)
    {
        printf("Nije pronaden direktorij\n");
        return c;
    }
    return c;
}

void brisi(poz p)
{
    if(!p)
        return;
    brisi(p->sibling);
    brisi(p->child);
    free(p);
}

stpoz push(stpoz red, poz p)
{
    stpoz q;
    q = (stpoz)malloc(sizeof(struct stog));
    q->data = p;
    q->next = red;
    return q;
}

poz pop(stpoz red)
{
    poz q;
    q = red->data;
    return q;
}

stpoz popStog(stpoz red)
{
    stpoz q = red->next;
    return q;
}
