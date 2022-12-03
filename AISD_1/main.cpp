#include <cstdio>

int BinarySearch(int* tab, int b, int e, int k, int inc) {

    int srodek;

    srodek = (b + e) / 2;

    if (b > e) return -1;
    if (tab[srodek] == k) return srodek;

    if (tab[srodek] > k) {
        if (inc) {
            e = srodek - 1;
        }
        else if (!inc) {
            b = srodek + 1;
        }
    }
    else {
        if (inc) {
            b = srodek + 1;
        }
        else if (!inc) {
            e = srodek - 1;
        }
    }
    return BinarySearch(tab, b, e, k, inc);
}

int main() {

    int m, k, b, e, n, p, inc;

    scanf_s("%d", &m);

    while (m--) {

        scanf_s("%d", &n);

        int* tab = new int[n];

        for (int i = 0; i < n; i++) {
            scanf_s("%d", &tab[i]);
        }

        if (tab[0] < tab[n - 1]) {
            inc = 1;
        }
        else {
            inc = 0;
        }

        scanf_s("%d", &p);

        while (p--) {

            scanf_s("%d", &k);

            b = 0;
            e = n - 1;

            printf("%d\n", BinarySearch(tab, b, e, k, inc));

        }

        delete[] tab;
    }

    return 0;

}