/************************************************************
 * Filename: library_main.c
 * Exercise: Final Project
 * Name: Vince Fernald
 * Date Created: July 10th, 2012
 *
 * Description: This file is part of my multi-file final project titled "Book Library Manager." This particular file holds the main funciton, which contains the user interface.
 *************************************************************/

#include <stdio.h>
int mainMenu(void);

extern int addEntry(void);
extern int searchLibrary (void);
extern int titleSort (void);
extern int authorSort (void);
extern int deleteEntry (void);
extern void deleteLibrary(void);



int main (void)
{
    
    int currentSelection;
    char select_yorn;
    
    printf("%s", "Hello! Let me help you manage your library of books.\nFirst, choose from one of the options(q to quit):\n");
    
    while ((currentSelection = mainMenu()) != 0)
    {    
    
        if (currentSelection == 1) 
            addEntry();
    
        if (currentSelection == 2) 
            searchLibrary();
    
        if (currentSelection == 3)
        {
            getchar();
            deleteEntry();
        }
            
        if (currentSelection == 4)
            titleSort();
    
        if (currentSelection == 5)
            authorSort();
        
        if (currentSelection == 6)
            deleteLibrary();

        
        printf("%s", "\nBack to Main Menu?(y/n)?\n");
        select_yorn = getchar();
        if (select_yorn == 'y' || select_yorn == 'Y') 
            printf("%s", "Choose from one of the following options(q to quit):\n");
        else
            break;
 
    }
    return 0;
    
}
                                                 
int mainMenu(void) { 
    
    char mainText[] = " 1 -Add a book\t\t\t\t4 -Sort by title\n 2 -Search for a book\t\t\t5 -Sort by author\n 3 -Delete a book\t\t\t6 -Delete all books\n";
    
    printf("%s", mainText);
    int selection;
    scanf("%d", &selection);
    return selection;
    
}

