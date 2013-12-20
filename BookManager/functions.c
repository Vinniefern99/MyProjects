/************************************************************
 * Filename: functions.c
 * Exercise: Final Project
 * Name: Vince Fernald
 * Date Created: July 10th, 2012
 *
 * Description: This file is part of my multi-file final project titled "Book Library Manager." This particular file containes all function definitions.
 *************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "library_prototypes.h"

/* ------------------------ SELECTION 1 - ENTER A BOOK -----------------------------*/
int addEntry(void)
{
    
    
    struct book library;
    int i;
    char newlineDelete[SIZE];
    
    fgets(newlineDelete, sizeof(newlineDelete), stdin);     //delete newline character from buffer
    
    printf("%s", "\nAdd Item:\n");
    printf("%s", "\nWhat's the title of the book?\n");
    
    fgets(library.title, sizeof(library.title), stdin);
    for (i = 0; i < strlen(library.title); i++)
    {
        if (library.title[i] == '\n' ||  library.title[i] == '\r') 
        {
            library.title[i] = '\0';
        }
            
    }
    
    if (islower(library.title[0]))
    {    
        library.title[0] = toupper(library.title[0]);
        
    }
        
    printf("%s", "What's the author's name (Last, First)?\n");
    // scanf("%s", &library.author); 
    fgets(library.author, sizeof(library.author), stdin);
    for (i = 0; i < strlen(library.author); i++)
    {
        if (library.author[i] == '\n' ||  library.author[i] == '\r') 
        {
            library.author[i] = '\0';
        }
    } 
    
    if (islower(library.author[0]))
    {    
        library.author[0] = toupper(library.author[0]);
    }
    
    printf("%s", "What year was it published?\n");
    scanf("%d", &library.date); 
    
    saveEntry(library);
    
    getchar();                  //clear stdin
    
    return 0;
}

int saveEntry(struct book newEntry) 
{
    
    FILE *fp;
    int IDnumber;
    IDnumber = newBookID();
    
    if ((fp = fopen(book_library, "a")) == NULL) 
    {
        fprintf(stdout, "Can't open file.\n");
        exit(1);
    }
    
    fprintf(fp,"%d_%s_%s_%d\n", IDnumber, newEntry.title, newEntry.author, newEntry.date);
    
    if (fclose(fp) != 0)
        fprintf(stderr, "Error closing file\n");
    
    
    return 0;
}

// THIS FUNCTION ASSIGNS A BOOK ID

int newBookID()
{
    
    FILE *newBookID_fp;
    int oldID;
    int newID;
    int x = -2;
    fpos_t  pos1;
    fpos_t  pos2;
    
    
    if ((newBookID_fp = fopen(book_library,"r")) == NULL)
    {
        fprintf(stdout, "Can't open file.\n");
        exit(1);
    }    
    
    rewind(newBookID_fp);                       
    if (fgetc(newBookID_fp) == EOF)             //if file is empty, make newID: 1
    {    
        newID = 1;
        return newID;
    }
    
    rewind(newBookID_fp);
    fgetpos(newBookID_fp, &pos1);
    
    fseek(newBookID_fp, x, SEEK_END);
        
    while (fgetc(newBookID_fp) != '\n')
    {
        x--;
        fseek(newBookID_fp, x, SEEK_END);
        fgetpos(newBookID_fp, &pos2);           
        if (pos2 == pos1)                       //If only 1 entry exists file, assign newID: 2
        {
            newID = 2;
            return newID;
        }
    }
    fscanf(newBookID_fp, "%d", &oldID);
    
    newID = oldID + 1;
    
    fclose(newBookID_fp);
    
    return newID;
}



/* ------------------------ SELECTION 2 SEARCH LIBRARY FOR A BOOK -----------------------------*/

int searchLibrary(void)
{
    
    int search_lim = totalEntries();
    
    char search_input[search_lim][SIZE];
    char search_term[30];
    char *search_final[search_lim];
    char buffer[search_lim][SIZE];
    char secondSearch;
    int search_line = 0;
    int sizeEntry = 0;
        
    FILE *filep;
    
    if ((filep = fopen(book_library, "r")) == NULL) 
    {
        printf("Can't open file.\n");
    }
        
    printf("%s", "\nEnter part of title, author, or pub date.\n");;
    fgets(search_term, sizeof(search_term), stdin);
    
    while (sizeEntry < 3) 
    {
        printf("(Min 3 characters,case sensitive)(m for MainMenu):\n");
        
        fgets(search_term, sizeof(search_term), stdin);
        printf("%s", "\n");
        
        if (strcmp(search_term, "m\n") == 0) 
        {
            return 0;
        }
        
        while(search_term[sizeEntry] != '\n')             //find true length of file string
            sizeEntry++;
    }
    
    while (search_line < search_lim && fgets(search_input[search_line], SIZE, filep) != NULL 
           && search_input[search_line][0] != '\0')
    { 
        
        if (search(search_input[search_line], search_term) != 0)
        {
            search_final[search_line] = titleFirst(search_input[search_line], buffer[search_line]);
            
            printf("%s\n", search_final[search_line]);
        }
    }
            
        printf("%s", "\nSearch again? (y/n)\n");
    secondSearch = getchar();
    if (secondSearch == 'y' || secondSearch == 'Y')
        searchLibrary();
    else
    {    
        getchar();
        return 0;
    }
    
    fclose(filep);
    
 
    return 0;
}



/* ------------------------ SELECTION 3 - DELETE A BOOK -----------------------------*/

int deleteEntry(void)
{
    
    int delete_lim = totalEntries();
    
    char delete_input[delete_lim][SIZE];
    int bookID;
    char withUnder[20];
    char *ptstr;
    char buffer[delete_lim][SIZE];
    int ct = 0;
    
    char tempBuffer[delete_lim][SIZE];
    char lineBuffer[SIZE];
    
    FILE *delete_fp;
    FILE *delete_fp_temp;
    
    
    if ((delete_fp = fopen(book_library, "r+")) == NULL) 
    {
        printf("Can't open file.\n");
    }
    
    printf("\n%s", "Enter BookID of entry to delete(m for Main Menu).\n (To find BookID, choose #2 from main menu to search)\n");

    scanf("%d", &bookID);
    
    sprintf(withUnder, "%d%s%s", bookID, "_", "\n");
    
    while (ct < delete_lim && fgets(delete_input[ct], SIZE, delete_fp) != NULL 
           && delete_input[ct][0] != '\0')
    { 
        if (ID_search(delete_input[ct], withUnder) != 0)
        {
            
            ptstr = titleFirst(delete_input[ct], buffer[ct]);
            
            printf("\n%s\n", ptstr);
            printf("\n%s\n", "Is this the entry you'd like to delete(y/n)?");
            getchar();                                              //flush stdin
            if (getchar() == 'y')
            {    
                if ((delete_fp_temp = fopen(temp_file, "w+")) == NULL) 
                {
                    printf("Can't open file.\n");
                }
                
                fseek(delete_fp, 0, SEEK_SET);
                
                for (int i = 0; i < delete_lim; i++) 
                {       
                    fgets(tempBuffer[i], sizeof(tempBuffer[i]), delete_fp);
                    
                    if (strcmp(tempBuffer[i], delete_input[ct]) != 0)
                        fputs(tempBuffer[i], delete_fp_temp);
                }
                
                fclose(delete_fp_temp);
                fileCopy();
                printf("\n%s\n%s\n", "** ENTRY DELETED **", ptstr);
            }
            else
                deleteEntry(); 
        }
        ct++;
    }
    
    fclose(delete_fp);
    
    remove(temp_file);
    
    fgets(lineBuffer, sizeof(lineBuffer), stdin);     //delete newline character from buffer
    
    return 0;
}


int ID_search(char content[], char search_term[])
{
    
    int sizeContent = 0;        
    int sizeSearch_term = 0;
    int t, v;
    v = 0;
    
    while(content[sizeContent] != '\n')             //find true length of file string
        sizeContent++;
    while(search_term[sizeSearch_term] != '\n')     //find true length of search term
        sizeSearch_term++;
    
    
    for (t = 0;t < sizeSearch_term; t++)
    {
        if(content[t] != search_term[t])
            return 0;
    }
    
    return 1;                    

}



void fileCopy(void)
{
    
    int lim = totalEntriesinTemp();
    
    FILE *fileCopy_fp;
    FILE *fileCopy_fp_temp;
    
    char tempBuffer2[lim][SIZE];
    
    if ((fileCopy_fp = fopen(book_library, "w+")) == NULL) 
    {
    printf("Can't open file.\n");
    }

    if ((fileCopy_fp_temp = fopen(temp_file, "r")) == NULL) 
    {
        printf("Can't open file.\n");
    }
    
    for (int i = 0; i < lim; i++) 
    {       
        fgets(tempBuffer2[i], sizeof(tempBuffer2[i]), fileCopy_fp_temp);
        fputs(tempBuffer2[i], fileCopy_fp);
    }

fclose(fileCopy_fp);
fclose(fileCopy_fp_temp);

}


/* ------------------------ SELECTION 4 - SORT BY TITLE -----------------------------*/

int titleSort(void)
{
    int title_lim = totalEntries();
    printf("You have %d books stored.\n", title_lim);
    
    
    char title_input[title_lim][SIZE];
    char *title_final[title_lim];
    char title_buffer[title_lim][SIZE];
    int title_line = 0;
    int title_k;
    FILE *title_fp;
    
    if ((title_fp = fopen(book_library, "r")) == NULL) 
    {
        printf("Can't open file.\n");
    }
    
    
    while (title_line < title_lim && fgets(title_input[title_line], SIZE, title_fp) != NULL 
           && title_input[title_line][0] != '\0')
    { 
        title_final[title_line] = titleFirst(title_input[title_line], title_buffer[title_line]);
        title_line++;
    }
    
    fclose(title_fp);
    
    stsrt(title_final, title_line);
    puts("Here's the sorted list:\n");
    for (title_k = 0; title_k < title_line; title_k++) 
        puts(title_final[title_k]);
    
    getchar();                  //clear stdin
    
    return 0;
    
}

//ORGANIZES EACH ENTRY SO TITLE APPEARS FIRST
char* titleFirst (char str[], char* test)
{
    
    int wordCount = 0;
    char testString[80];
    char * nextWordPtr;
    char* sentence[4];
    char newstr[SIZE];
    int j, k;
    j = 0;
    k = 0;
    
    while (str[j] != '\n')
    {
        newstr[j] = str[j];
        j++;
    }   
    
    strcpy(testString, newstr);
    
    nextWordPtr = strtok(testString,"_"); // split using space as divider
    
    while (nextWordPtr != NULL) 
    {
        sentence[wordCount] = nextWordPtr;
        wordCount++;
        nextWordPtr = strtok(NULL,"_");
    }
    
    sprintf(test,"\"%s\" by %s. %s. (ID: %s)", sentence[1], sentence[2], sentence[3], sentence[0]);
    
    for (k = 0; k < 81; k++)            //for loop to clear newstr array
        newstr[k] = '\0';
    
    
    return test;
}    


/* ------------------------ SELECTION 5 - SORT BY AUTHOR -----------------------------*/
int authorSort(void)
{
    
    int author_lim = totalEntries();
    printf("You have %d books stored.\n", author_lim);
    
    if (author_lim == 0)
        return 0;
    
    char author_input[author_lim][SIZE];
    char *author_final[author_lim];
    char author_buffer[author_lim][SIZE];
    int author_line = 0;
    int author_k;
    FILE *author_fp;
    
    if ((author_fp = fopen(book_library, "r")) == NULL) 
    {
        printf("Can't open file.\n");
    }
    
    while (author_line < author_lim && fgets(author_input[author_line], SIZE, author_fp) != NULL 
           && author_input[author_line][0] != '\0')
    { 
        author_final[author_line] = authorFirst(author_input[author_line], author_buffer[author_line]);
        author_line++;
    }
    
    fclose(author_fp);
    
    stsrt(author_final, author_line);
    puts("Here's the sorted list:\n");
    for (author_k = 0; author_k < author_line; author_k++) 
        puts(author_final[author_k]);
    
    getchar();                  //clear stdin
    
    return 0;
    
}

//ORGANIZES EACH ENTRY SO AUTHOR APPEARS FIRST
char* authorFirst (char str[], char* test)
{
    
    int wordCount = 0;
    char testString[80];
    char * nextWordPtr;
    char* sentence[4];
    char newstr[SIZE];
    int j, k;
    j = 0;
    k = 0;
    
    while (str[j] != '\n')
    {
        newstr[j] = str[j];
        j++;
    }   
    
    strcpy(testString, newstr);
    
    nextWordPtr = strtok(testString,"_"); // split using space as divider
    
    while (nextWordPtr != NULL) 
    {
        sentence[wordCount] = nextWordPtr;
        wordCount++;
        nextWordPtr = strtok(NULL,"_");
    }
    
    sprintf(test,"%s \"%s.\" %s. (ID: %s)", sentence[2], sentence[1], sentence[3], sentence[0]);
    
    for (k = 0; k < 81; k++)            //for loop to clear newstr array
        newstr[k] = '\0';

    
    return test;
}    


/* ------------------------ //SELECTION 6 DELETE ALL BOOKS -----------------------------*/

void deleteLibrary(void)
{
    FILE *deleteLibrary_fp;

    
    printf("%s", "Are you sure you want to delete all entries?(y/n)\n (WARNING: All info will be permanently deleted)\n");
    getchar();                                              //flush stdin
    if (getchar() == 'y')
    {         
        if ((deleteLibrary_fp = fopen(book_library, "w")) == NULL) 
        {
            printf("Can't open file.\n");
        }
        fclose(deleteLibrary_fp);
    }
    getchar();              //clear stdio
    
}



/* ------------------------ UNIVERSAL FUNCTIONS -----------------------------*/

//FUNCTION THAT SEARCHES GIVEN STRING FOR A TERM
int search(char content[], char search_term[])
{
    
    int sizeContent = 0;        
    int sizeSearch_term = 0;
    int t, v;
    v = 0;
    
    while(content[sizeContent] != '\n')             //find true length of file string
        sizeContent++;
    while(search_term[sizeSearch_term] != '\n')     //find true length of search term
        sizeSearch_term++;
    
    
    for (t = 0;t < sizeContent; t++)
    {
        if(content[t] == search_term[v])
        {
            while (v < sizeSearch_term)
            {
                if (content[t] != search_term[v])
                    return 0;
                v++;
                t++;
            }    
            return 1;
            
        }
    }
    
    return 0;                       // not found
}


//FUNCTION THAT COUNTS THE TOTAL AMOUNT OF ENTRIES
int totalEntries(void)
{
    char lines[SIZE];
    int x = 0;
    FILE *fp;
    
    if ((fp = fopen(book_library, "r")) == NULL) 
    {
        printf("Can't open file.\n");
    }
    
    while (fgets(lines, SIZE, fp) != NULL) 
    {
        x++;
    }
    fclose(fp);
    
    //    printf("This file has %d lines\n", x);
    
    return x;
}

//FUNCTION THAT COUNTS THE TOTAL AMOUNT OF ENTRIES IN TEMP
int totalEntriesinTemp(void)
{
    char lines[SIZE];
    int x = 0;
    FILE *fp;
    
    if ((fp = fopen(temp_file, "r")) == NULL) 
    {
        printf("Can't open file.\n");
    }
    
    while (fgets(lines, SIZE, fp) != NULL) 
    {
        x++;
    }
    fclose(fp);
    
    //    printf("This file has %d lines\n", x);
    
    return x;
}


//FUNCTION THAT SORTS THE ENTRIES IN ALPHA/NUNERIC ORDER BY FIRST LETTER/NUMBER IN STRING
void stsrt(char *strings[], int num)
{
    char *temp;
    int top, seek;
    
    for (top = 0; top < num-1; top++)
        for (seek = top + 1; seek < num; seek++)
            if (strcmp(strings[top], strings[seek]) > 0)
            {
                temp = strings[top];
                strings[top] = strings[seek];
                strings[seek] = temp;
            }
}


