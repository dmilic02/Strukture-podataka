#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define N 20

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
poz stvoriOsobu(char* ime, char* prezime, int godina);
int umetniIza(poz pozicija, poz nova);
int ispis(poz prva);
int kraj(poz head, char* ime, char* prezime, int godina);
poz nadiPrezime(poz prvi, char* prezime);
int brisi(poz head, poz pozicija);

int main(void)
{
    osoba head;
    poz brisanje = NULL;
    head.next = NULL;

    pocetak(&head, "duje", "milic", 2001);
   // pocetak(&head, "dodo", "milic", 2003);
    //pocetak(&head, "ivan", "vaki", 2004);
    //kraj(&head, "vlahica", "petko", 2002);
    kraj(&head, "mate", "buljan", 2003);
    ispis(head.next);

    printf("\n\n");
    brisanje = nadiPrezime(&head, "buljan");
    brisi(&head, brisanje);
    brisanje = nadiPrezime(&head, "milic");
    brisi(&head, brisanje);
    ispis(head.next);

    kraj(&head, "vlahica", "petko", 2002);
    printf("\n\n");
    ispis(head.next);

	return 0;
}


int pocetak(poz head, char* ime, char* prezime, int godina)
{
	poz nova = NULL;
	nova = (poz)malloc(sizeof(osoba));
	if (!nova)
	{
		perror("Memorija se ne moze alocirati!\n");
		return -1;
	}
	nova = stvoriOsobu(ime, prezime, godina);
	if (!nova)
		return -1;
	umetniIza(head, nova);
	return EXIT_SUCCESS;
}

poz stvoriOsobu(char* ime, char* prezime, int godina)
{
	poz nova = NULL;
	nova = (poz)malloc(sizeof(osoba));
	if (!nova)
	{
		perror("Memorija se ne moze alocirati!\n");
		//return -1;
	}
	strcpy(nova->ime, ime);
	strcpy(nova->prezime, prezime);
	nova->godina = godina;
	nova->next = NULL;
	return nova;
}

int umetniIza(poz pozicija, poz nova)
{
	nova->next = pozicija->next;
	pozicija->next = nova;
	return EXIT_SUCCESS;
}

int ispis(poz prva)
{
    poz t = prva;
    int br = 0;
    printf("Vezana lista osoba:\n");
	while (t)
	{
		printf("Ime: %s, prezime: %s, godina: %d\n", t->ime, t->prezime, t->godina);
		t = t->next;
		br++;
	}
	if(br == 0)
        printf("Lista je trenutno prazna\n");
	return EXIT_SUCCESS;
}

int kraj(poz head, char* ime, char* prezime, int godina)
{
	poz nova = NULL;
	poz zadnja = head;
	nova = (poz)malloc(sizeof(osoba));
	if(!nova)
	{
		perror("Memorija se ne moze alocirati!\n");
		return -1;
	}
	nova = stvoriOsobu(ime, prezime, godina);
	if (!nova)
		return -1;
	while (zadnja->next != NULL)
		zadnja = zadnja->next;
	umetniIza(zadnja, nova);
	return EXIT_SUCCESS;
}

poz nadiPrezime(poz prvi, char* prezime)
{
	poz t = prvi;
	while (t != NULL)
	{
		if (strcmp(prezime, t->prezime) == 0)
        {
           // printf("\n SVE DOBRO ZASAD \n");
            return t;
        }
		t = t->next;
	}
	printf("Element nije pronaden\n");
	return NULL;
}

int brisi(poz head, poz pozicija)
{
	poz t = pozicija;
	if(t == NULL)
    {
        printf("Pogresan argument\n");
        return EXIT_FAILURE;
    }
	while (head != NULL)
	{
		if (head->next == t)
		{
			head->next = t->next;
			free(pozicija);
		}
		head = head->next;
	}
	return EXIT_SUCCESS;
}

