#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int main() {

    int ocupadoI[MAX], ocupadoF[MAX], livreI[MAX], livreF[MAX], duracao[MAX], h, min, comecoDia=8*60, fimDia=0, i=0, j, k, aux, menor, posicaoMenor=0;
    char opcao='1';

    while(1) {
        system("cls");
        printf("CALCULADORA DE HORARIOS LIVRES\n\n");
        printf("[0] Sair\n");
        printf("[1] Definir inicio e fim do dia\n");
        printf("[2] Inserir um periodo de tempo ocupado\n");
        printf("[3] Calcular horarios livres\n\n");
        printf("Horarios em formato 24h (xx:xx)\n\n");

        while(1) {
            printf("Opcao: ");
            scanf(" %c", &opcao);
            if(opcao=='0'||opcao=='1'||opcao=='2'||opcao=='3')
                break;
            else
                printf("Opcao invalida! Por favor, insira novamente.\n");                
        }
        printf("\n");
        if(opcao=='0') {
            system("cls");
            break;
        }
        else if(opcao=='1') {
            while(1) {
                while(1) {
                    printf("Digite o horario do inicio do dia: ");
                    scanf("%d:%d", &h, &min);
                    if(h<0 || h>23 || min<0 || min>59)
                        printf("Horario invalido! Por favor, insira novamente.\n");
                    else
                        break;
                }
                comecoDia=min+h*60; //conversao para minutos
                while(1) {
                    printf("Digite o horario do fim do dia: ");
                    scanf("%d:%d", &h, &min);
                    if(h<0 || h>23 || min<0 || min>59)
                        printf("Horario invalido! Por favor, insira novamente.\n");
                    else
                        break;
                }
                fimDia=min+h*60; //conversao para minutos
                if(comecoDia==fimDia)
                    printf("Periodo invalido! Por favor, insira novamente.\n");
                else
                    break;
            }
        }
        else if(opcao=='2') {
            while(1) {
                while(1) {
                    printf("Digite o horario do inicio do periodo: ");
                    scanf("%d:%d", &h, &min);
                    if(h<0 || h>23 || min<0 || min>59)
                        printf("Horario invalido! Por favor, insira novamente.\n");
                    else
                        break;
                }
                ocupadoI[i]=h*60+min; //conversao para minutos
                while(1) {
                    printf("Digite o horario do fim do periodo: ");
                    scanf("%d:%d", &h, &min);
                    if(h<0 || h>23 || min<0 || min>59)
                        printf("Horario invalido! Por favor, insira novamente.\n");
                    else
                        break;
                }
                ocupadoF[i]=h*60+min; //conversao para minutos
                if(ocupadoI[i]==ocupadoF[i])
                    printf("Periodo invalido! Por favor, insira novamente.\n");
                else {
                    i++;
                    break;
                }
            }
        }
        else if(opcao=='3') {
            if(comecoDia>fimDia) {
                ocupadoI[i]=fimDia;
                ocupadoF[i]=comecoDia;
            }
            else {
                ocupadoI[i]=fimDia;
                ocupadoF[i]=0;
                i++;
                ocupadoI[i+1]=0;
                ocupadoF[i+1]=comecoDia;
            }

            //select sort entre as entradas
            for(j=0; j<=i-1; j++) {
                menor=100000;
                for(k=j; k<=i; k++) {
                    if(ocupadoI[k]<menor) {
                        menor=ocupadoI[k];
                        posicaoMenor=k;
                    }
                }            
                aux=ocupadoI[j];
                ocupadoI[j]=ocupadoI[posicaoMenor];
                ocupadoI[posicaoMenor]=aux;

                aux=ocupadoF[j];
                ocupadoF[j]=ocupadoF[posicaoMenor];
                ocupadoF[posicaoMenor]=aux;
            }
            
            //remover periodos de tempo redundantes
            for(j=1; j<=i; j++) {
                //se um periodo estiver contido em outro, vamos exclui-lo
                if(ocupadoI[j]>ocupadoI[j-1] && ocupadoF[j]<ocupadoF[j-1]) {
                    for(k=j; k<=i-1; k++) {
                        ocupadoI[k]=ocupadoI[k+1];
                        ocupadoF[k]=ocupadoF[k+1];
                    }
                    i--; //um periodo a menos
                    j--; //um periodo a menos
                }
                //se um periodo comecar antes ou quando outro acabar, vamos junta-los
                else if(ocupadoI[j]<=ocupadoF[j-1]) {
                    ocupadoF[j-1]=ocupadoF[j];
                    for(k=j; k<=i-1; k++) {
                        ocupadoI[k]=ocupadoI[k+1];
                        ocupadoF[k]=ocupadoF[k+1];
                    }
                    i--; //um periodo a menos
                    j--; //um periodo a menos
                }
            }

            for(j=0; j<=i+1; j++) {
                if(j==0) { //primeiro livre do dia (pode ser 0)
                    livreI[j]=0;
                    livreF[j]=ocupadoI[j];
                }
                else if(j==i+1) { //ultimo livre do dia (pode ser 0)
                    livreI[j]=ocupadoF[j-1];
                    livreF[j]=0;
                }
                else{ //periodo livre vai ser intervalo entre fim de um ocupado e comeco de outro
                    livreI[j]=ocupadoF[j-1];
                    livreF[j]=ocupadoI[j];
                }
            }
            printf("Periodos de tempo livre:\n");
            for(j=0; j<=i+1; j++) {
                if(livreF[j]==0 && livreI[j]!=0) //para a duraçao de algo que vai ate 00:00 dar certo           
                    duracao[j]=24*60-livreI[j];
                else
                    duracao[j]=livreF[j]-livreI[j];
                if(duracao[j]!=0) { //se a duracao for 0, nao sera mostrado
                    printf("> %02d:%02.0f - %02d:%02.0f\n", livreI[j]/60, (livreI[j]/60.0-livreI[j]/60)*60, livreF[j]/60, (livreF[j]/60.0-livreF[j]/60)*60);
                    printf("  Duracao: %02d:%02.0f\n", duracao[j]/60, (duracao[j]/60.0-duracao[j]/60)*60);
                }
            }

            i=0;
            system("pause");
        }
    }

    return 0;
}