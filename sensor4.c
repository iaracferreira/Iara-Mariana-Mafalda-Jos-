

# include <stdio.h>
# include <math.h>
# include <limits.h>

int main () { 
    // Declaração de variáveis
    float temp;
    int x;
    int j=0;
    int n_valores = 5;
    int valores[n_valores];
    double temperaturas[n_valores];
    double desvio1=0.0;
    int numtotallidos=0;
    double minimo = INT_MAX;
    double maximo = INT_MIN;
    double soma = 0.0;
    double somadesvios = 0.0;

    printf("Introduza o número de valores a ler:"); // Lê o número de valores a ler
    scanf("%d", &n_valores);

    do {
        printf("Introduza o valor do sensor: ");
    while (scanf("%d", &x) != 1) {
        printf("Por favor introduza um número inteiro: ");
        while (getchar() != '\n');
    }
    
    temp = (260.0 * x) / 1023.0 - 20.0;
    if (x == -1) {
        break;
    }

    valores[j] = x;                             // Guarda os valores lidos num array

    if (temp >= -10.0 && temp <= 190.0) {
        printf("%.2f\n", temp);
    } else {
        printf("Valor fora da gama\n");
    }
    temperaturas[j] = temp;                    // Guarda as temperaturas num array
    j++;                                       //Índice do array de temperaturas e dos valores lidos
    numtotallidos++; 
    } while (x != -1 && j< n_valores);
    
    printf("\n");

    printf("Valores lidos (sensor -> temperatura):\n");
    // Faz os prints dos valores e das temperaturas e calcula a soma das temperaturas para calcular a média
    for (int i = 0; i < numtotallidos; i++) { 
        printf("%d -> %.2f\n", valores[i], temperaturas[i]);
        soma+= temperaturas[i];
    }
    printf("\n");
    printf("Número de valores lidos: %d\n", numtotallidos);

    double media = soma / (numtotallidos);      // Calcula a média das temperaturas

    for (int i = 0; i < numtotallidos; i++) {
        if (temperaturas[i] < minimo) {         // Vê se a temperatura é menor que o mínimo e atualiza o mínimo
            minimo = temperaturas[i];
        }

        if (temperaturas[i] > maximo) {         // Vê se a temperatura é maior que o máximo e atualiza o máximo
            maximo = temperaturas[i];
        }
        desvio1+= (temperaturas[i] - media) * (temperaturas[i] - media); // Calcula o desvio padrão
    }

    // Faz os prints das estatísticas
    printf("Temperatura mínima: %.2f\n", minimo);
    printf("Temperatura máxima: %.2f\n", maximo);
    printf("Temperatura média: %.2f\n", media);
    printf("Desvio padrão: %.2f\n", sqrt(desvio1/(numtotallidos)));
    return 0;
}
