/************************************************************
 * Filename: library_prototypes.h
 * Exercise: Final Project
 * Name: Vince Fernald
 * Date Created: July 10th, 2012
 *
 * Description: This file is part of my multi-file final project titled "Book Library Manager." This particular file containes all function prototypes.
 *************************************************************/

#define MAX 50

// *CORRECT DIRECTORY BEFORE RUNNING!* 
// Enter the directory here for the book_library file.
#define book_library "/Users/vinniefern99/Documents/Intro2C/VFernald_newFinal/VFernald_newFinal/book_library.txt"

// *CORRECT DIRECTORY BEFORE RUNNING!* 
//Enter the directory for a temp file. File does not exist at launch, but will be created and deleted during the delete_file module. It should be in the same folder as the book_library file.
#define temp_file "/Users/vinniefern99/Documents/Intro2C/VFernald_newFinal/VFernald_newFinal/temp.txt"


struct book 
{
    char title[MAX];
    char author[MAX];
    int date;
};


//SELECTION 1 FUNCTIONS AND DEFINITIONS
int addEntry(void);
int saveEntry(struct book);
int newBookID(void);

//SELECTION 2 SEARCH LIBRARY FOR A BOOK
int searchLibrary (void);
int search(char content[], char search_term[]);

//SELECTION 3 DELETE AN ENTRY
int deleteEntry (void);
int ID_search(char content[], char search_term[]);
void fileCopy(void);

//SELECTION 4 FUNCTIONS AND DEFINITIONS
#define SIZE 81
#define HALT ""
int titleSort (void);

char* titleFirst (char str[], char* text); 

//SELECTION 5 FUNCTIONS AND DEFINITIONS
int authorSort (void);
char* authorFirst (char str[], char* text); 

//SELECTION 6 DELETE ALL BOOKS
void deleteLibrary(void);

//UNIVERSAL FUNCTIONS 
int totalEntries(void);
void stsrt(char *strings[], int num);
int totalEntriesinTemp(void);

