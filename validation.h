//
// Created by B BACK on 7/13/2026.
//

#ifndef CULTURALAGENDA_VALIDATION_H
#define CULTURALAGENDA_VALIDATION_H

//  Bibek Gnawali (a59441) AND Divya Shrestha (a57524)
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

void clear();
void read_eventname(char* eventname);
int is_leap_year(int year);
int days_in_month(int year, int month);
Date current_time();
int is_same_date(Date a, Date b);
int is_future_date(Date date);
int is_future_time(Date date);
int date_is_valid(Date date);
int time_is_valid(Time time);
int valid_duration(Time time);
int valid_classification(Classification event);
void compress_time(Time* time);
Time add_time(Time a, Time b);
int valid_capacity(int num);
char* classify(Classification sec);
void print_event(EventRegister a);
int cancel_event(EventRegister events[], int event_key,int*num);
int time_overlapped(EventRegister events[], Date date, int num);
int event_status(EventRegister event);
void lines(int num);

#endif //CULTURALAGENDA_VALIDATION_H
