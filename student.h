#ifndef ASSIGNMENT_STUDENT_H
#define ASSIGNMENT_STUDENT_H
#define MAXSTRING 20
#define MAX_FILE_NAME 20

//STRUCTS
typedef struct student{
    char name[MAXSTRING];
    int id;
}student;

typedef struct node{
    student stud;
    struct node *next;
}node;

//FUNCTIONS
void print_menu();
void print(student student_t);
void print_students(node *head);
void save(char *filename, node *head);
void input(char *format, void *result, char *error_msg);

int add_student(student student_new, node *head);
int update_student(student student_t, node *head);
int delete_student(student student_t, node **head);
int input_int(int digits);

node* find_student(int id, node *head);
node* load(char *filename);

#endif //ASSIGNMENT_STUDENT_H