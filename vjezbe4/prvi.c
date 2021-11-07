#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define maxDuljina 1024

struct polinom;
typedef struct polinom* poli;
typedef struct polinom
{
    int koef;
    int eksp;
    poli next;
} _polinom;

void ucitajIzDatoteke(poli, char*);
void unos(poli, int, int);
void zbrojiPolinome(poli, poli, poli);
void mnoziPolinome(poli, poli, poli);
void ispisi(poli);


int main(void)
{
    char dat[20];
    char buffer[maxDuljina];
    FILE* f = NULL;
    struct polinom head1;
    struct polinom head;
    struct polinom head2;
    struct polinom zbroj;
    struct polinom umnozak;
    poli p = NULL, q = NULL;

    head1.next = NULL;
    head.next = NULL;
    head2.next = NULL;
    zbroj.next = NULL;
    umnozak.next = NULL;

    printf("Unesite prvu datoteku sa koeficijentima i eksponentima: ");
    scanf("%s", dat);
    f = fopen(dat, "r");
    if(f == NULL)
    {
        perror("Greska pri dohvacanju datoteke!");
        return 0;
    }
    while(!feof(f))
    {
        fgets(buffer, maxDuljina, f);
        ucitajIzDatoteke(&head1, buffer);
    }

    printf("Unesite drugu datoteku sa koeficijentima i eksponentima: ");
    scanf("%s", dat);
    f = fopen(dat, "r");
    if(f == NULL)
    {
        perror("Greska pri dohvacanju datoteke!");
        return 0;
    }
    while(!feof(f))
    {
        fgets(buffer, maxDuljina, f);
        ucitajIzDatoteke(&head2, buffer);
    }

    p = head1.next;
    while(p != NULL)
    {
        q = (poli)malloc(sizeof(struct polinom));
        q->eksp = p->eksp;
        q->koef = p->koef;
        q->next = head.next;
        head.next = q;
        p = p->next;
    }

    zbrojiPolinome(&zbroj, &head1, &head2);

    p = head1.next;
    ispisi(p);

    /*p = zbroj.next;
    ispisi(p);*/
    //head2 = drugi niz, head = prvi niz
    /*p = head2.next;
    ispisi(p);
    p = head.next;
    ispisi(p);*/

    mnoziPolinome(&umnozak, &head, &head2);
    ispisi(umnozak.next);


    return 0;
}

void ucitajIzDatoteke(poli head, char* buffer)
{
    int k, e, brojBitova;
    char* trenutni = buffer;
    poli p = head, q = NULL, prev = head;
    while(strlen(trenutni) > 1)
    {
        prev = head;
        p = prev->next;
        sscanf(trenutni, "%d %d%n", &k, &e, &brojBitova);
        while(p != NULL)
        {
            if(e > p->eksp)
            {
                q = (poli)malloc(sizeof(struct polinom));
                q->koef = k;
                q->eksp = e;
                q->next = prev->next;
                prev->next = q;
                trenutni += brojBitova;
                p = head;
                break;
            }
            else if(e == p->eksp)
            {
                p->koef += k;
                if(p->koef == 0)
                {
                    prev->next = p->next;
                    free(p);
                }
                trenutni += brojBitova;
                p = head;
                break;
            }
            prev = prev->next;
            p = p->next;
        }
        if(p == NULL)
        {
            q = (poli)malloc(sizeof(struct polinom));
            q->koef = k;
            q->eksp = e;
            q->next = prev->next;
            prev->next = q;
            trenutni += brojBitova;
        }

    }
}

void zbrojiPolinome(poli zbroj, poli h1, poli h2)
{
    poli q = NULL, prev = NULL;
    prev = h1;
    zbroj->next = prev->next;
    h2 = h2->next;
    while(h2 != NULL)
    {
        zbroj = prev->next;
        while(zbroj != NULL)
        {
            if(h2->eksp == zbroj->eksp)
            {
                zbroj->koef += h2->koef;
                break;
            }
            if(h2->eksp > zbroj->eksp)
            {
                q = (poli)malloc(sizeof(struct polinom));
                q->eksp = h2->eksp;
                q->koef = h2->koef;
                q->next = prev->next;
                prev->next = q;
                break;
            }
            prev = prev->next;
            zbroj = prev->next;
        }
        if(zbroj == NULL)
        {
            q = (poli)malloc(sizeof(struct polinom));
            q->eksp = h2->eksp;
            q->koef = h2->koef;
            q->next = prev->next;
            prev->next = q;
        }
        h2 = h2->next;
    }
}

void mnoziPolinome(poli umnozak, poli h1, poli h2)
{
    poli start = h2->next;
    h1 = h1->next;
    while(h1 != NULL)
    {
        h2 = start;
        while(h2 != NULL)
        {
            unos(umnozak, h1->koef * h2->koef, h1->eksp + h2->eksp);
            h2 = h2->next;
        }
        h1 = h1->next;
    }
}




void ispisi(poli p)
{
    printf("\n\n");
    while(p != NULL)
    {
        printf("%d x^(%d)   ", p->koef, p->eksp);
        p = p->next;
    }
}

void unos(poli p, int k, int e)
{
    poli q = NULL, prev = NULL;
    prev = p;
    p = p->next;
    while(p != NULL && p->eksp > e)
    {
        prev = p;
        p = p->next;
    }
    if(p != NULL && p->eksp == e)
        p->koef += k;
    else
    {
        q = (poli)malloc(sizeof(struct polinom));
        q->eksp = e;
        q->koef = k;
        q->next = p;
        prev->next = q;
    }
}
