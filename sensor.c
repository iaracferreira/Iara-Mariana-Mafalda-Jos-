# include <stdio.h>
int main () {
    float temp;
    int x;
    printf("Introduza o valor do sensor: ");
    while (scanf("%d", &x) != 1) {
        printf("Por favor introduza um número inteiro: ");
        while (getchar() != '\n');
    }
    temp = (260.0 * x) / 1023.0 - 20.0;
    if (temp >= -10.0 && temp <= 190.0) {
        printf("%.2f\n", temp);
    } else {
        printf("Valor fora da gama\n");
    }
    return 0;
}