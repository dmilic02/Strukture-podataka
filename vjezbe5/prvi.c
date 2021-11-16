#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _stog;
typedef struct _stog* poz;
typedef struct _stog{
    double broj;
    poz next;
} stog;

poz stvori(double broj);
int unesiIza(poz pozicija, poz novi);
int push(poz head, double broj);
int izbrisiIza(poz pozicija);
int pop(double* odrediste, poz head);
int operacija(poz head, char operacija);
int postfixFile(double* odrediste, char* imeDatoteke);
int brisiSve(poz head);


int main(void)
{
    double r = 0;
    char ime[30];
    printf("Unesite ime datoteke s postfix izrazom: ");
    scanf("%s", ime);

    postfixFile(&r, ime);

    printf("Rezultat vaseg izraza je %lf\n", r);

    return 0;
}

poz stvori(double broj)
{
    poz novi = NULL;

    novi = (poz)malloc(sizeof(stog));
    if(!novi)
    {
        perror("Greska pri alociranju!\n");
        return NULL;
    }

    novi->broj = broj;
    novi->next = NULL;

    return novi;
}

int unesiIza(poz pozicija, poz novi)
{
    novi->next = pozicija->next;
    pozicija->next = novi;

    return EXIT_SUCCESS;
}

int push(poz head, double broj)
{
    poz novi = NULL;
    novi = stvori(broj);
    if(!novi)
        return -1;

    unesiIza(head, novi);

    return EXIT_SUCCESS;
}

int izbrisiIza(poz pozicija)
{
    poz t = pozicija->next;

    if(!t)
        return EXIT_SUCCESS;

    pozicija->next = t->next;
    free(t);

    return EXIT_SUCCESS;
}

int pop(double* odrediste, poz head)
{
    poz prvi = head->next;

    if(!prvi)
    {
        perror("Postfix nije dobar!\n");
        return -1;
    }

    *odrediste = prvi->broj;
    izbrisiIza(head);

    return EXIT_SUCCESS;
}

int operacija(poz head, char operacija)
{
    double op1 = 0, op2 = 0, rezultat = 0;
    int status1 = 0, status2 = 0;

    status2 = pop(&op2, head);
    if(status2 != EXIT_SUCCESS)
        return -1;

    status1 = pop(&op1, head);
    if(status1 != EXIT_SUCCESS)
        return -1;

    switch(operacija)
    {
        case '+':
            rezultat = op1 + op2;
            break;
        case '-':
            rezultat = op1 - op2;
            break;
        case '*':
            rezultat = op1 * op2;
            break;
        case '/':
            if(op2 == 0)
            {
                perror("NAN");
                return -1;
            }
            rezultat = op1 / op2;
            break;
    }

    return push(head, rezultat);
}

int postfixFile(double* odrediste, char* imeDatoteke)
{
    FILE* f = NULL;
    int duljina = 0, brojBitova = 0, broj = 0, status = 0;
    char* buffer = NULL;
    char* currentBuffer = NULL;
    char znak = 0;
    stog head = { .broj = 0, .next = NULL};

    f = fopen(imeDatoteke, "rb");

    if(!f)
    {
        perror("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    fseek(f, 0, SEEK_END);
    duljina = ftell(f);

    buffer = (char*)calloc(duljina + 1, sizeof(char));
    if(!buffer)
    {
        perror("Geska pri alociranju!\n");
        return -1;
    }

    rewind(f);
    fread(buffer, sizeof(char), duljina, f);
    printf("|%s|\n", buffer);
    fclose(f);

    currentBuffer = buffer;
    while(strlen(currentBuffer) > 0)
    {
        status = sscanf(currentBuffer, "%lf %n", &broj, &brojBitova);
        if(status != 1)
        {
            if(status != EXIT_SUCCESS)
            {
                free(buffer);
                brisiSve(&head);
                return -1;
            }
            currentBuffer += brojBitova;
        }
        else
        {
            sscanf(currentBuffer, "%c %n", &znak, &brojBitova);
            status = operacija(&head, znak);
            if(status != EXIT_SUCCESS)
            {
                free(buffer);
                brisiSve(&head);
                return -1;
            }
            currentBuffer += brojBitova;
        }
    }
    free(buffer);

    status = pop(odrediste, &head);
    if(status != EXIT_SUCCESS)
    {
        brisiSve(&head);
        return -1;
    }

    return EXIT_SUCCESS;
}

int brisiSve(poz head)
{
    while(head->next != NULL)
        izbrisiIza(head);

    return EXIT_SUCCESS;
}


