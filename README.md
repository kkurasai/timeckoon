# Timeckoon

## Conceito
Projeto que visa facilitar reuniões entre os membros de uma equipe. Após informar os períodos de tempo em que os membros da equipe estão ocupados, você poderá saber quais são os períodos de tempo em que todos estão disponíveis.

## Recursos utilizados
O programa foi feito usando as bibliotecas stdio.h, stdlib.h e string.h da linguagem C.

## Passo a passo
(O projeto foi criado no primeiro semestre da faculdade, durante o processo aprendizado de programação em C)
1. Criação de um programa simples usando poucos recursos da linguagem, que tem menu simples, trabalha com um dia qualquer, usa como output o terminal e faz uso de comandos do terminal Windows.
2. Implementação do uso de arranjos multidimensionais e strings e criação do segundo menu, que possibilita trabalhar com uma semana inteira ou parte dela.
3. Implementação da manipulação de arquivos como forma de armazenamento permanente.
4. Implementação de recursos mais avançados da linguagem, como structs, typedef, enum, funções e procedimentos.
5. Aprimoramento da interface e limpeza do código.

## Instalação
1. Instale um compilador da linguagem C, como o MinGW.
2. Baixe a pasta compactada com o arquivo .c do repositório no GitHub.
3. Abra o terminal do Windows.
4. Abra o diretório em que está localizado o arquivo .c, digitando "cd ", clicando e arrastando a pasta até o terminal e apertando enter.
5. Compile o arquivo usando "gcc timeckoon.c -o timeckoon".
6. Execute o arquivo gerado digitando o nome do arquivo no terminal.

## Execução
Ao executar o programa, menu inicial aparecerá.

![imagem](https://github.com/kkurasai/timeckoon/blob/main/imagem01.jpg)!

Você poderá ir tanto para o menu que trabalha com um único dia quanto o que trabalha com vários dias de uma semana.

### Calcular horarios disponiveis em um dia qualquer
Selecionando o menu de dia único o seguinte menú aparecerá:

![imagem](https://github.com/kkurasai/timeckoon/blob/main/imagem02.jpg)

Neste menu você poderá definir o início (hora de acordar) e o fim (hora de dormir) do dia e horários ocupados.

Para imprimir os horários livres na tela, selecione "mostrar horários disponíveis".

![imagem](https://github.com/kkurasai/timeckoon/blob/main/imagem03.jpg)

Para criar um arquivo com os horários, selecione "criar arquivo com horários disponíveis".

### Calcular horarios disponiveis em uma semana
Selecionando o menu da semana o seguinte menú aparecerá:

![imagem](https://github.com/kkurasai/timeckoon/blob/main/imagem04.jpg)

Neste menu você poderá definir o inicio e o fim de dias especificos ou da semana inteira, definir o dia da semana cujos horários você irá inserir e inserir um período (é preciso ter um dia definido).

Para imprimir os horários livres na tela, selecione "mostrar horários disponíveis" e escolha entre imprimir os horários de dias específicos ou da semana inteira.

![imagem](https://github.com/kkurasai/timeckoon/blob/main/imagem05.jpg)

Para criar um arquivo com os horários, selecione "criar arquivo com horários disponíveis" e escolha entre horários de dias específicos ou da semana inteira.

## Bugs/problemas conhecidos
Devido ao uso de comandos do terminal Windows na execução do programa, ele não funciona bem em outros sistemas operacionais.

## Autor
Ryan Sakurai - estudante de Ciência da Computação na UFSCAR
