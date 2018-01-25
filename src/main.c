/****************************************************************************************************
 *****************************************************************************************************
 *** modul:          main.c
 *** description:    mainprogram
 *****************************************************************************************************
 ****************************************************************************************************/

#include "teams.h"
#include "menu.h"
#include "datastructure.h"
#include "database.h"

int main()
{
   TTeam *tmp = FirstTeam;
   int input, checkSave = 0;
   char *menuTitel = "Mannschaften-Verwaltung V0.6";       // Menutitel
   char *menuItems[] = {"Neue Mannschaften anlegen",       // Untermenu
                        "Spieler hinzufuegen",
                        "Spieler loeschen",
                        "Mannschaft loeschen",
                        "Suchen ",
                        "Sortieren",
                        "Auflisten",
                        "Datei laden",
                        "Programm beenden"};

   while( (input = getMenu(menuTitel, menuItems, 9))) // Menuauswahl
   {
      switch(input)
      {
         case 1: createTeam();         break;
         case 2: addPlayer();          break;
         case 3: deletePlayer();       break;
         case 4: deleteTeam();         break;
         case 5: searchPlayer();       break;
         case 6: sortTeams();          break;
         case 7: listTeams();          break;
         case 8: loadFileMenu();       break;
         case 9: checkSave = save(tmp);   break;
      }
      if(checkSave == 1)
         return 0;
   }
   return 0;
}

