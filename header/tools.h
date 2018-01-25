#ifndef TOOLS_H
   #define TOOLS_H TOOLS.H

   void clearBuffer();
   void clearScreen();
   int askYesOrNo(char *);
   void waitForEnter();
   void printLine(char, int);
   short getText(char *, int, int, char **);
   void getNumber(char *, int *, int, int);
   char* clearSpaceOrTab(char *);

#endif
