/****************************************************************************************************
*****************************************************************************************************
*** modul:           sort.c
*** description:    file for sort
*** global FKT:     quickSort
***                 cmpName
***                 cmpBirthday
***                 cmpTrikot
***                 cmpGoals
*** local FKT:      swap
***                 partition
***                 qsort
*****************************************************************************************************
****************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "datastructure.h"
#include "sort.h"

void swap(TPlayer *, TPlayer *);


/**********************************************************
 * function:      partition
 * description:   devide array in two parts each with differents size
 * parameter:     Array - array for sort
 *                ui  - sort lower part of array
 *                oi    - sort higher part of array
 * return:     int   - index of middle value
 **********************************************************/

int partition(TPlayer *Array, int ui, int oi, int (*cmp)(TPlayer *, TPlayer *))
{
   int i = ui + 1, j = oi;
   TPlayer *comp = (Array + ui);

   while (i <= j)
   {

      while ((i <= j) && (cmp((Array + i), comp) <= 0))
         i++;

      while ((j >= i) && (cmp((Array + j), comp) >= 0))
         j--;
      if (i < j)
      {
         swap(Array + i, Array + j);
         i++;
         j--;
      }
   }
   i--;
   swap(comp, Array + i);
   return i;
}

/**********************************************************
 * function:      qsort
 * description:  split array in two parts and sort left and
 *                right recursivly
 * Parameter:     Array - array for sort
 *                ui  - sort lower part of array
 *                oi    - sort higher part of array
 * return:     -/-
 **********************************************************/
void qsort(TPlayer *Array, int ui, int oi, int (*cmp)(TPlayer *, TPlayer *))
{
   int idx;      // Schranke middle value

   if (ui >= oi) // termination condition of the recursion
      return;
   else
   {
      idx = partition(Array, ui, oi, cmp);
      qsort(Array, ui, idx - 1, cmp); // linken Teil rekursiv sortieren
      qsort(Array, idx + 1, oi, cmp); // rechten Teil rekursiv sortieren
   }
}

/***********************************************************
 * function:      QuickSort
 * description:  Sorts the specified number array in ascending order.
 * Parameter:     *Array  – pointer of sort array
 *                count - count element of array
 * return:     -/-
 ***********************************************************/
void QuickSort(TPlayer *Array, int Anzahl, int (*cmp)(TPlayer *, TPlayer *))
{
   printf("Anzahl: %i\n", Anzahl);
   qsort(Array, 0, Anzahl - 1, cmp);
}

/********************************************************************
 * function:      swap
 * description:  comparison
 * Paramater:     - dataset 1
 *                - dataset 2
 * return:      -/-
 *******************************************************************/
void swap(TPlayer *D1, TPlayer *D2)
{
    TPlayer tmp;
    tmp = *D1;
    *D1 = *D2;
    *D2 = tmp;
}

/********************************************************************
 * Funktion:      cmpName
 * Beschreibung:  vergleich
 * Paramater:     - Datensatz 1
 *                - Datensatz 2
 * Ergebnis:      Differenz
 *******************************************************************/
int cmpName(TPlayer *D1, TPlayer *D2)
{
   return strcmp(D1->Name, D2->Name);
}

/********************************************************************
 * Funktion:      cmpBirthday
 * Beschreibung:  vergleich
 * Paramater:     - Datensatz 1
 *                - Datensatz 2
 * Ergebnis:      Differenz
 *******************************************************************/
int cmpBirthday(TPlayer *D1, TPlayer *D2)
{
   if(D1->Birthday && D2->Birthday)
   {
      if(D1->Birthday->Year > D2->Birthday->Year)
         return 1;
      if(D1->Birthday->Year < D2->Birthday->Year)
         return -1;
      if(D1->Birthday->Month > D2->Birthday->Month)
         return 1;
      if(D1->Birthday->Month < D2->Birthday->Month)
         return -1;
      if(D1->Birthday->Day > D2->Birthday->Day)
         return 1;
      if(D1->Birthday->Day < D2->Birthday->Day)
         return -1;
      return cmpName(D1, D2);
   }
   return 0;
}

/********************************************************************
 * function:      cmpTrikot
 * description:  comparison
 * Paramater:     - dataset 1
 *                - dataset 2
 * return:      difference
 *******************************************************************/
int cmpTrikot(TPlayer *D1, TPlayer *D2)
{
   return D1->Number - D2->Number;
}

/********************************************************************
 * function:      cmpGoals
 * description:  comparison
 * Paramater:     - dataset 1
 *                - dataset 2
 * return:      difference
 *******************************************************************/
int cmpGoals(TPlayer *D1, TPlayer *D2)
{
   int Diff = D1->Goals - D2->Goals;

   if (Diff)
      return Diff;
   return cmpName(D1, D2);
}

