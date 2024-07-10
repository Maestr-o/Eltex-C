#ifndef HEADER_H
#define HEADER_H

#define MAX_SYMBOLS 30
#define MAX_CONTACTS 100
#define MAX_PHONES 5
#define MAX_EMAILS 5
#define MAX_ACCOUNTS 5

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
    SocialAccount accounts[MAX_ACCOUNTS];
} Contact;

void print_list(Contact contacts[MAX_CONTACTS]);
int add_contact(Contact contacts[MAX_CONTACTS]);
int del_contact();
int edit_contact();
void input_person(Person *new_person);
void input_phones(char phones[MAX_PHONES][MAX_SYMBOLS]);
void input_emails(char phones[MAX_EMAILS][MAX_SYMBOLS]);
void input_account(SocialAccount account[MAX_ACCOUNTS]);
int get_count_contacts(Contact contacts[MAX_CONTACTS]);
void input_nullable_string(char str[MAX_SYMBOLS]);

#endif