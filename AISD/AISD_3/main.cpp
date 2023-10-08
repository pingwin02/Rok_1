#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

struct BigNumber {
    int n = 0;
    BigNumber* next = nullptr;
};

BigNumber* add_element(BigNumber* list, BigNumber* prelast, char value) {

    BigNumber* x = new BigNumber;

    int valueafter = value - '0';

    x->n = valueafter;
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

void remove_all(BigNumber* list) {

    while (list->next != nullptr) {
        BigNumber* cur = list->next;
        list->next = list->next->next;
        delete cur;
    }
}

int compare(BigNumber* left, BigNumber* right, int size_left, int size_right) {

    BigNumber* lefttemp = left->next;
    BigNumber* righttemp = right->next;

    if (size_left > size_right) {
        return 1;
    }
    if (size_left == size_right) {
        for (int i = 0; i < size_left; i++) {
            if (lefttemp->n > righttemp->n)
            {
                return 1;
            }
            if (lefttemp->n < righttemp->n) {
                return -1;
            }
            else if (lefttemp->n == righttemp->n) {
                lefttemp = lefttemp->next;
                righttemp = righttemp->next;
            }
        }
        return 2;
    }
    return -1;
}


int partition(BigNumber** tab, int l, int r, int* size) {

    BigNumber* pivot = new BigNumber;
    BigNumber* cur1 = tab[l]->next;
    BigNumber* cur2 = pivot;
    int pivot_size = size[l];
    for (int i = 0; i < pivot_size; i++) {
        BigNumber* new_number = new BigNumber;
        cur2->next = new_number;
        new_number->n = cur1->n;
        cur1 = cur1->next;
        cur2 = cur2->next;
    }
    int ltmp = l;
    int rtmp = r;
    BigNumber* temp;
    int temp_size;

    while (1) {
        while (compare(tab[rtmp], pivot, size[rtmp], pivot_size) == 1) {
            rtmp--;
        }
        while (compare(tab[ltmp], pivot, size[ltmp], pivot_size) == -1) {
            ltmp++;
        }
        if (ltmp < rtmp) {

            temp = tab[ltmp];
            tab[ltmp] = tab[rtmp];
            tab[rtmp] = temp;

            temp_size = size[ltmp];
            size[ltmp] = size[rtmp];
            size[rtmp] = temp_size;

            ltmp++;
            rtmp--;
        }
        else {
            remove_all(pivot);
            delete pivot;
            return rtmp;
        }
    }
    remove_all(pivot);
    delete pivot;

}

void quickSort(BigNumber** tab, int l, int r, int* size) {
    if (l < r) {
        int q = partition(tab, l, r, size);
        quickSort(tab, l, q, size);
        quickSort(tab, q + 1, r, size);
    }
}


int main() {

    int n;

    char a = 0;

    scanf("%d ", &n);

    BigNumber** number_list = new BigNumber* [n];
    BigNumber* prelast = nullptr;

    int* size = new int[n];

    for (int i = 0; i < n; i++) {
        size[i] = 0;
    }

    for (int i = 0; i < n; i++) {
        BigNumber* number = new BigNumber;
        number_list[i] = number;
        while (1) {
            scanf("%c", &a);
            if (a == '\n' || feof(stdin) != 0) {
                break;
            }
            prelast = add_element(number_list[i], prelast, a);
            size[i]++;
        }
        prelast = nullptr;
    }

    
    
    quickSort(number_list, 0, n - 1, size);
    
    
    printf("\n");
    for (int i = 0; i < n; i++) {
        BigNumber* cur = number_list[i]->next;
        for (int j = 0; j < size[i]; j++) {
            printf("%d", cur->n);
            cur = cur->next;
        }
        printf("\n");
    }

    for (int i = 0; i < n; i++) {
        remove_all(number_list[i]);
        delete number_list[i];
    }
    delete[] number_list;
    delete[] size;

	return 0;

}