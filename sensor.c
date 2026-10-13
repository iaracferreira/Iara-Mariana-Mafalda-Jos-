# include <ctype.h>
# include <stdlib.h>


        int eInteiro (char * buffer, int size) {
            for (int i=0; i<size; i++) {
                if (!isdigit(buffer[i]) && buffer[i]!='\n')
                    return 0;
                if (buffer[i]=='\n') 
                    break;
            return 1;
            }
        }

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


