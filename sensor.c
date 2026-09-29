# include <stdio.h>
int main() {
    int x;
    double temp;
    scanf("%d", &x);
    temp = 260.0 * x/1023.0-20.0;
    printf("%.2f\n", temp);
    return 0;
}