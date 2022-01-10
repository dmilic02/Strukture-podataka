#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct stog;
typedef struct stog* poz;
struct stog
{
    int el;
    poz next;
};

int push(int x, poz p);
int pop(poz p);
int print(poz p);
int op(poz p, char operacija);

int main(void)
{
    FILE* f;
    struct stog head = {.el = 0, .next = NULL};
    int el = '+';
    int br = 0;
    int status = 0;
    char buffer[1024];
    char operacija = ' ';
    char* trenutni = NULL;
    int brojBitova = 0;

    f = fopen("postfiks.txt", "r");
    if(f == NULL)
    {
        perror("Greska pri dohvacanju datoteke!\n");
        return -1;
    }
    fgets(buffer, 1024, f);
    trenutni = &buffer[0];

    while(br < strlen(buffer) - 1)
    {
        status = 0;
        status = sscanf(trenutni, "%d%n", &el, &brojBitova);
        //printf("Status nakon skeniranja: %d\n", status);
        if(status == 1)
            push(el, &head);
        else
        {
            sscanf(trenutni, " %c%n", &operacija, &brojBitova);
            op(&head, operacija);
            //printf("*%c*", operacija);
        }
        trenutni += brojBitova;
        br += brojBitova;
        print(head.next);
    }



    return 0;
}

int push(int x, poz p)
{
    poz q = NULL;
    q = (poz)malloc(sizeof(struct stog));
    if(q == NULL)
    {
        perror("Greska pri alokaciji!\n");
        return -1;
    }
    q->el = x;
    q->next = p->next;
    p->next = q;
    return EXIT_SUCCESS;
}

int pop(poz p)
{
    poz q = NULL;
    int x = 0;
    if(p->next == NULL)
    {
        printf("Nema nicega u stogu!\n");
        return -1;
    }
    q = p->next;
    p->next = q->next;
    x = q->el;
    free(q);
    return x;
}

int print(poz p)
{

    if(p == NULL)
    {
        printf("Stog je prazan!\n");
        return 0;
    }
    printf("Vas stog: ");
    while(p != NULL)
    {
        printf("%d ", p->el);
        p = p->next;
    }
    printf("\n");
    return 0;
}

int op(poz p, char operacija)
{
    int x = 0;
    int y = 0;
    switch(operacija)
    {
    case '+':
        {
            x = pop(p);
            y = pop(p);
            push(x + y, p);
            break;
        }
    case '-':
        {
            x = pop(p);
            y = pop(p);
            push(x - y, p);
            break;
        }
    case '*':
        {
            x = pop(p);
            y = pop(p);
            push(x * y, p);
            break;
        }
    }
    return 0;
}






