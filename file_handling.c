// C Program to illustrate file opening
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void add_person(char * id, char * name){
    FILE * ptr = fopen("listname.txt", "a");

    if(ptr == NULL){
        printf("The file is not found!!!\n");
        exit(1);
    }
    char * list = (char *)malloc((strlen(id) + strlen(name)) * sizeof(char));
    strcpy(list, id);
    strcat(list, " :");
    strcat(list, name);
    strcat(list, "\n");

    fprintf(ptr ,"%s", list);

    fclose(ptr);

}

void create_folder(){
    FILE * ptr = fopen("listname.txt", "w");

    if(ptr != NULL){
        printf("successfully file created!\n");
    }else{
        printf("file found! \n");
    }

    fclose(ptr);
}

char * read_list(){
    FILE * ptr = fopen("listname.txt", "r");

    if(ptr == NULL){
        printf("File not found!\n");
    }

    char * content, * line;
    line = (char *)malloc(128 * sizeof(char));
    content = (char *)malloc(1024 * sizeof(char));


    //for intialization of content
    strcpy(content, " ");

    while(fscanf(ptr , " %[^\n]", line) != EOF){
        strcat(content, line);
    }
    content[strlen(content)] = '\0';


    fclose(ptr);

    return content;
}


int main()
{
    int no_people = 0, select;
    char * num, *name;
    char * content;
    while(1){
        printf(" (1). ADD PERSON \n");
        printf(" (2). READ LIST \n");
        printf(" (3). TERMINATE PROGRAM \n");
        printf("select ---> ");
        scanf("%d", &select);


        switch(select){
        case 1:
            no_people++;
            num = (char *)malloc(no_people * sizeof(char));
            itoa(no_people,num,10);
            num[no_people + 1] = '\0';

            name = (char *)malloc(64 * sizeof(char));
            printf("Enter name: ");
            scanf(" %[^\n]", name);

            name[strlen(name)] = '\0';
            add_person(num, name);
            break;
        case 2:
            content = read_list();
            printf("\nLIST NAMES: \n%s\n", content);
            break;
        default:
            exit(1);
        }
    }



	return 0;
}
