// CSCI 2530
// Assignment: 7
// Author:     Walter Sellars
// File:       event.h
// Tab stops:  4

#ifndef EVENT_H
#define EVENT_H

/*
 The "Event" structure contains a sender, receiver and time. Event's
 constructor initializes each of the fields in the structure.
*/

struct Event
{
    double time;
    int sender;
    int receiver;

    Event(int send, int rec, double tm)
    {
        sender = send;
        receiver = rec;
        time = tm;
    }
};

#endif