
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SENSORES 3
#define MAX_LEITURAS 100
#define TAM_NOME 20

typedef struct {
    char nome[TAM_NOME];
    int ganho;
    int desvio;
} SensorCalib;

typedef struct {
    char sensor[TAM_NOME];
    int instante;
    int valor;
    double temperatura;
} Leitura;

//Definição dos dados de calibração num único ponto do código

SensorCalib sensores[MAX_SENSORES] = {
    {"TEMP1", 260, -20},
    {"TEMP2", 250, -15},
    {"TEMP3", 240, -10}
};
//Função para procurar o indice do sensor pelo nome
int buscar_sensor(const char *nome) {
    for (int i = 0; i < MAX_SENSORES; i++) {
        if (strcmp(sensores[i].nome, nome) == 0) {
            return i;
        }
    }
    return -1; 
}

int main() {
    char linha [256];
    Leitura leituras[MAX_LEITURAS];
    int total_leituras = 0;

  //leitura linha a linha até encontrar "FIM" ou atingir o limite 
 while (fgets(linha, sizeof(linha), stdin) != NULL) {
    //remover quebra de linha (\n ou\r\n)
     linha[strcspn(linha, "\r\n")] = 0;

    //condição de paragem 
    if (strcmp(linha, "FIM") == 0) {
        break;
    }
    //ignorar linhas vazias
    if (strlen(linha) == 0) {
        continue;
    }

    char nome_sensor[TAM_NOME];
    int instante;
    int valor;

    //validar e extrair os 3 campos esperados
int campos_lidos = sscanf(linha, "%s %d %d", nome_sensor, &instante, &valor);
    if (campos_lidos != 3) {
        printf("Linha inválida\n");
        continue;
    }

     //verificar se o sensor existe (se é conhecido)
int idx = buscar_sensor(nome_sensor);
    if (idx == -1) {
        printf("Sensor desconhecido\n");
        continue;
    }

    //verificar se o valor bruto está na gama permitida (0 a 1023)
    if (valor < 0 || valor > 1023) {
        printf("Valor fora da gama\n");
        continue;
    }
     //calcular a temperatura usando a fórmula fornecida
    double temperatura = (valor * sensores[idx].ganho) / 1023.0 + sensores[idx].desvio;

    //verificar se a temperatura calculada está na gama válida (-10ºC a 190ºC)
    if (temperatura < -10 || temperatura > 190) {
        printf("Temperatura fora da gama válida\n");
        continue;
    }

    //Apresentar a temperatura calculada imediatamente
    printf("%.2f\n", temperatura);
    //registar a leitura válida
    if (total_leituras < MAX_LEITURAS) {
        strcpy(leituras[total_leituras].sensor, nome_sensor);
        leituras[total_leituras].instante = instante;
        leituras[total_leituras].valor = valor;
        leituras[total_leituras].temperatura = temperatura;
        total_leituras++;
    } else {
        printf("Limite de leituras atingido\n");
        break;
    }
     //Apresentar listagem de leituras registadas 
     printf("\nLeituras registadas (sensor instante: valor -> temperatura):\n");
     for (int i = 0; i < total_leituras; i++) {
        printf("%s %d: %d -> %.2f\n", leituras[i].sensor, leituras[i].instante, leituras[i].valor, leituras[i].temperatura);
    }
    printf("\n");
}
//Estatisticas detalhadas por sensor

for (int i = 0; i < MAX_SENSORES; i++) {
    int count = 0;
    double min_temperatura = 9999.0;
    double max_temperatura = -9999.0;
    double soma = 0.0;
    double temperaturas_sensor[MAX_LEITURAS];

    //Recolher dados estatísticos p o sensor atual
    for (int j = 0; j < total_leituras; j++) {
        if (strcmp(leituras[j].sensor, sensores[i].nome) == 0) {
            double t = leituras[j].temperatura;
            temperaturas_sensor[count] = t;
            soma += t;
            if (t < min_temperatura) {
                min_temperatura = t;
            }
            if (t> max_temperatura) {
                max_temperatura = t;
            count++;
            }
        }
    }
    //se houver leituras para o sensor, calcular média e desvio-padrão
    if (count > 0) {
        double media = soma / count;
        double soma_diferencas_quadrado = 0.0;

        for (int k = 0; k < count; k++) {
            soma_diferencas_quadrado += pow(temperaturas_sensor[k] - media, 2);
        }
        double desvio_padrao = sqrt(soma_diferencas_quadrado / count);

        printf("Sensor %s:\n", sensores[i].nome);
        printf("Número de Valores lidos: %d\n", count);
        printf("Temperatura mímima: %.2f\n", min_temperatura);
        printf("Temperatura máxima: %.2f\n", max_temperatura);
        printf("Temperatura Média: %.2f\n", media);
        printf("Desvio Padrão: %.2f\n\n", desvio_padrao);
           }     
     } 
     return 0;
}


