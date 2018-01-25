/****************************************************************************************************
*****************************************************************************************************
*** modul:           database.c
*** BESCHREIBUNG:
*** GLOBALE FKT:     save
***                  load
*** LOKALE FKT:      loadTeam
***                  loadPlayer
***                  saveTeam
***                  savePlayer
*****************************************************************************************************
****************************************************************************************************/
#define PATH  "../src/xml/save_teams.xml"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datastructure.h"
#include "database.h"
#include "datetime.h"
#include "tools.h"
#include "list.h"

void loadTeam(char *, FILE *);
void loadPlayer(char *, FILE *, TTeam *);
void saveTeam(TTeam *, FILE *);
void savePlayer(TPlayer *, FILE *);

/********************************************************************
 * Funktion:      load
 * Beschreibung:  xml file to load
 * Paramater:     file
 * Ergebnis:      -/-
 *******************************************************************/
int load(char *Datei)
{
   FILE *fp;
   char tmp[101];
   char *row;

   fp = fopen(Datei, "rt");
   if (fp == NULL)
   {
      printf("\nDatei konnte nicht gelesen werden!\n");
      waitForEnter();
      clearScreen();
      return 0;
   }
   else
   {
      do
      {
         while((fgets(tmp, 100, fp)) != NULL)
         {
            row = tmp;
            while((*row == ' ') || (*row == 9))
               row++;
            if(strncmp(row, "<Team>", 6) == 0)
            {
               loadTeam(tmp, fp);
            }
            if (feof(fp))
               break;
         }
      } while(strncmp(row, "</Daten>", 8) != 0);
      fclose(fp);
   }
   waitForEnter();
   return 0;
}

/********************************************************************
 * Funktion:      loadTeam
 * Beschreibung:  load teams from data
 * Paramater:     *tmp -
 *                *fp - FilePointer
 * Ergebnis:      -/-
 *******************************************************************/
void loadTeam(char *tmp, FILE *fp)
{
   char *row;
   int len = 0;
   TTeam *Team = calloc(1, sizeof(TTeam));

   if(Team)
   {
      Team->Name = NULL;
      Team->Coach = NULL;
      Team->Size = 0;

      do
      {
         row = tmp;
         fgets(tmp, 100, fp);
         while((*row == ' ') || (*row == 9))
            row++;
         if(strncmp(row, "<Player>", 8) == 0)
            loadPlayer(tmp, fp, Team);


         if(strncmp(row, "<Name>", 6) == 0)
         {
            len = strlen(row + 6) - 8;           // -2 differenz wegen \r
            if (*(row + strlen(row) - 2) == '\r')
                  len--;
            Team->Name = calloc(len + 1, sizeof(char));
            if(Team->Name)
               strncpy(Team->Name, row + 6, len);
         }


         if(strncmp(row, "<Trainer>", 9) == 0)
         {
            len = strlen(row + 9) - 11;           // -2 differenz wegen \r
            if (*(row + strlen(row) - 2) == '\r')
                  len--;
            Team->Coach = calloc(len + 1, sizeof(char));
            if(Team->Coach)
               strncpy(Team->Coach, row + 9, len);
         }
      } while(strncmp(row, "</Team>", 7) !=  0);
      insertInDVList(Team);
      TeamCounter++;
   }
}

/********************************************************************
 * Funktion:      loadPlayer
 * Beschreibung:  load players from data
 * Paramater:     *tmp -
 *                *fp - FilePointer
 *                *Team - the team
 * Ergebnis:      -/-
 *******************************************************************/
void loadPlayer(char *tmp, FILE *fp, TTeam *Team)
{
   char *Zeile;
   int len = 0;
   TPlayer *Player = Team->Player + Team->Size;

   if(Team->Size < MAXPLAYER)
   {
      do
      {
         Zeile = tmp;
         fgets(tmp, 100, fp);
         while((*Zeile == ' ') || (*Zeile == 9))
            Zeile++;
         if(strncmp(Zeile, "</Player>", 9) != 0)
         {

            if(strncmp(Zeile, "<Name>", 6) == 0)
            {
               len = strlen(Zeile + 6) - 8;           // -2 differenz wegen \r
               if (*(Zeile + strlen(Zeile) - 2) == '\r')
                  len--;
               Player->Name = calloc(len + 1, sizeof(char));
               if(Player->Name)
                  strncpy(Player->Name, Zeile + 6, len);
            }

            if(strncmp(Zeile, "<Birthday>", 10) == 0)
            {
               len = strlen(Zeile + 10) - 12;           // -2 differenz wegen \r
               if (*(Zeile + strlen(Zeile) - 2) == '\r')
                  len--;
               Player->Birthday = calloc(1, sizeof(TDate));
               if(Player->Birthday)
               {
                  getDateFromString(Zeile+10, Player->Birthday);
               }
            }

            if(strncmp(Zeile, "<TricotNr>", 10) == 0)
            {
               len = strlen(Zeile + 10) - 12;           // -2 differenz wegen \r
               if (*(Zeile + strlen(Zeile) - 2) == '\r')
                  len--;
               Player->Number = atoi(Zeile + 10);
            }

            if(strncmp(Zeile, "<Goals>", 7) == 0)
            {
               len = strlen(Zeile + 7) - 9;           // -2 differenz wegen \r
               if (*(Zeile + strlen(Zeile) - 2) == '\r')
                  len--;
               Player->Goals = atoi(Zeile + 7);
            }
         }
      } while(strncmp(Zeile, "</Player>", 9) != 0);
      (Team->Size)++;
   }
   else
      fgets(tmp, 100, fp);
}

/********************************************************************
 * Funktion:      save
 * Beschreibung:  save data in file
 * Paramater:     -/-
 * Ergebnis:      0 - not successful
 *                1 - successful
 *******************************************************************/
int save()
{
   FILE *wp;

   if(askYesOrNo("Moechten Sie Ihre Eingaben speichern (j/n) ? ") == 1)
   {
      wp = fopen(PATH, "ab+");

      if (wp == NULL)
      {
         printf("Datei, um Daten zu speichern, konnte nicht geöffnet werden!\n");
         waitForEnter();
         clearScreen();
         return 0;
      }
      else
      {
         if(TeamCounter != 0)
         {
            fprintf(wp, "<Daten>\n");
            TTeam *tmp = FirstTeam;
            while(tmp)
            {
               saveTeam(tmp, wp);
               tmp = tmp->Next;
            }
            fprintf(wp, "</Daten>");
            fclose(wp);
         }
         fclose(wp);
      }
   }
   return 1;
}

/********************************************************************
 * Funktion:      saveTeam
 * Beschreibung:  save the teams in file
 * Paramater:     *D
 *                *wp
 * Ergebnis:      -/-
 *******************************************************************/
void saveTeam(TTeam *D, FILE *wp)
{
   int i;
   fprintf(wp," <Team>\n");
   fprintf(wp,"  <Name>%s</Name>\n", D->Name);
   if(D->Coach)
      fprintf(wp,"  <Trainer>%s</Trainer>\n", D->Coach);

   for(i = 0; i < D->Size; i++)
   {
      savePlayer(D->Player + i, wp);
   }
   fprintf(wp," </Team>\n");
}

/********************************************************************
 * Funktion:      savePlayer
 * Beschreibung:  save the players in file
 * Paramater:     *P
 *                *wp
 * Ergebnis:      -/-
 *******************************************************************/
void savePlayer(TPlayer *P, FILE *wp)
{
   fprintf(wp, "  <Player>\n");
   fprintf(wp, "   <Name>%s</Name>\n", P->Name);
   if(P->Birthday)
      fprintf(wp, "   <Birthday>%02i.%02i.%4i</Birthday>\n", P->Birthday->Day, P->Birthday->Month, P->Birthday->Year);
   fprintf(wp, "   <TricotNr>%02i</TricotNr>\n", P->Number);
   fprintf(wp, "   <Goals>%i</Goals>\n", P->Goals);
   fprintf(wp, "  </Player>\n");
}
