#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef int Iterador;
typedef int Horario;

typedef struct Periodo {
    Horario comeco;
    Horario fim;
} Periodo;

enum DiaSemana {dom, seg, ter, qua, qui, sex, sab};
typedef enum DiaSemana DiaSemana;

int main() {

    FILE * fp;

    //variaveis do menu de dia unico
    Horario comecoDia, fimDia;
    Periodo ocupado1[MAX], disp1[MAX];
    int cont1, duracao[MAX];    

    //variaveis comuns
    Horario menor;
    Iterador i, j, k, l;
    int h, min, aux, posicaoMenor, numRepetidos;    

    //variaveis do menu de semana
    Horario comecoDiaVet[7], fimDiaVet[7];
    Periodo ocupado2[7][MAX], disp2[7][MAX];
    DiaSemana diaInserir, dias[7];
    int qtdDias, cont2[7];
    char opcao, diaString[20], diaAnterior[20];

    while(1) {
        //inicializando variaveis
        for(i=0; i<MAX; i++)
            ocupado1[i].comeco = ocupado1[i].fim = disp1[i].comeco = disp1[i].fim = duracao[i]=0;
        for(i=0; i<7; i++) {
            cont2[i] = comecoDiaVet[i] = fimDiaVet[i] = 0;
            for(j=0; j<MAX; j++)
                ocupado2[i][j].comeco = ocupado2[i][j].fim = disp2[i][j].comeco = disp2[i][j].fim = 0;
        }        
        cont1 = fimDia = comecoDia = 0;
              
        //menu geral
        system("cls");
        printf(">>>>>  T I M E C K O O N  <<<<<\n\n");
        printf("Uma calculadora de tempos disponiveis entre os membros de um grupo!\n\n");
        printf("[0] Sair do programa\n");
        printf("[1] Calcular horarios disponiveis em um dia qualquer\n");
        printf("[2] Calcular horarios disponiveis em uma semana\n");

        //validador de opcao
        while(1) {
            printf("\nOpcao: ");
            scanf(" %c", &opcao);
            if(opcao=='0'||opcao=='1'||opcao=='2')
                break;                
            else
                printf("Opcao invalida! Por favor, insira novamente.\n");
        }
     
        //sair do programa
        if(opcao=='0')
            break;


        //menu de dia unico
        else if(opcao=='1') {        
            while(1) {
                system("cls");
                printf(">>>>>  T I M E C K O O N  <<<<<\n\n");
                printf("Uma calculadora de tempos disponiveis entre os membros de um grupo!\n\n");
                printf("[0] Sair do menu\n");
                printf("[1] Definir inicio e fim do dia\n");
                printf("[2] Inserir um periodo de tempo ocupado\n");
                printf("[3] Mostrar horarios disponiveis\n");
                printf("[4] Criar arquivo com horarios disponiveis\n\n");
                printf("< Horarios vao de 00:00 a 24:00 >\n");

                //validador de opcao
                while(1) {
                    printf("\nOpcao: ");
                    scanf(" %c", &opcao);
                    if(opcao=='0'||opcao=='1'||opcao=='2'||opcao=='3'||opcao=='4')
                        break;                
                    else
                        printf("Opcao invalida! Por favor, insira novamente.\n");
                }

                //sair do menu
                if(opcao=='0')
                    break;

                //definir inicio e fim do dia
                else if(opcao=='1') {  
                    //validador de entrada do inicio
                    while(1) {
                        printf("\nDigite o horario do inicio do dia: ");
                        scanf("%d:%d", &h, &min);
                        if(h*60+min>=0 && h*60+min<=24*60)
                            break;
                        else
                            printf("Horario invalido! Por favor, insira novamente.\n");
                    }                        
                    comecoDia = h*60 + min;

                    //validador de entrada do fim
                    while(1) {
                        printf("\nDigite o horario do fim do dia: ");
                        scanf("%d:%d", &h, &min);
                        if(h*60+min>=0 && h*60+min<=24*60)
                            break;
                        else
                            printf("Horario invalido! Por favor, insira novamente.\n");
                    }
                    fimDia = h*60 + min;
                }                
                
                //inserir um periodo de tempo ocupado
                else if(opcao=='2') {
                    while(1) {
                        //validador do inicio do periodo
                        while(1) {
                            printf("\nDigite o horario do inicio do periodo: ");
                            scanf("%d:%d", &h, &min);
                            if(h*60+min>=0 && h*60+min<=24*60)
                                break;
                            else
                                printf("Horario invalido! Por favor, insira novamente.\n");
                        }
                        ocupado1[cont1].comeco = h*60 + min;

                        //validador do fim do periodo
                        while(1) {
                            printf("\nDigite o horario do fim do periodo: ");
                            scanf("%d:%d", &h, &min);
                            if(h*60+min>=0 && h*60+min<=24*60)
                                break;
                            else
                                printf("Horario invalido! Por favor, insira novamente.\n");
                        }
                        ocupado1[cont1].fim = h*60 + min; //conversao para minutos

                        //validador do periodo
                        if(ocupado1[cont1].comeco >= ocupado1[cont1].fim)
                            printf("Periodo invalido! Por favor, insira novamente.\n");
                        else {
                            cont1++;
                            break;
                        }
                    }
                }
                
                //calcular horarios disponiveis
                else if(opcao=='3') {
                    /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
                       Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
                       seu tempo de sono pode ser considerado um bloco de tempo ocupado.
                       Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
                       blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */

                    if(comecoDia>fimDia) {
                        ocupado1[cont1].comeco = fimDia;
                        ocupado1[cont1].fim = comecoDia;
                    }
                    else if(comecoDia<fimDia) {
                        ocupado1[cont1].comeco = fimDia;
                        ocupado1[cont1].fim = 24*60;
                        cont1++;
                        ocupado1[cont1].comeco = 0;
                        ocupado1[cont1].fim = comecoDia;
                    }

                    //select sort entre as entradas
                    for(i=0; i <= cont1-1; i++) {
                        menor = 100000;
                        for(j=i; j <= cont1; j++) {
                            if(ocupado1[j].comeco < menor) {
                                menor = ocupado1[j].comeco;
                                posicaoMenor = j;
                            }
                        }            
                        aux = ocupado1[i].comeco;
                        ocupado1[i].comeco = ocupado1[posicaoMenor].comeco;
                        ocupado1[posicaoMenor].comeco = aux;

                        aux = ocupado1[i].fim;
                        ocupado1[i].fim = ocupado1[posicaoMenor].fim;
                        ocupado1[posicaoMenor].fim = aux;
                    }

                    // select sort se o ocupado1.comeco for igual mas ocupado.fim diferente
                    for(i=0; i <= cont1; i += numRepetidos+1) {
                        numRepetidos=0;
                        for(j = i+1; j <= cont1; j++)
                            if(ocupado1[j].comeco == ocupado1[i].comeco)
                                numRepetidos++;

                        for(j=i; j <= i+numRepetidos-1; j++) {
                            menor = 100000;
                            for(k=i; k <= i+numRepetidos; k++) {
                                if(ocupado1[k].fim < menor) {
                                    menor = ocupado1[k].fim;
                                    posicaoMenor = k;
                                }
                            }            
                            aux = ocupado1[j].fim;
                            ocupado1[j].fim = ocupado1[posicaoMenor].fim;
                            ocupado1[posicaoMenor].fim = aux;
                        }
                    }
                    
                    //remover periodos de tempo redundantes
                    for(i=1; i <= cont1; i++) {
                        //se um periodo estiver contido em outro, vamos exclui-lo
                        if(ocupado1[i].comeco > ocupado1[i-1].comeco && ocupado1[i].fim < ocupado1[i-1].fim) {
                            for(j=i; j <= cont1-1; j++) {
                                ocupado1[j].comeco = ocupado1[j+1].comeco;
                                ocupado1[j].fim = ocupado1[j+1].fim;
                            }
                            cont1--; //um periodo a menos no vetor
                            i--;
                        }

                        //se um periodo comecar antes ou quando outro acabar, vamos junta-los
                        else if(ocupado1[i].comeco <= ocupado1[i-1].fim) {
                            ocupado1[i-1].fim = ocupado1[i].fim;
                            for(j=i; j <= cont1-1; j++) {
                                ocupado1[j].comeco = ocupado1[j+1].comeco;
                                ocupado1[j].fim = ocupado1[j+1].fim;
                            }
                            cont1--; //um periodo a menos no vetor
                            i--;
                        }
                    }


                    //calculo dos tempos disponiveis
                    for(i=0; i <= cont1+1; i++) {
                        /* No geral, os periodos disponiveis sao o intervalo entre o final de
                           um periodo ocupado e comeco do seguinte.
                           Para que o algoritmo seja generico, o primeiro periodo sera sempre
                           o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
                           tiver duracao 0, ele sera ignorado)
                           A mesma logica se aplica ao ultimo periodo disp. */

                        if(i==0) {
                            disp1[i].comeco = 0;
                            disp1[i].fim = ocupado1[i].comeco;
                        }
                        else if(i == cont1+1) {
                            disp1[i].comeco = ocupado1[i-1].fim;
                            disp1[i].fim = 24*60;
                        }
                        else {
                            disp1[i].comeco = ocupado1[i-1].fim;
                            disp1[i].fim = ocupado1[i].comeco;
                        }
                    }

                    printf("\nPeriodos de tempo disponiveis:\n");
                    for(i=0; i <= cont1+1; i++) {
                        duracao[i] = disp1[i].fim - disp1[i].comeco;

                        if(duracao[i] != 0) { //para excluir periodos nulos
                            printf("> %02d:%02.0f - %02d:%02.0f\n", disp1[i].comeco/60, (disp1[i].comeco/60.0 - disp1[i].comeco/60)*60, disp1[i].fim/60, (disp1[i].fim/60.0 - disp1[i].fim/60)*60);
                            printf("  Duracao: %02d:%02.0f\n\n", duracao[i]/60, (duracao[i]/60.0 - duracao[i]/60)*60);
                        }
                        else if(i==1)
                            printf("Nenhum\n");
                    }
                    
                    printf("\n");
                    system("pause");
                    break;
                }
            
                //criar arquivo com horarios disponiveis
                else if(opcao=='4') {
                    /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
                       Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
                       seu tempo de sono pode ser considerado um bloco de tempo ocupado.
                       Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
                       blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */

                    if(comecoDia>fimDia) {
                        ocupado1[cont1].comeco = fimDia;
                        ocupado1[cont1].fim = comecoDia;
                    }
                    else if(comecoDia<fimDia) {
                        ocupado1[cont1].comeco = fimDia;
                        ocupado1[cont1].fim = 24*60;
                        cont1++;
                        ocupado1[cont1].comeco = 0;
                        ocupado1[cont1].fim = comecoDia;
                    }

                    //select sort entre as entradas
                    for(i=0; i <= cont1-1; i++) {
                        menor = 100000;
                        for(j=i; j <= cont1; j++) {
                            if(ocupado1[j].comeco < menor) {
                                menor = ocupado1[j].comeco;
                                posicaoMenor = j;
                            }
                        }            
                        aux = ocupado1[i].comeco;
                        ocupado1[i].comeco = ocupado1[posicaoMenor].comeco;
                        ocupado1[posicaoMenor].comeco = aux;

                        aux = ocupado1[i].fim;
                        ocupado1[i].fim = ocupado1[posicaoMenor].fim;
                        ocupado1[posicaoMenor].fim = aux;
                    }

                    // select sort se o ocupado1.comeco for igual mas ocupado.fim diferente
                    for(i=0; i <= cont1; i += numRepetidos+1) {
                        numRepetidos = 0;
                        for(j = i+1; j <= cont1; j++)
                            if(ocupado1[j].comeco == ocupado1[i].comeco)
                                numRepetidos++;

                        for(j=i; j <= i+numRepetidos-1; j++) {
                            menor = 100000;
                            for(k=i; k <= i+numRepetidos; k++) {
                                if(ocupado1[k].comeco < menor) {
                                    menor = ocupado1[k].comeco;
                                    posicaoMenor = k;
                                }
                            }            
                            aux = ocupado1[j].comeco;
                            ocupado1[j].comeco = ocupado1[posicaoMenor].comeco;
                            ocupado1[posicaoMenor].comeco = aux;
                        }
                    }
                    
                    //remover periodos de tempo redundantes
                    for(i=1; i <= cont1; i++) {
                        //se um periodo estiver contido em outro, vamos exclui-lo
                        if(ocupado1[i].comeco > ocupado1[i-1].comeco && ocupado1[i].fim < ocupado1[i-1].fim) {
                            for(j=i; j <= cont1-1; j++) {
                                ocupado1[j].comeco = ocupado1[j+1].comeco;
                                ocupado1[j].fim = ocupado1[j+1].fim;
                            }
                            cont1--; //um periodo a menos no vetor
                            i--;
                        }

                        //se um periodo comecar antes ou quando outro acabar, vamos junta-los
                        else if(ocupado1[i].comeco <= ocupado1[i-1].fim) {
                            ocupado1[i-1].fim = ocupado1[i].fim;
                            for(j=i; j <= cont1-1; j++) {
                                ocupado1[j].comeco = ocupado1[j+1].comeco;
                                ocupado1[j].fim = ocupado1[j+1].fim;
                            }
                            cont1--; //um periodo a menos no vetor
                            i--;
                        }
                    }


                    //calculo dos tempos disponiveis
                    for(i=0; i <= cont1+1; i++) {
                        /* No geral, os periodos disponiveis sao o intervalo entre o final de
                           um periodo ocupado e comeco do seguinte.
                           Para que o algoritmo seja generico, o primeiro periodo sera sempre
                           o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
                           tiver duracao 0, ele sera ignorado)
                           A mesma logica se aplica ao ultimo periodo disponivel. */

                        if(i==0) {
                            disp1[i].comeco = 0;
                            disp1[i].fim = ocupado1[i].comeco;
                        }
                        else if(i == cont1+1) {
                            disp1[i].comeco = ocupado1[i-1].fim;
                            disp1[i].fim = 24*60;
                        }
                        else {
                            disp1[i].comeco = ocupado1[i-1].fim;
                            disp1[i].fim = ocupado1[i].comeco;
                        }
                    }

                    fp=fopen("horarios.txt", "w");

                    fprintf(fp, "Periodos de tempo disponiveis:\n");
                    for(i=0; i <= cont1+1; i++) {
                        duracao[i] = disp1[i].fim - disp1[i].comeco;

                        if(duracao[i] != 0) { //para excluir periodos nulos
                            fprintf(fp, "> %02d:%02.0f - %02d:%02.0f\n", disp1[i].comeco/60, (disp1[i].comeco/60.0 - disp1[i].comeco/60)*60, disp1[i].fim/60, (disp1[i].fim/60.0 - disp1[i].fim/60)*60);
                            fprintf(fp, "  Duracao: %02d:%02.0f\n\n", duracao[i]/60, (duracao[i]/60.0 - duracao[i]/60)*60);
                        }
                        else if(i==1)
                            fprintf(fp, "Nenhum\n");
                        printf("\n");
                    }
                    fclose(fp);
                    break;
                }
            }
        }


        //menu da semana
        else if(opcao=='2') {
            while(1) {

                system("cls");
                printf(">>>>>  T I M E C K O O N  <<<<<\n\n");
                printf("Uma calculadora de tempos disponiveis entre os membros de um grupo!\n\n");
                printf("[0] Sair do menu\n");
                printf("[1] Definir inicio e fim do dia\n");
                printf("[2] Definir dia da semana para inserir periodo de tempo\n");
                printf("[3] Inserir um periodo de tempo ocupado\n");
                printf("[4] Mostrar horarios disponiveis\n");
                printf("[5] Criar arquivo com horario disponiveis\n\n");
                printf("< Horarios vao de 00:00 a 24:00 >\n\n");
                printf("< Nao usar palavra com acento ou cedilha >\n");

                //validador de opcao
                while(1) {
                    printf("\nOpcao: ");
                    scanf(" %c", &opcao);
                    if(opcao=='0'||opcao=='1'||opcao=='2'||opcao=='3'||opcao=='4'||opcao=='5'||opcao=='6')
                        break;                
                    else
                        printf("Opcao invalida! Por favor, insira novamente.\n");
                }

                //sair do menu
                if(opcao=='0')
                    break;

                //definir inicio e fim do dia
                else if(opcao=='1') {
                    //menu para definir abrangencia
                    printf("\n[0] Sair do menu\n");
                    printf("[1] Definir para todos os dias\n");
                    printf("[2] Definir para dias especificos\n");
                            
                    //validacao de entrada da opcao
                    while(1) {
                        printf("\nOpcao: ");
                        scanf(" %c", &opcao);
                        if(opcao=='0'||opcao=='1'||opcao=='2')
                            break;                                
                        else
                            printf("Opcao invalida! Por favor, insira novamente.\n");
                    }

                    //lendo os dias os dias, caso for definir para dias especificos
                    if(opcao=='2') {
                        //quantidade de dias
                        printf("\nQuantidade de dias: ");
                        scanf("%d", &qtdDias);

                        //lendo os dias
                        for(i=0; i<qtdDias; ) {
                            printf("\nDia %d: ", i+1);
                            fflush(stdin);
                            gets(diaString);
                            if(stricmp(diaString, diaAnterior)==0)
                                printf("Dia da semana repetido! Por favor, insira novamente.\n");
                            else if(stricmp(diaString, "Domingo")==0 || stricmp(diaString, "domingo")==0 || stricmp(diaString, "DOMINGO")==0) {
                                dias[i]=dom;
                                i++;
                            }
                            else if(stricmp(diaString, "Segunda")==0 || stricmp(diaString, "segunda")==0 || stricmp(diaString, "SEGUNDA")==0 || stricmp(diaString, "Segunda-feira")==0 || stricmp(diaString, "segunda-feira")==0 || stricmp(diaString, "SEGUNDA-FEIRA")==0) {
                                dias[i]=seg;
                                i++;
                            }
                            else if(stricmp(diaString, "Terca")==0 || stricmp(diaString, "terca")==0 || stricmp(diaString, "TERCA")==0 || stricmp(diaString, "Terca-feira")==0 || stricmp(diaString, "terca-feira")==0 || stricmp(diaString, "TERCA-FEIRA")==0) {
                                dias[i]=ter;
                                i++;
                            }
                            else if(stricmp(diaString, "Quarta")==0 || stricmp(diaString, "quarta")==0 || stricmp(diaString, "QUARTA")==0 || stricmp(diaString, "Quarta-feira")==0 || stricmp(diaString, "quarta-feira")==0 || stricmp(diaString, "QUARTA-FEIRA")==0) {
                                dias[i]=qua;
                                i++;
                            }
                            else if(stricmp(diaString, "Quinta")==0 || stricmp(diaString, "quinta")==0 || stricmp(diaString, "QUINTA")==0 || stricmp(diaString, "Quinta-feira")==0 || stricmp(diaString, "quinta-feira")==0 || stricmp(diaString, "QUINTA-FEIRA")==0) {
                                dias[i]=qui;
                                i++;
                            }
                            else if(stricmp(diaString, "Sexta")==0 || stricmp(diaString, "sexta")==0 || stricmp(diaString, "SEXTA")==0 || stricmp(diaString, "Sexta-feira")==0 || stricmp(diaString, "sexta-feira")==0 || stricmp(diaString, "SEXTA-FEIRA")==0) {
                                dias[i]=sex;
                                i++;
                            }
                            else if(stricmp(diaString, "Sabado")==0 || stricmp(diaString, "sabado")==0 || stricmp(diaString, "SABADO")==0) {
                                dias[i]=sab;
                                i++;
                            }
                            else
                                printf("Dia da semana invalido! Por favor, insira novamente.\n");

                            strcpy(diaAnterior, diaString);
                        }
                    }

                    //validador de entrada do horario de inicio
                    while(1) {
                        printf("\nDigite o horario do inicio do dia: ");
                        scanf("%d:%d", &h, &min);
                        if(h*60+min>=0 && h*60+min<=24*60)
                            break;
                        else
                            printf("Horario invalido! Por favor, insira novamente.\n");
                    }

                    //se for para todos os dias
                    if(opcao=='1')
                        for(i=0; i<7; i++)
                            comecoDiaVet[i] = min + h*60;
                    //se for para dias especificos
                    else
                        for(i=0; i<qtdDias; i++)
                            comecoDiaVet[dias[i]] = min + h*60;

                    //validacao de entrada do horario de fim
                    while(1) {
                        printf("\nDigite o horario do fim do dia: ");
                        scanf("%d:%d", &h, &min);
                        if(h*60+min>=0 && h*60+min<=24*60)
                            break;
                        else
                            printf("Horario invalido! Por favor, insira novamente.\n");
                    }

                    //se for para todos os dias
                    if(opcao=='1')
                        for(i=0; i<7; i++)
                            fimDiaVet[i] = min + h*60;
                    //se for para dias especificos
                    else
                        for(i=0; i<qtdDias; i++)
                            fimDiaVet[dias[i]] = min + h*60;
                }

                //definir dia da semana
                else if(opcao=='2') {
                    while(1) {
                        printf("\nDigite o dia da semana: ");
                        fflush(stdin);
                        gets(diaString);
                        if(stricmp(diaString, "Domingo")==0 || stricmp(diaString, "domingo")==0 || stricmp(diaString, "DOMINGO")==0) {
                            diaInserir=dom;
                            break;
                        }
                        else if(stricmp(diaString, "Segunda")==0 || stricmp(diaString, "segunda")==0 || stricmp(diaString, "SEGUNDA")==0 || stricmp(diaString, "Segunda-feira")==0 || stricmp(diaString, "segunda-feira")==0 || stricmp(diaString, "SEGUNDA-FEIRA")==0) {
                            diaInserir=seg;
                            break;
                        }
                        else if(stricmp(diaString, "Terca")==0 || stricmp(diaString, "terca")==0 || stricmp(diaString, "TERCA")==0 || stricmp(diaString, "Terca-feira")==0 || stricmp(diaString, "terca-feira")==0 || stricmp(diaString, "TERCA-FEIRA")==0) {
                            diaInserir=ter;
                            break;
                        }
                        else if(stricmp(diaString, "Quarta")==0 || stricmp(diaString, "quarta")==0 || stricmp(diaString, "QUARTA")==0 || stricmp(diaString, "Quarta-feira")==0 || stricmp(diaString, "quarta-feira")==0 || stricmp(diaString, "QUARTA-FEIRA")==0) {
                            diaInserir=qua;
                            break;
                        }
                        else if(stricmp(diaString, "Quinta")==0 || stricmp(diaString, "quinta")==0 || stricmp(diaString, "QUINTA")==0 || stricmp(diaString, "Quinta-feira")==0 || stricmp(diaString, "quinta-feira")==0 || stricmp(diaString, "QUINTA-FEIRA")==0) {
                            diaInserir=qui;
                            break;
                        }
                        else if(stricmp(diaString, "Sexta")==0 || stricmp(diaString, "sexta")==0 || stricmp(diaString, "SEXTA")==0 || stricmp(diaString, "Sexta-feira")==0 || stricmp(diaString, "sexta-feira")==0 || stricmp(diaString, "SEXTA-FEIRA")==0) {
                            diaInserir=sex;
                            break;
                        }
                        else if(stricmp(diaString, "Sabado")==0 || stricmp(diaString, "sabado")==0 || stricmp(diaString, "SABADO")==0) {
                            diaInserir=sab;
                            break;
                        }
                        else
                            printf("Dia da semana invalido! Por favor, insira novamente.\n");
                    }
                }

                //inserir um periodo de tempo ocupado
                else if(opcao=='3') {
                    while(1) {
                        //caso um dia nao tiver sido escolhido previamente
                        if(diaInserir==10) {
                            printf("Voce precisa escolher o um dia primeiro!\n");
                            system("pause");
                            break;
                        }

                        //validador de entrada do inicio
                        while(1) {
                            printf("\nDigite o horario do inicio do periodo: ");
                            scanf("%d:%d", &h, &min);
                            if(h*60+min>=0 && h*60+min<=24*60)
                                break;
                            else
                                printf("Horario invalido! Por favor, insira novamente.\n");
                        }

                        ocupado2[diaInserir][cont2[diaInserir]].comeco = h*60 + min;

                        //validador de entrada do fim
                        while(1) {
                            printf("\nDigite o horario do fim do periodo: ");
                            scanf("%d:%d", &h, &min);
                            if(h*60+min>=0 && h*60+min<=24*60)
                                break;
                            else
                                printf("Horario invalido! Por favor, insira novamente.\n");
                        }

                        //validador de periodo
                        if(ocupado2[diaInserir][cont2[diaInserir]].comeco >= h*60 + min)
                            printf("Periodo invalido! Por favor, insira novamente.\n");
                        else {
                            ocupado2[diaInserir][cont2[diaInserir]].fim = h*60 + min;
                            cont2[diaInserir]++;
                            break;
                        }
                    }
                }
                
                //mostrar horarios disponiveis
                else if(opcao=='4') {
                    printf("\n[0] Sair do menu\n");
                    printf("[1] Dias especificos\n");
                    printf("[2] Semana inteira\n");

                    //validacao de entrada da opcao
                    while(1) {
                        printf("\nOpcao: ");
                        scanf(" %c", &opcao);
                        if(opcao=='0'||opcao=='1'||opcao=='2')
                            break;                                
                        else
                            printf("Opcao invalida! Por favor, insira novamente.\n");
                    }

                    //dias especificos
                    if(opcao=='1') {
                        //quantidade de dias
                        printf("\nQuantidade de dias: ");
                        scanf("%d", &qtdDias);

                        //lendo os dias
                        for(i=0; i<qtdDias; ) {
                            printf("\nDia %d: ", i+1);
                            fflush(stdin);
                            gets(diaString);
                            if(stricmp(diaString, diaAnterior)==0)
                                printf("Dia da semana repetido! Por favor, insira novamente.\n");
                            else if(stricmp(diaString, "Domingo")==0 || stricmp(diaString, "domingo")==0 || stricmp(diaString, "DOMINGO")==0) {
                                dias[i]=dom;
                                i++;
                            }
                            else if(stricmp(diaString, "Segunda")==0 || stricmp(diaString, "segunda")==0 || stricmp(diaString, "SEGUNDA")==0 || stricmp(diaString, "Segunda-feira")==0 || stricmp(diaString, "segunda-feira")==0 || stricmp(diaString, "SEGUNDA-FEIRA")==0) {
                                dias[i]=seg;
                                i++;
                            }
                            else if(stricmp(diaString, "Terca")==0 || stricmp(diaString, "terca")==0 || stricmp(diaString, "TERCA")==0 || stricmp(diaString, "Terca-feira")==0 || stricmp(diaString, "terca-feira")==0 || stricmp(diaString, "TERCA-FEIRA")==0) {
                                dias[i]=ter;
                                i++;
                            }
                            else if(stricmp(diaString, "Quarta")==0 || stricmp(diaString, "quarta")==0 || stricmp(diaString, "QUARTA")==0 || stricmp(diaString, "Quarta-feira")==0 || stricmp(diaString, "quarta-feira")==0 || stricmp(diaString, "QUARTA-FEIRA")==0) {
                                dias[i]=qua;
                                i++;
                            }
                            else if(stricmp(diaString, "Quinta")==0 || stricmp(diaString, "quinta")==0 || stricmp(diaString, "QUINTA")==0 || stricmp(diaString, "Quinta-feira")==0 || stricmp(diaString, "quinta-feira")==0 || stricmp(diaString, "QUINTA-FEIRA")==0) {
                                dias[i]=qui;
                                i++;
                            }
                            else if(stricmp(diaString, "Sexta")==0 || stricmp(diaString, "sexta")==0 || stricmp(diaString, "SEXTA")==0 || stricmp(diaString, "Sexta-feira")==0 || stricmp(diaString, "sexta-feira")==0 || stricmp(diaString, "SEXTA-FEIRA")==0) {
                                dias[i]=sex;
                                i++;
                            }
                            else if(stricmp(diaString, "Sabado")==0 || stricmp(diaString, "sabado")==0 || stricmp(diaString, "SABADO")==0) {
                                dias[i]=sab;
                                i++;
                            }
                            else
                                printf("Dia da semana invalido! Por favor, insira novamente.\n");

                            strcpy(diaAnterior, diaString);
                        }

                        for(i=0; i<qtdDias; i++) {
                            /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
                            Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
                            seu tempo de sono pode ser considerado um bloco de tempo ocupado.
                            Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
                            blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */
                            
                            if(comecoDiaVet[dias[i]] > fimDiaVet[dias[i]]) {
                                ocupado2[dias[i]][cont2[dias[i]]].comeco = fimDiaVet[dias[i]];
                                ocupado2[dias[i]][cont2[dias[i]]].fim = comecoDiaVet[dias[i]];
                            }
                            else if(comecoDiaVet[dias[i]] < fimDiaVet[dias[i]]) {
                                ocupado2[dias[i]][cont2[dias[i]]].comeco = fimDiaVet[dias[i]];
                                ocupado2[dias[i]][cont2[dias[i]]].fim = 24*60;
                                cont2[dias[i]]++;
                                ocupado2[dias[i]][cont2[dias[i]]].comeco = 0;
                                ocupado2[dias[i]][cont2[dias[i]]].fim = comecoDiaVet[dias[i]];
                            }

                            //select sort entre as entradas
                            for(j=0; j <= cont2[dias[i]]-1; j++) {
                                menor = 100000;
                                for(k=j; k <= cont2[dias[i]]; k++) {
                                    if(ocupado2[dias[i]][k].comeco < menor) {
                                        menor = ocupado2[dias[i]][k].comeco;
                                        posicaoMenor = k;
                                    }
                                }            
                                aux = ocupado2[dias[i]][j].comeco;
                                ocupado2[dias[i]][j].comeco = ocupado2[dias[i]][posicaoMenor].comeco;
                                ocupado2[dias[i]][posicaoMenor].comeco = aux;

                                aux = ocupado2[dias[i]][j].fim;
                                ocupado2[dias[i]][j].fim = ocupado2[dias[i]][posicaoMenor].fim;
                                ocupado2[dias[i]][posicaoMenor].fim = aux;
                            }

                            // select sort se o ocupado2.comeco for igual mas ocupado.fim diferente
                            for(j=0; j <= cont2[dias[i]]; j += numRepetidos+1) {
                                numRepetidos = 0;
                                for(k = j+1; k <= cont2[dias[i]]; k++)
                                    if(ocupado2[dias[i]][k].comeco == ocupado2[dias[i]][j].comeco)
                                        numRepetidos++;

                                for(k=j; k <= j+numRepetidos-1; k++) {
                                    menor = 100000;
                                    for(l=j; l <= j+numRepetidos; l++) {
                                        if(ocupado2[dias[i]][l].fim < menor) {
                                            menor = ocupado2[dias[i]][l].fim;
                                            posicaoMenor = l;
                                        }
                                    }            
                                    aux = ocupado2[dias[i]][k].fim;
                                    ocupado2[dias[i]][k].fim = ocupado2[dias[i]][posicaoMenor].fim;
                                    ocupado2[dias[i]][posicaoMenor].fim = aux;
                                }
                            }
                            
                            //remover periodos de tempo redundantes
                            for(j = 1; j <= cont2[dias[i]]; j++) {
                                //se um periodo estiver contido em outro, vamos exclui-lo
                                if(ocupado2[dias[i]][j].comeco > ocupado2[dias[i]][j-1].comeco && ocupado2[dias[i]][j].fim < ocupado2[dias[i]][j-1].fim) {
                                    for(k=j; k <= cont2[dias[i]] - 1; k++) {
                                        ocupado2[dias[i]][k].comeco = ocupado2[dias[i]][k+1].comeco;
                                        ocupado2[dias[i]][k].fim = ocupado2[dias[i]][k+1].fim;
                                    }
                                    cont2[dias[i]]--; //um periodo a menos no vetor
                                    j--;
                                }

                                //se um periodo comecar antes ou quando outro acabar, vamos junta-los
                                else if(ocupado2[dias[i]][j].comeco <= ocupado2[dias[i]][j-1].fim) {
                                    ocupado2[dias[i]][j-1].fim = ocupado2[dias[i]][j].fim;
                                    for(k=j; k <= cont2[dias[i]] - 1; k++) {
                                        ocupado2[dias[i]][k].comeco = ocupado2[dias[i]][k+1].comeco;
                                        ocupado2[dias[i]][k].fim = ocupado2[dias[i]][k+1].fim;
                                    }
                                    cont2[dias[i]]--; //um periodo a menos no vetor
                                    j--;
                                }
                            }

                            //calculo dos tempos disponiveis
                            for(j=0; j <= cont2[dias[i]] + 1; j++) {
                                /* No geral, os periodos disponiveis sao o intervalo entre o final de
                                um periodo ocupado e comeco do seguinte.
                                Para que o algoritmo seja generico, o primeiro periodo sera sempre
                                o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
                                tiver duracao 0, ele sera ignorado)
                                A mesma logica se aplica ao ultimo periodo disponivel. */

                                if(j==0) {
                                    disp2[dias[i]][j].comeco = 0;
                                    disp2[dias[i]][j].fim = ocupado2[dias[i]][j].comeco;
                                }
                                else if(j == cont2[dias[i]] + 1) {
                                    disp2[dias[i]][j].comeco = ocupado2[dias[i]][j-1].fim;
                                    disp2[dias[i]][j].fim = 24*60;
                                }
                                else {
                                    disp2[dias[i]][j].comeco = ocupado2[dias[i]][j-1].fim;
                                    disp2[dias[i]][j].fim = ocupado2[dias[i]][j].comeco;
                                }
                            }

                            printf("\nPeriodos de tempo disponiveis:\n");
                            for(j=0; j <= cont2[dias[i]] + 1; j++) {
                                duracao[j] = disp2[dias[i]][j].fim - disp2[dias[i]][j].comeco;

                                if(duracao[j] != 0) { //para excluir periodos nulos
                                    printf("> %02d:%02.0f - %02d:%02.0f\n", disp2[dias[i]][j].comeco/60, (disp2[dias[i]][j].comeco/60.0 - disp2[dias[i]][j].comeco/60)*60, disp2[dias[i]][j].fim/60, (disp2[dias[i]][j].fim/60.0 - disp2[dias[i]][j].fim/60)*60);
                                    printf("  Duracao: %02d:%02.0f\n\n", duracao[j]/60, (duracao[j]/60.0 - duracao[j]/60)*60);
                                }
                                else if(j==1)
                                    printf("Nenhum\n");
                            }
                        }
                        printf("\n");
                        system("pause");
                    }
                
                    //semana inteira
                    else if(opcao=='2') {
                        for(i=0; i<7; i++) {
                            /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
                            Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
                            seu tempo de sono pode ser considerado um bloco de tempo ocupado.
                            Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
                            blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */
                            
                            if(comecoDiaVet[i]>fimDiaVet[i]) {
                                ocupado2[i][cont2[i]].comeco = fimDiaVet[i];
                                ocupado2[i][cont2[i]].fim = comecoDiaVet[i];
                            }
                            else if(comecoDiaVet[i]<fimDiaVet[i]) {
                                ocupado2[i][cont2[i]].comeco = fimDiaVet[i];
                                ocupado2[i][cont2[i]].fim = 24*60;
                                cont2[i]++;
                                ocupado2[i][cont2[i]].comeco = 0;
                                ocupado2[i][cont2[i]].fim = comecoDiaVet[i];
                            }

                            //select sort entre as entradas
                            for(j=0; j <= cont2[i]-1; j++) {
                                menor = 100000;
                                for(k=j; k <= cont2[i]; k++) {
                                    if(ocupado2[i][k].comeco < menor) {
                                        menor = ocupado2[i][k].comeco;
                                        posicaoMenor = k;
                                    }
                                }            
                                aux = ocupado2[i][j].comeco;
                                ocupado2[i][j].comeco = ocupado2[i][posicaoMenor].comeco;
                                ocupado2[i][posicaoMenor].comeco = aux;

                                aux = ocupado2[i][j].fim;
                                ocupado2[i][j].fim = ocupado2[i][posicaoMenor].fim;
                                ocupado2[i][posicaoMenor].fim = aux;
                            }

                            // select sort se o ocupado2.comeco for igual mas ocupado.fim diferente
                            for(j=0; j <= cont2[i]; j += numRepetidos+1) {
                                numRepetidos = 0;
                                for(k = j+1; k <= cont2[i]; k++)
                                    if(ocupado2[i][k].comeco == ocupado2[i][j].comeco)
                                        numRepetidos++;

                                for(k=j; k <= j+numRepetidos-1; k++) {
                                    menor = 100000;
                                    for(l=j; l <= j+numRepetidos; l++) {
                                        if(ocupado2[i][l].fim < menor) {
                                            menor = ocupado2[i][l].fim;
                                            posicaoMenor = l;
                                        }
                                    }            
                                    aux = ocupado2[i][k].fim;
                                    ocupado2 [i][k].fim = ocupado2[i][posicaoMenor].fim;
                                    ocupado2 [i][posicaoMenor].fim = aux;
                                }
                            }
                            
                            //remover periodos de tempo redundantes
                            for(j=1; j <= cont2[i]; j++) {
                                //se um periodo estiver contido em outro, vamos exclui-lo
                                if(ocupado2[i][j].comeco > ocupado2[i][j-1].comeco && ocupado2[i][j].fim < ocupado2[i][j-1].fim) {
                                    for(k=j; k <= cont2[i]-1; k++) {
                                        ocupado2[i][k].comeco = ocupado2[i][k+1].comeco;
                                        ocupado2[i][k].fim = ocupado2[i][k+1].fim;
                                    }
                                    cont2[i]--; //um periodo a menos no vetor
                                    j--;
                                }

                                //se um periodo comecar antes ou quando outro acabar, vamos kunta-los
                                else if(ocupado2[i][j].comeco <= ocupado2[i][j-1].fim) {
                                    ocupado2[i][j-1].fim = ocupado2[i][j].fim;
                                    for(k=j; k <= cont2[i]-1; k++) {
                                        ocupado2[i][k].comeco = ocupado2[i][k+1].comeco;
                                        ocupado2[i][k].fim = ocupado2[i][k+1].fim;
                                    }
                                    cont2[i]--; //um periodo a menos no vetor
                                    j--;
                                }
                            }

                            //calculo dos tempos disponiveis
                            for(j=0; j <= cont2[i]+1; j++) {
                                /* No geral, os periodos disponiveis sao o intervalo entre o final de
                                um periodo ocupado e comeco do seguinte.
                                Para que o algoritmo seja generico, o primeiro periodo sera sempre
                                o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
                                tiver duracao 0, ele sera ignorado)
                                A mesma logica se aplica ao ultimo periodo disponivel. */

                                if(j==0) {
                                    disp2[i][j].comeco = 0;
                                    disp2[i][j].fim = ocupado2[i][j].comeco;
                                }
                                else if(j == cont2[i]+1) {
                                    disp2[i][j].comeco = ocupado2[i][j-1].fim;
                                    disp2[i][j].fim = 24*60;
                                }
                                else {
                                    disp2[i][j].comeco = ocupado2[i][j-1].fim;
                                    disp2[i][j].fim = ocupado2[i][j].comeco;
                                }
                            }

                            switch(i) {
                                case dom:
                                    printf("\nDOMINGO\n");
                                    break;
                                case seg:
                                    printf("\nSEGUNDA-FEIRA\n");
                                    break;
                                case ter:
                                    printf("\nTERCA-FEIRA\n");
                                    break;
                                case qua:
                                    printf("\nQUARTA-FEIRA\n");
                                    break;
                                case qui:
                                    printf("\nQUINTA-FEIRA\n");
                                    break;
                                case sex:
                                    printf("\nSEXTA-FEIRA\n");
                                    break;
                                case sab:
                                    printf("\nSABADO\n");
                            }

                            printf("Periodos de tempo disponiveis:\n");
                            for(j=0; j <= cont2[i] + 1; j++) {
                                duracao[j] = disp2[i][j].fim - disp2[i][j].comeco;

                                if(duracao[j] != 0) { //para excluir periodos nulos
                                    printf("> %02d:%02.0f - %02d:%02.0f\n", disp2[i][j].comeco/60, (disp2[i][j].comeco/60.0 - disp2[i][j].comeco/60)*60, disp2[i][j].fim/60, (disp2[i][j].fim/60.0 - disp2[i][j].fim/60)*60);
                                    printf("  Duracao: %02d:%02.0f\n\n", duracao[j]/60, (duracao[j]/60.0 - duracao[j]/60)*60);
                                }
                                else if(j==1)
                                    printf("Nenhum\n");
                            }
                        }
                        printf("\n");
                        system("pause");
                    }
                    break;              
                }                
            
                //criar arquivo com horario disponiveis
                else if(opcao=='5') {
                    printf("\n[0] Sair do menu\n");
                    printf("[1] Dias especificos\n");
                    printf("[2] Semana inteira\n");

                    //validacao de entrada da opcao
                    while(1) {
                        printf("\nOpcao: ");
                        scanf(" %c", &opcao);
                        if(opcao=='0'||opcao=='1'||opcao=='2')
                            break;                                
                        else
                            printf("Opcao invalida! Por favor, insira novamente.\n");
                    }

                    if(opcao=='0')
                        break;

                    //dias especificos
                    else if(opcao=='1') {
                        //quantidade de dias
                        printf("\nQuantidade de dias: ");
                        scanf("%d", &qtdDias);

                        //lendo os dias
                        for(i=0; i<qtdDias; ) {
                            printf("\nDia %d: ", i+1);
                            fflush(stdin);
                            gets(diaString);
                            if(stricmp(diaString, diaAnterior)==0)
                                printf("Dia da semana repetido! Por favor, insira novamente.\n");
                            else if(stricmp(diaString, "Domingo")==0 || stricmp(diaString, "domingo")==0 || stricmp(diaString, "DOMINGO")==0) {
                                dias[i]=dom;
                                i++;
                            }
                            else if(stricmp(diaString, "Segunda")==0 || stricmp(diaString, "segunda")==0 || stricmp(diaString, "SEGUNDA")==0 || stricmp(diaString, "Segunda-feira")==0 || stricmp(diaString, "segunda-feira")==0 || stricmp(diaString, "SEGUNDA-FEIRA")==0) {
                                dias[i]=seg;
                                i++;
                            }
                            else if(stricmp(diaString, "Terca")==0 || stricmp(diaString, "terca")==0 || stricmp(diaString, "TERCA")==0 || stricmp(diaString, "Terca-feira")==0 || stricmp(diaString, "terca-feira")==0 || stricmp(diaString, "TERCA-FEIRA")==0) {
                                dias[i]=ter;
                                i++;
                            }
                            else if(stricmp(diaString, "Quarta")==0 || stricmp(diaString, "quarta")==0 || stricmp(diaString, "QUARTA")==0 || stricmp(diaString, "Quarta-feira")==0 || stricmp(diaString, "quarta-feira")==0 || stricmp(diaString, "QUARTA-FEIRA")==0) {
                                dias[i]=qua;
                                i++;
                            }
                            else if(stricmp(diaString, "Quinta")==0 || stricmp(diaString, "quinta")==0 || stricmp(diaString, "QUINTA")==0 || stricmp(diaString, "Quinta-feira")==0 || stricmp(diaString, "quinta-feira")==0 || stricmp(diaString, "QUINTA-FEIRA")==0) {
                                dias[i]=qui;
                                i++;
                            }
                            else if(stricmp(diaString, "Sexta")==0 || stricmp(diaString, "sexta")==0 || stricmp(diaString, "SEXTA")==0 || stricmp(diaString, "Sexta-feira")==0 || stricmp(diaString, "sexta-feira")==0 || stricmp(diaString, "SEXTA-FEIRA")==0) {
                                dias[i]=sex;
                                i++;
                            }
                            else if(stricmp(diaString, "Sabado")==0 || stricmp(diaString, "sabado")==0 || stricmp(diaString, "SABADO")==0) {
                                dias[i]=sab;
                                i++;
                            }
                            else
                                printf("Dia da semana invalido! Por favor, insira novamente.\n");

                            strcpy(diaAnterior, diaString);
                        }

                        for(i=0; i<qtdDias; i++) {
                            /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
                            Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
                            seu tempo de sono pode ser considerado um bloco de tempo ocupado.
                            Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
                            blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */
                            
                            if(comecoDiaVet[dias[i]] > fimDiaVet[dias[i]]) {
                                ocupado2[dias[i]][cont2[dias[i]]].comeco = fimDiaVet[dias[i]];
                                ocupado2[dias[i]][cont2[dias[i]]].fim = comecoDiaVet[dias[i]];
                            }
                            else if(comecoDiaVet[dias[i]] < fimDiaVet[dias[i]]) {
                                ocupado2[dias[i]][cont2[dias[i]]].comeco = fimDiaVet[dias[i]];
                                ocupado2[dias[i]][cont2[dias[i]]].fim = 24*60;
                                cont2[dias[i]]++;
                                ocupado2[dias[i]][cont2[dias[i]]].comeco = 0;
                                ocupado2[dias[i]][cont2[dias[i]]].fim = comecoDiaVet[dias[i]];
                            }

                            //select sort entre as entradas
                            for(j=0; j <= cont2[dias[i]]-1; j++) {
                                menor = 100000;
                                for(k=j; k <= cont2[dias[i]]; k++) {
                                    if(ocupado2[dias[i]][k].comeco < menor) {
                                        menor = ocupado2[dias[i]][k].comeco;
                                        posicaoMenor = k;
                                    }
                                }            
                                aux = ocupado2[dias[i]][j].comeco;
                                ocupado2[dias[i]][j].comeco = ocupado2[dias[i]][posicaoMenor].comeco;
                                ocupado2[dias[i]][posicaoMenor].comeco = aux;

                                aux = ocupado2[dias[i]][j].fim;
                                ocupado2[dias[i]][j].fim = ocupado2[dias[i]][posicaoMenor].fim;
                                ocupado2[dias[i]][posicaoMenor].fim = aux;
                            }

                            // select sort se o ocupado2.comeco for igual mas ocupado.fim diferente
                            for(j=0; j <= cont2[dias[i]]; j += numRepetidos+1) {
                                numRepetidos = 0;
                                for(k = j+1; k <= cont2[dias[i]]; k++)
                                    if(ocupado2[dias[i]][k].comeco == ocupado2[dias[i]][j].comeco)
                                        numRepetidos++;

                                for(k=j; k <= j+numRepetidos-1; k++) {
                                    menor = 100000;
                                    for(l=j; l <= j+numRepetidos; l++) {
                                        if(ocupado2[dias[i]][l].fim < menor) {
                                            menor = ocupado2[dias[i]][l].fim;
                                            posicaoMenor = l;
                                        }
                                    }            
                                    aux = ocupado2[dias[i]][k].fim;
                                    ocupado2[dias[i]][k].fim = ocupado2[dias[i]][posicaoMenor].fim;
                                    ocupado2[dias[i]][posicaoMenor].fim = aux;
                                }
                            }
                            
                            //remover periodos de tempo redundantes
                            for(j=1; j <= cont2[dias[i]]; j++) {
                                //se um periodo estiver contido em outro, vamos exclui-lo
                                if(ocupado2[dias[i]][j].comeco > ocupado2[dias[i]][j-1].comeco && ocupado2[dias[i]][j].fim < ocupado2[dias[i]][j-1].fim) {
                                    for(k=j; k <= cont2[dias[i]]-1; k++) {
                                        ocupado2[dias[i]][k].comeco = ocupado2[dias[i]][k+1].comeco;
                                        ocupado2[dias[i]][k].fim = ocupado2[dias[i]][k+1].fim;
                                    }
                                    cont2[dias[i]]--; //um periodo a menos no vetor
                                    j--;
                                }

                                //se um periodo comecar antes ou quando outro acabar, vamos kunta-los
                                else if(ocupado2[dias[i]][j].comeco <= ocupado2[dias[i]][j-1].fim) {
                                    ocupado2[dias[i]][j-1].fim = ocupado2[dias[i]][j].fim;
                                    for(k=j; k <= cont2[dias[i]]-1; k++) {
                                        ocupado2[dias[i]][k].comeco = ocupado2[dias[i]][k+1].comeco;
                                        ocupado2[dias[i]][k].fim = ocupado2[dias[i]][k+1].fim;
                                    }
                                    cont2[dias[i]]--; //um periodo a menos no vetor
                                    j--;
                                }
                            }

                            //calculo dos tempos disponiveis
                            for(j=0; j <= cont2[dias[i]] + 1; j++) {
                                /* No geral, os periodos disponiveis sao o intervalo entre o final de
                                um periodo ocupado e comeco do seguinte.
                                Para que o algoritmo seja generico, o primeiro periodo sera sempre
                                o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
                                tiver duracao 0, ele sera ignorado)
                                A mesma logica se aplica ao ultimo periodo disponivel. */

                                if(j==0) {
                                    disp2[dias[i]][j].comeco = 0;
                                    disp2[dias[i]][j].fim = ocupado2[dias[i]][j].comeco;
                                }
                                else if(j == cont2[dias[i]] + 1) {
                                    disp2[dias[i]][j].comeco = ocupado2[dias[i]][j-1].fim;
                                    disp2[dias[i]][j].fim = 24*60;
                                }
                                else {
                                    disp2[dias[i]][j].comeco = ocupado2[dias[i]][j-1].fim;
                                    disp2[dias[i]][j].fim = ocupado2[dias[i]][j].comeco;
                                }
                            }

                            switch(dias[i]) {
                                case dom:
                                    fp=fopen("horarios_domingo.txt", "w");
                                    break;
                                case seg:
                                    fp=fopen("horarios_segunda.txt", "w");
                                    break;
                                case ter:
                                    fp=fopen("horarios_terca.txt", "w");
                                    break;
                                case qua:
                                    fp=fopen("horarios_quarta.txt", "w");
                                    break;
                                case qui:
                                    fp=fopen("horarios_quinta.txt", "w");
                                    break;
                                case sex:
                                    fp=fopen("horarios_sexta.txt", "w");
                                    break;
                                case sab:
                                    fp=fopen("horarios_sabado.txt", "w");
                            }

                            fprintf(fp, "Periodos de tempo disponiveis:\n");
                            for(j=0; j <= cont2[dias[i]] + 1; j++) {
                                duracao[j] = disp2[dias[i]][j].fim - disp2[dias[i]][j].comeco;

                                if(duracao[j] != 0) { //para excluir periodos nulos
                                    fprintf(fp, "> %02d:%02.0f - %02d:%02.0f\n", disp2[dias[i]][j].comeco/60, (disp2[dias[i]][j].comeco/60.0 - disp2[dias[i]][j].comeco/60)*60, disp2[dias[i]][j].fim/60, (disp2[dias[i]][j].fim/60.0 - disp2[dias[i]][j].fim/60)*60);
                                    fprintf(fp, "  Duracao: %02d:%02.0f\n", duracao[j]/60, (duracao[j]/60.0 - duracao[j]/60)*60);
                                }
                                else if(j==1)
                                    fprintf(fp, "Nenhum\n");
                            }                            
                            fclose(fp);
                        }
                    }
                
                    //semana inteira
                    else if(opcao=='2') {
                        fp=fopen("horarios_semana.txt", "w");
                        for(i=0; i<7; i++) {
                            /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
                            Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
                            seu tempo de sono pode ser considerado um bloco de tempo ocupado.
                            Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
                            blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */
                            
                            if(comecoDiaVet[i]>fimDiaVet[i]) {
                                ocupado2[i][cont2[i]].comeco = fimDiaVet[i];
                                ocupado2[i][cont2[i]].fim = comecoDiaVet[i];
                            }
                            else if(comecoDiaVet[i]<fimDiaVet[i]) {
                                ocupado2[i][cont2[i]].comeco = fimDiaVet[i];
                                ocupado2[i][cont2[i]].fim = 24*60;
                                cont2[i]++;
                                ocupado2[i][cont2[i]].comeco = 0;
                                ocupado2[i][cont2[i]].fim = comecoDiaVet[i];
                            }

                            //select sort entre as entradas
                            for(j=0; j <= cont2[i]-1; j++) {
                                menor = 100000;
                                for(k=j; k <= cont2[i]; k++) {
                                    if(ocupado2[i][k].comeco < menor) {
                                        menor = ocupado2[i][k].comeco;
                                        posicaoMenor = k;
                                    }
                                }            
                                aux = ocupado2[i][j].comeco;
                                ocupado2[i][j].comeco = ocupado2[i][posicaoMenor].comeco;
                                ocupado2[i][posicaoMenor].comeco = aux;

                                aux = ocupado2[i][j].fim;
                                ocupado2[i][j].fim = ocupado2[i][posicaoMenor].fim;
                                ocupado2[i][posicaoMenor].fim = aux;
                            }

                            // select sort se o ocupado2.comeco for igual mas ocupado.fim diferente
                            for(j=0; j <= cont2[i]; j += numRepetidos+1) {
                                numRepetidos = 0;
                                for(k=j+1; k<=cont2[i]; k++)
                                    if(ocupado2[i][k].comeco == ocupado2[i][j].comeco)
                                        numRepetidos++;

                                for(k=j; k <= j+numRepetidos-1; k++) {
                                    menor = 100000;
                                    for(l=j; l <= j+numRepetidos; l++) {
                                        if(ocupado2[i][l].fim < menor) {
                                            menor = ocupado2[i][l].fim;
                                            posicaoMenor = l;
                                        }
                                    }            
                                    aux = ocupado2[i][k].fim;
                                    ocupado2[i][k].fim = ocupado2[i][posicaoMenor].fim;
                                    ocupado2[i][posicaoMenor].fim = aux;
                                }
                            }
                            
                            //remover periodos de tempo redundantes
                            for(j=1; j <= cont2[i]; j++) {
                                //se um periodo estiver contido em outro, vamos exclui-lo
                                if(ocupado2[i][j].comeco > ocupado2[i][j-1].comeco && ocupado2[i][j].fim < ocupado2[i][j-1].fim) {
                                    for(k=j; k <= cont2[i]-1; k++) {
                                        ocupado2[i][k].comeco = ocupado2[i][k+1].comeco;
                                        ocupado2[i][k].fim = ocupado2[i][k+1].fim;
                                    }
                                    cont2[i]--; //um periodo a menos no vetor
                                    j--;
                                }

                                //se um periodo comecar antes ou quando outro acabar, vamos kunta-los
                                else if(ocupado2[i][j].comeco <= ocupado2[i][j-1].fim) {
                                    ocupado2[i][j-1].fim = ocupado2[i][j].fim;
                                    for(k=j; k <= cont2[i]-1; k++) {
                                        ocupado2[i][k].comeco = ocupado2[i][k+1].comeco;
                                        ocupado2[i][k].fim = ocupado2[i][k+1].fim;
                                    }
                                    cont2[i]--; //um periodo a menos no vetor
                                    j--;
                                }
                            }

                            //calculo dos tempos disponiveis
                            for(j=0; j <= cont2[i]+1; j++) {
                                /* No geral, os periodos disponiveis sao o intervalo entre o final de
                                um periodo ocupado e comeco do seguinte.
                                Para que o algoritmo seja generico, o primeiro periodo sera sempre
                                o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
                                tiver duracao 0, ele sera ignorado)
                                A mesma logica se aplica ao ultimo periodo disponivel. */

                                if(j==0) {
                                    disp2[i][j].comeco = 0;
                                    disp2[i][j].fim = ocupado2[i][j].comeco;
                                }
                                else if(j == cont2[i]+1) {
                                    disp2[i][j].comeco = ocupado2[i][j-1].fim;
                                    disp2[i][j].fim = 24*60;
                                }
                                else {
                                    disp2[i][j].comeco = ocupado2[i][j-1].fim;
                                    disp2[i][j].fim = ocupado2[i][j].comeco;
                                }
                            }

                            switch(i) {
                                case dom:
                                    fprintf(fp, "\nDOMINGO\n");
                                    break;
                                case seg:
                                    fprintf(fp, "\nSEGUNDA-FEIRA\n");
                                    break;
                                case ter:
                                    fprintf(fp, "\nTERCA-FEIRA\n");
                                    break;
                                case qua:
                                    fprintf(fp, "\nQUARTA-FEIRA\n");
                                    break;
                                case qui:
                                    fprintf(fp, "\nQUINTA-FEIRA\n");
                                    break;
                                case sex:
                                    fprintf(fp, "\nSEXTA-FEIRA\n");
                                    break;
                                case sab:
                                    fprintf(fp, "\nSABADO\n");
                            }

                            fprintf(fp, "Periodos de tempo disponiveis:\n");
                            for(j=0; j <= cont2[i]+1; j++) {
                                duracao[j] = disp2[i][j].fim - disp2[i][j].comeco;

                                if(duracao[j] != 0) { //para excluir periodos nulos
                                    fprintf(fp, "> %02d:%02.0f - %02d:%02.0f\n", disp2[i][j].comeco/60, (disp2[i][j].comeco/60.0 - disp2[i][j].comeco/60)*60, disp2[i][j].fim/60, ((disp2[i][j].fim/60.0) - (disp2[i][j].fim/60))*60);
                                    fprintf(fp, "  Duracao: %02d:%02.0f\n", duracao[j]/60, (duracao[j]/60.0 - duracao[j]/60)*60);
                                }
                                else if(j==1)
                                    fprintf(fp, "Nenhum\n");
                            }
                        }
                        
                        fclose(fp);
                        break;
                    }
                }
            }
        }
    }

    return 0;
}