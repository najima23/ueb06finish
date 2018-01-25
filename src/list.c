/****************************************************************************************************
*****************************************************************************************************
*** modul:           list.c
*** BESCHREIBUNG:    Verkettete Liste
*** GLOBALE FKT:     insertInDVList
***                  removeFromDVList
***                  freeOneTeam
***                  freeOnePlayer
*** LOKALE FKT:      compare
*****************************************************************************************************
****************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "list.h"

int compare(TTeam *, TTeam *);

/***********************************************************
 * function:      insertInDVList
 * descreption:  for sorted paste into the double chained
 *                list
 * Parameter:     -/-
 * Rueckgabe:     -/-
 ***********************************************************/
int insertInDVList(TTeam *Neu)
{
   TTeam *akt = FirstTeam;

   if(!Neu)
      return 0;

   if(FirstTeam == NULL)
   {
      FirstTeam = LastTeam = Neu;
      return 1;
   }

   if(compare(FirstTeam, Neu) >=0)
   {
      Neu->Next = FirstTeam;
      Neu->Prev = NULL;
      FirstTeam = FirstTeam->Prev = Neu;
      return 1;
   }

   if(compare(LastTeam, Neu) <= 0)
   {
      Neu->Next = NULL;
      Neu->Prev = LastTeam;
      LastTeam = LastTeam->Next = Neu;
      return 1;
   }

   while(akt->Next != NULL)
   {
      if(compare(akt->Next, Neu) >= 0)
      {
         Neu->Next = akt->Next;          // (1.1)
         Neu->Prev = akt;                // (1.2)
         akt->Next->Prev = Neu;          // (1.3)
         akt->Next = Neu;                // (1.4)
         return 1;
      }
      akt = akt->Next;
   }
   return 0;
}

/***********************************************************
 * Funktion:      removeFromDVList
 * Beschreibung:  remove from double chained list
 * Parameter:     -/-
 * Rueckgabe:     -/-
 ***********************************************************/
TTeam *removeFromDVList(TTeam *Del)
{
   TTeam *akt = FirstTeam, *tmp = NULL;
   if(!Del)
      return NULL;
   if(FirstTeam == NULL)
      return NULL;
   if(compare(FirstTeam, Del) == 0)
   {
      if(FirstTeam->Next == NULL)
      {
         tmp = FirstTeam;
         FirstTeam = LastTeam = NULL;
         return tmp;
      }
      FirstTeam->Next->Prev = NULL;           // (2.1)
      tmp = FirstTeam;                        // (2.2)
      FirstTeam = FirstTeam->Next;            // (2.3)
      return tmp;
   }
   if(compare(LastTeam, Del) == 0)
   {
      LastTeam->Prev->Next = NULL;            // (3.)
      tmp = LastTeam;
      LastTeam = LastTeam->Prev;
      return tmp;
   }
   while(akt->Next != NULL)
   {
      if(compare(akt->Next, Del) == 0)
      {
         tmp = akt->Next;                // (4.1)
         tmp->Next->Prev = akt;          // (4.2)
         akt->Next = tmp->Next;          // (4.3)
         return tmp;
      }
      akt = akt->Next;
   }
   return NULL;
}
/***********************************************************
 * Funktion:      compare
 * Beschreibung:
 * Parameter:     -/-
 * Rueckgabe:     -/-
 ***********************************************************/
int compare(TTeam *D1, TTeam *D2)
{
   return(strcmp(D1->Name, D2->Name));
}

/***********************************************************
 * Funktion:      freeOneTeam
 * Beschreibung:
 * Parameter:     -/-
 * Rueckgabe:     -/-
 ***********************************************************/
void freeOneTeam(TTeam *deleteTeam)
{
   int i = 0;

   free(deleteTeam->Name);
   free(deleteTeam->Coach);
   while(i < deleteTeam->Size)x
   {
      freeOnePlayer(deleteTeam->Player + i);
      i++;
   }
   free(deleteTeam);
}

/***********************************************************
 * Funktion:      freeOnePlayer
 * BxxxXeschreibung:
 * Parameter:     -/-
 * Rueckgabe:     -/-
 ***********************************************************/
void freeOnePlayer(TPlayer *deletePlayer)
{
   free(deletePlayer->Name);
   free(deletePlayer->Birthday);
}
