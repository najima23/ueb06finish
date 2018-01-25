/****************************************************************************************************
*****************************************************************************************************
*** modul:           tools.c
*** description:     functios for tools
*** global FKT:      clearBuffer
***                  clearScreen
***                  printLine
***                  WaitForEnter
***                  AskYesOrNo
***                  getNumber
*** local FKT:      -/-
*****************************************************************************************************
****************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools.h"


#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

/********************************************************
 * function:      clearBuffer
 * ------------------------------------------------------
 *  descriptin:   reset the input buffer till '\n'
 *  scope:        global
 *******************************************************/

void clearBuffer(void)
{
   char dummy;
   do
   {
      scanf("%c", &dummy);

   } while (dummy != '\n');
}

/********************************************************
 * function:         clearScreen
 * ------------------------------------------------------
 *  description:     clears terminal screen
 *  scope:           global
 *******************************************************/

void clearScreen(void)
{
   system(CLEAR);
}

/********************************************************
 * function:         askYesOrNo
 * ------------------------------------------------------
 *  description:     ask if the user wants to use useless
 *  scope:           global
 *  parameter:       char *text
 *  retrun:          int      *yes == 1 , no == 0
 *******************************************************/

int askYesOrNo(char *text)
{
   char akward;

   do
   {

      printf("\n");
      printf("%s", text);
      scanf("%c", &akward);
      if (akward != '\n') clearBuffer();


      if ((akward == 'j') || (akward == 'J') || (akward == 'n') || (akward == 'N'))
         return ((akward == 'j') || (akward == 'J')) ? 1 : 0;


      printf("Ups, da lief etwas schief!\nBitte nur 'j' oder 'n' eingeben!");
   } while (1);
}

/********************************************************
 * function:         waitForEnter
 * ------------------------------------------------------
 *  description:     Prompt for operation the enter key
 *  scope:           global
 *  parameter:       -
 *  return:          void
 *******************************************************/

void waitForEnter()
{
   printf("Bitte Eingabetaste druecken. \n");
   clearBuffer();
}

/********************************************************
 * function:         printLine
 * ------------------------------------------------------
 *  description:     Returns a character in the desired Number off
 *  scope:           global
 *  parameter:       char c , int count
 *  return:          void
 *******************************************************/

void printLine(char c, int count)
{
   while (count != 0)
   {
      printf("%c", c);
      count--;
   }
   printf("\n");
}


/**********************************************************
 * function:     getText
 * description: XXXXXXXXXX
 * Parameter:    - Text der Eingelesen werden soll
 *               - maximale Anzahl an Zeichen
 *               - 0/1 leere eingabe nicht zul�ssig/zul�ssig
 *               - Zeiger auf Text, der in der Datenstruktur
 *                 gespeichert werden soll
 * return:     - 1/0 functioniert/functioniert nicht
**********************************************************/
short getText(char *Prompt, int MaxLen, int AllowEmpty, char **Text)
{
   char *Input;
   char Format[20];
   int scanErg;
   int Len;                                                    // L�nge
   if (MaxLen <= 0)
      return 0;
   if (Text == NULL)
      return 0;
   *Text = NULL;
   Input = calloc(MaxLen + 1, sizeof(char));                    // Speicher reservieren // im ersten Zeichen wird ein \0 gespeichert
   if (Input)                                                  // Pr�fen, ob Speicher reserviert worden istt
   {
      (Format, "%%%i[^\n]", MaxLen);                   // Kapitel 5
      do
      {
         printf("%s", Prompt);
         scanErg = scanf(Format, Input);
         clearBuffer();
         Len = strlen(Input);                               // Wie lang ist die eingabe
         if (Len > 0)
         {
            *Text = malloc((Len + 1) * sizeof(char));        //
            if (Text)
            {
               strcpy(*Text, Input);
            } else
            {
               free(Input);
               return 0;
            }
         } else
         {
            if (AllowEmpty)
            {
               free(Input);
               return 1;
            } else
            {
               scanErg = 0;
            }
         }
      } while (scanErg == 0);
      free(Input);
      return 1;
   }
   return 0;
}

/**********************************************************
 * function:     getNumber
 * description: XXXXXXXXXX
 * Parameter:    - Text der Eingelesen werden soll
 *               - Zeiger auf Text, der in der Datenstruktur
 *                 gespeichert werden soll
 *               - Gueltiger Zahlenbereich VON
 *               - Gueltiger Zahlenbereich BIS
 * return:     -/-
**********************************************************/
void getNumber(char *Prompt, int *Number, int From, int To)
{
   int zahl;
   do
   {
      printf("%s", Prompt);
      zahl = 0;
      scanf("%d", &zahl);
      clearBuffer();
   } while (zahl < From || To < zahl);
   *Number = zahl;
}

/**********************************************************
 * function:      clearSpaceOrTab
 * description:  Wenn ein Zeiger auf ein space oder tab im
 *                string zeigt, geh ein Zeichen weiter.
 * Parameter:     zu pr�fenden Zeiger
 * return:      -/-
**********************************************************/
char *clearSpaceOrTab(char *Prompt)
{
   while ((*Prompt == ' ') || (*Prompt == 9))
      Prompt++;
   return Prompt;
}