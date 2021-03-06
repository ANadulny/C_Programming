#include<stdio.h>
#include<time.h>   //dzialanie funkcji
#include<stdlib.h> //srand
#include <unistd.h> //dzialanie funkcji sleep()

char kolory[4][6]={"kier","karo","pik","trefl"};
int tab[4]={1,2,3,4};// 1-to kier, 2- to karo, 3- to pik, 4- to trefl
char figury[13][8]={"2","3","4","5","6","7","8","9","10","As","Walet","Dama","Krol"}; //rodzaj karty
int tablica[13]={2,3,4,5,6,7,8,9,10,11,2,3,4};

const int STALA = 20;
int Gracz1[20];     //wartosci wylosowanych figur
int Gracz2[20];    // wartosci wylosowanego koloru

int Komputer1[20];  //wartosci wylosowanych figur
int Komputer2[20];  //wartosci wylosowanego koloru

int CzyBylaWylosowana(int bLiczba, int aLiczba, int t1[], int t2[])
{
     int i; //zmienna pomocnicza
     for(i=0;i<STALA; i++)
     {
        if( tablica[bLiczba] == t1[i])
            if(tab[aLiczba]==t2[i])
             {
               return 2; //true - 2;
               break;
             }
     }
     return 1; //false - 1
}

void sleepcp(int milliseconds) // opoznienie programu
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

int main()
{
    srand(time(NULL));
    int a, b, i; //zmienne pomocnicze
    int sumaGracza=0; //suma wartosci wszystkich kart na rece
    int sumaKomputer=0; //suma wartosci wyszystkich kart komputera
    int przegrana = 0; //zmienna pomocnicza do sprawdzenia czy gracz przegral to wtedy komp nie dostaje swoich kart gra skonczona
    int przegranaKomp =0; //zmienna pomocnicza do sprawdzenia czy komp przegral to wtedy gracz wygrywa
for (i=0; i<20; i++) //Dla gracza
{
   a=rand()%4;  // a to kolor
   b=rand()%13; // b to rodzaj karty
   if( CzyBylaWylosowana(b, a, Gracz1, Gracz2) == 1 )
   {
        sumaGracza += tablica[b];
        printf("\t %s %s\n", figury[b], kolory[a]);
        Gracz1[i]=b+2;
        Gracz2[i]=a+1;

if(i>=1)
        {
         if(sumaGracza==21)
              {
                 sleepcp(1000);
                 system( "clear" );
                 printf("Twoje karty to: \n");
                    int j;
                    for(j=0;j<STALA; j++)
                       {
                          if(Gracz1[j] != 0)
                         printf("\t \t %s %s\n", figury[Gracz1[j]-2], kolory[Gracz2[j]-1]);
                       }
                     printf("\nTwoja suma kart to: %d\n", sumaGracza);
                  printf("\t \tMasz oczko\n");
                 break;
              }
         else if(sumaGracza>22)
              {
                sleepcp(1000);
                system( "clear" );
                printf("Masz za duza wartosc kart: %d \n \tPrzegrales!", sumaGracza);
                przegrana=1;
                break;
              }
         else if(sumaGracza == 22)
              {
                if(Gracz1[0]==11 && Gracz1[1]==11) //szczegolny przypadek dla As i As na poczatku gry
                 {
                  sleepcp(1000);
                  system( "clear" );
                  printf("Twoje karty to: \n");
                    int j;
                    for(j=0;j<STALA; j++)
                       {
                          if(Gracz1[j] != 0)
                         printf("\t \t %s %s\n", figury[Gracz1[j]-2], kolory[Gracz2[j]-1]);
                       }
                     printf("\nTwoja suma kart to: %d\n", sumaGracza);
                   printf("\t \tMasz oczko\n");
                  break;
                 }
                 else
                 {
                  sleepcp(1000);
                  system( "clear" );
                  printf("Masz za duza wartosc kart: %d \n \tPrzegrales!", sumaGracza);
                  przegrana=1;
                  break;
                 }
              }
         else if(sumaGracza<21)
                {
                  sleepcp(2000);
                  int nowy=0;
                  do
                  {
                    system( "clear" );
                    printf("Twoje karty to: \n");
                    int j;
                    for(j=0;j<STALA; j++)
                       {
                          if(Gracz1[j] != 0)
                         printf("\t \t %s %s\n", figury[Gracz1[j]-2], kolory[Gracz2[j]-1]);
                       }
                     printf("\nTwoja suma kart to: %d\n", sumaGracza);
                     printf("\nCzy chcesz ciagnac karte? \nWpisz 1 jezeli chcesz, w innym wypadku wpisz 0.\n");
                     scanf("%d", &nowy);   //cin>>nowy; //nie wiem czy dobrze
                  }//petla do ... while
                  while(nowy != 1 && nowy != 0);

                  if(nowy == 0)
                      {
                        system( "clear" );
                        printf("\nTwoja suma kart to: %d\n \n",sumaGracza);
                        break;
                      }
                 } //else if(suma<=21)
         }//if(i>=1)
    }
} //dla gracza

if(przegrana==0)
{
  printf("Karty komputera to:\n");
  for (i=0; i<20; i++) //Dla komputera
  {
     a=rand()%4;  // a to kolor
     b=rand()%13; // b to rodzaj karty
     if( CzyBylaWylosowana(b, a, Gracz1, Gracz2) == 1 )
        if( CzyBylaWylosowana(b, a, Komputer1, Komputer2) == 1 )
          {
           sumaKomputer += tablica[b];
           printf("\t %s %s\n",figury[b], kolory[a]);
           Komputer1[i]=b+2;
           Komputer2[i]=a+1;
              if(sumaKomputer > 16 && sumaKomputer < 21)
              {
                 printf("\nSuma kart komputera to: %d\n", sumaKomputer);
                 break;
              }
              else if(sumaKomputer == 21)
                {
                  printf("\nKomputer ma oczko: \n");
                  break;
                }
              else if(sumaKomputer == 22)
               {
                   if(Komputer1[0]==11 && Komputer1[1]==11) //szczegolny przypadek dla As i As na poczatku gry
                   {
                  printf("\t \tKomputer ma oczko\n");
                  break;
                 }
                 else
                 {
                  printf("Komputer ma za duza wartosc kart: %d", sumaKomputer);
                  przegranaKomp=1;
                  break;
                 }
               }  // zamyka else if(sumaKomputer == 22)
               else if(sumaKomputer > 22)
               {
                  printf("Komputer ma za duza wartosc kart: %d",sumaKomputer);
                  przegranaKomp=1;
                  break;
               }
          }
  }//zamyka for
}//zamyka nawias dla if(przegrana==0)


printf("\n \n");
   if(przegranaKomp == 1)
      printf("\tGracz wygal!!!\n \t Gratulacje!");
   else //if(przegranaKomp == 0)
   {
      if((sumaKomputer<=21 && sumaGracza <21 && (sumaKomputer > sumaGracza)) || (sumaKomputer == 22 && sumaGracza == 21) || ((sumaKomputer == 21 || sumaKomputer == 22)&& sumaGracza < 21))
        printf("Komputer wygral!");
      else if((sumaKomputer<21 && sumaGracza <=21 && (sumaKomputer < sumaGracza)) || (sumaKomputer == 21 && sumaGracza == 22))
         printf("Gracz wygral! Gratulacje!");
      else
         printf("Remis!");
   }

return 0;
}
