#include "header.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void print_list(Item *head) {
    system("clear");
    int count = get_count_contacts(head);
    if (count == 0) {
        printf("Список пуст!\n");
        return;
    }
    printf("Список контактов:\n");
    int i = 1;
    for (Item* p = head; p != NULL; p = p->next, i++) {
        printf("%d. %s %s %s | работа: ", i, p->contact.person.last_name, p->contact.person.first_name, p->contact.person.mid_name);
        printf("%s %s | тел.: ", p->contact.job_title, p->contact.job_place);
        print_phones(p->contact.phones);
        printf("| почта: ");
        print_emails(p->contact.emails);
        printf("| соцсети: ");
        print_accounts(p->contact.accounts);
        printf("\n");
    }
};

Item* add_contact(Item* head) {
    int count_contacts = get_count_contacts(head);
    if (count_contacts >= MAX_CONTACTS) {
        printf("Превышен лимит на кол-во контактов\n");
        return head;
    }

    Contact new_contact;
    
    input_person(&new_contact.person);
    if (get_person_index(head, new_contact.person) >= 0) {
        printf("Контакт с таким ФИО уже существует\n");
        return head;
    };

    printf("Введите место работы: ");
    input_nullable_string(new_contact.job_place);
    printf("Введите должность: ");
    input_nullable_string(new_contact.job_title);
    
    input_phones(new_contact.phones);
    input_emails(new_contact.emails);
    input_account(new_contact.accounts);

    return insert(head, new_contact);
};

Item* insert(Item* head, Contact contact) {
    Item* item = malloc(sizeof(Item));
    item->contact = contact;
    if (head == NULL) {
        return item;
    }
    Item* right = find_pointer(head, contact);
    if (right == NULL) {
        Item* last = head;
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = item;
        item->prev = last;
    } else if (right->prev == NULL) {
        item->next = right;
        right->prev = item;
        head = item;
    } else {
        Item* left = right->prev;
        left->next = item;
        item->prev = left;
        item->next = right;
        right->prev = item;
    }
    return head;
}

Item* find_pointer(Item* head, Contact contact) {
    Item* p = head;
    while (p != NULL) {
        if (strcmp(p->contact.person.last_name, contact.person.last_name) >= 0) {
            break;
        }
        p = p->next;
    }
    return p;
}

Item* del_contact(Item* head, int n) {
    int count_contacts = get_count_contacts(head);
    if (n < 0 || n >= count_contacts) {
        printf("Контакта с таким номером не существует\n");
        return head;
    }
    Item *p = head;
    for (int i = 0; i < n; i++) p = p->next;
    if (p->prev != NULL) {
        p->prev->next = p->next;
    } else {
        head = p->next;
    }
    if (p->next != NULL) {
        p->next->prev = p->prev;
    }
    clear_contact(&p->contact);
    free(p);
    return head;
}

Item* sort_contacts(Item* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }
    Item* sorted = NULL;
    Item* current = head;
    while (current != NULL) {
        Item* next = current->next;
        current->prev = current->next = NULL;
        sorted = insert(sorted, current->contact);
        current = next;
    }
    return sorted;
}

int get_person_index(Item* head, Person person) {
    int i = 0;
    for (Item* p = head; p != NULL; p = p->next, i++) {
        if (strcmp(p->contact.person.first_name, person.first_name) == 0
            && strcmp(p->contact.person.last_name, person.last_name) == 0
            && strcmp(p->contact.person.mid_name, person.mid_name) == 0) 
            return i;
    }
    return -1;
};

Item* edit_contact(Item* head, int n) {
    int count_contacts = get_count_contacts(head);
    if (n < 0 || n >= count_contacts) {
        printf("Контакта с таким номером не существует\n");
        return head;
    }
    Item *p = head;
    for (int i = 0; i < n; i++) p = p->next;

    system("clear");
    printf("Что вы хотите изменить?\n1. Фамилию\n2. Имя\n3. Отчество\n4. Место работы\n5. Должность\n6. Телефон\n7. Почту\n8. Профиль в соцсети\n0. Назад\n");
    int c;
    scanf(" %d", &c);
    system("clear");
    switch (c) {
        case 1: {
            printf("Введите новую фамилию: ");
            input_string(p->contact.person.last_name);
            return sort_contacts(head);
        }
        case 2: {
            printf("Введите новое имя: ");
            input_string(p->contact.person.first_name);
            break;
        }
        case 3: {
            printf("Введите новое отчество: ");
            input_string(p->contact.person.mid_name);
            break;
        }
        case 4: {
            printf("Введите новое место работы: ");
            input_string(p->contact.job_place);
            break;
        }
        case 5: {
            printf("Введите новую должность: ");
            input_string(p->contact.job_title);
            break;
        }
        case 6: {
            int phones_count = print_phones(p->contact.phones);
            if (phones_count == 0) {
                printf("Номеров нет, добавьте новый: ");
                input_string(p->contact.phones[0]);
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
                    input_string(p->contact.phones[c - 1]);
                    p->contact.phones[phones_count][0] = '\0';
                } else {
                    printf("Введен неверный номер!\n");
                }
            }
            break;
        }
        case 7: {
            int emails_count = print_emails(p->contact.emails);
            if (emails_count == 0) {
                printf("Адресов нет, добавьте новый: ");
                input_string(p->contact.emails[0]);
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
                    input_string(p->contact.emails[c - 1]);
                    p->contact.emails[emails_count][0] = '\0';
                } else {
                    printf("Введен неверный номер!\n");
                }
            }
            break;
        }
        case 8: {
            int accounts_count = print_accounts(p->contact.accounts);
            if (accounts_count == 0) {
                printf("Профилей нет, создайте первый.\nВведите название соцсети: ");
                input_string(p->contact.accounts[0].name);
                printf("Введите ссылку на профиль: ");
                input_string(p->contact.accounts[0].link);
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
                    input_string(p->contact.accounts[c - 1].name);
                    printf("Введите ссылку на профиль: ");
                    input_string(p->contact.accounts[c - 1].link);
                    p->contact.accounts[accounts_count].name[0] = '\0';
                    p->contact.accounts[accounts_count].link[0] = '\0';
                } else {
                    printf("Введен неверный номер!\n");
                }
            }
            break;
        }
        case 0:
            return head;
        default: {
            printf("Неверный пункт!\n");
            break;
        }
    }
    return head;
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

int get_count_contacts(Item *head) {
    int i;
    Item* p = head;
    for (i = 0; p != NULL; p = p->next, i++);
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