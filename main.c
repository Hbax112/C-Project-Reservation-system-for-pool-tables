#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void vizualizeaza_disponibilitatea(int masa_selectata, int zi, int luna) {
    char nume_fisier[20];
    sprintf(nume_fisier, "Masa_%d.txt", masa_selectata);

    FILE* fp = fopen(nume_fisier, "r");
    if (fp == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return;
    }

    char line[100];


    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
}

int verifica_masa_disponibila(int masa_selectata, int zi, int luna, int ora_inceput, int minute_inceput, int durata) {
    char nume_fisier[20];
    sprintf(nume_fisier, "Masa_%d.txt", masa_selectata);

    FILE* fp = fopen(nume_fisier, "r");
    if (fp == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return 0;
    }

    char line[100];

    while (fgets(line, sizeof(line), fp)) {
        int zi_fisier, luna_fisier, ora_inceput_fisier, minute_inceput_fisier, durata_fisier;

        sscanf(line, "%d/%d/2023 %d:%d %d", &zi_fisier, &luna_fisier, &ora_inceput_fisier, &minute_inceput_fisier, &durata_fisier);

        if (zi_fisier == zi && luna_fisier == luna) {
            int sfarsit_inceput = (ora_inceput * 60 + minute_inceput) + durata_fisier;
            int sfarsit_cautat = (ora_inceput * 60 + minute_inceput) + durata;

            if ((ora_inceput_fisier * 60 + minute_inceput_fisier) < sfarsit_inceput && sfarsit_cautat > (ora_inceput_fisier * 60 + minute_inceput_fisier)) {
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    return 1;
}

int este_interval_disponibil(int masa_selectata, int zi, int luna, int ora_inceput, int minute_inceput, int durata) {
    char nume_fisier[20];
    sprintf(nume_fisier, "Masa_%d.txt", masa_selectata);

    FILE* fp = fopen(nume_fisier, "r");
    if (fp == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return 0;
    }

    char line[100];

    while (fgets(line, sizeof(line), fp)) {
        int zi_fisier, luna_fisier, ora_inceput_fisier, minute_inceput_fisier, durata_fisier;

        sscanf(line, "%d/%d/2023 %d:%d %d", &zi_fisier, &luna_fisier, &ora_inceput_fisier, &minute_inceput_fisier, &durata_fisier);

        if (zi_fisier == zi && luna_fisier == luna) {
            int sfarsit_inceput = (ora_inceput * 60 + minute_inceput) + durata_fisier;
            int sfarsit_cautat = (ora_inceput * 60 + minute_inceput) + durata;

            if ((ora_inceput_fisier * 60 + minute_inceput_fisier) < sfarsit_inceput && sfarsit_cautat > (ora_inceput_fisier * 60 + minute_inceput_fisier)) {
                fclose(fp);
                return 0;
            }
        }
    }

    fclose(fp);
    return 1;
}

int este_disponibila(int masa_selectata, int zi, int luna, int ora_inceput, int minute_inceput, int durata) {
    if (!este_interval_disponibil(masa_selectata, zi, luna, ora_inceput, minute_inceput, durata)) {
        printf("Masa nu este disponibila in aceasta perioada! Incercati alta zi sau alt interval orar!\n");
        return 0;
    }
    return 1;
}

void rezerva_masa() {
    int masa_selectata = 0;
    int durata = 0;
    int zi = 0;
    int luna = 0;
    int ora_inceput = 0;
    int minute_inceput = 0;
    printf("Selectati masa dorita (1-6): ");
    scanf("%d", &masa_selectata);

    if (masa_selectata < 1 || masa_selectata > 6) {
        printf("Masa selectata nu exista! Incearca din nou.\n");
        rezerva_masa();
        return;

    }



    printf("Introduceti ziua dorita: ");
    scanf("%d, ",&zi);

    while (zi < 1 ||  zi > 31 )
    {
        printf("Datele alese nu sunt valide, te rugam sa incerci din nou: ");
        scanf("%d", &zi);
    }

    printf("Introduceti luna dorita(1-12): ");
    scanf("%d, ",&luna);
    while ( luna < 1 || luna > 12)
    {
            printf("Luna invalida te rugam sa alegeti din nou (1-12): ");
            scanf("%d",&luna);
    }


    printf("Introduceti ora  de inceput: ");
    scanf("%d",&ora_inceput);
    while (ora_inceput < 15 || ora_inceput > 20)
    {
        printf("Intervalul orar este 15:00-21:00, te rugam alege alta ora de inceput (15-20): ");
        scanf("%d",&ora_inceput);
    }

    printf("Introduceti minutul de inceput: ");
    scanf("%d", &minute_inceput);
    while (minute_inceput <0 || minute_inceput>59)
    {
        printf("Intervalul indisponibil . Introdu minutul de inceput (0-59): ");
        scanf("%d", &minute_inceput);
    }

    printf("Introduceti durata rezervarii (minim 30 min.): ");
    scanf("%d", &durata);

    while (durata < 30) {
        printf("Durata introdusa nu este valida!\n");
        printf("Introduceti durata rezervarii (minim 30 min.): ");
        scanf("%d", &durata);
    }

    if (!este_disponibila(masa_selectata, zi, luna, ora_inceput, minute_inceput, durata)) {
        return;
    }

    // Creare fisier mesaj pentru client
    char nume_fisier[20];
    sprintf(nume_fisier, "Masa_%d.txt", masa_selectata);

    FILE* fp = fopen(nume_fisier, "a");
    if (fp == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return;
    }

    fprintf(fp, "%d/%d/2023 %.02d:%.02d-%.02d:%.02d interval: %d\n", zi, luna, ora_inceput, minute_inceput, (ora_inceput + (minute_inceput + durata) / 60) % 24, (minute_inceput + durata) % 60, durata);
    fclose(fp);

    printf("Rezervarea pentru masa %d a fost efectuata cu succes!\n", masa_selectata);
}


void adauga_rezervare(int masa_selectata, int zi, int luna, int ora_inceput, int minute_inceput, int durata) {
    char nume_fisier[20];
    sprintf(nume_fisier, "Masa_%d.txt", masa_selectata);

    FILE* fp = fopen(nume_fisier, "a");
    if (fp == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return;
    }

    int ora_sfarsit = (ora_inceput + (minute_inceput + durata) / 60) % 24;
    int minute_sfarsit = (minute_inceput + durata) % 60;

    fprintf(fp, "%d/%d/2023 %02d:%02d-%02d:%02d\n", zi, luna, ora_inceput, minute_inceput, ora_sfarsit, minute_sfarsit);
    fclose(fp);
}



void afiseaza_statistici_masa(int masa_selectata, int masa_luna)
{
    // citim din fisier statisticile meselor și afișăm cele pentru masa selectată
    char filename[20];
    sprintf(filename, "Masa_%d.txt", masa_selectata);

    FILE* fp;
    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Eroare la deschiderea fisierului!");
        return;
    }
    char luna[2];
    char line[100];
    int k=0;
    char c[3];
    int s=0;
    while (fgets(line, sizeof(line), fp)) {
            luna[2]='\0';
            luna[1]=line[3];
            if(line[2]>='0' && line[2]<='9')
                luna[0]=line[2];
            else luna[0]='0';
            int lunanr=atoi(luna);
            if(lunanr==masa_luna)
            {
            int n=strlen(line);
            c[3]='\0';
            c[2]=line[n-1];
            c[1]=line[n-2];
            c[0]=line[n-3];
            int nr=atoi(c);
            s=s+nr;
            k++;
            }
    }
    fclose(fp);
    sprintf(filename, "statistici_masa_%d.txt", masa_selectata);
    fp = fopen(filename, "w");
        if(masa_luna==1)
        {
            fprintf(fp,"  LUNA IANUARIE  \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        }
        else if(masa_luna==2)
        {
            fprintf(fp,"  LUNA FEBRUARIE  \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        } else if(masa_luna==3)
        {
            fprintf(fp,"  LUNA MARTIE  \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        } else if(masa_luna==4)
        {
            fprintf(fp,"  LUNA APRILIE  \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        } else if(masa_luna==5)
        {
            fprintf(fp,"  LUNA MAI  \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        } else if(masa_luna==6)
        {
            fprintf(fp,"  LUNA IUNIE  \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        }else  if(masa_luna==7)
        {
            fprintf(fp,"  LUNA IULIE  \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        }else if(masa_luna==8)
        {
            fprintf(fp,"  LUNA AUGUST  \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        }
        else if(masa_luna==9)
        {
            fprintf(fp,"  LUNA SEPTEMRIE \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        }
        else if(masa_luna==10)
        {
            fprintf(fp,"  LUNA OCTOMBRIE  \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        } else if(masa_luna==11)
        {
            fprintf(fp,"  LUNA NOIEMBRIE \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        } else if(masa_luna==12)
        {
            fprintf(fp,"  LUNA DECEMBRIE \n");
            fprintf(fp,"Masa %d:\n",masa_selectata);
            fprintf(fp,"-Nr de rezervari:%d\n",k);
            fprintf(fp,"-Timp total rezervat: %dh %dmin",s/60,s%60);
        }
        fclose(fp);
        fp = fopen(filename, "r");
        char linee[100];
        while (fgets(linee, sizeof(linee), fp)) {
            printf("%s",linee);
        }


}


int main()
{
    int masa_selectata,zi,luna,masa_luna;

    while (1)
        {
        system("cls");
        printf("-= SISTEM DE REZERVARE MESE BILIARD =-\n");
        printf("1. Vizualizeaza disponibilitatea meselor\n");
        printf("2. Rezerva o masa de biliard\n");
        printf("3. Vizualizeaza statistici despre mese\n");
        printf("4. Iesire\n");

        int optiune;
        do
        {
            printf("Introdu optiunea: ");
            scanf("%d", &optiune);
        } while (optiune < 1 || optiune > 4);

        system("cls");

        switch (optiune)
        {
            case 1:
                printf("-= DISPONIBILITATEA MESELOR =-\n");
                printf("Introdu numarul mesei (1-6): ");
                scanf("%d", &masa_selectata);
                printf("\n Mesele nu sunt disponibile in intervalul/intervalele de mai jos:\n");
                vizualizeaza_disponibilitatea(masa_selectata,zi,luna);
                printf("\nApasa orice tasta pentru a reveni la meniul principal...");
                system("pause > null");

                break;
            case 2:
                printf("-= REZERVARE MASA DE BILIARD =-\n");
                rezerva_masa();
                printf("\nApasa orice tasta pentru a reveni la meniul principal...");
                system("pause > null");
                break;
            case 3:
                printf("-= STATISTICI DESPRE MESE =-\n");
                printf("Introdu numarul mesei (1-6): ");
                scanf("%d", &masa_selectata);
                printf("Introdu luna dorita (1-12): ");
                scanf("%d", &masa_luna);
                afiseaza_statistici_masa(masa_selectata,masa_luna);
                printf("\nApasa orice tasta pentru a reveni la meniul principal...");
                system("pause > null");
                break;
            case 4:
                printf("La revedere!\n");

                return 0;
        }
    }
}


