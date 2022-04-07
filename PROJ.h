#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <setjmp.h>

/* A linked list node containing a string and length */
typedef struct list  //Struct for list
{
    char name[15];
    int length;
    struct linkedlist *next;
} list;
list *bts;
FILE *in_f;
FILE *out_f;
struct array   //Struct for  array
{
    char c;
    list *next;
};
typedef struct array array;

void read_file()   //read from file and fill in linked list
{
    in_f = fopen("myf.txt", "r"); // read only
    char line[15];
    // test for files not empty.
    list *ptr;
    if (in_f == NULL)
    {
        printf("Error! File is empty ,please put some names\n");
        exit(-1);
    }
    else
    {
        while (fscanf(in_f, "%s", line) != EOF)
        {
            list *o = malloc(sizeof(list));
            o->next = NULL;
            strcpy(o->name, line);
            o->length = (int) strlen(o->name);
            ptr = bts;
            while (ptr->next)
            {
                ptr = (list *) ptr->next;
            }
            ptr->next = (struct linkedlist *) o;
        }
    }
    printf("Read Successfully");
}

void print()   //function print the list
{
    list *ne;
    ne = bts;
    while (ne->next)
    {
        ne = (list *) ne->next;
        printf("%s\n", ne->name);
    }
}


struct array buckets[255];

void init_Array()   //function inti the struct array
{
    for (int b = 0; b < 255; b++)
    {
        buckets[b].c = (char) b;
        buckets[b].next = malloc(sizeof(list));
        buckets[b].next->next = NULL;
    }
}

void CopyFromArrayToLinkedList()   //fuction copy from array after sort and back to linked list
{
    list *pt, *o;
    for (int j = 0; j < 255; j++)
    {
        pt = buckets[j].next;
        while (pt->next)
        {
            pt = (list *) pt->next;
            list *p = malloc(sizeof(list));
            p->next = NULL;
            strcpy(p->name, pt->name);
            p->length = pt->length;
            o = bts;
            while (o->next)
            {
                o = (list *) o->next;
            }
            o->next = (struct linkedlist *) p;
        }
        pt = buckets[j].next;
        free(pt->next);
        pt->next = NULL;
    }
}

int maxLen() //return max length of name
{
    int num = 0;
    list *len;
    len = bts;
    while (len->next)
    {
        len = (list *) len->next;
        if ((len->length) > num)
            num = len->length;
    }
    return num;
}

void printlist()   // function print the array
{
    list *pt, *p, *o;
    for (int j = 0; j < 255; j++)
    {
        pt = buckets[j].next;
        while (pt->next)
        {
            pt = (list *) pt->next;
            printf("%d >>>>>>  %s\n", j, pt->name);
        }
    }
}

static int y = 0;
static int cv = -1;

void bucket_strings()   // function make sort
{
    list *pos, *ptr;
    for (int j = 0; j < maxLen(); j++)
    {
        pos = bts;
        cv++;
        while (pos->next != NULL)
        {
            pos = (list *) pos->next;
            int i = 0;
            while (i < 255)
            {
                int q = pos->length - 1 - cv;
                if (q<0)
                    q=0;
                if (buckets[i].c == pos->name[q])
                {
                    list *p = malloc(sizeof(struct list));
                    p->next = NULL;
                    strcpy(p->name, pos->name);
                    p->length = pos->length;
                    ptr = buckets[i].next;
                    while (ptr->next)
                    {
                        ptr = (list *) ptr->next;
                    }
                    ptr->next = (struct linkedlist *) p;
                    break;
                }
                i++;
            }
        }
        free(bts->next);
        bts->next = NULL;
        CopyFromArrayToLinkedList();
    }
    printf("Sort Successfully\n");
}

void menu()  // main menu
{
    do
    {
        system ("cls");
        printf("\t\t\t~~~ { Maen Khdour     1171944      sec:2}~~~   \n");
        printf("\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\t\t\t\t ~  project#1: Linked List with Radix Sort .  ~\n");
        printf("\t\t\t ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("\n\n\t\t\t~ please select the number of instruction: ~ \n");
        printf("\n\n\t\t\t ~ 1 : Read FILE                          ~\n");
        printf("\n\n\t\t\t ~ 2 : Print before Sorting               ~\n");
        printf("\n\n\t\t\t ~ 3 : sort the strings                   ~\n");
        printf("\n\n\t\t\t ~ 4 : print the sorted strings           ~\n");
        printf("\n\n\t\t\t ~ 5 : exit                               ~\n");
        char y;
        printf("\n\t\t\t~ the instruction number is : %c ", y);
        scanf(" %c", &y);
        system ("cls");

        if(y == '1')
        {
            read_file();
            sleep(1);
        }
        else if(y == '2')
        {
            print();
            sleep(10);
        }
        else if(y == '3')
        {
            system("cls");
            init_Array();
            CopyFromArrayToLinkedList();
            bucket_strings();
            sleep(2);
        }
        else if(y == '4')
        {
            print();
            sleep (10);
        }

        else if(y== '5')
        {
            exit(0);

        }
        else
        {
            menu();
        }
    }
    while (1);
}




