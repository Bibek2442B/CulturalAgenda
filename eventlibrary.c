//
// Created by B BACK on 7/13/2026.
//
#include<stdio.h>
#include<string.h>
#include<time.h>
#include"validation.h"
#define MAX 100
#define THEATER_CAPACITY 500

int menu() {
	printf("\t\t\t\t\t\t\tMAIN MENU\n\n");
	printf("\t\t\t\t\t\tChoose an option:\n\n");
	lines(printf("\t\t\t\t\t\tEnter 1 -> Insert an Event.\n")); //lines function prints ----- below text printed.
	lines(printf("\t\t\t\t\t\tEnter 2 -> Show info about an Event.\n"));
	lines(printf("\t\t\t\t\t\tEnter 3 -> Cancel an Event.\n"));
	lines(printf("\t\t\t\t\t\tEnter 4 -> Filter events by rating.\n"));
	lines(printf("\t\t\t\t\t\tEnter 5 -> Register ticket purchases.\n"));
	lines(printf("\t\t\t\t\t\tEnter 6 -> Show all events.\n"));
	lines(printf("\t\t\t\t\t\tEnter 0 -> Save events and Exit.\n"));
	printf("Your option: ");
	clear();
	int opt;
	scanf("%d", &opt);
	return opt;
}

//Loads events into the vector
int LoadEvents(EventRegister events[], const char* file) {
	int num = 0;
	FILE* fp = fopen(file, "rb");
	if (fp != NULL) {
		clear();
		fread(&num, sizeof(int), 1, fp);
		fread(events, sizeof(EventRegister), num, fp);
		fclose(fp);
	}
	return num;
}

//Opens the binary file in write binary mode, therefore, the contents are overwritten
void SaveEvents(const EventRegister* event, char* str, const int num) {
	FILE* fp = fopen(str, "wb");
	fwrite(&num, sizeof(int), 1, fp);
	fwrite(event, sizeof(EventRegister), num, fp);
	printf("%d events sucessfully saved in %s.\n", num, str);
	fclose(fp);
}

//Inserts Event into the vector after validating all the inputs are valid and the vector has enough space to store new event.
int InsertEvent(EventRegister events[], int* num) {
	if (*num >= MAX) {
		printf("Not enough space in vector to insert a new event.\n");
		return -1;
	}

	printf("Type event name: ");
	read_eventname(events[*num].event);

	printf("Type artist name: ");
	while (1) {
		clear();
		gets(events[*num].artist);
		if (strlen(events[*num].event) > 0 && strlen(events[*num].event) < MAX) break;
		else printf("Invalid character length!\nType artist name (%d char. max): ", MAX);
	}

	printf("Choose classification: ");
	//Loop until a valid classification is entered.
	while (1) {
		printf("1)B6\t2)B12\t3)B16\n");
		clear();
		scanf("%d", &(events[*num].classification));
		if (valid_classification(events[*num].classification)) break;
		else printf("Invalid classification!\nPlease enter a valid classification: ");
	}

	printf("Date of Event (DD/MM/YYYY): ");
	while (1) {
		clear();
		scanf("%d/%d/%d", &(events[*num].date.day), &(events[*num].date.month), &(events[*num].date.year));
		if (date_is_valid(events[*num].date)) {
			if (is_future_date(events[*num].date)) break;
			else printf("This date has already passed.\nPlease enter valid date(DD/MM/YYYY): ");
		}
		else printf("Invalid date!\nPlease enter a valid date: ");
	}

	printf("Time of Event (Hour : Minutes): ");
	while (1) {
		clear();
		scanf("%d:%d", &(events[*num].date.time.hours), &(events[*num].date.time.minutes));
		if (time_is_valid(events[*num].date.time)) {
			if (is_future_time(events[*num].date)) {
				if (time_overlapped(events, events[*num].date, *num)) printf("Please enter other time for the event (Hours : Minutes): ");
				else break;
			}
			else printf("This time has already passed.\nPlease enter valid time (Hours : Minutes): ");
		}
		else printf("Invalid Time!\nPlease enter a valid time (Hours : Minutes): ");
	}

	printf("Duration of the Event(Hour:Minutes): ");
	//Loop until a valid duration is typed
	while (1) {
		clear();
		scanf("%d:%d", &(events[*num].duration.hours), &(events[*num].duration.minutes));
		if (valid_duration(events[*num].duration)) break;
		else printf("Invalid duration!\nPlease enter a valid duration (Hours : Minutes): ");
	}
	compress_time(&(events[*num].duration));

	printf("Capacity of the Event: ");
	//Loop until the user enters value less than the theater capacity.
	while (1) {
		clear();
		scanf("%d", &events[*num].capacity);
		if (valid_capacity(events[*num].capacity)) break;
		else printf("Invalid capacity!\n Please enter a valid capacity (max. %d): ", THEATER_CAPACITY);
	}
	events[*num].tickets_available = events[*num].capacity;
	events[*num].event_key = *num + 1;
	(*num)++;
	return 1;
}

//Prints Event that matches the name received in parameter
int PrintEvent(char* event_name, EventRegister events[], const int num) {
	int s = 1;
	for (int i = 0; i < num; i++) {
		if (strstr(event_name, events[i].event)) {
			if (s)	printf("Event with name %s:\n", event_name);
			print_event(events[i]);
			s = 0;
		}
	}
	if (s)printf("There is no event with name %s.\n", event_name);
	return s;
}

//Function to print events	that are still available
void FilterEvents(EventRegister events[], const Classification classification, const int num) {
	int s = 1;
	for (int i = 0; i < num; i++) {
		if (events[i].classification == classification && is_future_time(events[i].date)) {
			if (s) printf("The events with classification %s are:\n", classify(classification));
			print_event(events[i]);
			s = 0;
		}
	}
	if (s) printf("There is no event with classification %s.\n", classify(classification));
}

int CancelEvents(EventRegister events[], char* event_name, int* num) {
	int key;
	if (PrintEvent(event_name, events, *num)) return 0;
	while (1) {
		printf("Enter the key of the event you want to cancel: ");
		clear();
		scanf("%d", &key);
		if (key > 0 && key < *num) break;
		else printf("Event with %d key doesn't exist.\n",key);
	}
	const int event_cancelled = cancel_event(events, key, num);
	if (event_cancelled) printf("Event with key no. %d was cancelled sucessfully.\n", key);
	return event_cancelled;
}

int BuyTicket(EventRegister events[], char* eventname, const int tickets, const int num) {
	int key;
	if (PrintEvent(eventname, events, num)) return 0;
	while(1) {
		printf("Enter the key of the event to buy tickets: ");
		clear();
		scanf("%d", &key);
		if (key > 0 && key <= num) break;
		else printf("Event with %d key doesn't exist.\n", key);
	}
	if (!event_status(events[--key])) return 0;

	if (!events[key].tickets_available) {
		printf("No tickets available for event %s.\n", events[key].event);
		return 0;
	}
	if (events[key].tickets_available < tickets) {
		printf("Only %d tickets available for event %s\n", events[key].tickets_available, events[key].event);
		return 0;
	}
	events[key].tickets_available -= tickets;
	printf("%d tickets sucessfully registered for event.\n", tickets);
	return 1;
}

//Function to show all Events in case the Event name is forgotten
void show_all_events(EventRegister events[], const int num) {
	for (int i = 0; i < num; i++) {
		print_event(events[i]);
	}
}