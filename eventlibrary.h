//
// Created by B BACK on 7/13/2026.
//

#ifndef CULTURALAGENDA_EVENTLIBRARY_H
#define CULTURALAGENDA_EVENTLIBRARY_H

#include<stdio.h>
#include<string.h>
#include<time.h>
#include"validation.h"
#define MAX 100
#define THEATER_CAPACITY 500
int menu();
int SaveEvents(EventRegister* event, char* str, int num);
int InsertEvent(EventRegister events[], int *num);
int LoadEvents(EventRegister events[], const char* file);
int PrintEvent(char* str, EventRegister events[],int num);
void show_all_events(EventRegister events[], int num);
int CancelEvents(EventRegister events[], char* event_name,int* num);
void FilterEvents(EventRegister events[], Classification classification,int num);
int BuyTicket(EventRegister events[], char* eventname, int tickets,int num);


#endif //CULTURALAGENDA_EVENTLIBRARY_H
