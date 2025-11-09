#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include<string.h>
#include<ctype.h>

//structure

struct contact
{
    char name[20];
    char mobile[11];
    char mail[50];
};
struct address
{
    struct contact arr[100];
    int    contact_count;
};

//function declarations

int valid(struct contact *c,int mode);
void create(struct address *a, int *contact_count);
void display(struct address *a);
int search(struct address *a);
void delete(struct address *a);
void edit(struct address *a);
int unique (struct address *a,struct contact*c,int mode,int skip_index);
void save(struct address*a);
void load(struct address*a,int *contact_count);
#endif