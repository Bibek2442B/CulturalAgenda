//
// Created by B BACK on 7/13/2026.
//
// C file containing extra functions for checking invalid input and other extra functions.
#include<stdio.h>
#include<string.h>
#include<time.h>
#define MAX 100
#define THEATER_CAPACITY 500

typedef enum { B6 = 1, B12, B16 }Classification;

typedef struct {
	int minutes;
	int hours;
}Time;

typedef struct {
	Time time;
	int day;
	int month;
	int year;
}Date;

typedef struct {
	int event_key;
	char event[MAX];
	char artist[MAX];
	Classification classification;
	Date date;
	Time duration;
	int capacity;
	int tickets_available;
}EventRegister;

//Function with less characters to use instead of FSEEK everytime before scanf in loop.
void clear() { fseek(stdin, 0, SEEK_END); }

void read_eventname(char* eventname) {
	while (1) {
		clear();
		gets(eventname);
		if (strlen(eventname) > 0 && strlen(eventname) < MAX) break;
		else printf("Invalid character length!\nType event name (%d char. max): ", MAX);
	}
}

//To check if the year is leap year to see if Feburary has 28 or 29 days
int is_leap_year(const int year) {
	return (!(year % 4) && ((year % 100) || !(year % 400)));
}

//Returns last day of month to check if the date entered is valid or not.
int days_in_month(const int year, const int month) {
	switch (month) {
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		return 31;
	case 4:
	case 6:
	case 9:
	case 11:
		return 30;
	case 2:
		return (is_leap_year(year)) ? 29 : 28;
	default:
		return 0;
	}
}

Date current_time() {
	time_t t;
	Date date;
	time(&t);
	const struct tm *time_now = localtime(&t);
	date.year = time_now->tm_year + 1900;
	date.month = time_now->tm_mon + 1;
	date.day = time_now->tm_mday;
	date.time.hours = time_now->tm_hour;
	date.time.minutes = time_now->tm_min;
	return date;
}

//Compares if two dates are same to ensure the events do not overlap
int is_same_date(const Date a, const Date b) {
	return (a.year == b.year && a.month == b.month && a.day == b.day);
}

int is_future_date(const Date date) {
	const Date time_now = current_time();
	if (is_same_date(date, time_now)) return 1;
	if (date.year > time_now.year) return 1;
	if (date.year < time_now.year) return 0;
	if (date.month > time_now.month) return 1;
	if (date.month < time_now.month) return 0;
	if (date.day > time_now.day) return 1;
	if (date.day < time_now.day) return 0;
	return 0;
}

int is_future_time(const Date date) {
	Date time_now = current_time();
	if (is_same_date(date, time_now)) {
		if (date.time.hours > time_now.time.hours) return 1;
		if (date.time.hours < time_now.time.hours) return 0;
		if (date.time.minutes > time_now.time.minutes) return 1;
		if (date.time.minutes < time_now.time.minutes) return 0;
		return 0;
	}
	else if (is_future_date(date)) return 1;
	else return 0;
}

//Returns 0 if the date is VALID so that the loop is stopped.
int date_is_valid(const Date date) {
	return (date.day > 0 && date.day <= days_in_month(date.year, date.month) && date.month > 0 && date.month < 13 && date.year < 2100);
}

//Returns 0 if the time is VALID so that the loop is stopped.
int time_is_valid(const Time time) {
	return (time.hours >= 0 && time.hours < 24 && time.minutes >= 0 && time.minutes < 60);
}

//Returns 0 if the duration is VALID so that the loop is stopped.
int valid_duration(const Time time) {
	if (time.hours > 0) return (time.minutes >= 0);
	if (time.hours == 0) return (time.minutes > 0);
	return 0;
}

//Returns 0 if the classification is VALID so that the loop is stopped.
int valid_classification(const Classification event) {
	switch (event) {
	case 1:
	case 2:
	case 3:
		return 1;
	default:
		return 0;
	}
}

//Function to compress time (E.g 1h:90m will be converted into 2h:30m)
void compress_time(Time* time) {
	time->hours += time->minutes / 60;
	time->minutes = time->minutes % 60;
}


//Function to add time to calculate Ending time of event by adding Start time with duration
Time add_time(const Time a, const Time b) {
	Time c;
	c.hours = a.hours + b.hours;
	c.minutes = a.minutes + b.minutes;
	compress_time(&c);
	return c;
}

//Returns 0 if the capacity is VALID so that the loop is stopped.
int valid_capacity(const int num) {
	return (num <= THEATER_CAPACITY && num > 0);
}

//Returns string for ENUM Classification
char* classify(const Classification sec) {
	switch (sec) {
	case B6:
		return "B6";
	case B12:
		return "B12";
	case B16:
		return "B16";
	}
	return nullptr;
}

int event_status(const EventRegister event) {
	Date temp = event.date;
	temp.time = add_time(event.date.time, event.duration);
	if (!is_future_time(temp)) {
		printf("The event has already passed! Booking closed.\n");
		return 0;
	}
	if (!is_future_time(event.date) && is_future_time(temp)) {
		printf("The event is currently happenning. Booking closed.\n");
		return 0;
	}
	return 1;
}

//Function to print all datas of data type EventRegister
void print_event(EventRegister a) {
	printf("Event key: %d\n", a.event_key);
	printf("\tEvent name: %s\n", a.event);
	printf("\tArtist name: %s\n", a.artist);
	printf("\tClassification: %s\n", classify(a.classification));
	printf("\tDate: %02d/%02d/%04d\n", a.date.day, a.date.month, a.date.year);
	printf("\tTime: %02d:%02d\n", a.date.time.hours, a.date.time.minutes);
	printf("\tDuration: %02dh %02dm\n", a.duration.hours, a.duration.minutes);
	printf("\tCapacity: %d\n", a.capacity);
	printf("\tTickets available: %d\n", a.tickets_available);
	event_status(a);
	printf("\n");
}

int cancel_event(EventRegister events[], const int event_key, int* num) {
	int s = 0;
	for (int i = 0; i < *num; i++) {
		if (events[i].event_key == event_key) s = 1;
		if (s) {
			events[i] = events[i + 1];
			events[i].event_key--;
		}
	}
	(*num)--;
	return s;
}

//Checks if the entered time is overlapping with other events or not
int time_overlapped(EventRegister events[], const Date date, const int num) {
	Time end_time;
	for (int i = 0; i < num; i++) {
		if (is_same_date(events[i].date, date)) {
			end_time = add_time(events[i].date.time, events[i].duration);
			if (date.time.hours >= events[i].date.time.hours && date.time.hours < end_time.hours) {
				printf("The following event already exists at this time:\n ");
				print_event(events[i]);
				return 1;
			}
			else if (date.time.hours == events[i].date.time.hours && date.time.hours == end_time.hours && date.time.minutes >= events[i].date.time.minutes && date.time.minutes < end_time.minutes) {
				printf("The following event already exists at this time:\n ");
				print_event(events[i]);
				return 1;
			}
			else if (date.time.hours == events[i].date.time.hours && date.time.minutes > events[i].date.time.minutes) {
				printf("This event already exists at this time:\n ");
				print_event(events[i]);
				return 1;
			}
			else if (date.time.hours == end_time.hours && date.time.minutes < end_time.minutes) {
				printf("This event already exists at this time:\n ");
				print_event(events[i]);
				return 1;
			}
		}
	}
	return 0;
}

// Weird way to print specific number of "--------". Sorry for this!!!
void lines(const int num) {
	printf("\t\t\t\t\t\t");
	for (int i = 0; i < num - 7; i++) {
		printf("-");
	}
	printf("\n");
}