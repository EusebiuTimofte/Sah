#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functii.h"
#include "constante.h"

int main()
{
    int sah_mat=0,remiza=0,c=1;// variabila c memoreaza
    //se stabilesc numele jucatorilor
    char nume_player1[20],nume_player2[20];
    printf("Introduceti numele primului jucator.\n");
    scanf("%s",nume_player1);
    printf("Introduceti numele celui de-al doilea jucator.\n");
    scanf("%s",nume_player2);

    patrate patrat[9][9];//variabila ce memoreaza tabla de sah
    aseaza_piesele(patrat);//piesele sunt asezate in pozitia de start

    while(sah_mat==0 && remiza==0)//cat timp nu este sah mat
    {
        afiseaza(patrat);//tabla este afisata
        //specifica randul carui jucator este
        if(c==0)
            printf("Este randul jucatorului %s.(numar %d)\n",nume_player1,c);
        else
            printf("Este randul jucatorului %s. (numar %d)\n",nume_player2,c);

        if(rege_sah(c,patrat))//daca jucatorul care muta este in sah
        {
            printf("Regele %d este in sah.\n",c);
            muta_rege(c,patrat,&sah_mat);//jucatorul cu nr c este obligat sa-si mute regele , iar daca nu poate , este sah mat
        }
        else
            muta(c,patrat);//jucatorul cu nr c isi muta o piesa
        c=(c+1)%2;
        verifica_remiza(patrat,&remiza);//verifica daca este remiza
    }
    //afiseaza numele castigatorului
    if(sah_mat==1)
    {
        if(c==0)
            printf("SAH MAT! Jucatorul %s a castigat!",nume_player1);
        else
            printf("SAH MAT! Jucatorul %s a castigat!",nume_player2);
    }
    if(remiza==1)
        printf("Este remiza!");
    return 0;
}
