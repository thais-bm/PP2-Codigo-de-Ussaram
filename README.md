
# Guerra em Tau: O código de Ussaram

Este Projeto tem o objetivo de exercitar minhas habilidades em:

* Codificar um ou mais dos tipos abstratos de dados **LISTAS, PILHAS, FILAS e TABELAS HASH** (com possıveis combinações entre eles) em C++
* solucionar problemas empregando estas estruturas de dados.
* Desenvolver codigo de qualidade com boas pŕaticas de programacao: boa indentação, boa nomeação, refinamentos sucessivos, POO (exceto heranca), programacão genérica, etc.

* Aprender a lidar com desenvolvimento de software em equipe.

# Descrição do problema

**Ano 4001 da Terceira Era de Tau.**

A guerra iniciada pela traição dos ardilosos Ianteco persiste sangrenta. Milhões de vidas do povo Azuri foram perdidas sob o ataque impiedoso das forças Ianteco e seus escravos Umashi, tornando a intenção de paz dos Azuri um sonho distante.

Porém, uma nova esperança pode estar a caminho: após uma missão desesperada da Inteligência Azuri, a nobre comandante Ion-Ur descobriu como quebrar o intricado código criptográfico das comunicações militares dos Ianteco, conhecido por **Código de Ussaran**!

A Real Academia de Ciências Computacionais dos Azuri convocou você e sua equipe para desenvolver um programa para quebrar o Código de Ussaran e ajudar os Azuri a ganhar alguma vantagem sobre os inimigos Ianteco e Umashi, antecipando suas movimentações hostis.

O inimigo cifra suas mensagens empregando o Código de Ussaran, técnica desenvolvida por Urta Ussaran, gênio das ciências Ianteco. O Código de Ussaran oculta uma mensagem secreta dentro de uma estrutura de dados **fila**, embaralhando seus caracteres por meio da aplicação das operações de **enfileiramento** e **desenfileiramento** de caracteres sobre a mensagem.

Porém, estas operações ficam espalhadas aleatoriamente em linhas de código de programas Ianteco!

Observe o programa Ianteco, abaixo, codificado no alfabeto Ianteco, o que o torna ilegível para os Azuri.

```
:.:---:
------:...:|.:.|::|.::..|::|..:::---..|
------:...:|.:.|::|.::..|::|..:::---:::
------:...:|.:.|::|.::..|::|..:::---:.|

:::---:
------:...:|.:.|::|.::..|::|..:::---:::
------:.:
------::.:...|.:...:|.:.|::|.::..|::|..:::
------::.:...|.:...:|.:.|::|.::..|::|..:::
------:...:|.:.|::|.::..|::|..:::---.||

.::---:
------:...:|.:.|::|.::..|::|..:::---:::
------:...:|.:.|::|.::..|::|..:::---..|
------::.:...|.:...:|.:.|::|.::..|::|..:::
------:::

--.---:
------:...:|.:.|::|.::..|::|..:::----.-
------:...:|.:.|::|.::..|::|..:::---:.|
------.::
------:...:|.:.|::|.::..|::|..:::---:..
------::.:...|.:...:|.:.|::|.::..|::|..:::

~
```

Entretanto, os agentes da comandante Ion-Ur conseguiram roubar um **dicionário Ianteco-Azuri**, descrito na **Figura 1**. Portanto, o programa Ianteco, após passar por um processo de **tradução** para o idioma Azuri, fica como mostra a **Figura 2** (os números de linhas foram introduzidos para facilitar o entendimento do rastreamento do programa).

No programa Ianteco traduzido, **Z, A, B** e **C** são procedimentos que não recebem parâmetros. O procedimento **Z** (linha 19) sempre será o primeiro a ser executado (semelhante à função `main` na linguagem C/C++), e o símbolo **\~** (linha 26) indica o **fim do programa**.

Os únicos três comandos possíveis em um procedimento são:

---


## **(a) Chamada a um outro procedimento**
Observe que o procedimento **Z** chama o procedimento **B** (linha 13), o procedimento **B** chama o procedimento **A** (linha 06), e este chama o procedimento **C** (linha 01). O procedimento **C** não possui chamada a nenhum outro procedimento.

Um procedimento sempre termina com uma **linha em branco**. Ao ser alcançado o fim de um procedimento **P**, o processamento deve retornar para o procedimento que chamou **P**, continuando na linha seguinte à linha da chamada de **P**.

---

## **(b) Comando `ENFILEIRA`.**
Este comando enfileira um caractere em uma **fila interna**.

---

## **(c) Comando `DESENFILEIRA`.**
Este comando desenfileira um caractere da **fila interna**.

---

### **Figura 1 - Dicionario Ianteco-Azuri**


 **#** | **Ianteco** | **Azuri** | **#** | **Ianteco** | **Azuri** | **#** | **Ianteco** | **Azuri** 
---|---|---|---|---|---|---|---|---
 **1** | `:::` | A | 14 | `.:\|`   | N | 27 | `---` | espaco em branco 
 **2** | `.::`   | B | 15 | `\|:.`   | O | 28 | `~` | `~` 
 **3** | `:.:`   | C | 16 | `:\|.`   | P | 29 | `:␣␣` | `:␣␣` 
 **4** | `::.`   | D | 17 | `:.\|` | Q |  |  |  
 **5** | `:..`   | E | 18 | `\|..`   | R |  |  |  
 **6** | `.:.`   | F | 19 | `.\|.` | S |  |  |  
 **7** | `..:`   | G | 20 | `..\|`   | T |  |  |  
 **8** | `...`   | H | 21 | `.\|\|`   | U |  |  |  
 **9** | `\|::`   | I | 22 | `\|.\|`   | V |  |  |  
 **10** | `:\|:`   | J | 23 | `\|\|.`   | W |  |  |  
 **11** | `::\|`   | K | 24 | `-.-`   | X |  |  |  
 **12** | `\|.:`   | L | 25 | `.--`   | Y |  |  |  
 **13** | `.\|:` | M | 26 | `--.`   | Z |  |  |  


---

Agora, finalmente, você verá o que acontece com a fila interna quando este programa é executado. Aqui, a fila está representada por **\[a1, a2, ..., an]**, onde **a1** é o primeiro da fila, **an** é o último da fila, e a fila vazia é indicada por **\[]**. Veja a execução e o estado da fila na **Figura 3**. A mensagem secreta é **“ATAQUE”**. Veja que só é possível descobrir esta mensagem executando o programa Ianteco traduzido!

Você e sua equipe devem criar e codificar um programa que:

  1. Receba um programa Ianteco e o traduza para seu correspondente no idioma Azuri, utilizando o dicionário Ianteco-Azuri;
  1. Execute o programa traduzido para descobrir e imprimir a mensagem secreta contida na fila interna do programa.

Assim, você quebrará o terrível Código de Ussaran e ajudará o povo Azuri a retomar a supremacia sobre a Joia do Touro: o pequeno planeta Tau.

# Entrada e saída

A entrada do seu programa será um programa Ianteco codificado com os símbolos alienígenas do alfabeto Ianteco. Isto é, uma grande string.

Para controlar as chamadas a procedimentos no programa Ianteco, você deverá programar uma pilha dinâmica. Para implementar a fila interna do programa Ianteco traduzido, você deverá programar uma fila dinâmica. Para implementar o dicionário Ianteco-Azuri, você deverá programar uma tabela hash com resolução de colisão por encadeamento (o tamanho da tabela e a função de hash serão repassados pelo professor). As listas de colisão devem guardar pares do tipo: (símbolo-Ianteco, símbolo-Azuri). Você pode usar listas, filas, pilhas e tabelas hash adicionais se achar necessário. Isso dependerá de como você conceberá a sua solução para o problema.

A saída será a impressão da mensagem secreta. Esta mensagem será uma frase com uma ou mais palavras.

### Figura 2: Programa Ianteco Traduzido

```
01 C :
02 ENFILEIRA T
03 ENFILEIRA A
04 ENFILEIRA Q
05
06 A :
07 ENFILEIRA A
08 C
09 DESENFILEIRA
10 DESENFILEIRA
11 ENFILEIRA U
12
13 B :
14 ENFILEIRA A
15 ENFILEIRA T
16 DESENFILEIRA
17 A
18
19 Z :
20 ENFILEIRA X
21 ENFILEIRA Q
22 B
23 ENFILEIRA E
24 DESENFILEIRA
25
26 ~
```

# Requisitos do Projeto
## 1. Ferramentas e Técnicas

O projeto deve ser codificado em **C++20**.  
Será permitido **programação procedural**, mas todas as estruturas de dados (TADs) principais **devem ser programadas orientadas a objeto**, **generalizadas (templates)** e **encapsuladas**.

### Figura 3: Execução do Programa Ianteco Traduzido

| Fila        | Procedimento, linha | Comando/Ação                         |
|-------------|---------------------|--------------------------------------|
| `[]`        | proc. Z, linha 19   | fila inicia vazia                    |
| `[]`        | proc. Z, linha 20   | enfileira “X”                        |
| `[X]`       | proc. Z, linha 21   | enfileira “Q”                        |
| `[XQ]`      | proc. Z, linha 22   | chama proc. B                        |
| `[XQ]`      | proc. B, linha 13   | -                                    |
| `[XQ]`      | proc. B, linha 14   | enfileira “A”                        |
| `[XQA]`     | proc. B, linha 15   | enfileira “T”                        |
| `[XQAT]`    | proc. B, linha 16   | desenfileira, sai “X”                |
| `[QAT]`     | proc. B, linha 17   | chama proc. A                        |
| `[QAT]`     | proc. A, linha 06   | -                                    |
| `[QAT]`     | proc. A, linha 07   | enfileira “A”                        |
| `[QATA]`    | proc. A, linha 08   | chama proc. C                        |
| `[QATA]`    | proc. C, linha 01   | -                                    |
| `[QATA]`    | proc. C, linha 02   | enfileira “T”                        |
| `[QATAT]`   | proc. C, linha 03   | enfileira “A”                        |
| `[QATATA]`  | proc. C, linha 04   | enfileira “Q”                        |
| `[QATATAQ]` | fim proc. C, linha 05 | retorna para proc. A              |
| `[QATATAQ]` | proc. A, linha 09   | desenfileira, sai “Q”                |
| `[ATATAQ]`  | proc. A, linha 10   | desenfileira, sai “A”                |
| `[TATAQ]`   | proc. A, linha 11   | enfileira “U”                        |
| `[TATAQU]`  | fim proc. A, linha 12 | retorna para proc. B              |
| `[TATAQU]`  | fim proc. B, linha 18 | retorna para proc. Z              |
| `[TATAQU]`  | proc. Z, linha 23   | enfileira “E”                        |
| `[TATAQUE]` | proc. Z, linha 24   | desenfileira, sai “T”                |
| `[ATAQUE]`  | fim proc. Z, linha 25 | -                                 |
| `[ATAQUE]`  | linha 26            | fim do programa                      |



## 2. Padrões de Codificação

- Siga o **CamelCase do Java** como padrão de nomeação de identificadores.
- A **indentação** e **posicionamento de chaves** deve seguir o padrão **K&R, variante de Stroustrup**  (mais informações: [Indent Style - Wikipedia](https://en.wikipedia.org/wiki/Indent_style#K.26R_style)).

## 4. Compilador

- Recomenda-se o uso do compilador **GCC - the GNU Compiler Collection**: [GCC-GNU](http://gcc.gnu.org)
- Ou sua variante [MINGW](https://sourceforge.net/projects/mingw/) para Microsoft Windows 
- Ou ainda o compilador **clang**: [clang.llvm.org](https://clang.llvm.org)
- Sempre teste seu projeto em compiladores online, como: [https://cpp.sh](https://cpp.sh)  
- Às vezes, o projeto pode funcionar bem na sua máquina, mas apresentar erros em outros compiladores.

## 5. Bibliotecas e Funções

Sua equipe **não deve utilizar nenhuma estrutura de dados pronta** (listas, pilhas, filas, vectors, etc.) da **Standard Template Library (STL)** ou de qualquer outra biblioteca C++.

É suficiente o uso dos seguintes cabeçalhos:

```cpp
#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
```

# 6. Mais requisitos

- Implementação de fila com implementação dinâmica
- Implementação de pilha com implementação dinâmica
- Implementação de tabela hash com resolução de colisões por encadeamento
- Não uso de recursividade
- Uso da linguagem C++ (C++20)
- Uso das bibliotecas iostream e cstdlib (uso optativo de cctype e cstring)
- Uso correto de funções e parâmetros por valor e/ou referência; 
- uso de ponteiros, constantes, referências, templates, classes C++; 
- não uso de variáveis globais
- Uso de POO (classes e templates) para os TADs
- Estilo de código e indentação como descrito acima

# 
## Autores do Desafio

- Professor Flavio Coelho

