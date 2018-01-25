/****************************************************************************************************
*****************************************************************************************************
*** modul:           datetime.c
*** description:    functions for date and time
*** global FKT:     getDateFromString
***                  getDate
***                  printDate
*** local FKT:      isLeapYear
***                  isDateValid
*****************************************************************************************************
****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "tools.h"
#include "datastructure.h"
#include "datetime.h"

/********************************************************************
 * function:     isLeapYear
 * description:  check if the year is a leap-year
 * Paramater:    year to proof
 * return:       boolean if leap-year return 1 else 0
 *******************************************************************/
short isLeapYear(int year)
{
   if (year % 400 == 0)
      return 1;
   else if (year % 100 == 0)
      return 0;
   else if (year % 4 == 0)
      return 1;
   else
      return 0;
}

/********************************************************************
 * function:      isDateValid
 * description:   check if the date is valid
 * Paramater:     struct date
 * return:        boolean
 *******************************************************************/
short isDateValid(TDate date)
{
   //check year
   if ((date.Year > 9999) || (date.Year < 0)) return 0;

   //check month
   if ((date.Month > 12) || (date.Month < 0)) return 0;

   //check day
   if ((date.Day > 31) || (date.Day < 0)) return 0;

   if (((date.Month == 4) || (date.Month == 6) || (date.Month == 9) || (date.Month == 11)) &&
       (date.Day > 30))
      return 0;

   if (date.Month == 2)
   {
      if ((date.Day == 28) && (isLeapYear(date.Year))) return 1;
      if (date.Day > 28) return 0;
   }
   return 1;
}

/********************************************************************
 * function:    getDateFromString
 * description: convert string input from user to a valid time and seperate with ":"
 * Paramater:   char input from user(date) , and time
 * return:      boolean
 *******************************************************************/
short getDateFromString(char *input, TDate *date)
{
   date->Day = atoi(input);


   //get month pointer
   do
   {
      if (*input == '\0') return 0;
      input++;
   } while (*input != '.');
   input++;
   date->Month = atoi(input);

   //get year pinter
   do
   {
      if (*input == '\0') return 0;
      input++;
   } while (*input != '.');
   input++;
   date->Year = atoi(input);

   if (isDateValid(*date))
   {
      return 1;
   } else
   {
      return 0;
   }                                      // Ansonsten die function mit 0 beenden
}


/********************************************************************
 * function:      getDate
 * description:  - user enter a date
 *                - Eingabe wird mit Hilfe der function getDateFromString geparst
 *                und geprueft. Bei gueltigem Datum steht dieses in der Datums-
 *                variable Date.
 *                - return der Eingabe wird entsprechend angezeigt.
 *                - wird nur die Eingabetaste gedrueckt, wird die function ohne
 *                weitere Bildschirmausgabe beendet.
 * Paramater:     keine
 * return:      -/-
 *******************************************************************/
void getDate(char *Prompt, TDate **Datum)
{
   TDate Date;
   char Input[20];
   int chek = 0;

   do
   {
      printf("%s", Prompt);
      *Input = '\0';
      scanf("%19[^\n]", Input);
      clearBuffer();
      if (*Input)
         if (getDateFromString(Input, &Date))
         {
            *Datum = calloc(1, sizeof(TDate));
            if (*Datum)
            {
               (*Datum)->Day = Date.Day;
               (*Datum)->Month = Date.Month;
               (*Datum)->Year = Date.Year;
            }
            chek = 1;
         } else
            printf("Das eingegebene Datum %s ist ungueltig!\n", Input);
      else
         break;
   } while (!chek);
}

/********************************************************************
 * function:      printDate
 * description:
 * Paramater:     pointer to date with typ TDate
 * return:      -/-
 *******************************************************************/
void printDate(TDate *Date)
{
   if (Date != NULL)
      printf("; * %02i.%02i.%04i", Date->Day, Date->Month, Date->Year);
}