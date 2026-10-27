
# include <stdio.h>
# include <math.h>
# include <limits.h>

int valoresaler (int a);
int scan (int a);
double temperatura(int a);
double tempvalidação (double temp);
double saidasvalores (int valores[], double temperaturas[], int numtotallidos);
double Media (double a, int b);
double Minimo(double temperaturas[], int numtotallidos);
double Maximo(double temperaturas[], int numtotallidos);
double DesvioPadrao(double temperaturas[], double media, int numtotallidos);
double saidas (double minimo, double maximo, double media, double desvio, int numtotallidos);

int main () { 
    // Declaração de variáveis
    float temp;
    int x;
    int j=0;
    int n_valores = 5;
    int valores[n_valores];
    double temperaturas[n_valores];
    int numtotallidos=0;
    double soma = 0.0;

    n_valores = valoresaler(n_valores); // Lê o número de valores a ler

    do {

        x = scan(x); // Lê o valor do sensor e valida a entrada

    temp = temperatura(x);
    if (x == -1) {
        break;
    }
    valores[j] = x;                             // Guarda os valores lidos num array
    if (tempvalidação (temp) == temp) {
        printf("Temperatura: %.2f\n", temp);
    } else {
        printf("Valor fora da gama\n");
    }
    temperaturas[j] = tempvalidação(temp);      // Guarda as temperaturas num array
    j++;                                       //Índice do array de temperaturas e dos valores lidos
    numtotallidos++; 
    } while (x != -1 && j< n_valores);

    printf("\n");
    printf("Valores lidos (sensor -> temperatura):\n");
    soma = saidasvalores(valores, temperaturas, numtotallidos);
    printf("\n");
    printf("Número de valores lidos: %d\n", numtotallidos);
    double media = Media(soma, numtotallidos);
    double minimo = Minimo(temperaturas, numtotallidos); 
    double maximo = Maximo(temperaturas, numtotallidos); 
    double desvio = DesvioPadrao(temperaturas, media, numtotallidos);
    double fim = saidas(minimo, maximo, media, desvio, numtotallidos); // Faz os prints das estatísticas
    return 0;
}

// Funções

// Função para ler o número de valores a ler
int valoresaler (int n_valores) {
    printf("Introduza o número de valores a ler:"); // Lê o número de valores a ler
    int a;
    scanf("%d", &a);
    return a;
}

// Função para ler um valor inteiro do sensor, recebe um inteiro (valor a ler no sensor) e devolve o valor lido
int scan (int a) {
    printf("Introduza o valor do sensor: ");
    while (scanf("%d", &a) != 1) {
        printf("Por favor introduza um número inteiro: ");
        while (getchar() != '\n');
    }
    return a;
}

// Função para calcular a temperatura a partir do valor do sensor, 
//recebe um inteiro (o valor lido no sensor) e devolve a temperatura calculada
double temperatura(int a) {
    return (260.0 * a) / 1023.0 - 20.0;
}

// Função para validar a temperatura, recebe um double (a temperatura calculada) 
//e devolve a temperatura se estiver dentro da gama, caso contrário devolve -1.0
double tempvalidação (double temp){
    if (temp >= -10.0 && temp <= 190.0) {
        return temp;
    } else {
        return -1.0;
    }
}

// Função para imprimir os valores lidos e as temperaturas correspondentes,
//recebe um array de inteiros (valores lidos no sensor), 
//um array de doubles (temperaturas calculadas) e 
//um inteiro (número total de valores lidos)
double saidasvalores (int valores[], double temperaturas[], int numtotallidos) {
    double soma = 0;
    for (int i = 0; i < numtotallidos; i++) {
        printf("%d -> %.2f\n", valores[i], temperaturas[i]);
        soma+= temperaturas[i];
    }
    return soma;
}

// Função para calcular a média das temperaturas, recebe um double (soma das temperaturas)
//e um inteiro (número total de valores lidos) e devolve a média
double Media (double a, int b) {
    return a / b;
}

// Função para encontrar o valor mínimo das temperaturas, recebe um array de doubles (temperaturas calculadas)
//e um inteiro (número total de valores lidos) e devolve o valor mínimo
double Minimo(double temperaturas[], int numtotallidos) {
    double minimo = INT_MAX;
    for (int i = 0; i < numtotallidos; i++) {
        if (temperaturas[i] < minimo) {
            minimo = temperaturas[i];
        }
    }
    return minimo;
}

// Função para encontrar o valor máximo das temperaturas, recebe um array de doubles (temperaturas calculadas)
//e um inteiro (número total de valores lidos) e devolve o valor máximo
double Maximo(double temperaturas[], int numtotallidos) {
    double maximo = INT_MIN;
    for (int i = 0; i < numtotallidos; i++) {
        if (temperaturas[i] > maximo) {
            maximo = temperaturas[i];
        }
    }
    return maximo;
}

// Função para calcular o desvio padrão das temperaturas, recebe um array de doubles (temperaturas calculadas),
//um double (média das temperaturas) e um inteiro (número total de valores lidos) e devolve o desvio padrão
double DesvioPadrao(double temperaturas[], double media, int numtotallidos){
    double desvio = 0.0;
    for (int i = 0; i < numtotallidos; i++) {
        desvio+= (temperaturas[i] - media) * (temperaturas[i] - media); // Calcula o desvio padrão
    }
    return desvio;
}

// Função para imprimir as estatísticas das temperaturas, recebe quatro double's (valor mínimo, valor máximo, média, desvio padrão) 
//e um inteiro (número total de valores lidos) e devolve um double (valor final),
double saidas (double minimo, double maximo, double media, double desvio, int numtotallidos) {
    double fim = 2.0;
    printf("Temperatura mínima: %.2f\n", minimo);
    printf("Temperatura máxima: %.2f\n", maximo);
    printf("Temperatura média: %.2f\n", media);
    printf("Desvio padrão: %.2f\n", sqrt(desvio/(numtotallidos)));
    return fim;
}
