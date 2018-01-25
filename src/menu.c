/****************************************************************************************************
*****************************************************************************************************
*** MODUL:           menu.c
*** description:    print menu & get menu
*** global FKT:     getMenu
*** local FKT:      -/-
*****************************************************************************************************
****************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include "tools.h"
#include "menu.h"
#include "teams.h"

/********************************************************************
 * function:      getMenu
 * description:  print title und submenus
 * paramater:     titel
 *                menuItem
 *                number auf submenu
 * return:      int chosen menu
 *******************************************************************/
int getMenu(char *titel, char **menuItem, int numberOfItems)
{
   int input = 0,
       i;

   do
   {
      clearScreen();

      printf("%s\n", titel);
      printLine('=', strlen(titel));                     // Ausgabe Menutitel
      printf("\n\n");

      for (i = 0 ; i < numberOfItems ; i++)              // Ausgabe Untermenus
         printf("%02d. %s\n", i+1, *(menuItem+i) );

      printf("\nIhre Wahl: ");                           // Auswahl des Untermenus
      scanf("%d", &input);
      clearBuffer();

   } while (input < 1 || input > numberOfItems);         // Solange keine gueltige Eingabe getaetigt

   return input;
}

/********************************************************************
 * function:      menuDVSortList
 * description:  print menu for sort
 * paramenter:     -/-
 * return:      int chosen menu
 *******************************************************************/
int menuDVSortList()
{
   int input;
   char *menuTitle =       "Ausgabe";
   char *menuItems[] = {   "Aufwaerts ausgeben",
                           "Abwaerts ausgeben",
                           "zurueck zum Hauptmenu"};

   input = getMenu(menuTitle, menuItems, 3);  // Menuauswahl
   switch(input)
   {
      case 1: return 1;    break;
      case 2: return 2;    break;
      case 3: return 0;    break;
   }
   return 0;
}
