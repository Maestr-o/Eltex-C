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
        printf("%d. %s %s %s, работа: ", i + 1, contacts[i].person.last_name, contacts[i].person.first_name, contacts[i].person.mid_name);
        printf("%s %s тел.: ", contacts[i].job_title, contacts[i].job_place);
        print_phones(&contacts[i]);
        printf("почта: ");
        print_emails(&contacts[i]);
        printf("соцсети: ");
        print_accounts(&contacts[i]);
        printf("\n");
    }
};

int add_contact(Contact contacts[MAX_CONTACTS]) {
    int count_contacts = get_count_contacts(contacts);
    if (count_contacts >= MAX_CONTACTS) return 1;

    Contact new_contact;
    
    input_person(&new_contact.person);
    if (get_person_index(contacts, count_contacts, &new_contact.person) >= 0) return 1;

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

int del_contact(Contact contacts[MAX_CONTACTS]) {
    int count_contacts = get_count_contacts(contacts);
    Person person;
    input_person(&person);
    int person_index = get_person_index(contacts, count_contacts, &person);
    if (person_index >= 0) {
        for (int i = person_index; i < count_contacts - 1; i++) {
            contacts[i] = contacts[i + 1];
        }
        clear_contact(&contacts[count_contacts - 1]);
        return 0;
    } else {
        return 1;
    }
};

int edit_contact(Contact contacts[MAX_CONTACTS]) {
    int count_contacts = get_count_contacts(contacts);
    Person person;
    input_person(&person);
    int person_index = get_person_index(contacts, count_contacts, &person);
    if (person_index >= 0) {
        system("clear");
        printf("Что вы хотите изменить?\n1. Фамилию\n2. Имя\n3. Отчество\n4. Место работы\n5. Должность\n6. Телефон\n7. Почту\n8. Профиль в соцсети\n0. Назад\n");
        int c;
        scanf(" %d", &c);
        system("clear");
        switch (c) {
            case 1: {
                printf("Введите новую фамилию: ");
                input_string(contacts[person_index].person.last_name);
                break;
            }
            case 2: {
                printf("Введите новое имя: ");
                input_string(contacts[person_index].person.first_name);
                break;
            }
            case 3: {
                printf("Введите новое отчество: ");
                input_string(contacts[person_index].person.mid_name);
                break;
            }
            case 4: {
                printf("Введите новое место работы: ");
                input_string(contacts[person_index].job_place);
                break;
            }
            case 5: {
                printf("Введите новую должность: ");
                input_string(contacts[person_index].job_title);
                break;
            }
            case 6: {
                printf("Выберите телефон для редактирования:\n");

                break;
            }
            case 0:
                return 0;
            default: {
                printf("Неверный пункт!\n");
                break;
            }
        }
        return 0;
    } else {
        return 1;
    }
};

void input_person(Person *new_person) {
    printf("Введите фамилию (обязательно): ");
    input_string(new_person->last_name);
    printf("Введите имя (обязательно): ");
    input_string(new_person->first_name);
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
        scanf("%c", &input_continue);
        if (input_continue != 'y') {
            accounts[i].name[0] = '\0';
            break;
        }
        printf("Введите название соцсети: ");
        input_string(accounts[i].name);
        printf("Введите ссылку на профиль: ");
        input_string(accounts[i++].link);
    }
};

int get_count_contacts(Contact contacts[MAX_CONTACTS]) {
    int i = 0;
    while (contacts[i].person.last_name[0] != '\0') {
        i++;
    }
    return i;
}

void input_string(char str[MAX_SYMBOLS]) {
    int ch;
    int length = 0;

    while (1) {
        length = 0;
        while ((ch = getchar()) != '\n' && ch != EOF && length < MAX_SYMBOLS - 1) {
            str[length++] = ch;
        }
        str[length] = '\0';
        if (length == MAX_SYMBOLS - 1) {
            while ((ch = getchar()) != '\n' && ch != EOF);
        }
        if (length > 0) {
            break;
        }
    }
}

void input_nullable_string(char str[MAX_SYMBOLS]) {
    int ch;
    int length = 0;
    while ((ch = getchar()) != '\n' && ch != EOF && length < MAX_SYMBOLS - 1) {
        str[length++] = ch;
    }
    str[length] = '\0';
    if (length == MAX_SYMBOLS - 1) {
        while ((ch = getchar()) != '\n' && ch != EOF);
    }
};

int get_person_index(Contact contacts[MAX_CONTACTS], int count_contacts, Person *person) {
    for (int i = 0; i < count_contacts; i++) {
        if (strcmp(contacts[i].person.first_name, person->first_name) == 0
            && strcmp(contacts[i].person.last_name, person->last_name) == 0
            && strcmp(contacts[i].person.mid_name, person->mid_name) == 0) 
            return i;
    }
    return -1;
};

void clear_contact(Contact *contact) {
    memset(contact->person.first_name, 0, sizeof(contact->person.first_name));
    memset(contact->person.last_name, 0, sizeof(contact->person.last_name));
    memset(contact->person.mid_name, 0, sizeof(contact->person.mid_name));
    memset(contact->job_place, 0, sizeof(contact->job_place));
    memset(contact->job_title, 0, sizeof(contact->job_title));
    for (int i = 0; i < MAX_PHONES; i++) {
        memset(contact->phones[i], 0, sizeof(contact->phones[i]));
    }
    for (int i = 0; i < MAX_EMAILS; i++) {
        memset(contact->emails[i], 0, sizeof(contact->emails[i]));
    }
    for (int i = 0; i < MAX_ACCOUNTS; i++) {
        memset(contact->accounts[i].name, 0, sizeof(contact->accounts[i].name));
        memset(contact->accounts[i].link, 0, sizeof(contact->accounts[i].link));
    }
}

void print_phones(Contact *contact) {
    for (int j = 0; j < MAX_PHONES && contact->phones[j][0] != '\0'; j++) {
        printf("%d) %s, ", j + 1, contact->phones[j]);
    }
}

void print_emails(Contact *contact) {
    for (int j = 0; j < MAX_EMAILS && contact->emails[j][0] != '\0'; j++) {
        printf("%d) %s, ", j + 1, contact->emails[j]);
    }
}

void print_accounts(Contact *contact) {
    for (int j = 0; j < MAX_ACCOUNTS && contact->accounts[j].name[0] != '\0'; j++) {
        printf("%d) %s - %s, ", j + 1, contact->accounts[j].name, contact->accounts[j].link);
    }
}