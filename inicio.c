#include <stdio.h>
int main(void)
{
int sensor_value;
float temp_value;
int input_status;
do { 
    printf("Introduza o valor do sensor: ");
    input_status= scanf("%d", &sensor_value);
    if (input_status == 0)
    { 
        printf("Erro na leitura do valor do sensor. Por favor, introduza um valor inteiro.\n");
        while(getchar()!= '\n');
        sensor_value= -1;
    } 
   
    else if(sensor_value>0 && sensor_value<1023)
 { 
    printf("O valor do sensor é: %d\n", sensor_value);
 }
else 
    {
    printf("O valor do sensor está fora da gama.\n");
 }
}while(sensor_value<0 || sensor_value>1023);
temp_value=260.0*sensor_value/1023.0 -20.0;

if (temp_value>-10 && temp_value<100)
   { 
     printf("O valor da temperatura é: %.2fºC \n", temp_value);
   }
    else 
    {
     printf("O valor da temperatura está fora da gama.  \n");
    }
    
    
return 0;
}