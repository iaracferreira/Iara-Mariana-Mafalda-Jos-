#include <stdio.h>
#include <string.h>
#include <math.h>

#define MAX_LEITURAS 100
#define NUM_SENSORES 3

// Estrutura de um sensor
typedef struct {
    char   id[10];
    double ganho;
    double desvio;
} Sensor;

Sensor sensores[3];

// Estrutura de uma leitura 
typedef struct {
    int    sensor;      // posição do sensor no array de sensores
    int    instante;    // instante da leitura
    int    valor;       // valor lido no sensor
    double temp;        // temperatura calculada a partir do valor lido
} Leitura;

int procurarSensor(const char id[]);
double calcularTemperatura(const Sensor *sensor, int valor);
int contar(const Leitura leituras[], int total, int s);
double minimo(const Leitura leituras[], int total, int s);
double maximo(const Leitura leituras[], int total, int s);
double media(const Leitura leituras[], int total, int s);
double desvioPadrao(const Leitura leituras[], int total, int s);

int main(void) {
    Leitura leituras[MAX_LEITURAS];
    int total = 0;

    char id[10];        // identificador do sensor (1, 2 ou 3)
    char linha[256];    // buffer para ler a linha completa
    int instante;
    int valor;

    // Sensor 1 com os respetivos dados de calibração
    strcpy(sensores[0].id, "TEMP1");
    sensores[0].ganho  = 260;
    sensores[0].desvio = -20;
    // Sensor 2 com os respetivos dados de calibração
    strcpy(sensores[1].id, "TEMP2");
    sensores[1].ganho  = 250;
    sensores[1].desvio = -15;
    // Sensor 3 com os respetivos dados de calibração
    strcpy(sensores[2].id, "TEMP3");
    sensores[2].ganho  = 240;
    sensores[2].desvio = -10;

    while (total < MAX_LEITURAS) {

        if (fgets(linha, sizeof(linha), stdin) == NULL) { //Lê uma linha do input
            break;
        }
         int n = sscanf(linha, "%9s %d %d", id, &instante, &valor); //Lê os valores da linha e armazena nas variáveis id, instante e valor

         if (n<1){ 
            continue; //Ignorar linhas vazias
         }

         if (strcmp(id, "FIM") == 0) {
            break; //Condição de paragem
         }

        int s = procurarSensor(id); //Procura o sensor pelo id e retorna a posição no array de sensores

        if (s == -1) {
            printf("Sensor desconhecido\n"); //Se o sensor não for encontrado, imprime mensagem de erro
        } else if (n != 3) { //Se não forem lidos os 3 campos esperados, imprime mensagem de erro
            printf("Linha inválida\n");
        } else { //Se o sensor for encontrado e os 3 campos forem lidos corretamente, calcula a temperatura
            double temp = calcularTemperatura(&sensores[s], valor);

            if (valor < 0 || valor > 1023 || temp < -10 || temp > 190) { //Se o valor lido ou a temperatura calculada estiver fora da gama válida, imprime mensagem de erro
                printf("Valor fora da gama\n");
            } else {
                printf("%.2f\n", temp); //Imprime a temperatura calculada
                leituras[total].sensor   = s; //Armazena a posição do sensor no array de sensores
                leituras[total].instante = instante; //Armazena o instante da leitura
                leituras[total].valor    = valor; //Armazena o valor lido no sensor
                leituras[total].temp     = temp;  //Armazena a temperatura calculada
                total++;
            }
        }

    }
        if (total > 0){
            /* Lista de todas as leituras */
            printf("\nLeituras registadas (sensor instante valor -> temperatura):\n");
            for (int i = 0; i < total; i++) {
                printf("%s %d : %d -> %.2f\n",
                sensores[leituras[i].sensor].id,         //Imprime o id do sensor
                leituras[i].instante,                    //Imprime o instante da leitura
                leituras[i].valor,                       //Imprime o valor lido no sensor
                leituras[i].temp);                       //Imprime a temperatura calculada
            }

            /* Estatísticas de cada sensor que tenha leituras */
            for (int s = 0; s < NUM_SENSORES; s++) {
                int n = contar(leituras, total, s);
                if (n > 0) {
                    printf("\n");
                    printf("Sensor %s:\n", sensores[s].id);                                 //Imprime o id do sensor
                    printf("Número de valores lidos: %d\n", n);                             //Imprime o número de leituras do sensor
                    printf("Temperatura mínima: %.2f\n", minimo(leituras, total, s));       //Imprime a temperatura mínima
                    printf("Temperatura máxima: %.2f\n", maximo(leituras, total, s));       //Imprime a temperatura máxima
                    printf("Temperatura média: %.2f\n", media(leituras, total, s));         //Imprime a temperatura média
                    printf("Desvio-padrão: %.2f\n", desvioPadrao(leituras, total, s));      //Imprime o desvio-padrão das temperaturas
                    printf("\n");
                }
            }
    
        }
    return 0;}


/* Devolve a posição do sensor no array de sensores, ou -1 se não existir */
int procurarSensor(const char id[]) {
    for (int i = 0; i < NUM_SENSORES; i++) { //Percorre o array de sensores para procurar o sensor com o id fornecido
        if (strcmp(id, sensores[i].id) == 0) { //Compara o id fornecido com o id do sensor no array
            return i;
        }
    }
    return -1;
}

/* temp = ganho*x/1023 + desvio, com a calibração do sensor */
double calcularTemperatura(const Sensor *sensor, int valor) {
    return sensor->ganho * valor / 1023.0 + sensor->desvio;
}

/* Número de leituras do sensor s */
int contar(const Leitura leituras[], int total, int s) {
    int n = 0;
    for (int i = 0; i < total; i++) {
        if (leituras[i].sensor == s) { //Se a posição do sensor na leitura for igual à posição do sensor fornecida, incrementa o contador
            n++;
        }
    }
    return n;
}

/* Temperatura mínima do sensor s */
double minimo(const Leitura leituras[], int total, int s) {
    double min = 1000.0;
    for (int i = 0; i < total; i++) {
        if (leituras[i].sensor == s && leituras[i].temp < min) {
            min = leituras[i].temp;
        }
    }
    return min;
}

/* Temperatura máxima do sensor s */
double maximo(const Leitura leituras[], int total, int s) {
    double max = -1000.0;
    for (int i = 0; i < total; i++) {
        if (leituras[i].sensor == s && leituras[i].temp > max) {
            max = leituras[i].temp;
        }
    }
    return max;
}

/* Média das temperaturas do sensor s */
double media(const Leitura leituras[], int total, int s) {
    double soma = 0.0;
    for (int i = 0; i < total; i++) {
        if (leituras[i].sensor == s) {
            soma += leituras[i].temp;
        }
    }
    return soma / contar(leituras, total, s);
}

/* Desvio-padrão das temperaturas do sensor s */
double desvioPadrao(const Leitura leituras[], int total, int s) {
    double m = media(leituras, total, s);
    double soma = 0.0;
    for (int i = 0; i < total; i++) {
        if (leituras[i].sensor == s) {
            soma += (leituras[i].temp - m) * (leituras[i].temp - m);
        }
    }
    return sqrt(soma / contar(leituras, total, s));
}