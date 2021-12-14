#include<stdio.h>
#include<stdlib.h>

struct stablo;
typedef struct stablo* poz;
struct stablo
{
    int el;
    poz l;
    poz d;
};

void ispisOrder(poz current);
void ispisPostorder(poz current);
void ispisPreorder(poz current);
poz unos(poz current, int x);
poz brisi(poz current, int x);
poz traziNajmanji(poz current);
poz traziNajveci(poz current);
poz trazi(poz current, int x);

int main(void)
{
    poz root = NULL;
    int n = 0, i = 0, x = 0;

    printf("Unesite broj elemenata stabla: ");
    scanf("%d", &n);
    printf("Unesite elemente:\n");
    for(i = 0; i < n; i++)
    {
        scanf("%d", &x);
        root = unos(root, x);
    }
    printf("\nIspis inorder:\n");
    ispisOrder(root);
    printf("\nIspis postorder:\n");
    ispisPostorder(root);
    printf("\nIspis preorder:\n");
    ispisPreorder(root);

    printf("\nUnesite clanove koje zelite izbrisati(ili 0 za kraj)\n");
    while(1)
    {
        scanf("%d", &x);
        if(x == 0)
            break;
        root = brisi(root, x);
        ispisOrder(root);
        printf("\n");
        if(root == NULL)
            break;
    }

    ispisOrder(root);



    return 0;
}
void ispisOrder(poz current)
{
    if(current == NULL)
        return;
    ispisOrder(current->l);
    printf("%d ", current->el);
    ispisOrder(current->d);
    return;
}

poz unos(poz current, int x)
{
    poz q = NULL;
    if(current == NULL)
    {
        q = (poz)malloc(sizeof(struct stablo));
        q->el = x;
        q->l = NULL;
        q->d = NULL;
        return q;
    }
    else if(x < current->el)
        current->l = unos(current->l, x);
    else if(x > current->el)
        current->d = unos(current->d, x);
    return current;
}

poz brisi(poz current, int x)
{
    poz t = NULL;
    if(current == NULL)
        printf("Nema tog elementa!\n");
    else if(x < current->el)
        current->l = brisi(current->l, x);
    else if(x > current->el)
        current->d = brisi(current->d, x);
    else if(current->l != NULL && current->d != NULL)
    {
        t = traziNajmanji(current->d);
        current->el = t->el;
        current->d = brisi(current->d, current->el);
    }
    else
    {
        t = current;
        if(current->l == NULL)
            current = current->d;
        else
            current = current->l;
        free(t);
    }
    return current;
}

poz traziNajmanji(poz current)
{
    while(current->l != NULL)
        current = current->l;
    return current;
}

poz traziNajveci(poz current)
{
    while(current->d != NULL)
        current = current->d;
    return current;
}

void ispisPostorder(poz current)
{
    if(current == NULL)
        return;
    ispisPostorder(current->l);
    ispisPostorder(current->d);
    printf("%d ", current->el);
}

void ispisPreorder(poz current)
{
    if(current == NULL)
        return;
    printf("%d ", current->el);
    ispisPreorder(current->l);
    ispisPreorder(current->d);
}

poz trazi(poz current, int x)
{
    if(current == NULL)
        return NULL;
    else if(x < current->el)
        return trazi(current->l, x);
    else if(x > current->el)
        return trazi(current->d, x);
    return current;
}
