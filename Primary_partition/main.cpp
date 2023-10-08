#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>

#define MAX_N_NUMBER 255
#define SMALLEST_PRIME 2

int* PrimeNumbers(int max) {

	int* isprime = new int[max + 1];

	isprime[0] = 0;
	isprime[1] = 0;

	for (int i = SMALLEST_PRIME; i < max + 1; i++) {
		isprime[i] = 1;
	}

	for (int i = SMALLEST_PRIME; i * i < max + 1; i++) {
		if (isprime[i]) {
			for (int j = i * i; j < max + 1; j += i) {
				isprime[j] = 0;
			}
		}
	}

	return isprime;

}

void Print(int* nofprimes, int k) {

	printf("%d", k);

	for (int j = k; j >= SMALLEST_PRIME; j--) {
		for (int i = 0; i < nofprimes[j]; i++) {
			printf("+%d", j);
		}
	}

	printf("\n");

}

void Partition(int n, int k, int* isprime) {

	int sum = n - k;

	if (sum > 0) {

		int* nofprimes = new int[k + 1];

		for (int i = 0; i < k + 1; i++) {
			nofprimes[i] = 0;
		}

		sum = k;
		int checkEnd = 0;
		while (!checkEnd) {
			if (sum == n) {
				Print(nofprimes, k);
			}
			nofprimes[SMALLEST_PRIME]++;
			sum += SMALLEST_PRIME;
			for (int i = 2; i < k + 1 && !checkEnd; i++) {
				if (isprime[i]) {
					if (sum > n) {
						sum -= nofprimes[i] * i;
						nofprimes[i] = 0;
						int nextIndex = i + 1;
						while (!isprime[nextIndex]) {
							nextIndex++;
						}
						if (nextIndex > k) {
							checkEnd = 1;
						}
						else {
							nofprimes[nextIndex]++;
							sum += nextIndex;
						}
					}
				}
			}
		}

		delete[] nofprimes;
	}
	else {
		printf("%d\n", k);
	}

}

int main() {

	int lines = 0, n = 0, k = 0;

	int* isprime = PrimeNumbers(MAX_N_NUMBER);

	scanf("%d", &lines);

	while (lines--) {

		scanf("%d %d", &n, &k);

		if (!isprime[k] || k > n || k < SMALLEST_PRIME 
		|| n < SMALLEST_PRIME || n > MAX_N_NUMBER) {
			continue;
		}

		Partition(n, k, isprime);
	}

	delete[] isprime;

	return 0;
}