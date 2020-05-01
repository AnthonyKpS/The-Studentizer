#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

void print_menu()
{
    //Printing the main menu
    puts("");
    puts(">>> Please select one of the following <<<");
    puts("       1 to add a new student");
    puts("       2 to delete a student");
    puts("       3 to edit a student");
    puts("       4 to search for a student");
    puts("       5 to print the whole thing");
    puts("       6 to get rid of me");
}

node* find_student(int id, node *head)
{
    //Declaring temporary variables
    int id_t;
    node *node_current = head;

    //Doing a serial search on the list
    while (node_current != NULL)
    {
        //Getting the needed value from the the memory
        id_t = node_current->stud.id;

        if (id_t == id)
        {
            return node_current;
        }
        node_current = node_current->next;
    }
    return NULL;
}

void print(student student_t)
{
    if (student_t.id == -1)
    {
        puts("There is nothing to be seen!");
        return;
    }
    //Declaring temporary variables
    int id_t;
    char name_t[MAXSTRING];

    //Getting the needed values from the the memory
    id_t = student_t.id;
    strcpy(name_t, student_t.name);

    //Printing
    printf("ID: %d\tName: %s\n", id_t, name_t);
}

void print_students(node *head)
{
    //Initializing temporary structs
    student student_t;
    node *node_t = head;

    //Iterating through the whole list
    while (node_t != NULL)
    {
        //Getting the needed values from the memory
        student_t.id = node_t->stud.id;
        strcpy(student_t.name, node_t->stud.name);

        //Passing the student struct to print()
        print(student_t);

        node_t = node_t->next;
    }
}

int add_student(student student_new, node *head)
{
    //Checking if the ID is already taken OR out of range
    node* check = (node *) find_student(student_new.id, head);
    if (check || student_new.id < 0)
        return 0;

    //Checking if this is the first insertion
    if (head->stud.id == -1)
    {
        head->stud.id = student_new.id;
        strcpy(head->stud.name, student_new.name);
    }
    else
    {
        //Declaring temporary variable
        node *node_t = head;

        //Reaching the last node (tail of list) after the loop
        while (node_t->next != NULL)
        {
            node_t = node_t->next;
        }

        //Allocating the necessary memory for the new node
        node_t->next = malloc(sizeof(node));

        //Filling the empty node with the new student and setting it's destination to NULL
        node_t->next->stud = student_new;
        node_t->next->next = NULL;
    }
    return 1;
}


int update_student(student student_t, node *head)
{
    //Checking if the ID is present and returning its pointer
    node* check = (node *) find_student(student_t.id, head);

    if (!check)
        return 0;

    //New ID - New name
    int id_new;
    char name_new[MAXSTRING];

    //ID
    printf("Enter new ID ");
    input("%d", &id_new, "That is not a valid ID\n");

    //Name
    printf("Enter a new name ");
    input("%s", name_new, "That is not a valid ID\n");

    //Assigning new values
    check->stud.id = id_new;
    strcpy(check->stud.name, name_new);

    return 1;
}

int delete_student(student student_t, node **head)
{
    //Checking if the ID is present and returning its pointer
    node* check = (node *) find_student(student_t.id, *head);

    if (!check)
        return 0;

    if (check == *head)
    {
        /*
         node *node_t = (*head)->next;
        free(*head);
        *head = node_t;
        */

        (*head)->stud.id = -1;
    } else if (check->next == NULL)
    {
        node *node_t = *head;
        while (node_t->next->next != NULL)
            node_t = node_t->next;
        free(node_t->next);
        node_t->next = NULL;
    }
    else
    {
        //Initialising temporary node
        node *node_t = NULL;
        node *node_prev = *head;

        while (node_prev->next->stud.id != student_t.id)
            node_prev = node_prev->next;
        node_t = node_prev->next->next;
        node_prev->next = node_t;
    }
    return 1;
}

void save(char *filename, node *head)
{
    //Opening file
    FILE *file;
    file = fopen(filename, "w");
    if (!file)
        puts("Error trying to save");

    //Initialising temporary struct
    node *node_t = head;

    //Writing the student structs the file until the last node
    do {
        fwrite(&node_t->stud, sizeof(student), 1 ,file);
        node_t = node_t->next;
    } while (node_t != NULL);
    fclose(file);
}

node* load(char *filename)
{
    //Allocating the necessary memory for the first node of the list
    node *head = NULL;
    head = (node *) malloc(sizeof(node));

    //Checking if the allocation was successful
    if (!head)
    {
        puts("Could not allocate the necessary memory");
        puts("Shutting down...");
        exit(EXIT_FAILURE);
    }

    //Setting he first ID to -1. If there is data to be loaded, it will be overwritten, otherwise it will stay the same
    head->stud.id = -1;

    //Opening file
    FILE *file;
    file = fopen(filename, "r");
    if (!file)
        puts("The file could not be opened. Resuming normally");
    else
    {
        //Checking if empty
        size_t size;
        fseek(file, 0, SEEK_END);
        size = ftell(file);

        if (size != 0)
        {
            //Initialising a temporary node/student
            student student_t;

            //Iterating through the file from the start
            rewind(file);
            while (!feof(file))
            {
                fread(&student_t, sizeof(student), 1, file);

                //Adding the new student
                add_student(student_t, head);

            }
        }
        else
            puts("The file is empty. Resuming normally");
        fclose(file);
    }
    return head;
}

void input(char *format, void *result, char *error_msg)
{
    char c;
    while (!scanf(format, result))
    {
        while((c = (char)getchar()) != '\n' && c != EOF);
        if (error_msg)
            printf("%s", error_msg);
    }
    while((c = (char)getchar()) != '\n' && c != EOF);
}