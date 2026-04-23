#include <stdio.h>
#define MAX_EXPENSES 200
#define STORE_LIMIT 100
// defines array storing 100 types of data. a=[1,2,...,100]

int count = 0;
char choice;


struct Expense_data_type {
    int day, month, year;
    int hour, minute;
    float price;
    char type[100];
};
// defines structure of the artificial data type created 

struct Expense_data_type expenses[MAX_EXPENSES];
//creates array storing datatype Expense_data_type

void loadData() {
    FILE *fp = fopen("expenses.txt", "r"); //r = read
    if (fp == NULL) {
        count = 0;
        return;
    }

    fscanf(fp, "%d", &count);

    for (int i = 0; i < count; i++) {
        fscanf(fp, "%d %d %d %d %d %f %s",
            &expenses[i].day,
            &expenses[i].month,
            &expenses[i].year,
            &expenses[i].hour,
            &expenses[i].minute,
            &expenses[i].price,
            expenses[i].type
        );
        //file pointer or cursor scans lines every instruction (in here %d %d %d %d %d %f %s).
    }
    //scans line and stores data from rom to ram.
    fclose(fp);
}


void saveData() {
    FILE *fp = fopen("expenses.txt", "w"); //w = write or overwrite
    if (fp == NULL) {
        printf("Error saving file.\n");
        return;
    }

    fprintf(fp, "%d\n", count);

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %d %d %d %d %.2f %s\n",
            expenses[i].day,
            expenses[i].month,
            expenses[i].year,
            expenses[i].hour,
            expenses[i].minute,
            expenses[i].price,
            expenses[i].type
        );
    }

    fclose(fp);
}


struct Expense_data_type inputExpense() {
    struct Expense_data_type temp;

    printf("\nEnter date (DD MM YYYY): ");
    scanf("%d %d %d", &temp.day, &temp.month, &temp.year);
    if (temp.day < 1 || temp.day > 31 || temp.month < 1 || temp.month > 12 || temp.year < 1900 || temp.year > 2100) {
        printf("Invalid date. Please enter a valid date.\n");
        return inputExpense();
    }

    printf("Enter time (HH MM): ");
    scanf("%d %d", &temp.hour, &temp.minute);
    if (temp.hour < 0 || temp.hour > 23 || temp.minute < 0 || temp.minute > 59) {
        printf("Invalid time. Please enter a valid time.\n");
        return inputExpense();
    }

    printf("Enter amount: ");
    scanf("%f", &temp.price);
    if (temp.price < 0) {
        printf("Invalid amount. Please enter a non-negative value.\n");
        return inputExpense();
    }

    printf("Enter expense type without spaces: ");
    scanf(" %99s", temp.type);

    return temp;
}
// this gives us a part of array


int Data_enter(){
    do {
        if (count == STORE_LIMIT) {
            printf("\nStorage limit reached (only 100 expenses allowed).\n");
            break;
        }

        expenses[count] = inputExpense();
        count++;

        printf("Add another expense? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');
    return 0;
}
// checks if part of arrays exeeds limit. if no, then it adds the temp part of array in array until user says no.

int Total_expenses(){
    printf("\nStored Expenses:\n");
    for (int i = 0; i < count; i++) {
        printf("\nExpense %d\n", i + 1);
        printf("Date: %02d/%02d/%04d\n", expenses[i].day, expenses[i].month, expenses[i].year);
        printf("Time: %02d:%02d\n", expenses[i].hour, expenses[i].minute);
        printf("Amount: %.2f\n", expenses[i].price);
        printf("Type: %s\n", expenses[i].type);
    }
    return 0;
}
// this displays all the data stored in the array
void Monthly_expenses(){
    int month, year;
    float net_expense = 0.0;
    printf("\nEnter month (MM YYYY):");
    scanf("%d %d",&month,&year);
    for (int i = 0; i < count; i++) {
        if (expenses[i].month == month && expenses[i].year == year) {
            printf("\nExpense %d\n", i + 1);
            printf("Date: %02d/%02d/%04d\n", expenses[i].day, expenses[i].month, expenses[i].year);
            printf("Time: %02d:%02d\n", expenses[i].hour, expenses[i].minute);
            printf("Amount: %.2f\n", expenses[i].price);
            printf("Type: %s\n", expenses[i].type);
            net_expense += expenses[i].price;
        }
    }
    printf("Total expenses for the month: %.2f\n", net_expense);
}
// this displays data 
int Quit(){
    saveData();
    printf("Exiting the Expense Tracker. Goodbye!\n");
    return 0;
}


int main(void) {
    loadData();
    int ops = 0;
    int ops2 = 0;
    while (ops != 3) {
        printf("\nWelcome to the Expense Tracker!\n");
        printf("1:Data entry\n");
        printf("2:Data display\n");
        printf("3:Quit and save changes\n");
        printf("choose operation to be performed:");
        scanf("%d", &ops);
        if (ops==1){
            Data_enter();
        }
        else if (ops==2){
            printf("\n1: Total Expenditures\n");
            printf("2: Expenditures by month\n");
            printf("choose operation to be performed:");
            scanf("%d", &ops2);
            if (ops2==1){
                Total_expenses();
            }
            else if (ops2==2){
                Monthly_expenses();
            }
            else {
                printf("Invalid option. Please choose 1, or 2.\n");
            }
        }
        else if (ops==3){
            Quit();
        }
        else {
            printf("Invalid option. Please choose 1, 2, or 3.\n");
        }
    }
    return 0;
}