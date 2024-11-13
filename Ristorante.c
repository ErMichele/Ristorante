#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define Ordini "ordinazioni.txt"
#define MAX_ORDINAZIONE 2000

void rimuovi_n(char *str)
{
    str[strcspn(str, "\n")] = '\0';
}

int main()
{
    FILE *file = fopen(Ordini, "a");
    if (!file) {
        fclose (file);
        FILE *file = fopen (Ordini, "w");
    }
    fclose (file);
    char Ordinazione[MAX_ORDINAZIONE];
    int scelta;
    while (1)
    {
        printf("\n----Organizzatore di ordinazioni----\n1. Aggiunta ordine\n2. Lettura ordini\n3. Eliminazione ordine\n4. Chiusura programma\n\nChe cosa desidera fare (1-4): ");
        scanf("%d", &scelta);
        getchar();

        switch (scelta)
        {

        case 1:
            printf("\nInserire ordinazione: ");
            fgets(Ordinazione, sizeof(Ordinazione), stdin);
            rimuovi_n(Ordinazione);
            FILE *file = fopen(Ordini, "a");
            if (file)
            {
                fprintf(file, "%s\n", Ordinazione);
                fclose(file);
                printf("\nAggiunta ordinazione: %s", Ordinazione);
            }
            else
            {
                printf("\nErrore nel aprire il file, riprovare");
            }
            Sleep(4000);
            system("cls");
            break;

        case 2:
        {
            FILE *file = fopen(Ordini, "r");
            if (file)
            {
                printf("\nEcco le ordinazioni attuali: ");
                while (fgets(Ordinazione, sizeof(Ordinazione), file))
                {
                    printf("%s", Ordinazione);
                }
                fclose(file);
            }
            else
            {
                printf("\nErrore nel aprire il file, riprovare");
            }
            Sleep(4000);
            system("cls");
        }
        break;

        case 3:
            printf("\nQual e' ordinazione che volete rimuovere: ");
            fgets(Ordinazione, sizeof(Ordinazione), stdin);
            rimuovi_n(Ordinazione);
            {
                FILE *file = fopen(Ordini, "r");
                if (!file)
                {
                    printf("\nErrore nel aprire il file, riprovare");
                    Sleep(3000);
                    system("cls");
                    break;
                }

                FILE *tempfile = fopen("temp.txt", "w");
                char line[MAX_ORDINAZIONE];
                int find = 0;

                while (fgets(line, sizeof(line), file))
                {
                    rimuovi_n(line);
                    if (strcmp(line, Ordinazione) != 0)
                    {
                        fprintf(tempfile, "%s\n", line);
                    }
                    else
                    {
                        find = 1;
                    }
                }

                fclose(file);
                fclose(tempfile);
                remove(Ordini);
                rename("temp.txt", Ordini);
                if (find)
                {
                    printf("\nL'ordinazione e' stata rimossa");
                }
                else
                {
                    printf("\nL'ordinazione non e' stata trovata");
                }
                Sleep(4500);
                system("cls");
                break;
            }

        case 4:
            printf("\nGrazie di aver usato il programma!");
            Sleep(4000);
            return 0;

        default:
            printf("\nPosto un comando sbagliato, per favore rifare");
            Sleep(5000);
            system("cls");
            break;
        }
    }
    return 0;
}