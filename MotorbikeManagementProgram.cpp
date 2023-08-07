#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct motorbike {
    char name[25];
    char manufacturer[25];
    int release_year;
    float price;
};
struct motorbike mtb[58];
int n;

void input(){
    printf("Enter number of motorbikes: ");
    scanf("%d", &n);
    getchar();

    for(int i = 0; i < n; i++){
        printf("Please input motorbike: [%d]\n", i);

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
            printf("Motorbike release year must be greater than or equal 1990 !\n");
            i--;
            continue;
        }

        printf("Price: ");
        scanf("%f", &mtb[i].price);

        int c;
        while ((c = getchar()) != '\n' && c != EOF) { }

        if(mtb[i].price < 500 || mtb[i].price > 5000){
            printf("Motorbike price must be between 500($) and 5000($) !\n");
            i--;
            continue;
        }
    }
	
    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");

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

    printf("+-----------------------------------------------------+\n");
    printf("|Motorbike Name |Manufacturer |Release Year |Price($) |\n");
    printf("+-----------------------------------------------------+\n");

    for (int i = 0; i < n; i++) {
        printf("|%-15s|%-15s|%13d|%10.1f|\n", mtb[i].name, mtb[i].manufacturer, mtb[i].release_year, mtb[i].price);
    }

    printf("+-----------------------------------------------------+\n");
    
    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");

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
	
    printf("Statstics result: \n");

    for (int i = 0; i < n; i++) {
        if(count[i] != -1){
            printf("There are %d motorbike(s) from %s.\n", count[i], mtb[i].manufacturer);
        }
    }
	
    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");
	
    fflush(stdin);
    getchar();
}

void find(){
    char manufacturer[25];
    float min_price, max_price;
	
    printf("Manufacturer: ");
    fgets(manufacturer, sizeof(manufacturer), stdin);
    manufacturer[strcspn(manufacturer, "\n")] = 0;

    printf("Min price: ");
    scanf("%f", &min_price);
	
    printf("Max price: ");
    scanf("%f", &max_price);
    getchar();

    printf("+-----------------------------------------------------+\n");
    printf("|Motorbike Name |Manufacturer |Release Year |Price($) |\n");
    printf("+-----------------------------------------------------+\n");

    for (int i = 0; i < n; i++) {
        if (strcmp(mtb[i].manufacturer, manufacturer) == 0 && mtb[i].price >= min_price && mtb[i].price <= max_price) {
            printf("|%-15s|%-15s|%13d|%10.1f|\n", mtb[i].name, mtb[i].manufacturer, mtb[i].release_year, mtb[i].price);
        }
    }
	
    printf("+-----------------------------------------------------+\n");
    
    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");

    fflush(stdin);
    getchar();
}

void save(){
    printf("\tSave the list into file: \n");

    char file_name[25];
    printf("File name: ");
    scanf("%s", file_name);

    FILE *fout = fopen(file_name, "w+");

    fwrite(mtb, sizeof(struct motorbike), n, fout);
    fclose(fout);
}

void open(){
    printf("\tOpen file and display the list: \n");

    char file_name[25];
    printf("File name: ");
    scanf("%s", file_name);

    FILE *fin = fopen(file_name, "r");

    if(fin == NULL){
        printf("\nFile not found!\n");
        return;
    }

    fseek(fin, 0, SEEK_END);
    int mtb_num = ftell(fin) / sizeof(struct motorbike);
    fseek(fin, 0, SEEK_SET);

    fread(&mtb[n], sizeof(struct motorbike), mtb_num, fin);
    n += mtb_num;

    fclose(fin);

    printf("+-----------------------------------------------------+\n");
    printf("|Motorbike Name |Manufacturer |Release Year |Price($) |\n");
    printf("+-----------------------------------------------------+\n");

    for (int i = 0; i < n; i++) {
        printf("|%-15s|%-15s|%13d|%10.1f|\n", mtb[i].name, mtb[i].manufacturer, mtb[i].release_year, mtb[i].price);
    }

    printf("+-----------------------------------------------------+\n");

    printf("Do you want to continue?\n");
    printf("Yes (press any key)\n");
    printf("No (press 'N' or 'n')\n");
    printf("Please clear screen (press 'C' or 'c')\n");
    printf("Your choice: ");

    fflush(stdin);
    getchar();
}

int main(){
    while(1){
        printf("+-----------------------------------------------------------------+\n");
        printf("|               MOTORBIKE STORE MANAGEMENT PROGRAM                |\n");
        printf("+-----------------------------------------------------------------+\n");
        printf("|1. Input |2. Sort |3. Analyze |4.Find |5. Save |6. Open |7. Exit |\n");
        printf("+-----------------------------------------------------------------+\n");

        int choice;
        printf("Your choice: ");
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
                printf("Exiting program...\n");
                exit(0);
            default:
                printf("Invalid input...\n");
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
