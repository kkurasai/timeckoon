#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

typedef int horario;

typedef struct periodo {
    horario comeco;
    horario fim;
} periodo;

enum diaSemana {dom, seg, ter, qua, qui, sex, sab};
typedef enum diaSemana diaSemana;

void banner();
int validadorDeHorario(char comando[]);
char validadorMiniMenu();
void lerDias(diaSemana dias[7], int qtdDias);
void horarioDeSono(int comecoDia[7], int fimDia[7], periodo ocupado[7][MAX], int cont[7], int dia);
void selectSort(periodo ocupado[7][MAX], int cont[7], int dia);
void selectSortMesmoComeco(periodo ocupado[7][MAX], int cont[7], int dia);
void removerPeriodosRedundantes(periodo ocupado[7][MAX], int cont[7], int dia);
void tempoDisponivel(periodo ocupado[7][MAX], periodo disp[7][MAX], int cont[7], int dia);
void output(periodo disp[7][MAX], int cont[7], int dia);

int main() {

    FILE * fp;

    horario hora, comecoDia[7], fimDia[7];
    periodo ocupado[7][MAX], disp[7][MAX];
    diaSemana diaInserir, dias[7];
    int i, j, k, qtdDias, cont[7], duracao[MAX];
    char opcao, diaString[20], diaAnterior[20];

    while(1) {
        //inicializando variaveis
        for(i=0; i<MAX; i++)
            duracao[i]=0;
        for(i=0; i<7; i++) {
            cont[i] = comecoDia[i] = fimDia[i] = 0;
            for(j=0; j<MAX; j++)
                ocupado[i][j].comeco = ocupado[i][j].fim = disp[i][j].comeco = disp[i][j].fim = 0;
        }
              
        //menu geral
        system("cls");
        banner();
        printf("[0] Sair do programa\n");
        printf("[1] Calcular horarios disponiveis em um dia qualquer\n");
        printf("[2] Calcular horarios disponiveis em uma semana\n");

        opcao = validadorMiniMenu();
     
        //sair do programa
        if(opcao=='0')
            break;


        //menu de dia unico
        else if(opcao=='1') {        
            while(1) {
                system("cls");
                banner();
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
                        printf("\nOpcao invalida! Por favor, insira novamente.\n");
                }

                //sair do menu
                if(opcao=='0')
                    break;

                //definir inicio e fim do dia
                else if(opcao=='1') {
                    comecoDia[0] = validadorDeHorario("Digite o horario do inicio do dia: ");
                    fimDia[0] = validadorDeHorario("Digite o horario do fim do dia: ");
                }                
                
                //inserir um periodo de tempo ocupado
                else if(opcao=='2') {
                    while(1) {
                        ocupado[0][cont[0]].comeco = validadorDeHorario("Digite o horario do inicio do periodo: ");
                        ocupado[0][cont[0]].fim = validadorDeHorario("Digite o horario do fim do periodo: ");

                        //validador do periodo
                        if(ocupado[0][cont[0]].comeco >= ocupado[0][cont[0]].fim)
                            printf("\nPeriodo invalido! Por favor, insira novamente.\n");
                        else {
                            cont[0]++;
                            break;
                        }
                    }
                }
                
                //calcular horarios disponiveis
                else if(opcao=='3') {

                    horarioDeSono(comecoDia, fimDia, ocupado, cont, 0);

                    selectSort(ocupado, cont, 0);

                    selectSortMesmoComeco(ocupado, cont, 0);
                    
                    removerPeriodosRedundantes(ocupado, cont, 0);

                    tempoDisponivel(ocupado, disp, cont, 0);

                    output(disp, cont, 0);
                    
                    printf("\n");
                    system("pause");
                    break;
                }
            
                //criar arquivo com horarios disponiveis
                else if(opcao=='4') {

                    horarioDeSono(comecoDia, fimDia, ocupado, cont, 0);

                    selectSort(ocupado, cont, 0);

                    selectSortMesmoComeco(ocupado, cont, 0);

                    removerPeriodosRedundantes(ocupado, cont, 0);
                    
                    tempoDisponivel(ocupado, disp, cont, 0);

                    fp=fopen("horarios.txt", "w");

                    fprintf(fp, "Periodos de tempo disponiveis:\n");
                    for(int i=0; i <= cont[0] + 1; i++) {
                        duracao[i] = disp[0][i].fim - disp[0][i].comeco;

                        if(duracao[i] != 0) { //para excluir periodos nulos
                            fprintf(fp, "> %02d:%02.0f - %02d:%02.0f\n", disp[0][i].comeco/60, (disp[0][i].comeco/60.0 - disp[0][i].comeco/60)*60, disp[0][i].fim/60, (disp[0][i].fim/60.0 - disp[0][i].fim/60)*60);
                            fprintf(fp, "  Duracao: %02d:%02.0f\n", duracao[i]/60, (duracao[i]/60.0 - duracao[i]/60)*60);
                        }
                        else if(i==1)
                            fprintf(fp, "Nenhum\n");
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
                banner();
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
                        printf("\nOpcao invalida! Por favor, insira novamente.\n");
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
                            
                    opcao = validadorMiniMenu();

                    if(opcao=='0')
                        continue;
                    
                    //lendo os dias os dias, caso for definir para dias especificos
                    if(opcao=='2') {
                        //quantidade de dias
                        printf("\nQuantidade de dias: ");
                        scanf("%d", &qtdDias);

                        lerDias(dias, qtdDias);
                    }

                    hora = validadorDeHorario("Digite o horario do inicio do dia: ");

                    //se for para todos os dias
                    if(opcao=='1')
                        for(i=0; i<7; i++)
                            comecoDia[i] = hora;
                    //se for para dias especificos
                    else
                        for(i=0; i<qtdDias; i++)
                            comecoDia[dias[i]] = hora;

                    hora = validadorDeHorario("Digite o horario do fim do dia: ");

                    //se for para todos os dias
                    if(opcao=='1')
                        for(i=0; i<7; i++)
                            fimDia[i] = hora;
                    //se for para dias especificos
                    else
                        for(i=0; i<qtdDias; i++)
                            fimDia[dias[i]] = hora;
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
                            printf("\nDia da semana invalido! Por favor, insira novamente.\n");
                    }
                }

                //inserir um periodo de tempo ocupado
                else if(opcao=='3') {
                    while(1) {
                        //caso um dia nao tiver sido escolhido previamente
                        if(diaInserir==10) {
                            printf("\nVoce precisa escolher o um dia primeiro!\n");
                            system("pause");
                            break;
                        }

                        ocupado[diaInserir][cont[diaInserir]].comeco = validadorDeHorario("Digite o horario do inicio do periodo: ");

                        hora = validadorDeHorario("Digite o horario do fim do periodo: ");

                        //validador de periodo
                        if(ocupado[diaInserir][cont[diaInserir]].comeco >= hora)
                            printf("\nPeriodo invalido! Por favor, insira novamente.\n");
                        else {
                            ocupado[diaInserir][cont[diaInserir]].fim = hora;
                            cont[diaInserir]++;
                            break;
                        }
                    }
                }
                
                //mostrar horarios disponiveis
                else if(opcao=='4') {
                    printf("\n[0] Sair do menu\n");
                    printf("[1] Dias especificos\n");
                    printf("[2] Semana inteira\n");

                    opcao = validadorMiniMenu();

                    if(opcao=='0')
                        continue;
                    
                    //dias especificos
                    if(opcao=='1') {
                        //quantidade de dias
                        printf("\nQuantidade de dias: ");
                        scanf("%d", &qtdDias);

                        lerDias(dias, qtdDias);

                        for(i=0; i<qtdDias; i++) {
                            horarioDeSono(comecoDia, fimDia, ocupado, cont, dias[i]);

                            selectSort(ocupado, cont, dias[i]);

                            selectSortMesmoComeco(ocupado, cont, dias[i]);
                            
                            removerPeriodosRedundantes(ocupado, cont, dias[i]);

                            tempoDisponivel(ocupado, disp, cont, dias[i]);

                            output(disp, cont, dias[i]);
                        }
                        printf("\n");
                        system("pause");
                    }
                
                    //semana inteira
                    else if(opcao=='2') {
                        for(i=0; i<7; i++) {
                            horarioDeSono(comecoDia, fimDia, ocupado, cont, i);

                            selectSort(ocupado, cont, i);

                            selectSortMesmoComeco(ocupado, cont, i);
                            
                            removerPeriodosRedundantes(ocupado, cont, i);

                            tempoDisponivel(ocupado, disp, cont, i);

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

                            output(disp, cont, i);
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

                    opcao = validadorMiniMenu();

                    if(opcao=='0')
                        continue;

                    //dias especificos
                    else if(opcao=='1') {
                        //quantidade de dias
                        printf("\nQuantidade de dias: ");
                        scanf("%d", &qtdDias);

                        lerDias(dias, qtdDias);

                        for(i=0; i<qtdDias; i++) {
                            horarioDeSono(comecoDia, fimDia, ocupado, cont, dias[i]);

                            selectSort(ocupado, cont, dias[i]);

                            selectSortMesmoComeco(ocupado, cont, dias[i]);
                            
                            removerPeriodosRedundantes(ocupado, cont, dias[i]);

                            tempoDisponivel(ocupado, disp, cont, dias[i]);

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
                            for(int i=0; i <= cont[dias[i]] + 1; i++) {
                                duracao[i] = disp[dias[i]][i].fim - disp[dias[i]][i].comeco;

                                if(duracao[i] != 0) { //para excluir periodos nulos
                                    fprintf(fp, "> %02d:%02.0f - %02d:%02.0f\n", disp[dias[i]][i].comeco/60, (disp[dias[i]][i].comeco/60.0 - disp[dias[i]][i].comeco/60)*60, disp[dias[i]][i].fim/60, (disp[dias[i]][i].fim/60.0 - disp[dias[i]][i].fim/60)*60);
                                    fprintf(fp, "  Duracao: %02d:%02.0f\n", duracao[i]/60, (duracao[i]/60.0 - duracao[i]/60)*60);
                                }
                                else if(i==1)
                                    fprintf(fp, "Nenhum\n");
                            }
                            
                            fclose(fp);
                        }
                        break;
                    }
                
                    //semana inteira
                    else if(opcao=='2') {
                        fp=fopen("horarios_semana.txt", "w");
                        for(i=0; i<7; i++) {
                            
                            horarioDeSono(comecoDia, fimDia, ocupado, cont, i);

                            selectSort(ocupado, cont, i);

                            selectSortMesmoComeco(ocupado, cont, i);
                            
                            removerPeriodosRedundantes(ocupado, cont, i);

                            tempoDisponivel(ocupado, disp, cont, i);

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
                            for(int j=0; j <= cont[i] + 1; j++) {
                                duracao[j] = disp[i][j].fim - disp[i][j].comeco;

                                if(duracao[j] != 0) { //para excluir periodos nulos
                                    fprintf(fp, "> %02d:%02.0f - %02d:%02.0f\n", disp[i][j].comeco/60, (disp[i][j].comeco/60.0 - disp[i][j].comeco/60)*60, disp[i][j].fim/60, (disp[i][j].fim/60.0 - disp[i][j].fim/60)*60);
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

void banner() {
    printf("88888888888 d8b                                 888\n");
    printf("    888     Y8P                                 888\n");
    printf("    888                                         888\n");
    printf("    888     888 88888b.d88b.   .d88b.   .d8888b 888  888  .d88b.   .d88b.  88888b.\n");
    printf("    888     888 888 \"888 \"88b d8P  Y8b d88P\"    888 .88P d88\"\"88b d88\"\"88b 888 \"88b\n");
    printf("    888     888 888  888  888 88888888 888      888888K  888  888 888  888 888  888\n");
    printf("    888     888 888  888  888 Y8b.     Y88b.    888 \"88b Y88..88P Y88..88P 888  888\n");
    printf("    888     888 888  888  888  \"Y8888   \"Y8888P 888  888  \"Y88P\"   \"Y88P\"  888  888\n\n\n");
    printf("\tUma calculadora de tempos disponiveis entre os membros de um grupo!\n\n\n");
}

int validadorDeHorario(char comando[]) {
    int h, min;
    while(1) {
        printf("\n%s", comando);
        scanf("%d:%d", &h, &min);
        if(h*60+min>=0 && h*60+min<=24*60)
            break;
        else
            printf("\nHorario invalido! Por favor, insira novamente.\n");
    }                        
    return h*60 + min;
}

char validadorMiniMenu() {
    char opcao;
    while(1) {
        printf("\nOpcao: ");
        scanf(" %c", &opcao);
        if(opcao=='0'||opcao=='1'||opcao=='2')
            return opcao;                                
        else
            printf("\nOpcao invalida! Por favor, insira novamente.\n");
    }
}

void lerDias(diaSemana dias[7], int qtdDias) {
    char diaString[20], diaAnterior[20];
    for(int i=0; i<qtdDias; ) {
        printf("\nDia %d: ", i+1);
        fflush(stdin);
        gets(diaString);
        if(i>0 && stricmp(diaString, diaAnterior)==0)
            printf("\nDia da semana repetido! Por favor, insira novamente.\n");
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
            printf("\nDia da semana invalido! Por favor, insira novamente.\n");

        strcpy(diaAnterior, diaString);
    }
}

void horarioDeSono(int comecoDia[7], int fimDia[7], periodo ocupado[7][MAX], int cont[7], int dia) {
    /* No programa, o dia eh um periodo linear de 00:00 a 23:59.
       Se o dia da(s) pessoa(s) acabar depois de 00:00 e comecar depois disso, 
       seu tempo de sono pode ser considerado um bloco de tempo ocupado.
       Ja se o dia acabar antes de 23:59 e comecar depois das 00:00, serao dois
       blocos: de 00:00 até o comeco do dia e do fim do dia ate 23:59. */
    
    if(comecoDia[dia] > fimDia[dia]) {
        ocupado[dia][cont[dia]].comeco = fimDia[dia];
        ocupado[dia][cont[dia]].fim = comecoDia[dia];
    }
    else if(comecoDia[dia] < fimDia[dia]) {
        ocupado[dia][cont[dia]].comeco = fimDia[dia];
        ocupado[dia][cont[dia]].fim = 24*60;
        cont[dia]++;
        ocupado[dia][cont[dia]].comeco = 0;
        ocupado[dia][cont[dia]].fim = comecoDia[dia];
    }
}

void selectSort(periodo ocupado[7][MAX], int cont[7], int dia) {
    int menor, aux, posicaoMenor, i, j;
    for(i=0; i <= cont[dia]-1; i++) {
        menor = 100000;
        for(j=i; j <= cont[dia]; j++) {
            if(ocupado[dia][j].comeco < menor) {
                menor = ocupado[dia][j].comeco;
                posicaoMenor = j;
            }
        }            
        aux = ocupado[dia][i].comeco;
        ocupado[dia][i].comeco = ocupado[dia][posicaoMenor].comeco;
        ocupado[dia][posicaoMenor].comeco = aux;

        aux = ocupado[dia][i].fim;
        ocupado[dia][i].fim = ocupado[dia][posicaoMenor].fim;
        ocupado[dia][posicaoMenor].fim = aux;
    }
}

void selectSortMesmoComeco(periodo ocupado[7][MAX], int cont[7], int dia) {
    int i, j, k, numRepetidos, menor, posicaoMenor, aux;
    for(i=0; i <= cont[dia]; i += numRepetidos+1) {
        numRepetidos = 0;
        for(j = i+1; j <= cont[dia]; j++)
            if(ocupado[dia][j].comeco == ocupado[dia][i].comeco)
                numRepetidos++;

        for(j=i; j <= i+numRepetidos-1; j++) {
            menor = 100000;
            for(k=i; k <= i+numRepetidos; k++) {
                if(ocupado[dia][k].fim < menor) {
                    menor = ocupado[dia][k].fim;
                    posicaoMenor = k;
                }
            }            
            aux = ocupado[dia][j].fim;
            ocupado [dia][j].fim = ocupado[dia][posicaoMenor].fim;
            ocupado [dia][posicaoMenor].fim = aux;
        }
    }
}

void removerPeriodosRedundantes(periodo ocupado[7][MAX], int cont[7], int dia) {
    int i, j;
    for(i = 1; i <= cont[dia]; i++) {
        //se um periodo estiver contido em outro, vamos exclui-lo
        if(ocupado[dia][i].comeco > ocupado[dia][i-1].comeco && ocupado[dia][i].fim < ocupado[dia][i-1].fim) {
            for(j=i; j <= cont[dia] - 1; j++) {
                ocupado[dia][j].comeco = ocupado[dia][j+1].comeco;
                ocupado[dia][j].fim = ocupado[dia][j+1].fim;
            }
            cont[dia]--; //um periodo a menos no vetor
            i--;
        }

        //se um periodo comecar antes ou quando outro acabar, vamos iunta-los
        else if(ocupado[dia][i].comeco <= ocupado[dia][i-1].fim) {
            ocupado[dia][i-1].fim = ocupado[dia][i].fim;
            for(j=i; j <= cont[dia] - 1; j++) {
                ocupado[dia][j].comeco = ocupado[dia][j+1].comeco;
                ocupado[dia][j].fim = ocupado[dia][j+1].fim;
            }
            cont[dia]--; //um periodo a menos no vetor
            i--;
        }
    }
}

void tempoDisponivel(periodo ocupado[7][MAX], periodo disp[7][MAX], int cont[7], int dia) {
    for(int i=0; i <= cont[dia] + 1; i++) {
        /* No geral, os periodos disponiveis sao o intervalo entre o final de
           um periodo ocupado e comeco do seguinte.
           Para que o algoritmo seja generico, o primeiro periodo sera sempre
           o intervalo entre 00:00 e o comeco do proximo periodo (se o intervalo
           tiver duracao 0, ele sera ignorado)
           A mesma logica se aplica ao ultimo periodo disponivel. */

        if(i==0) {
            disp[dia][i].comeco = 0;
            disp[dia][i].fim = ocupado[dia][i].comeco;
        }
        else if(i == cont[dia] + 1) {
            disp[dia][i].comeco = ocupado[dia][i-1].fim;
            disp[dia][i].fim = 24*60;
        }
        else {
            disp[dia][i].comeco = ocupado[dia][i-1].fim;
            disp[dia][i].fim = ocupado[dia][i].comeco;
        }
    }
}

void output(periodo disp[7][MAX], int cont[7], int dia) {
    int duracao[MAX];
    printf("\nPeriodos de tempo disponiveis:\n");
    for(int i=0; i <= cont[dia] + 1; i++) {
        duracao[i] = disp[dia][i].fim - disp[dia][i].comeco;

        if(duracao[i] != 0) { //para excluir periodos nulos
            printf("> %02d:%02.0f - %02d:%02.0f\n", disp[dia][i].comeco/60, (disp[dia][i].comeco/60.0 - disp[dia][i].comeco/60)*60, disp[dia][i].fim/60, (disp[dia][i].fim/60.0 - disp[dia][i].fim/60)*60);
            printf("  Duracao: %02d:%02.0f\n\n", duracao[i]/60, (duracao[i]/60.0 - duracao[i]/60)*60);
        }
        else if(i==1)
            printf("Nenhum\n");
    }
}