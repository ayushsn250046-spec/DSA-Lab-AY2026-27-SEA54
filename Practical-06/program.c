#include <stdio.h>
#include <string.h>

#define MAX 3
#define NAME_SIZE 50

struct Passenger {
    int id;
    char name[NAME_SIZE];
};

/* Confirmed and waiting queues */
struct Passenger confirmed[MAX];
struct Passenger waiting[MAX];

int rearC = -1;
int rearW = -1;

void bookTicket(void)
{
    struct Passenger passenger;

    printf("\nEnter Passenger ID: ");
    if (scanf("%d", &passenger.id) != 1) {
        printf("Invalid ID.\n");
        return;
    }

    printf("Enter Passenger Name: ");
    if (scanf("%49s", passenger.name) != 1) {
        printf("Invalid name.\n");
        return;
    }

    if (rearC < MAX - 1) {
        confirmed[++rearC] = passenger;
        printf("Ticket CONFIRMED for %s.\n", passenger.name);
    } else if (rearW < MAX - 1) {
        waiting[++rearW] = passenger;
        printf("No seats available. %s added to the WAITING LIST.\n",
               passenger.name);
    } else {
        printf("The waiting list is also full.\n");
    }
}

void cancelTicket(void)
{
    int id;
    int found = 0;

    printf("\nEnter Passenger ID to cancel: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid ID.\n");
        return;
    }

    for (int i = 0; i <= rearC; i++) {
        if (confirmed[i].id == id) {
            found = 1;
            printf("Ticket cancelled for %s.\n", confirmed[i].name);

            /* Remove the passenger and close the gap. */
            for (int j = i; j < rearC; j++) {
                confirmed[j] = confirmed[j + 1];
            }
            rearC--;

            /* Promote the first waiting passenger, if there is one. */
            if (rearW >= 0) {
                confirmed[++rearC] = waiting[0];
                printf("%s moved from WAITING to CONFIRMED.\n",
                       waiting[0].name);

                for (int j = 0; j < rearW; j++) {
                    waiting[j] = waiting[j + 1];
                }
                rearW--;
            }
            break;
        }
    }

    if (!found) {
        printf("Confirmed passenger ID not found.\n");
    }
}

void displayConfirmed(void)
{
    printf("\n--- CONFIRMED PASSENGERS ---\n");

    if (rearC < 0) {
        printf("No confirmed passengers.\n");
        return;
    }

    for (int i = 0; i <= rearC; i++) {
        printf("ID: %d  Name: %s\n", confirmed[i].id, confirmed[i].name);
    }
}

void displayWaiting(void)
{
    printf("\n--- WAITING LIST ---\n");

    if (rearW < 0) {
        printf("Waiting list is empty.\n");
        return;
    }

    for (int i = 0; i <= rearW; i++) {
        printf("ID: %d  Name: %s\n", waiting[i].id, waiting[i].name);
    }
}

int main(void)
{
    int choice;

    do {
        printf("\n===== TRAIN TICKET BOOKING SYSTEM =====\n");
        printf("1. Book Ticket\n");
        printf("2. Cancel Ticket\n");
        printf("3. Display Confirmed Passengers\n");
        printf("4. Display Waiting List\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice.\n");
            return 1;
        }

        switch (choice) {
            case 1:
                bookTicket();
                break;
            case 2:
                cancelTicket();
                break;
            case 3:
                displayConfirmed();
                break;
            case 4:
                displayWaiting();
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 5);

    return 0;
}