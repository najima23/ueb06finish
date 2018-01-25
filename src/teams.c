/****************************************************************************************************
*****************************************************************************************************
*** modul:           teams.c
*** description      managing teams
*** global FKT:      createTeam
***                  deleteTeam
***                  addPlayer
***                  deletePlayer
***                  searchPlayer
***                  sortTeams
***                  listTeams
***                  loadFileMenu
*** local FKT:      createPlayer
***                  listOnePlayer
***                  listOneTeam
****************************************************************************************************
***************************************************************************************************/

#define TEAMPATH  "../src/xml/teams.xml"
#define NEWTEAMS  "./src/xml/new_teams.xml"
#define SAVETEAMS "./src/xml/save_teams.xml"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "datastructure.h"
#include "list.h"
#include "datetime.h"
#include "tools.h"
#include "database.h"
#include "menu.h"
#include "sort.h"


int TeamCounter = 0;

TTeam *FirstTeam = NULL;
TTeam *LastTeam = NULL;

/********************************************************************
 * function:     createPlayer
 * description:  enter player
 * paramater:    -/-
 * return:      -/-
 *******************************************************************/
void createPlayer(TPlayer *Player)
{
   getText("\nGeben Sie bitte den Namen des Spielers ein:\n-> ", 50, 0, &(Player->Name));
   getDate("Geben Sie bitte das Geburtsdatum des Spielers ein:\n-> ", &(Player->Birthday));
   getNumber("Geben Sie bitte die Trikotnr. des Spielers ein (1-99):\n-> ", &(Player->Number), 1, 99);
   Player->Goals = 0;
}

/********************************************************************
 * function:      createTeam
 * description:  create a team
 * paramater:     -/-
 * return:      -/-
 *******************************************************************/
void createTeam()
{
   TTeam *Team = calloc(1, sizeof(TTeam));
   char *title = "Erfassung einer neuen Mannschaft";
   clearScreen();

   if(Team)
   {
      printf("%s\n", title);
      printLine('=', strlen(title));
      printf("\n\n");

      getText("Geben Sie bitte den Namen der Mannschaften ein:\n-> ", 50, 0, &(Team->Name)); //
      getText("Geben Sie bitte den Namen des Trainers ein:\n-> ", 50, 1, &(Team->Coach));

      Team->Size = 0;

      /* Erfassung eines Spielers in einer neuen Manschaft */
      title = "Erfassung der Spieler";
      printf("\n%s\n", title);
      printLine('-', strlen(title));

      do
      {
         createPlayer((Team->Player) + (Team->Size));     // Spieler erstellen (
         (Team->Size)++;                              // Größe der Manschaft um 1 erhöhen
         printf("\nAnzahl der Spieler in der Mannschaft: %i", (Team->Size)); // Test !! Gibt die Aktuelle Größe der Spieler aus
      } while (askYesOrNo("\nMoechten sie einen weiteren Spieler eingeben (j/n)? "));
      insertInDVList(Team);
      TeamCounter++;
   }
   else
   {
      printf("Die maximale Anzahl an Teams(10) ist erreicht!\n\n");
      waitForEnter();
   }
}

/********************************************************************
 * function:      deleteTeam
 * description:  delete a team
 * Paramater:     -/-
 * return:      -/-
 *******************************************************************/
void deleteTeam()
{
   TTeam *tmp = FirstTeam;
   int   index = 1,
         input = 0,
         i = 0;
   char *title = "Lister der Mannschaften";

   do
   {
      clearScreen();

      printf("%s\n", title);
      printLine('=', strlen(title));
      printf("\n\n");

      index = 1;
      while(tmp)
      {
         printf("%02i. %s\n", index, tmp->Name);

         tmp = tmp->Next;
         index++;
      }
      printf("\nWelche Mannschaft moechten Sie loeschen (0 fuer Abbrechen) ?");
      scanf("%i", &input);
      tmp = FirstTeam;
   } while (input > index);

   if(input == 0)
      return;

   tmp = FirstTeam;
   while(i < input-1)
   {
      tmp = tmp->Next;
      i++;
   }
   removeFromDVList(tmp);
   freeOneTeam(tmp);
}

/********************************************************************
 * function:      addPlayer
 * description:  add player
 * Paramater:     -/-
 * return:      -/-
 *******************************************************************/
void addPlayer()
{
   printf("addPlayer\n\n");
   waitForEnter();
}

/********************************************************************
 * function:      deletePlayer
 * description:  delete a player
 * Paramater:     -/-
 * return:      -/-
 *******************************************************************/
void deletePlayer()
{
   printf("deletePlayer\n\n");
   waitForEnter();
}

/********************************************************************
 * function:      searchPlayer
 * description:  search a player
 * Paramater:     -/-
 * return:      -/-
 *******************************************************************/
void searchPlayer()
{
   printf("searchPlayer\n\n");
   waitForEnter();
}

/********************************************************************
 * function:      sortTeams
 * description:  sort team
 * Paramater:     -/-
 * return:      -/-
 *******************************************************************/
int sortTeams()
{
   int input;
   char *menuTitel = "Sortieren";
   char *menuItems[] = {"Spieler nach Namen sortieren",
                        "Spieler nach Geburtsdatum sortieren",
                        "Spieler nach TrikotNr. sortieren",
                        "Spieler nach Anzahl geschossener Tore sortieren",
                        "zurueck zum Hauptmenu"};
   input = getMenu(menuTitel, menuItems, 5);  // Menuauswahl
   TTeam *tmp = FirstTeam;

   switch(input)
   {
      case 1:
         while(tmp)
         {
            QuickSort(tmp->Player, tmp->Size, cmpName);
            tmp = tmp->Next;
         }
         break;
      case 2:
            while(tmp)
            {
               QuickSort(tmp->Player, tmp->Size, cmpBirthday);
               tmp = tmp->Next;
            }
         break;
      case 3:
         while(tmp)
         {
            QuickSort(tmp->Player, tmp->Size, cmpTrikot);
            tmp = tmp->Next;
         }
         break;
      case 4:
         {
            QuickSort(tmp->Player, tmp->Size, cmpGoals);
            tmp = tmp->Next;
         }
         break;
      case 5:
         return 0;
   }
   return 0;
}

/********************************************************************
 * function:      listOnePlayer
 * description:  list one player
 * Paramater:     -/-
 * return:      -/-
 *******************************************************************/
void listOnePlayer(TPlayer *Player, int Size)
{
   printf("\n   %02i. %-25s(%02i", Size, Player->Name, Player->Number);
   printDate(Player->Birthday);
   if(Player->Goals == 1)
      printf(";%2i Tor", Player->Goals);
   if(Player->Goals != 1)
      printf(";%2i Tore", Player->Goals  );
   printf(")");
}

/********************************************************************
 * function:      listOneTeam
 * description:  list one team
 * Paramater:     -/-
 * return:      -/-
 *******************************************************************/
void listOneTeam(TTeam *Team)
{
   int i;

   printf("\n\nName               : %s", Team->Name);
   if(Team->Coach)
   {
      printf("\nTrainer            : %s", Team->Coach);
   }
   printf("\nAnzahl der Spieler : %i", Team->Size);
   printf("\nSpieler:");

   for(i = 0; i < (Team->Size); i++)
   {
      listOnePlayer((Team->Player) + i, i+1);
   }
}

/********************************************************************
 * function:      listTeams
 * description:  List teams
 * Paramater:     -/-
 * return:      -/-
 *******************************************************************/
void listTeams()
{
   TTeam *tmp = FirstTeam;
   TTeam *tmp2 = LastTeam;
   int choice;
   char title[] = "Liste der Mannschaften";
   clearScreen();

   if(TeamCounter == 0)
   {
      printf("%s\n", title);     // Print Header für ListTeams
      printLine('=', strlen(title));
      printf("\n\nAktuell sind keine Mannschaften erstellt worden!\n\n");
   }
   else
   {
      choice = menuDVSortList();          // Menu zum Sortieren der Teams
      clearScreen();

      printf("%s\n", title);              // Print Header für ListTeams
      printLine('=', strlen(title));

      if(choice == 1)                     // Menuauswahl Abwaerts sortieren
      {
         while(tmp)
         {
            listOneTeam(tmp);             // Liste ein Team auf
            tmp = tmp->Next;              // geh zum naechsten Team
         }
      }

      else if(choice == 2)                     // Menuauswahl Abwaerts sortieren
      {
         while(tmp2)
         {
            listOneTeam(tmp2);            // Liste das ein Team von hinten auf
            tmp2 = tmp2->Prev;            // geh ein Team zurueck
         }
      }
   }
   printf("\n\n");
   waitForEnter();
}

/********************************************************************
 * function:      loadFileMenu
 * description:  print submenu
 * Paramater:     -/-
 * return:      selection(int) submenu
 *******************************************************************/
int loadFileMenu()
{
   int input;
   char *menuTitel = "Datei Laden";
   char *menuItems[] = {"Datei laden (teams.xml)",
                        "Datei laden (little_teams.xml)",
                        "Datei laden (save_teams.xml)",
                        "zurueck zum Hauptmenu"};

   input = getMenu(menuTitel, menuItems, 4);  // Menuauswahl
   switch(input)
   {
      case 1: load(TEAMPATH);    break;
      case 2: load(NEWTEAMS);    break;
      case 3: load(SAVETEAMS);    break;
      case 4: return 0;
   }
   return 0;
}
