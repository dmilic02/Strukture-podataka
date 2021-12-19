#include<stdio.h>
#include<stdlib.h>
#include<time.h>

struct cvor;
typedef struct cvor* poz;
struct cvor
{
    int el;
    poz l;
    poz d;
};

struct lista;
typedef struct lista* lpoz;
struct lista
{
    int el;
    lpoz next;
};

poz insert(poz p, int x);
void print(poz p, lpoz h);
int replace(poz p);
void dodajUListu(lpoz p, int x);
void upisiUDatoteku(FILE* f, lpoz p);


int main(void)
{
/*
    poz root;
    int a[] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
    int i;

    root->el = a[0];
    root->l = NULL;
    root->d = NULL;

    for(i = 1; i < 10; i++)
        root = insert(root, a[i]);
    print(root);
*/
    srand(time(NULL));
    poz root;
    int i, x;
    FILE* f;
    struct lista head = {.el = 0, .next = NULL};

    root = (poz)malloc(sizeof(struct cvor));
    root->el = rand() % 80 + 10;
    root->l = NULL;
    root->d = NULL;
    printf("%d ", root->el);

    for(i = 1; i < 10; i++)
    {
        x = rand() % 80 + 10;
        printf("%d ", x);
        root = insert(root, x);
    }
    printf("\n");

    print(root, &head);
    upisiUDatoteku(f, head.next);

    root->el = replace(root->l) + replace(root->d);

    printf("\n");
    print(root, &head);

    upisiUDatoteku(f, head.next);

    return 0;
}

poz insert(poz p, int x)
{
    poz q;
    if(p == NULL)
    {
        q = (poz)malloc(sizeof(struct cvor));
        q->el = x;
        q->l = NULL;
        q->d = NULL;
        return q;
    }
    if(x >= p->el)
        p->d = insert(p->d, x);
    if(x < p->el)
        p->l = insert(p->l, x);
    return p;
}

void print(poz p, lpoz h)
{
    if(p == NULL)
        return;
    print(p->d, h);
    printf("%d ", p->el);
    dodajUListu(h ,p->el);
    print(p->l, h);
}

int replace(poz p)
{
    int t;
    if(p == NULL)
        return 0;
    t = p->el;
    p->el = replace(p->l) + replace(p->d);
    return t + p->el;
}

void dodajUListu(lpoz p, int x)
{
    lpoz q;
    while(p != NULL)
    {
        if(p->next == NULL)
        {
            q = (lpoz)malloc(sizeof(struct lista));
            q->el = x;
            p->next = q;
            q->next = NULL;
            return;
        }
        p = p->next;
    }
}

void upisiUDatoteku(FILE* f, lpoz p)
{
    f = fopen("stablo", "w");
    while(p != NULL)
    {
        fprintf(f, "%d ", p->el);
        p = p->next;
    }
    fprintf(f, "\n");
    fclose(f);
}

