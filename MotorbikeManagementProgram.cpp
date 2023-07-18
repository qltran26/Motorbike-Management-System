#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

#define COLOR_DEFAULT 7
#define COLOR_RED 12
#define COLOR_GREEN 10
#define COLOR_YELLOW 14

void set_color(int color){
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

struct motorbike {
    char name[25];
    char manufacturer[25];
    int release_year;
    float price;
};
struct motorbike mtb[58];
int n;

void input(){
	set_color(COLOR_YELLOW);
    printf("Enter number of motorbikes: ");
    set_color(COLOR_DEFAULT);
    scanf("%d", &n);
    getchar();

    for(int i = 0; i < n; i++){
    	set_color(COLOR_GREEN);
        printf("Please input motorbike: [%d]\n", i);
        set_color(COLOR_DEFAULT);

        printf("Name: ");
        fgets(mtb[i].name, sizeof(mtb[i].name), stdin);
        mtb[i].name[strcspn(mtb[i].name, "\n")] = 0;

        printf("Manufacturer: ");
        fgets(mtb[i].manufacturer, sizeof(mtb[i].manufacturer), stdin);
        mtb[i].manufacturer[strcspn(mtb[i].manufacturer, "\n")] = 0;

        printf("Release year: ");
        scanf("%d", &mtb[i].release_year);
        getchar();

        if(mtb[i].release_year < 1990){
        	set_color(COLOR_RED);
            printf("Motorbike release year must be greater than or equal 1990 !\n");
            set_color(COLOR_DEFAULT);
            i--;
            continue;
        }

        printf("Price: ");
        scanf("%f", &mtb[i].price);

        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        if(mtb[i].price < 500 || mtb[i].price > 5000){
        	set_color(COLOR_RED);
            printf("Motorbike price must be between 500($) and 5000($) !\n");
            set_color(COLOR_DEFAULT);
            i--;
            continue;
        }
    }

	set_color(COLOR_YELLOW);
    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");
    set_color(COLOR_DEFAULT);

    fflush(stdin);
    getchar();
}

void sort(){
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (strcmp(mtb[i].name, mtb[j].name) > 0) {
                struct motorbike temp = mtb[i];
                mtb[i] = mtb[j];
                mtb[j] = temp;
            }
        }
    }

    set_color(COLOR_GREEN);
    printf("+-----------------------------------------------------+\n");
    printf("|Motorbike Name |Manufacturer |Release Year |Price($) |\n");
    printf("+-----------------------------------------------------+\n");
    set_color(COLOR_DEFAULT);

    for (int i = 0; i < n; i++) {
        printf("|%-15s|%-15s|%13d|%10.1f|\n", mtb[i].name, mtb[i].manufacturer, mtb[i].release_year, mtb[i].price);
    }

    set_color(COLOR_GREEN);
    printf("+-----------------------------------------------------+\n");
    
	set_color(COLOR_YELLOW);
    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");
    set_color(COLOR_DEFAULT);

    fflush(stdin);
    getchar();
}

void analyze(){
    int count[58] = {0};

    for (int i = 0; i < n; i++) {
        if(count[i] == -1) continue;
        count[i] = 1;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(mtb[i].manufacturer, mtb[j].manufacturer) == 0) {
                count[i]++;
                count[j] = -1;
            }
        }
    }
	
	set_color(COLOR_GREEN);
    printf("Statstics result: \n");
    set_color(COLOR_DEFAULT);

    for (int i = 0; i < n; i++) {
        if(count[i] != -1){
            printf("There are %d motorbike(s) from %s.\n", count[i], mtb[i].manufacturer);
        }
    }
	
	set_color(COLOR_YELLOW);
    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");
	set_color(COLOR_DEFAULT);
	
    fflush(stdin);
    getchar();
}

void find(){
    char manufacturer[25];
    float min_price, max_price;
	
	set_color(COLOR_YELLOW);
    printf("Manufacturer: ");
    set_color(COLOR_DEFAULT);
    fgets(manufacturer, sizeof(manufacturer), stdin);
    manufacturer[strcspn(manufacturer, "\n")] = 0;

	set_color(COLOR_YELLOW);
    printf("Min price: ");
    set_color(COLOR_DEFAULT);
    scanf("%f", &min_price);
	
	set_color(COLOR_YELLOW);
    printf("Max price: ");
    set_color(COLOR_DEFAULT);
    scanf("%f", &max_price);
    getchar();

	set_color(COLOR_GREEN);
    printf("+-----------------------------------------------------+\n");
    printf("|Motorbike Name |Manufacturer |Release Year |Price($) |\n");
    printf("+-----------------------------------------------------+\n");
	set_color(COLOR_DEFAULT);

    for (int i = 0; i < n; i++) {
        if (strcmp(mtb[i].manufacturer, manufacturer) == 0 && mtb[i].price >= min_price && mtb[i].price <= max_price) {
            printf("|%-15s|%-15s|%13d|%10.1f|\n", mtb[i].name, mtb[i].manufacturer, mtb[i].release_year, mtb[i].price);
        }
    }
	
	set_color(COLOR_GREEN);
    printf("+-----------------------------------------------------+\n");
    set_color(COLOR_DEFAULT);
    
      set_color(COLOR_YELLOW);
    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");
    set_color(COLOR_DEFAULT);

    fflush(stdin);
    getchar();
}

void save(){
    set_color(COLOR_YELLOW);
    printf("\tSave the list into file: \n");
    set_color(COLOR_DEFAULT);

    char file_name[25];
    printf("File name: ");
    scanf("%s", file_name);

    FILE *fout = fopen(file_name, "w+");

    fwrite(mtb, sizeof(struct motorbike), n, fout);
    fclose(fout);
}

void open(){
    set_color(COLOR_YELLOW);
    printf("\tOpen file and display the list: \n");
    set_color(COLOR_DEFAULT);

    char file_name[25];
    printf("File name: ");
    scanf("%s", file_name);

    FILE *fin = fopen(file_name, "r");

    if(fin == NULL){
        set_color(COLOR_RED);
        printf("\nFile not found!\n");
        set_color(COLOR_DEFAULT);
        return;
    }

    fseek(fin, 0, SEEK_END);
    int mtb_num = ftell(fin) / sizeof(struct motorbike);
    fseek(fin, 0, SEEK_SET);

    fread(&mtb[n], sizeof(struct motorbike), mtb_num, fin);
    n += mtb_num;

    fclose(fin);

    set_color(COLOR_GREEN);
    printf("+-----------------------------------------------------+\n");
    printf("|Motorbike Name |Manufacturer |Release Year |Price($) |\n");
    printf("+-----------------------------------------------------+\n");
    set_color(COLOR_DEFAULT);

    for (int i = 0; i < n; i++) {
        printf("|%-15s|%-15s|%13d|%10.1f|\n", mtb[i].name, mtb[i].manufacturer, mtb[i].release_year, mtb[i].price);
    }

    set_color(COLOR_GREEN);
    printf("+-----------------------------------------------------+\n");
    set_color(COLOR_DEFAULT);

    set_color(COLOR_YELLOW);
    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");
    set_color(COLOR_DEFAULT);

    fflush(stdin);
    getchar();
}

int main(){
    while(1){
        set_color(COLOR_GREEN);
        printf("+-----------------------------------------------------------------+\n");
        printf("|               MOTORBIKE STORE MANAGEMENT PROGRAM                |\n");
        printf("+-----------------------------------------------------------------+\n");
        printf("|1. Input |2. Sort |3. Analyze |4.Find |5. Save |6. Open |7. Exit |\n");
        printf("+-----------------------------------------------------------------+\n");
        set_color(COLOR_DEFAULT);

        int choice;
        set_color(COLOR_YELLOW);
        printf("Your choice: ");
        set_color(COLOR_DEFAULT);
        scanf("%d", &choice);

        switch (choice){
            case 1:
                input();
                break;
            case 2:
                sort();
                break;
            case 3:
                analyze();
                break;
            case 4:
                find();
                break;
            case 5:
                save();
                break;
            case 6:
                open();
                break;
            case 7:
                set_color(COLOR_RED);
                printf("Exiting program...\n");
                set_color(COLOR_DEFAULT);
                exit(0);
            default:
                set_color(COLOR_RED);
                printf("Invalid input...\n");
                set_color(COLOR_DEFAULT);
                break;
        }

        char c;
        fflush(stdin);
        scanf("%c", &c);

        if(c == 'c' || c == 'C'){
            system("cls");
        } else if (c == 'n' || c == 'N'){
            exit(0);
        }
    }
}
