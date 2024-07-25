#include "header.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

void read_db(Contact contacts[MAX_CONTACTS]) {
    int fd = open(FILE_DB, O_RDONLY | O_CREAT, 0666);
    if (fd == -1) {
        printf("Ошибка открытия файла базы данных\n");
        exit(EXIT_FAILURE);
    }
    read(fd, contacts, sizeof(Contact) * MAX_CONTACTS);
    close(fd);
}

void write_db(Contact contacts[MAX_CONTACTS]) {
    int fd = open(FILE_DB, O_WRONLY | O_CREAT, 0666);
    if (fd == -1) {
        printf("Ошибка открытия файла базы данных\n");
        exit(EXIT_FAILURE);
    }
    write(fd, contacts, sizeof(Contact) * MAX_CONTACTS);
    close(fd);
}

void print_list(Contact contacts[MAX_CONTACTS]) {
    system("clear");
    int count = get_count_contacts(contacts);
    if (count == 0) {
        printf("Список пуст!\n");
        return;
    }
    printf("Список контактов:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s %s %s | работа: ", i + 1, contacts[i].person.last_name, contacts[i].person.first_name, contacts[i].person.mid_name);
        printf("%s %s | тел.: ", contacts[i].job_title, contacts[i].job_place);
        print_phones(contacts[i].phones);
        printf("| почта: ");
        print_emails(contacts[i].emails);
        printf("| соцсети: ");
        print_accounts(contacts[i].accounts);
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
    printf("Введите номер контакта: ");
    int num;
    scanf("%d", &num);
    num--;
    if (num >= 0 && num < count_contacts) {
        for (int i = num; i < count_contacts; i++) {
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
    printf("Введите номер контакта: ");
    int num;
    scanf("%d", &num);
    num--;
    if (num >= 0 && num < count_contacts) {
        system("clear");
        printf("Что вы хотите изменить?\n1. Фамилию\n2. Имя\n3. Отчество\n4. Место работы\n5. Должность\n6. Телефон\n7. Почту\n8. Профиль в соцсети\n0. Назад\n");
        int c;
        scanf(" %d", &c);
        system("clear");
        switch (c) {
            case 1: {
                printf("Введите новую фамилию: ");
                input_string(contacts[num].person.last_name);
                break;
            }
            case 2: {
                printf("Введите новое имя: ");
                input_string(contacts[num].person.first_name);
                break;
            }
            case 3: {
                printf("Введите новое отчество: ");
                input_string(contacts[num].person.mid_name);
                break;
            }
            case 4: {
                printf("Введите новое место работы: ");
                input_string(contacts[num].job_place);
                break;
            }
            case 5: {
                printf("Введите новую должность: ");
                input_string(contacts[num].job_title);
                break;
            }
            case 6: {
                int phones_count = print_phones(contacts[num].phones);
                if (phones_count == 0) {
                    printf("Номеров нет, добавьте новый: ");
                    input_string(contacts[num].phones[0]);
                } else {
                    if (phones_count <= MAX_PHONES) {
                        printf("\nВыберите телефон для редактирования (%d - ввести новый): ", phones_count);
                    } else {
                        printf("\nВыберите телефон для редактирования: ");
                    }
                    int c;
                    scanf("%d", &c);
                    if (c >= 1 && c <= phones_count && c <= MAX_PHONES) {
                        printf("Введите новый номер телефона: ");
                        input_string(contacts[num].phones[c - 1]);
                        contacts[num].phones[phones_count][0] = '\0';
                    } else {
                        printf("Введен неверный номер!\n");
                    }
                }
                break;
            }
            case 7: {
                int emails_count = print_emails(contacts[num].emails);
                if (emails_count == 0) {
                    printf("Адресов нет, добавьте новый: ");
                    input_string(contacts[num].emails[0]);
                } else {
                    if (emails_count <= MAX_EMAILS) {
                        printf("\nВыберите адрес для редактирования (%d - ввести новый): ", emails_count);
                    } else {
                        printf("\nВыберите адрес для редактирования: ");
                    }
                    int c;
                    scanf("%d", &c);
                    if (c >= 1 && c <= emails_count && c <= MAX_EMAILS) {
                        printf("Введите новый адрес почты: ");
                        input_string(contacts[num].emails[c - 1]);
                        contacts[num].emails[emails_count][0] = '\0';
                    } else {
                        printf("Введен неверный номер!\n");
                    }
                }
                break;
            }
            case 8: {
                int accounts_count = print_accounts(contacts[num].accounts);
                if (accounts_count == 0) {
                    printf("Профилей нет, создайте первый.\nВведите название соцсети: ");
                    input_string(contacts[num].accounts[0].name);
                    printf("Введите ссылку на профиль: ");
                    input_string(contacts[num].accounts[0].link);
                } else {
                    if (accounts_count <= MAX_ACCOUNTS) {
                        printf("\nВыберите профиль для редактирования (%d - создать новый): ", accounts_count);
                    } else {
                        printf("\nВыберите профиль для редактирования: ");
                    }
                    int c;
                    scanf("%d", &c);
                    if (c >= 1 && c <= accounts_count && c <= MAX_ACCOUNTS) {
                        printf("Введите название соцсети: ");
                        input_string(contacts[num].accounts[c - 1].name);
                        printf("Введите ссылку на профиль: ");
                        input_string(contacts[num].accounts[c - 1].link);
                        contacts[num].accounts[accounts_count].name[0] = '\0';
                        contacts[num].accounts[accounts_count].link[0] = '\0';
                    } else {
                        printf("Введен неверный номер!\n");
                    }
                }
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
        scanf(" %c", &input_continue);
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

int print_phones(char phones[MAX_PHONES][MAX_SYMBOLS]) {
    int j;
    if (phones[0][0] == '\0') return 0;
    for (j = 0; j < MAX_PHONES && phones[j][0] != '\0'; j++) {
        printf("%d) %s. ", j + 1, phones[j]);
    }
    return j + 1;
}

int print_emails(char emails[MAX_EMAILS][MAX_SYMBOLS]) {
    int j;
    if (emails[0][0] == '\0') return 0;
    for (j = 0; j < MAX_EMAILS && emails[j][0] != '\0'; j++) {
        printf("%d) %s. ", j + 1, emails[j]);
    }
    return j + 1;
}

int print_accounts(SocialAccount accounts[MAX_ACCOUNTS]) {
    int j;
    if (accounts[0].name[0] == '\0') return 0;
    for (j = 0; j < MAX_ACCOUNTS && accounts[j].name[0] != '\0'; j++) {
        printf("%d) %s - %s. ", j + 1, accounts[j].name, accounts[j].link);
    }
    return j + 1;
}