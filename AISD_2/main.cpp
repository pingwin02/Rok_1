#include <cstdio>

struct Element {
    int key = 0;
    struct Element* next = nullptr;
};

Element* add_element(Element* list, Element* prelast, int value) {

    Element* x = new Element;

    x->key = value;
    x->next = nullptr;

    if (prelast != nullptr && prelast->next != nullptr) {
        prelast->next->next = x;
        prelast = prelast->next;
    }
    else {
        list->next = x;
        prelast = list;
    }

    return prelast;
}

int find_element(Element* list, int key) {

    Element* cur = list->next;
    int index = 0;

    if (key == cur->key) {
        return 0;
    }

    while (key != cur->key) {
        if (cur->next == nullptr) {
            return -1;
        }
        cur = cur->next;
        index++;
    }
    return index;
}

Element remove_element(Element* list) {

    if (list->next != nullptr) {
        Element* cur = list->next;

        list->next = list->next->next;

        delete cur;
    }

    return *list;

}

void remove_all(Element* list) {

    while (list->next != nullptr) {
        Element* cur = list->next;
        list->next = list->next->next;
        delete cur;
    }
}

int main() {

    Element list;
    char command1;
    int command2;
    Element* prelast = nullptr;

    while (1) {
        scanf_s("%c", &command1, 1);
        if (command1 == 'q') {
            remove_all(&list);
            return 0;
        }
        else if (command1 == 'i') {
            scanf_s("%d", &command2);
            prelast = add_element(&list, prelast, command2);
        }
        else if (command1 == 'd') {
            list = remove_element(&list);
        }
        else if (command1 == 's') {
            scanf_s("%d", &command2);
            printf("%d\n", find_element(&list, command2));
        }

    }

    return 0;
}