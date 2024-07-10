#include "header.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_list(Contact contacts[MAX_CONTACTS]) {
    system("clear");
    int count = get_count_contacts(contacts);
    if (count == 0) {
        printf("Список пуст!\n");
        return;
    }
    printf("Список контактов:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s %s %s - ", i + 1, contacts[i].person.last_name, contacts[i].person.first_name, contacts[i].person.mid_name);
        printf("%s в %s, тел.: ", contacts[i].job_title, contacts[i].job_place);
        for (int j = 0; j < MAX_PHONES && contacts[i].phones[j][0] != '\0'; j++) {
            printf("%s, ", contacts[i].phones[j]);
        }
        printf("почта: ");
        for (int j = 0; j < MAX_EMAILS && contacts[i].emails[j][0] != '\0'; j++) {
            printf("%s, ", contacts[i].emails[j]);
        }
        printf("соцсети: ");
        for (int j = 0; j < MAX_ACCOUNTS && contacts[i].accounts[j].name[0] != '\0'; j++) {
            printf("%s - %s, ", contacts[i].accounts[j].name, contacts[i].accounts[j].link);
        }
        printf("\n");
    }
};

int add_contact(Contact contacts[MAX_CONTACTS]) {
    int count_contacts = get_count_contacts(contacts);
    Contact new_contact;
    
    input_person(&new_contact.person);

    printf("Введите место работы: ");
    input_nullable_string(new_contact.job_place);
    printf("Введите должность: ");
    input_nullable_string(new_contact.job_title);
    
    input_phones(new_contact.phones);
    input_emails(new_contact.emails);
    input_account(new_contact.accounts);

    contacts[count_contacts] = new_contact;

    return 0;
};

int del_contact() {
    return 0;
};

int edit_contact() {
    return 0;
};

void input_person(Person *new_person) {
    printf("Введите фамилию (обязательно): ");
    scanf("%s", new_person->last_name);
    printf("Введите имя (обязательно): ");
    scanf("%s", new_person->first_name);
    printf("Введите отчество: ");
    input_nullable_string(new_person->mid_name);
};

void input_phones(char phones[MAX_PHONES][MAX_SYMBOLS]) {
    int i = 0;
    while ((i == 0 || phones[i - 1][0] != '\0') && i < MAX_PHONES) {
        printf("Введите %d-й номер телефона: ", i + 1);
        input_nullable_string(phones[i++]);
    }
};

void input_emails(char emails[MAX_EMAILS][MAX_SYMBOLS]) {
    int i = 0;
    while ((i == 0 || emails[i - 1][0] != '\0') && i < MAX_EMAILS) {
        printf("Введите %d-й email: ", i + 1);
        input_nullable_string(emails[i++]);
    }
};

void input_account(SocialAccount accounts[MAX_ACCOUNTS]) {
    int i = 0;
    while (i < MAX_ACCOUNTS) {
        char input_continue;
        printf("Добавить %d-й аккаунт соцсети? [y/n] ", i + 1);
        scanf(" %c", &input_continue);
        if (input_continue != 'y') break;
        printf("Введите название соцсети: ");
        scanf("%s", accounts[i].name);
        printf("Введите ссылку на профиль: ");
        scanf("%s", accounts[i++].link);
    }
};

int get_count_contacts(Contact contacts[MAX_CONTACTS]) {
    int i = 0;
    while (contacts[i].person.last_name[0] != '\0') {
        i++;
    }
    return i;
}

void input_nullable_string(char str[MAX_SYMBOLS]) {
    getchar();
    scanf("%255[^\n]", str);
};