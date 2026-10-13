# include <ctype.h>
# include <stdio.h>
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


int main() {
    int x;
    int i=0;
    double temp;
    char buffer[100];
    while (i==0) {
        fgets(buffer, 100, stdin);
        if (eInteiro(buffer, 100)) {
            x = atoi(buffer);
            if (x>=0 && x<=1023) {
                i=1;
                temp = 260.0 * x/1023.0-20.0;
                 if (-10.0<= temp && temp <=190.0){
                     printf("%.2f\n", temp);
                    return 0;
                     }   else {
                        printf("Valor fora da gama\n");
                        return 0;
                        }
            } else {
                continue;
            }
            
    }

}
}


/*
# include <stdlib.h>
long strtol (char * string, char ** endptr, int base);  //Converte string para long.

# include <stdio.h>
int isdigit (char ch);                                  //Verifica se char é dígito ou não.

# include <stdio.h>
void fgets (char * buffer, int bufferSize, File *)     //Se FILE=stdin, vai ler um string com o máx
                                                        //bufferSize caracteres para o string buffer.

# include <stdio.h>
int atoi (char * string);                               //Converte de string para inteiro.
*/
