#ifndef HEADER_H
#define HEADER_H

#define FILE_DB "data.db"
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

void read_db(Contact contacts[MAX_CONTACTS]);
void write_db(Contact contacts[MAX_CONTACTS]);

int add_contact(Contact contacts[MAX_CONTACTS]);
int del_contact(Contact contacts[MAX_CONTACTS]);
int edit_contact(Contact contacts[MAX_CONTACTS]);

void clear_contact(Contact *contact);

void input_person(Person *new_person);
void input_phones(char phones[MAX_PHONES][MAX_SYMBOLS]);
void input_emails(char phones[MAX_EMAILS][MAX_SYMBOLS]);
void input_account(SocialAccount account[MAX_ACCOUNTS]);

void input_nullable_string(char str[MAX_SYMBOLS]);
void input_string(char str[MAX_SYMBOLS]);

int get_count_contacts(Contact contacts[MAX_CONTACTS]);
int get_person_index(Contact contacts[MAX_CONTACTS], int count_contacts, Person *person);

void print_list(Contact contacts[MAX_CONTACTS]);
int print_phones(char phones[MAX_PHONES][MAX_SYMBOLS]);
int print_emails(char emails[MAX_EMAILS][MAX_SYMBOLS]);
int print_accounts(SocialAccount accounts[MAX_ACCOUNTS]);

#endif