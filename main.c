#include<stdio.h>
#include<string.h>
#include<time.h>
#include"eventlibrary.h"
#define MAX 100
#define THEATER_CAPACITY 500
#define PATH "events.dat"

int main() {
    EventRegister events[MAX];
    int tickets;
    int num = LoadEvents(events, PATH);
    char eventname[MAX];
    Classification class;
    while (1) {
        switch (menu()) {
            case 1:
                InsertEvent(events, &num);
                break;
            case 2:
                printf("Type the name of the event: ");
                read_eventname(eventname);
                PrintEvent(eventname, events,num);
                break;
            case 3:
                printf("Type the name of the event to cancel: ");
                read_eventname(eventname);
                CancelEvents(events, eventname,&num);
                break;
            case 4:
                printf("Enter the classification: ");
                while (1) {
                    printf("1)B6\t2)B12\t3)B16\n");
                    clear();
                    scanf("%d", &class);
                    if (valid_classification(class)) break;
                    else printf("Invalid classification!\nPlease enter a valid classification: ");
                }
                FilterEvents(events, class,num);
                break;
            case 5:
                printf("Enter Event Name: ");
                read_eventname(eventname);
                while (1) {
                    printf("Enter no. of tickets to register: ");
                    clear();
                    scanf("%d", &tickets);
                    if (tickets <= THEATER_CAPACITY && tickets > 0) break;
                    else printf("Invalid no. of tickets. (%d max. tickets)\n",MAX);
                }
                BuyTicket(events, eventname, tickets,num);
                break;
            case 6:
                show_all_events(events, num);
                break;
            case 0:
                SaveEvents(events, PATH, num);
                return 0;
        }
    }
    return 0;
}