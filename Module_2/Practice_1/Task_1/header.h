#ifndef HEADER_H
#define HEADER_H

#define MAX_SYMBOLS 30
#define MAX_PHONES 5
#define MAX_EMAILS 5

typedef struct {
    char first_name[MAX_SYMBOLS];
    char last_name[MAX_SYMBOLS];
    char mid_name[MAX_SYMBOLS];
} Person;

typedef struct {
    char name[MAX_SYMBOLS];
    char link[MAX_SYMBOLS];
} SocialAccount;

typedef struct {
    Person person;
    char job_place[MAX_SYMBOLS];
    char job_title[MAX_SYMBOLS];
    char phones[MAX_PHONES][MAX_SYMBOLS];
    char emails[MAX_EMAILS][MAX_SYMBOLS];
    SocialAccount *accounts;
} Contact;

int print_list();
int add_contact();
int del_contact();
int edit_contact();

#endif