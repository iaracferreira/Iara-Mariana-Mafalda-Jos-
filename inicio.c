#include <stdio.h>
int main(void)
{
int sensor_value;
float temp_value;
    printf("Número fornecido pelo sensor: %d", sensor_value);
    scanf("%d", &sensor_value);
    temp_value=260*sensor_value/1024 -20;
    printf("Temperatura: %.2f", temp_value);
return 0;
}