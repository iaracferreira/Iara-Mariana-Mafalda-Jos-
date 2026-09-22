#include <stdio.h>

int main(void)
{
    int valor;
    float fim1;
    float fim2;

    printf("Entrada:");
    scanf("%d", &valor);

    fim1 = valor*260.0/1023.0;
    fim2 = fim1 - 20.0;
    printf("Saída: %.2f\n", fim2);


	return 0;
}
