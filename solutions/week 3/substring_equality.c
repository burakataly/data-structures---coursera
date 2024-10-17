#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX 500001

/*
here we define two polynomial hash functions by having two different p and x values. and we try to use that for two different substrings
that is not equal to eachother the possibilty of two different polynomial hash function values being equal is really really low.
one polynomial hash function's results can be same while substrings not equal to eachother even though this possibiliy is again low. having both resuts
equal is much lower than that.

we uses this approach to calculate the hash for substring S[a...a + l - 1] -> hash(S[a...a + l - 1]) = ( hash(S[0...a + l - 1]) - x^l * hash(S[0...a]) ) % p
so we dont need to call polynomialHash function like we used to do in rabin karps algorithm. this is a special case...
*/

void calculateHashes(char* T, int n, long long p, long long x, long long* hashes, long long* y){
	int i, j;
	
	y[0] = 1;
	hashes[0] = 0;
	
	for(i=1;i<=n;i++){
		y[i] = (y[i - 1] * x) % p; //calculating x^l values to use them later
		hashes[i] = ((hashes[i - 1] * x) % p + T[i - 1]) % p; //calculating hash value for substring S[0...i - 1]
	}
	
	//for(i=0;i<=n;i++) printf("%d ", hashes[i]);
	//printf("\n");
}

void processQueries(long long* hashes1, long long* hashes2, long long* y1, long long* y2, int n, long long p1, long long p2, char* T){
	int i, q, a, b, l;
	long long firstHash1, firstHash2, secondHash1, secondHash2;
	
	scanf("%d", &q);
	
	for(i=0;i<q;i++){
		scanf("%d %d %d", &a, &b, &l);
		
		firstHash1 = (hashes1[a + l] - (y1[l] * hashes1[a]) % p1 + p1) % p1;
		secondHash1 = (hashes1[b + l] - (y1[l] * hashes1[b]) % p1 + p1) % p1;
		firstHash2 = (hashes2[a + l] - (y2[l] * hashes2[a]) % p2 + p2) % p2;
		secondHash2 = (hashes2[b + l] - (y2[l] * hashes2[b]) % p2 + p2) % p2;
		
		//printf("\n%d - %d * %d = %d\n", hashes[a + l], y[l], (hashes[a]), firstHash);
		//printf("\n%d - %d * %d = %d\n", hashes[b + l], y[l], (hashes[b]), secondHash);
		if(firstHash1 == secondHash1 && firstHash2 == secondHash2){
			printf("Yes\n");
		}
		else{
			printf("No\n");
		}
	}
}

int main(){
	long long p1 = 1000000007, x1 = 31, p2 = 1000000009, x2 = 37;
	char* T = (char*) malloc(MAX * sizeof(char));
	int n;
	long long *hashes1, *hashes2, *y1, *y2;
	
	scanf("%s", T);

	n = strlen(T);
	hashes1 = (long long*) malloc((n + 1) * sizeof(long long));
	hashes2 = (long long*) malloc((n + 1) * sizeof(long long));
	y1 = (long long*) malloc((n + 1) * sizeof(long long));
	y2 = (long long*) malloc((n + 1) * sizeof(long long));

	calculateHashes(T, n, p1, x1, hashes1, y1); //calculating hash values using hash function 1 for substrings S[0...i] for i from 0 to n - 1
	calculateHashes(T, n, p2, x2, hashes2, y2); //calculating hash values using hash function 2 for substrings S[0...i] for i from 0 to n - 1

	processQueries(hashes1, hashes2, y1, y2, n, p1, p2, T);
	
	free(T);	
	free(hashes1);
	free(y1);
	free(hashes2);
	free(y2);
	
	return 0;
}
