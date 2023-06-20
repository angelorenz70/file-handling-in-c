#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char * token(char * string){
    char * split;
    char * arrange_string;
    arrange_string = (char *)malloc(1024 * sizeof(char));
    strcpy(arrange_string ," ");

    split = strtok(string, ",");
    while(split != NULL){
        strcat(arrange_string, split);
        strcat(arrange_string, "\t ");

        split = strtok(NULL, ",");
    }
    arrange_string[strlen(arrange_string)] = '\0';

    return arrange_string;

}

char * read_csv(){
    FILE * ptr = fopen("C:/Users/Angelo/Documents/mysql/exported_four_person.csv", "r");

    if(ptr == NULL){
        printf("File not found!! \n");
        exit(1);
    }

    char * content, *read_line, * arrange_line;
    content = (char *)malloc(1024 * sizeof(char));
    read_line = (char *)malloc(128 * sizeof(char));

    strcpy(content, " ");

    while(fscanf(ptr, " %[^\n]", read_line) != EOF){
        read_line[strlen(read_line)] = '\0';

        arrange_line = token(read_line);

        strcat(content,arrange_line);
        strcat(content, "\n");
    }

    content[strlen(content)] = '\0';

    fclose(ptr);

    return content;
}

char * changeTo_comma(char * content){
    int count = 0;
    char * copy_content;
    copy_content = (char *)malloc(1025 * sizeof(char));
    strcpy(copy_content, content);
    copy_content[strlen(copy_content)] = '\0';

    char * split_content, *split_space, * return_content, *line_content;
    return_content = (char *)malloc(128 * sizeof(char));
    line_content = (char *)malloc(128 * sizeof(char));
    strcpy(line_content, " ");
    strcpy(return_content, " ");

    split_content = strtok(copy_content, "\n");
    while(split_content != NULL){
        printf("%s", split_content);
        split_space = strtok(split_content, "\t");
        while(split_space != NULL){
            strcat(line_content, split_space);
            strcat(line_content, ",");
            split_space = strtok(NULL, "\t");
        }
        line_content[strlen(line_content)] = '\0';
        strcat(return_content, line_content);
        strcat(return_content, "\n");

        split_content = strtok(NULL, "\n");
    }
    return_content[strlen(return_content)] = '\0';
    printf("%s", return_content);
    return return_content;

}

void output_file(char * content, char * extention){
    char * path;
    path = (char *)malloc(128 * sizeof(char));
    strcpy(path, "output/output_file.");
    strcat(path, extention);
    path[strlen(path)] = '\0';

    FILE * ptr = fopen(path, "w");

    if(ptr != NULL){
        printf("See the name output_file.txt in the directory output to view the result \n");
    }

    if(strcmp(extention, "txt") == 0){
        fprintf(ptr, " %s", content);
    }else{
        char * csv_content;
        csv_content = changeTo_comma(content);
        fprintf(ptr, " %s", csv_content);
    }

    fclose(ptr);
}

int main(){
    char * content, * extention;
    int select;
    extention = (char *)malloc(4 * sizeof(char));

    printf("FILE CONTENT: ------------->\n");

    content = read_csv();
    printf("read: %s\n\n", content);
    printf("Choose extention: ");
    printf("(1) - txt, (2) - csv: --->>");
    scanf("%d", &select);
    switch(select){
    case 1:
        strcpy(extention, "txt");
        extention[strlen(extention)] = '\0';

        break;
    case 2:
        strcpy(extention, "csv");
        extention[strlen(extention)] = '\0';
        break;
    }

    output_file(content, extention);

    return 0;
}
