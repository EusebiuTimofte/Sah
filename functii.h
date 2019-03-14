#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constante.h"
#include <math.h>
    struct piese
    {
        char tip[10];
        int culoare;
    };
    typedef struct
    {
        struct piese piesa;
        int gol;
    }patrate;

void aseaza_piesele(patrate patrat[9][9])
{///pune piesele in pozitia initiala
    //aseaza turele
    strcpy(patrat[1][1].piesa.tip,"tura");
    patrat[1][1].piesa.culoare=1;
    patrat[1][1].gol=0;

    strcpy(patrat[1][8].piesa.tip,"tura");
    patrat[1][8].piesa.culoare=1;
    patrat[1][8].gol=0;

    strcpy(patrat[8][1].piesa.tip,"tura");
    patrat[8][1].piesa.culoare=0;
    patrat[8][1].gol=0;

    strcpy(patrat[8][8].piesa.tip,"tura");
    patrat[8][8].piesa.culoare=0;
    patrat[8][8].gol=0;
    //aseaza caii
    strcpy(patrat[1][2].piesa.tip,"cal");
    patrat[1][2].piesa.culoare=1;
    patrat[1][2].gol=0;

    strcpy(patrat[1][7].piesa.tip,"cal");
    patrat[1][7].piesa.culoare=1;
    patrat[1][7].gol=0;

    strcpy(patrat[8][2].piesa.tip,"cal");
    patrat[8][2].piesa.culoare=0;
    patrat[8][2].gol=0;

    strcpy(patrat[8][7].piesa.tip,"cal");
    patrat[8][7].piesa.culoare=0;
    patrat[8][7].gol=0;
    //aseaza nebunii
    strcpy(patrat[1][3].piesa.tip,"nebun");
    patrat[1][3].piesa.culoare=1;
    patrat[1][3].gol=0;

    strcpy(patrat[1][6].piesa.tip,"nebun");
    patrat[1][6].piesa.culoare=1;
    patrat[1][6].gol=0;

    strcpy(patrat[8][3].piesa.tip,"nebun");
    patrat[8][3].piesa.culoare=0;
    patrat[8][3].gol=0;

    strcpy(patrat[8][6].piesa.tip,"nebun");
    patrat[8][6].piesa.culoare=0;
    patrat[8][6].gol=0;
    //aseaza reginele
    strcpy(patrat[1][4].piesa.tip,"regina");
    patrat[1][4].piesa.culoare=1;
    patrat[1][4].gol=0;

    strcpy(patrat[8][5].piesa.tip,"regina");
    patrat[8][5].piesa.culoare=0;
    patrat[8][5].gol=0;
    //aseaza regii
    strcpy(patrat[1][5].piesa.tip,"rege");
    patrat[1][5].piesa.culoare=1;
    patrat[1][5].gol=0;

    strcpy(patrat[8][4].piesa.tip,"rege");
    patrat[8][4].piesa.culoare=0;
    patrat[8][4].gol=0;
    //aseaza pionii
    int i;
    for(i=1;i<=8;i++)
    {
        strcpy(patrat[2][i].piesa.tip,"pion");
        patrat[2][i].piesa.culoare=1;
        patrat[2][i].gol=0;

        strcpy(patrat[7][i].piesa.tip,"pion");
        patrat[7][i].piesa.culoare=0;
        patrat[7][i].gol=0;
    }
    //seteaza restul patratelor ca fiind goale
    int j;
    for(i=3;i<=6;i++)
        for(j=1;j<=8;j++)
        patrat[i][j].gol=1;
}

void afiseaza(patrate patrat[9][9])
{//afiseaza tabla de sah
    int i,j,t;

    printf("   ");
    for(j=1;j<=DIM_TABLA;j++)
        printf("    %d   ",j);
    printf("\n");
    for(i=1;i<=8;i++)
    {
       printf("   -----------------------------------------------------------------\n");

       printf("   ");
       for(j=1;j<=DIM_TABLA;j++)
        printf("|       ");
       printf("|\n");

       printf(" %d ",i);

       for(j=1;j<=DIM_TABLA;j++)
       {
           if(patrat[i][j].gol==1)
            printf("|       ");
           else
           {
               printf("|%s%d",patrat[i][j].piesa.tip,patrat[i][j].piesa.culoare);
               t=strlen(patrat[i][j].piesa.tip);
               while(t<6)
               {
                   printf(" ");
                   t++;
               }
           }
       }
       printf("|\n");

       printf("   ");

       for(j=1;j<=DIM_TABLA;j++)
        printf("|       ");
       printf("|\n");
    }
    printf("   -----------------------------------------------------------------\n");
}

int rege_sah(int c,patrate patrat[9][9])//stabileste daca regele jucatorului cu nr c se afla in sah ( 1 -DA , 0- NU)
{
    int i,j,k,linr,colr;//i,j,k contoare , linr si colr reprezinta numarul liniei si al coloanei patratului in care se afla regele cu nr c
    for(i=1;i<=DIM_TABLA;i++)
        for(j=1;j<=DIM_TABLA;j++)
        if(patrat[i][j].gol==0 && strcmp(patrat[i][j].piesa.tip,"rege")==0 && patrat[i][j].piesa.culoare==c)//daca regele cu nr c se afla in patratul de coordonate i si j
    {
        linr=i;
        colr=j;
        break;
    }
    ///verifica daca regele este atacat de un pion advers
    //in functie de numarul care le corespunde (0 sau 1), pionii se deplaseaza cu o linie mai jos sau mai sus ( 1-jos , 0-sus) . Variabila i va primi o valoare care sa marcheaza una dintre optiuni
    if(c==0)
        i=1;
    else
        i=-1;
    if(patrat[linr+i][colr+1].gol==0 && patrat[linr+i][colr+1].piesa.culoare!=c && strcmp(patrat[linr+i][colr+1].piesa.tip,"pion")==0)
        return 1;
    if(patrat[linr+i][colr-1].gol==0 && patrat[linr+i][colr-1].piesa.culoare!=c && strcmp(patrat[linr+i][colr-1].piesa.tip,"pion")==0)
        return 1;
    ///verifica daca regele este atacat de un cal advers
    //calul se misca in L ,adica diferenta in modul dintre linia la care se afla inainte si dupa mutare este egala cu 1 sau 2 , iar diferenta in modul dintre coloana la care se afla inainte si dupa mutare este tot 1 sau 2 . Cele 2 diferente nu pot avea aceeasi valoare simultan.
    for(k=0;k<=1;k++)//pt k=0 ,diferenta in modul pe linie este 1 , iar pe coloana 2 . pt k=1 diferenta in modul pe linie este 2 ,iar pe coloana 1
      for(i=-1;i<=1;i=i+2)//i se inmulteste cu diferenta in modul pe linie si se aduna la linia patratului din care pleaca calul pt a obtine linia patratului destinatie
        for(j=-1;j<=1;j=j+2)//j se inmulteste cu diferenta in modul pe coloana si se aduna la coloana patratului din care pleaca calul pt a obtine coloana patratului destinatie
        if(linr+i*(k+1)>=1 && linr+i*(k+1)<=DIM_TABLA && colr+j*(((k+1)%2)+1)>=1 && colr+j*(((k+1)%2)+1)<=DIM_TABLA && patrat[linr+i*(k+1)][colr+j*(((k+1)%2)+1)].gol==0 && patrat[linr+i*(k+1)][colr+j*(((k+1)%2)+1)].piesa.culoare!=c && strcmp(patrat[linr+i*(k+1)][colr+j*(((k+1)%2)+1)].piesa.tip,"cal")==0)
        return 1;//regele este in sah
    ///verifica daca regele este atacat de un nebun sau o regina adversa pe diagonala dreapta , jos
    i=1;
    while(linr+i<=DIM_TABLA && colr+i<=DIM_TABLA)
    {
        if(patrat[linr+i][colr+i].gol==0)
        {
           if(patrat[linr+i][colr+i].piesa.culoare!=c && (strcmp(patrat[linr+i][colr+i].piesa.tip,"regina")==0 || strcmp(patrat[linr+i][colr+i].piesa.tip,"nebun")==0))//daca prima piesa gasita este un nebun sau regina adversa
            return 1;//regele se afla in sah
           break;//opreste cautarea
        }
        i++;
    }
    ///verifica daca regele este atacat de un nebun sau o regina adversa pe diagonala stanga, jos
    i=1;
    while(linr+i<=DIM_TABLA && colr-i>=1)
    {
        if(patrat[linr+i][colr-i].gol==0)
        {
           if(patrat[linr+i][colr-i].piesa.culoare!=c && (strcmp(patrat[linr+i][colr-i].piesa.tip,"regina")==0 || strcmp(patrat[linr+i][colr-i].piesa.tip,"nebun")==0))//daca prima piesa gasita este un nebun sau regina adversa
            return 1;//regele se afla in sah
           break;//opreste cautarea
        }
        i++;
    }
    ///verifica daca regele este atacat de un nebun sau o regina adversa pe diagonala dreapta , sus
    i=1;
    while(linr-i>=1 && colr+i<=DIM_TABLA)
    {
        if(patrat[linr-i][colr+i].gol==0)
        {
           if(patrat[linr-i][colr+i].piesa.culoare!=c && (strcmp(patrat[linr-i][colr+i].piesa.tip,"regina")==0 || strcmp(patrat[linr-i][colr+i].piesa.tip,"nebun")==0))//daca prima piesa gasita este un nebun sau regina adversa
            return 1;//regele se afla in sah
           break;//opreste cautarea
        }
        i++;
    }
    ///verifica daca regele este atacat de un nebun sau o regina adversa pe diagonala stanga,sus
    i=1;
    while(linr-i>=1 && colr-i>=1)
    {
        if(patrat[linr-i][colr-i].gol==0)
        {
           if(patrat[linr-i][colr-i].piesa.culoare!=c && (strcmp(patrat[linr-i][colr-i].piesa.tip,"regina")==0 || strcmp(patrat[linr-i][colr-i].piesa.tip,"nebun")==0))//daca prima piesa gasita este un nebun sau regina adversa
            return 1;//regele se afla in sah
           break;//opreste cautarea
        }
        i++;
    }
    ///verifica daca regele este atacat de regina sau o tura adversa pe verticala ,sus
    i=1;
    while(linr-i>=1)
    {
        if(patrat[linr-i][colr].gol==0)
        {
            if(patrat[linr-i][colr].piesa.culoare!=c && (strcmp(patrat[linr-i][colr].piesa.tip,"regina")==0 || strcmp(patrat[linr-i][colr].piesa.tip,"tura")==0))//daca prima piesa gasita este o tura sau regina adversa
                return 1;
            break;
        }
        i++;
    }
    ///verifica daca regele este atacat de regina  sau o tura adversa pe verticala , jos
    i=1;
    while(linr+i<=DIM_TABLA)
    {
        if(patrat[linr+i][colr].gol==0)
        {
            if(patrat[linr+i][colr].piesa.culoare!=c && (strcmp(patrat[linr+i][colr].piesa.tip,"regina")==0 || strcmp(patrat[linr+i][colr].piesa.tip,"tura")==0))//daca prima piesa gasita este o tura sau regina adversa
                return 1;
            break;
        }
        i++;
    }
    ///verifica daca regele este atacat de regina sau o tura adversa pe orizontala , dreapta
    i=1;
    while(colr+i<=DIM_TABLA)
    {
        if(patrat[linr][colr+i].gol==0)
        {
            if(patrat[linr][colr+i].piesa.culoare!=c && (strcmp(patrat[linr][colr+i].piesa.tip,"regina")==0 || strcmp(patrat[linr][colr+i].piesa.tip,"tura")==0))//daca prima piesa gasita este o tura sau regina adversa
                return 1;
            break;
        }
        i++;
    }
    ///verifica daca regele este atacat de regina sau o tura adversa pe orizontala , stanga
    i=1;
    while(colr-i>=1)
    {
        if(patrat[linr][colr-i].gol==0)
        {
            if(patrat[linr][colr-i].piesa.culoare!=c && (strcmp(patrat[linr][colr-i].piesa.tip,"regina")==0 || strcmp(patrat[linr][colr-i].piesa.tip,"tura")==0))//daca prima piesa gasita este o tura sau regina adversa
                return 1;
            break;
        }
        i++;
    }
    return 0;///regele nu se afla in sah
}

void muta_rege(int c,patrate patrat[9][9],int *sah_mat)
{
    patrate aux;
    int i,j,k,linr_sah,colr_sah,linr_adv,colr_adv,p[20];
    char linie,coloana;
    //cautam coordonatele celor doi regi
    for(i=1;i<=DIM_TABLA;i++)
        for(j=1;j<=DIM_TABLA;j++)
        {
            if(patrat[i][j].gol==0 && strcmp(patrat[i][j].piesa.tip,"rege")==0 && patrat[i][j].piesa.culoare==c)
            {
                linr_sah=i;//linia regelui care se afla in sah =i
                colr_sah=j;//coloana regelui care se afla in sah =j
            }
            if( patrat[i][j].gol==0 && strcmp(patrat[i][j].piesa.tip,"rege")==0 && patrat[i][j].piesa.culoare!=c)
            {
                linr_adv=i;//linia regelui advers =i
                colr_adv=j;//coloana regelui advers=j
            }
        }

    ///cautam pozitiile in care regele poate muta(daca nu exista niciuna , este sah mat)
    p[0]=0;//p[0] retine nr de pozitii gasite
    for(i=-1;i<=1;i++)
        for(j=-1;j<=1;j++)//adunandu-se i si j la linia si ,respectiv , coloana regelui se vor obtine toate pozitiile adiacente pozitiei regelui
    {
        if(linr_sah+i>=1 && linr_sah+i<=8 && colr_sah+j>=1 && colr_sah+j<=8 && (abs((linr_sah+i)-linr_adv)>1 || abs((colr_sah+j)-colr_adv)>1) )//daca pozitia se afla pe tabla si nu este adiacenta pozitiei regelui
        {
            if(patrat[linr_sah+i][colr_sah+j].gol==1)//patratul este gol
            {
                //pune regele in patratul gol
                patrat[linr_sah+i][colr_sah+j].piesa=patrat[linr_sah][colr_sah].piesa;
                patrat[linr_sah+i][colr_sah+j].gol=0;
                patrat[linr_sah][colr_sah].gol=1;
                if(rege_sah(c,patrat)==0)//verifica daca regele este in sah
                {
                    //in aceasta pozitie regele poate muta. salveaza pozitia
                    p[0]++;
                    p[p[0]*2-1]=linr_sah+i;
                    p[p[0]*2]=colr_sah+j;
                }
                //pune regele inapoi in locul sau
                patrat[linr_sah+i][colr_sah+j].gol=1;
                patrat[linr_sah][colr_sah].gol=0;
            }
            else
                if(patrat[linr_sah+i][colr_sah+j].piesa.culoare!=c)//daca piesa este adversa
            {
                //pune regele in pozitia piesei adverse respective
                aux.piesa=patrat[linr_sah+i][colr_sah+j].piesa;
                patrat[linr_sah+i][colr_sah+j].piesa=patrat[linr_sah][colr_sah].piesa;
                patrat[linr_sah][colr_sah].gol=1;
                if(rege_sah(c,patrat)==0)//regele nu se afla in sah
                {
                    //in aceasta pozitie regele poate muta. salveaza pozitia
                    p[0]++;
                    p[p[0]*2-1]=linr_sah+i;
                    p[p[0]*2]=colr_sah+j;
                }
                //regele si piesa adversa respectiva sunt puse la loc
                patrat[linr_sah][colr_sah].gol=0;
                patrat[linr_sah+i][colr_sah+j].piesa=aux.piesa;
            }
        }
    }
    if(p[0]==0)//daca nu s-a gasit nici o pozitie in care regele sa poata muta
    {
        *sah_mat=1;//este sah_mat
        return;
    }
    else
    {
        //regele poate fi mutat
        printf("Introduceti coordonatele patratului in care mutati regele.(linie , enter, coloana)\n");
        int ok=0;//ok=0 daca pozitia in care jucatorul alege sa mute regele nu este buna
        while(ok==0)
        {
            scanf(" %c %c",&linie,&coloana);
            while(!(linie>='1' && linie<='8' && coloana>='1' && coloana<='8'))//pozitia indicata nu se afla pe tabla si sunt introdu se corect
            {
                printf("Coordonatele sunt numere intregi din intervalul [1,8] si trebuie introduse respectand ordinea linie , enter , coloana.\n");
                scanf(" %c %c",&linie,&coloana);
            }
            i=(int)(linie-'0');
            j=(int)(coloana-'0');
        for(k=1;k<=p[0];k++)//parcurgem vectorul care memoreaza pozitiile in care regele poate fi mutat
        {
            if(i==p[k*2-1] && j==p[k*2])
            {
                //pozitia aleasa este buna.regele este mutat
                patrat[i][j].piesa=patrat[linr_sah][colr_sah].piesa;
                patrat[i][j].gol=0;
                patrat[linr_sah][colr_sah].gol=1;
                ok=1;//regele a fost mutat intr o pozitie buna
            }
        }
        if(ok==0)
        {
            printf("Regele nu poate fi mutat in patratul indicat,introduceti coordonatele din nou.\n");
        }
        }
    }
}

void muta(int c , patrate patrat[9][9])//jucatorul c muta o piesa
{
    int lin_piesa,col_piesa,lin_destinatie,col_destinatie,raspuns,comparatie_linie,comparatie_coloana,i,j;
    char linie,coloana;

    //introducerea coordonatelor patratului in care se afla piesa pe care jucatorul c vrea sa o mute
    introduceti_datele:;
    printf("\nIntroduceti coordonatele patratului in care se afla piesa pe care vreti sa o mutati.(linie , enter , coloana)\n");
    scanf(" %c %c",&linie,&coloana);
    if(!(linie>='1' && linie<='8' && coloana>='1' && coloana<='8'))//pozitia indicata nu se afla pe tabla si sunt introdu se corect
    {
        printf("Coordonatele sunt numere intregi din intervalul [1,8] si trebuie introduse respectand ordinea linie , enter , coloana.\n");
        goto introduceti_datele;
    }
    lin_piesa=(int)(linie-'0');
    col_piesa=(int)(coloana-'0');

    if(patrat[lin_piesa][col_piesa].gol==1 )//patratul indicat este gol
    {
        printf("\n In patratul indicat nu se afla nici o piesa");
        goto introduceti_datele;
    }
    if(patrat[lin_piesa][col_piesa].piesa.culoare!=c )//patratul indicat contine o piesa adversa.
    {
        printf("\n Nu puteti muta piesele adversarului");
        goto introduceti_datele;
    }

    //introducerea coordonatelor patratului in care jucatorul cu nr c vrea sa mute
    introduceti_coordonatele_destinatie:;
    printf("\n Introduceti coordonatele patratului in care vreti sa mutati.(linie , enter , coloana) \n");
    scanf(" %c %c",&linie,&coloana);
    if(!(linie>='1' && linie<='8' && coloana>='1' && coloana<='8'))//pozitia indicata nu se afla pe tabla si sunt introdu se corect
    {
        printf("Coordonatele sunt numere intregi din intervalul [1,8] si trebuie introduse respectand ordinea linie , enter , coloana.\n");
        goto introduceti_datele;
    }
    lin_destinatie=(int)(linie-'0');
    col_destinatie=(int)(coloana-'0');

    if(patrat[lin_destinatie][col_destinatie].gol==0 && patrat[lin_destinatie][col_destinatie].piesa.culoare==c)//daca patratul in care jucatorul c vrea sa mute deja contine o piesa proprie
    {
        printf("Nu va puteti ataca propria piesa.Doriti sa mutati acceasi piesa,dar in alt patrat? ( 1-DA , 0-NU)\n");
        scanf("%d",&raspuns);
        while(raspuns !=0 && raspuns != 1)
        {
            printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
            scanf("%d",&raspuns);
        }
        if(raspuns==1)
            goto introduceti_coordonatele_destinatie;
        else
            goto introduceti_datele;
    }
    //verificam daca patratul indicat contine regele advers
    if(strcmp(patrat[lin_destinatie][col_destinatie].piesa.tip,"rege")==0)
    {
        printf("Nu puteti ataca regele inamic.Doriti sa mutati aceeasi piesa , dar in alta pozitie? ( 1-DA , 0-NU)\n");
        scanf("%d",&raspuns);
        while(raspuns !=0 && raspuns != 1)
        {
            printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
            scanf("%d",&raspuns);
        }
        if(raspuns==1)
            goto introduceti_coordonatele_destinatie;
        else
            goto introduceti_datele;
    }

    ///verificam daca piesa mutata este un pion si daca poate fi mutata in patratul indicat
    if(strcmp(patrat[lin_piesa][col_piesa].piesa.tip,"pion")==0)
    {
        if(lin_destinatie==lin_piesa+(-1+c*2) && ( (col_destinatie==col_piesa && patrat[lin_destinatie][col_destinatie].gol==1) || ( ( col_destinatie==col_piesa-1 || col_destinatie==col_piesa+1)  && patrat[lin_destinatie][col_destinatie].gol==0) ) )//daca pionul este mutat cu o linie inainte si patratul in care a mutat era gol. sau daca pionul este mutat cu o linie inainte si o coloana la stanga sau dreapta , iar patratul contine o piesa adversa
        {
            //muta pionul
            patrat[lin_destinatie][col_destinatie].piesa=patrat[lin_piesa][col_piesa].piesa;
            patrat[lin_destinatie][col_destinatie].gol=0;
            patrat[lin_piesa][col_piesa].gol=1;
        }
        else
        {
            printf("Nu puteti muta in patratul indicat.Mutati aceeasi piesa , dar in alt patrat? ( 1-DA , 0-NU) \n");
            scanf("%d",&raspuns);
        while(raspuns !=0 && raspuns != 1)
        {
            printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
            scanf("%d",&raspuns);
        }
        if(raspuns==1)
            goto introduceti_coordonatele_destinatie;
        else
            goto introduceti_datele;

        }
    }

    /////verificam daca piesa mutata este o tura si daca poate fi mutata in patratul indicat
    if(strcmp(patrat[lin_piesa][col_piesa].piesa.tip,"tura")==0)
    {
        if(lin_destinatie==lin_piesa)//patratul in care tura se afla dupa mutare se afla pe aceeasi linie cu cel de dinainte
        {
            comparatie_coloana=abs(col_destinatie-col_piesa)/(col_destinatie-col_piesa);//comparatie_linie marcheaza daca coloana patratului in care este mutata tura se afla la stanga sau la dreapta coloanei in care se afla
            for(i=col_piesa+comparatie_coloana;i!=col_destinatie;i=i+comparatie_coloana)
                if(patrat[lin_destinatie][i].gol==0)//intre patratul de dinainte si de dupa mutare se afla o piesa
            {
                printf("Nu este drum liber pana la patratul indicat.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
                scanf("%d",&raspuns);
                while(raspuns !=0 && raspuns != 1)
                {
                    printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                    scanf("%d",&raspuns);
                }
                if(raspuns==1)
                    goto introduceti_coordonatele_destinatie;
                else
                    goto introduceti_datele;
            }
            //tura este mutata
            patrat[lin_destinatie][col_destinatie].piesa=patrat[lin_piesa][col_piesa].piesa;
            patrat[lin_destinatie][col_destinatie].gol=0;
            patrat[lin_piesa][col_piesa].gol=1;
        }
        if(col_destinatie==col_piesa)//daca patratele de dinainte si de dupa mutare se afla pe aceeasi coloana
        {
            comparatie_linie=abs(lin_destinatie-lin_piesa)/(lin_destinatie-lin_piesa);//comparatie_linie marcheaza daca patratul de dinainte de mutare se afla mai sus sau mai jos decat cel de dupa
            for(i=lin_piesa+comparatie_linie;i!=lin_destinatie;i=i+comparatie_linie)
                if(patrat[i][col_destinatie].gol==0)//intrat patratul de dinainte si de dupa mutare se afla o piesa
            {
                printf("Nu este drum liber pana la patratul indicat.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
                scanf("%d",&raspuns);
                while(raspuns !=0 && raspuns != 1)
                {
                    printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                    scanf("%d",&raspuns);
                }
                if(raspuns==1)
                    goto introduceti_coordonatele_destinatie;
                else
                    goto introduceti_datele;
            }
            //tura este mutata
            patrat[lin_destinatie][col_destinatie].piesa=patrat[lin_piesa][col_piesa].piesa;
            patrat[lin_destinatie][col_destinatie].gol=0;
            patrat[lin_piesa][col_piesa].gol=1;
        }
        if(lin_piesa != lin_destinatie && col_piesa!=col_destinatie)//daca tura nu a fost mutata pe orizontala sau pe verticala
        {
            printf("Tura poate fi mutata doar pe verticala sau orizontala.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
            scanf("%d",&raspuns);
            while(raspuns !=0 && raspuns != 1)
            {
                printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                scanf("%d",&raspuns);
            }
            if(raspuns==1)
                goto introduceti_coordonatele_destinatie;
            else
                goto introduceti_datele;
        }
    }

    ///verificam daca piesa mutata este un cal si daca poate fi mutata in patratul indicat
    if(strcmp(patrat[lin_piesa][col_piesa].piesa.tip,"cal")==0)
    {
        if( (abs(lin_destinatie-lin_piesa==2) && abs(col_destinatie-col_piesa)==1) || ( abs(lin_destinatie-lin_piesa==1) && abs(col_destinatie-col_piesa)==2) )//daca calul a fost mutata in L
        {
            //muta calul
            patrat[lin_destinatie][col_destinatie].piesa=patrat[lin_piesa][col_piesa].piesa;
            patrat[lin_destinatie][col_destinatie].gol=0;
            patrat[lin_piesa][col_piesa].gol=1;
        }
        else
        {
            printf("Calul poate fi mutat doar in L.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
            scanf("%d",&raspuns);
            while(raspuns !=0 && raspuns != 1)
            {
                printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                scanf("%d",&raspuns);
            }
            if(raspuns==1)
                goto introduceti_coordonatele_destinatie;
            else
                goto introduceti_datele;
        }
    }
    ///verificam daca piesa mutata este un nebun si daca poate fi mutata in patratul indicat
    if(strcmp(patrat[lin_piesa][col_piesa].piesa.tip,"nebun")==0)
    {
        if(abs(lin_destinatie-lin_piesa)==abs(col_destinatie-col_piesa))//daca nebunul a fost mutat pe diagonala
        {
            comparatie_linie=abs(lin_destinatie-lin_piesa)/(lin_destinatie-lin_piesa);//aflam daca a fost mutat in sus sau in jos
            comparatie_coloana=abs(col_destinatie-col_piesa)/(col_destinatie-col_piesa);//aflam daca a fost mutat la stanga sau la dreapta
            for(i=1;lin_piesa+i*comparatie_linie!=lin_destinatie;i++)
            {
                if(patrat[lin_piesa+i*comparatie_linie][col_piesa+i*comparatie_coloana].gol==0)//intre patratul in care se afla inainte si cel in care se afla dupa mutare este o piesa
                {
                    printf("Nu este drum liber pana la patratul indicat.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
                    scanf("%d",&raspuns);
                    while(raspuns !=0 && raspuns != 1)
                    {
                        printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                        scanf("%d",&raspuns);
                    }
                    if(raspuns==1)
                        goto introduceti_coordonatele_destinatie;
                    else
                        goto introduceti_datele;
                }
            }
            //muta nebunul
            patrat[lin_destinatie][col_destinatie].piesa=patrat[lin_piesa][col_piesa].piesa;
            patrat[lin_destinatie][col_destinatie].gol=0;
            patrat[lin_piesa][col_piesa].gol=1;
        }
        else
        {
            printf("Nebunul poate fi mutat doar pe diagonala. Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
            scanf("%d",&raspuns);
            while(raspuns !=0 && raspuns != 1)
            {
                printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                scanf("%d",&raspuns);
            }
            if(raspuns==1)
                goto introduceti_coordonatele_destinatie;
            else
                goto introduceti_datele;
        }
    }
    ///verificam daca piesa mutata este regina si daca poate fi mutata in patratul indicat
    if(strcmp(patrat[lin_piesa][col_piesa].piesa.tip,"regina")==0)
    {
        if(abs(lin_destinatie-lin_piesa)==abs(col_destinatie-col_piesa))//regina este mutata pe diagonala
        {
            comparatie_linie=abs(lin_destinatie-lin_piesa)/(lin_destinatie-lin_piesa);//aflam daca in sus sau in jos
            comparatie_coloana=abs(col_destinatie-col_piesa)/(col_destinatie-col_piesa);//aflam daca la stanga sau la dreapta
            for(i=1;lin_piesa+i*comparatie_linie!=lin_destinatie;i++)
            {
                if(patrat[lin_piesa+i*comparatie_linie][col_piesa+i*comparatie_coloana].gol==0)//intre patratul in care se afla regina inainte si cel in care se afla dupa mutare este o piesa
                {
                    printf("Nu este drum liber pana la patratul indicat.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
                    scanf("%d",&raspuns);
                    while(raspuns !=0 && raspuns != 1)
                    {
                        printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                        scanf("%d",&raspuns);
                    }
                    if(raspuns==1)
                        goto introduceti_coordonatele_destinatie;
                    else
                        goto introduceti_datele;
                }
            }
            //regina este mutata
            patrat[lin_destinatie][col_destinatie].piesa=patrat[lin_piesa][col_piesa].piesa;
            patrat[lin_destinatie][col_destinatie].gol=0;
            patrat[lin_piesa][col_piesa].gol=1;
        }

        if(lin_destinatie==lin_piesa)//se doreste ca regina sa fie mutata pe orizontala
        {
            comparatie_coloana=abs(col_destinatie-col_piesa)/(col_destinatie-col_piesa);//aflam daca la stanga sau la dreapta
            for(i=col_piesa+comparatie_coloana;i!=col_destinatie;i=i+comparatie_coloana)
                if(patrat[lin_destinatie][i].gol==0)//intre patratul de inainte si cel de dupa mutare este o piesa.
            {
                printf("Nu este drum liber pana la patratul indicat.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
                scanf("%d",&raspuns);
                while(raspuns !=0 && raspuns != 1)
                {
                    printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                    scanf("%d",&raspuns);
                }
                if(raspuns==1)
                    goto introduceti_coordonatele_destinatie;
                else
                    goto introduceti_datele;
            }
            //regina este mutata
            patrat[lin_destinatie][col_destinatie].piesa=patrat[lin_piesa][col_piesa].piesa;
            patrat[lin_destinatie][col_destinatie].gol=0;
            patrat[lin_piesa][col_piesa].gol=1;
        }
        if(col_destinatie==col_piesa)//se doreste ca regina sa fie mutata pe verticala
        {
            comparatie_linie=abs(lin_destinatie-lin_piesa)/(lin_destinatie-lin_piesa);//aflam daca in sus sau in jos
            for(i=lin_piesa+comparatie_linie;i!=lin_destinatie;i=i+comparatie_linie)
                if(patrat[i][col_destinatie].gol==0)//intre patratul de dinainte si cel de dupa mutare se afla o piesa
            {
                printf("Nu este drum liber pana la piesa atacata.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
                scanf("%d",&raspuns);
                while(raspuns !=0 && raspuns != 1)
                {
                    printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                    scanf("%d",&raspuns);
                }
                if(raspuns==1)
                    goto introduceti_coordonatele_destinatie;
                else
                    goto introduceti_datele;
            }
            //regina este mutata
            patrat[lin_destinatie][col_destinatie].piesa=patrat[lin_piesa][col_piesa].piesa;
            patrat[lin_destinatie][col_destinatie].gol=0;
            patrat[lin_piesa][col_piesa].gol=1;
        }

        if( (abs(lin_destinatie-lin_piesa)!=abs(col_destinatie-col_piesa)) && lin_destinatie!=lin_piesa && col_destinatie!=col_piesa)//regina nu a fost mutata nici pe diagonala , nici pe verticala , nici pe orizontala
        {
            printf("Regina poate fi mutata doar pe diagonala , verticala sau orizontala.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
            scanf("%d",&raspuns);
            while(raspuns !=0 && raspuns != 1)
            {
                printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                scanf("%d",&raspuns);
            }
            if(raspuns==1)
                goto introduceti_coordonatele_destinatie;
            else
                goto introduceti_datele;
        }
    }
    ///verificam daca piesa mutata este un rege si daca poate fi mutata in patratul indicat
    if(strcmp(patrat[lin_piesa][col_piesa].piesa.tip,"rege")==0)
    {
        if(abs(lin_destinatie-lin_piesa)<=1 && abs(col_destinatie-col_piesa)<=1)//daca patratul in care se doreste sa se mute este adiacent cu cel in care se afla regele
        {
            for(i=-1;i<=1;i++)
                for(j=-1;j<=1;j++)
            {
                if(patrat[lin_destinatie+i][col_destinatie+j].gol==0 && strcmp(patrat[lin_destinatie+i][col_destinatie+j].piesa.tip,"rege")==0 && patrat[lin_destinatie+i][col_destinatie+j].piesa.culoare!=c)
                {
                    printf("Patratul indicat se afla prea aproape de regle advers.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
                    scanf("%d",&raspuns);
                    while(raspuns !=0 && raspuns != 1)
                    {
                        printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                        scanf("%d",&raspuns);
                    }
                    if(raspuns==1)
                        goto introduceti_coordonatele_destinatie;
                    else
                        goto introduceti_datele;
                }
            }
            //regele este mutat
            patrat[lin_destinatie][col_destinatie].piesa=patrat[lin_piesa][col_piesa].piesa;
            patrat[lin_destinatie][col_destinatie].gol=0;
            patrat[lin_piesa][col_piesa].gol=1;
        }
        else
        {
            printf("Regele poate fi mutat doar intr-un patrat adiacent.Doriti sa mutati aceeasi piesa , dar in alt patrat? (1-DA , 0-NU)\n");
            scanf("%d",&raspuns);
            while(raspuns !=0 && raspuns != 1)
            {
                printf("Raspunsul poate fi 0 sau 1 , introduceti-l din nou.\n");
                scanf("%d",&raspuns);
            }
            if(raspuns==1)
                goto introduceti_coordonatele_destinatie;
            else
                goto introduceti_datele;
        }
    }
    if(rege_sah(c,patrat)==1)//daca regele se afla in sah
    {
        printf("Mutarea nu poate fi facuta ,deoarece in urma ei regele ar intra in sah\n");
        goto introduceti_datele;
    }

}

void verifica_remiza(patrate patrat[9][9],int *remiza)//verifica daca este remiza , adica daca pe tabla au ramas doar regii
{
    int i,j;
    for(i=1;i<=DIM_TABLA;i++)
        for(j=1;j<=DIM_TABLA;j++)
        if(patrat[i][j].gol==0 && strcmp(patrat[i][j].piesa.tip,"rege")!=0)//daca este o piesa diferita de rege
        return;//nu este remiza
    *remiza=1;//este remiza ,deoarece nu s-a gasit nicio piesa in afara de regi
}


