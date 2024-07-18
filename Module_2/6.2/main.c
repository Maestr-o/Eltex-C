#include "header.h"

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main() {
    Item* (*add_contact)(Item*);
    Item* (*del_contact)(Item*, int);
    Item* (*edit_contact)(Item*, int);
    Item* (*insert)(Item*, Contact);
    Item* (*find_pointer)(Item*, Contact);
    Item* (*sort_contacts)(Item*);
    void (*clear_contact)(Contact*);
    void (*input_person)(Person*);
    void (*input_phones)(char[MAX_PHONES][MAX_SYMBOLS]);
    void (*input_emails)(char[MAX_EMAILS][MAX_SYMBOLS]);
    void (*input_account)(SocialAccount[MAX_ACCOUNTS]);
    void (*input_nullable_string)(char[MAX_SYMBOLS]);
    void (*input_string)(char[MAX_SYMBOLS]);
    int (*get_count_contacts)(Item*);
    int (*get_person_index)(Item*, Person);
    void (*print_list)(Item*);
    int (*print_phones)(char[MAX_PHONES][MAX_SYMBOLS]);
    int (*print_emails)(char[MAX_EMAILS][MAX_SYMBOLS]);
    int (*print_accounts)(SocialAccount[MAX_ACCOUNTS]);

    void* lib = dlopen("./libsource.so", RTLD_LAZY);
    char *error;
    if (error = dlerror()) {
        printf("dlopen: %s\n",error);
        exit(1);
    }

    add_contact = dlsym(lib, "add_contact");
    del_contact = dlsym(lib, "del_contact");
    edit_contact = dlsym(lib, "edit_contact");
    insert = dlsym(lib, "insert");
    find_pointer = dlsym(lib, "find_pointer");
    sort_contacts = dlsym(lib, "sort_contacts");
    clear_contact = dlsym(lib, "clear_contact");
    input_person = dlsym(lib, "input_person");
    input_phones = dlsym(lib, "input_phones");
    input_emails = dlsym(lib, "input_emails");
    input_account = dlsym(lib, "input_account");
    input_nullable_string = dlsym(lib, "input_nullable_string");
    input_string = dlsym(lib, "input_string");
    get_count_contacts = dlsym(lib, "get_count_contacts");
    get_person_index = dlsym(lib, "get_person_index");
    print_list = dlsym(lib, "print_list");
    print_phones = dlsym(lib, "print_phones");
    print_emails = dlsym(lib, "print_emails");
    print_accounts = dlsym(lib, "print_accounts");

    Item* head = NULL;
    while (1) {
        printf("----------------------------------------\n");
        printf("Выберите действие:\n1. Просмотреть список контактов\n2. Добавить новый контакт\n3. Удалить контакт\n4. Редактировать контакт\n0. Выход\n");
        printf("----------------------------------------\n");
        int c;
        scanf("%d", &c);
        switch (c) {
            case 0:
                return 0;
            case 1:
                print_list(head);
                break;
            case 2: {
                system("clear");
                head = add_contact(head);
                break;
            }
            case 3: {
                system("clear");
                printf("Введите номер контакта: ");
                int n;
                scanf("%d", &n);
                head = del_contact(head, n - 1); // list = 0 => segfault
                break;
            }
            case 4: {
                system("clear");
                printf("Введите номер контакта: ");
                int n;
                scanf("%d", &n);
                head = edit_contact(head, n - 1);
                break;
            }
            default: {
                system("clear");
                printf("Введено неверное значение!\n");
                break;
            }
        }
    }
    
    dlclose(lib);
    return 0;
}
