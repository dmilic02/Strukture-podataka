#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 50

struct osoba;
typedef struct osoba* poz;
typedef struct osoba
{
    char ime[N];
    char prezime[N];
    int godina;
    poz next;
}osoba;

int pocetak(poz head, char* ime, char* prezime, int godina);
int dodajIza(poz head, char* ime, char* prezime, int godina, char* pozicija);
int dodajIspred(poz head, char* ime, char* prezime, int godina, char* pozicija);
poz stvoriOsobu(char* ime, char* prezime, int godina);
int ispisi(poz head);
int upisiDatoteku(poz head, FILE *f);
int brisiSve(poz head);
int unesiDatoteku(poz head, FILE *f);
int sortiranje(poz head);


int main(void)
{
    osoba head;
    FILE *f = NULL;
    FILE *u = NULL;

    f = fopen("studenti", "w");
    u = fopen("unos.txt", "r");
    if(u == NULL || f == NULL)
        return 0;
    head.next = NULL;

    pocetak(&head, "Mijo", "Mijic", 2000);
    pocetak(&head, "Mate", "Matic", 2002);
    pocetak(&head, "Ana", "Anic", 2004);
    ispisi(head.next);

    printf("\n");
    dodajIza(&head, "Ante", "Antic", 2001, "Matic");
    ispisi(head.next);

    printf("\n");
    dodajIspred(&head, "Roko", "Rokic", 2003, "Matic");
    ispisi(head.next);

    upisiDatoteku(head.next, f);

    printf("\n");
    brisiSve(&head);
    ispisi(head.next);

    printf("\n");
    unesiDatoteku(&head, u);
    ispisi(head.next);

    printf("\n");
    sortiranje(&head);
    ispisi(head.next);

    fclose(f);
    fclose(u);
    return 0;
}

int ispisi(poz head)
{
    while(head != NULL)
    {
        printf("Ime: %s, Prezime: %s, Godina: %d\n", head->ime, head->prezime, head->godina);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int pocetak(poz head, char* ime, char* prezime, int godina)
{
    poz nova = NULL;
    nova = (poz)malloc(sizeof(osoba));
    if(!nova)
    {
        perror("Memorija nije alocirana!");
        return -1;
    }
    nova = stvoriOsobu(ime, prezime, godina);
    if(!nova)
        return -1;
    nova->next = head->next;
    head->next = nova;
    return EXIT_SUCCESS;
}

int dodajIza(poz head,  char* ime, char* prezime, int godina, char* pozicija)
{
    poz nova;
    nova = stvoriOsobu(ime, prezime, godina);
    while(head->next != NULL)
    {
        if(strcmp(head->prezime, pozicija) == 0)
        {
            nova->next = head->next;
            head->next = nova;
            break;
        }
        head = head->next;
    }
    return EXIT_SUCCESS;
}

poz stvoriOsobu(char* ime, char* prezime, int godina)
{
    poz nova;
    nova = (poz)malloc(sizeof(osoba));
    strcpy(nova->ime, ime);
    strcpy(nova->prezime, prezime);
    nova->godina = godina;
    nova->next = NULL;
    return nova;
}


int dodajIspred(poz head, char* ime, char* prezime, int godina, char* pozicija)
{
    poz nova;
    nova = (poz)malloc(sizeof(osoba));
    nova = stvoriOsobu(ime, prezime, godina);
    while(head != NULL)
    {
        if(strcmp(head->next->prezime, pozicija) == 0)
        {
            nova->next = head->next;
            head->next = nova;
            break;
        }
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int upisiDatoteku(poz head, FILE *f)
{
    while(head != NULL)
    {
        fprintf(f, "Ime: %s, Prezime: %s, Godina: %d\n", head->ime, head->prezime, head->godina);
        head = head->next;
    }
    return EXIT_SUCCESS;
}

int brisiSve(poz head)
{
    poz q;
    q = (poz)malloc(sizeof(osoba));
    while(head->next != NULL)
    {
        q = head->next;
        head->next = q->next;
        free(q);
    }
    return EXIT_SUCCESS;

}

int unesiDatoteku(poz head, FILE *f)
{
    char ime[N];
    char prezime[N];
    int godina;

    while(!feof(f))
    {
        fscanf(f, "%s %s %d", ime, prezime, &godina);
        pocetak(head, ime, prezime, godina);
    }
    return EXIT_SUCCESS;
}

int sortiranje(poz head)
{
    poz x = NULL;
    poz prijex = NULL;
    poz t = NULL;
    poz end = NULL;


    while(head->next != end)
    {
        prijex = head;
        x = head->next;
        while(x->next != end)
        {
            if(strcmp(x->prezime, x->next->prezime) < 0)
            {
                t = x->next;
                prijex->next = t;
                x->next = t->next;
                t->next = x;

                x = t;
            }
            prijex = x;
            x = x->next;
        }
        end = x;
    }


    return EXIT_SUCCESS;
}

