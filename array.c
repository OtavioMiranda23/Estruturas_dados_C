int search(int x, int v[], int n);
int main() {
    
    return 0;
}

int search(int x, int v[], int n) {
    int k;
    k = n -1;
    while(k >= 0 && v[k] != x) {
        k--;
    }
    return k;
}

int searchSentinela(int x, int v[], int n) {
    int k;
    k = 0;
    v[n] = x;
    while(v[k] != x) {
        k++;
    }
    return k;
}

int remove(int k, int v[], int n) {
    int j = k;
    while (j = k, j < n -1, j++) {
        v[j] = v[j+1];
    }
    return n - 1;
}

int insert(int k, int y, int v[], int n) {
    int j;
    for (j = n; j > k; j--) {
        v[j] = v[j-1];
    }
    v[k] = y;
    return n+1;
}

int removeZeros(int v[], int n) {
    int i = 0, j;
    for (j = 0; j < n; j++) {
        if (v[j] != 0) {
            v[i] = v[j];
            i++;
        }
    }
    return i;
}