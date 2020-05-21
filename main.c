#include <stdio.h>
#include <string.h>
#include "student.h"
#include "student.c"
int main()
{
    puts("========================[Assignment for class: DIT116 | Welcome to The Studentizer 2020, ver 1.0 ]========================");
    puts("");

    //Asking for a filename
    puts(">>> Give me a file to save to. In case you do not have any, give your desired name and it will be generated it for you <<<");
    printf("   File name: ");
    char filename[MAX_FILE_NAME];
    input("%s", filename, "That is not a valid filename");

    //Loading the file (if it exists) and allocating the first node of the list -see load()-
    node *head = load(filename);

    //Printing the main prompt menu
    print_menu();

    //Manipulating user's prompt
    int prompt;
    input("%d", &prompt, "!!! There is no such option, please try again !!!\n");

    while (prompt != 6 /*Exit condition*/)
    {
        while (prompt < 0 || prompt > 6)
        {
            print_menu();
            input("%d", &prompt, "!!! There is no such option, please try again !!!\n");
        }

        switch (prompt)
        {
            case 1:
            {
                //Asking for credentials
                //ID
                printf("Enter a unique ID: ");
                int id_t;
                input("%d", &id_t, "That is not a valid ID\n");

                //name
                printf("Enter a unique name: ");
                char name_t[MAXSTRING];
                input("%s", name_t, "That is not a valid name\n");

                //Initializing temporary struct
                student stud_t;

                //Passing the temporary values
                stud_t.id = id_t;
                strcpy(stud_t.name, name_t);

                //Checking status of add_student
                int status = add_student(stud_t, head);
                if (!status)
                    puts("The ID is invalid or it is already taken, try something else\n");
                save(filename, head);
                break;
            }
            case 2:
            {
                //Asking for credentials
                //ID
                printf("Enter a unique ID: ");
                int id_t;
                input("%d", &id_t, "That is not a valid ID\n");

                //Initialising temporary struct
                student student_t;
                student_t.id = id_t;

                //Checking status of delete_student
                int status = delete_student(student_t, &head);
                if (status)
                    save(filename, head);
                else
                    puts("There is no such student\n");
                break;
            }
            case 3:
            {
                //Asking for credentials
                //ID
                printf("Enter a unique ID: ");
                int id_t;
                input("%d", &id_t, "That is not a valid ID\n");

                //Initialising temporary struct
                student student_t;
                student_t.id = id_t;

                //Checking status of update_student
                int status = update_student(student_t, head);
                if (status)
                    save(filename, head);
                else
                    puts("There is no such student\n");
                break;
            }
            case 4:
            {
                //Asking for credentials
                //ID
                printf("Enter a unique ID: ");
                int id_t;
                input("%d", &id_t, "That is not a valid ID\n");

                //Checking if the given id is present
                node *check = (node *) find_student(id_t, head);
                if (!check)
                    puts("There is no such student");
                else
                    print(check->stud);
                break;
            }
            case 5:
            {
                print_students(head);
                break;
            }
        }
        print_menu();
        input("%d", &prompt, "!!! There is no such option, please try again !!!\n");
    }
    
    // Freeing the used memory
    // Check if there is no entry
    
    if(head->stud.id == -1)
    {
        free(head);
    }
    else
    {
        // Keeping the node for deletion and the next node
        node *node_delete = head;
        node *node_next;

        while (node_delete != NULL)
        {
           node_next = node_delete->next;
           free(node_delete);
           node_delete = node_next;
        }
        
    }
    
    puts("Exiting...");
    return 0;
}