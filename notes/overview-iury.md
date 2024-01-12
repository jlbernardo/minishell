# Fluxo geral do minishell
---
author: iury
date: 2023-12-02

---

Neste documento busco verbalizar meu entendimento, sempre provisório, do fluxo de funcionamento do minishell.

## Partes principais
O minishell é um programa que recebe uma string e executa os comandos contidos nessa string.
## 1. Parser
O Parser é composto de duas partes: lexer e parser.
### 1.1 Lexer
Componente responsável por por processar a string de input e retornar uma estrutura de dados (um array, uma lista linkada, etc) contendo tokens.

Um token é a menor unidade de algo que faz sentido para o shell. Existem diferentes tipos de tokens: 
- identificadores (nomes de variáveis);
- metacaracteres(caracteres que tem significado distinto do seu significado textual usual);
- operadores;
- pontuação (parênteses e outros meios de agrupamento);
- _literals_ (valores contantes: strings ou números, por exemplo);

### 1.2 Parser
Usualmente, este componente é responsável por, de posse da lista de tokens, organizá-los em uma hierarquia comumente chamada de _Abstract Syntax Tree_. No entanto, como nosso minishell não implementa as funcionalidades relacionadas à linguagem de programação shell, nosso parser tem um objetivo mais modesto: reconhecer a estrutura de comandos (por exemplo identificando o nome do comando, flags e outros argumentos) e identificar eventuais redirecioanamentos.

## 2. Executor
De posse de uma estrutura de dados que contenha os comandos, argumentos e redirecionamentos, o papel do Executor é o que está explícito em seu nome: executar os comandos.

Caso o comando seja um builtin, o executor chama, no próprio processo do minishell, uma função programada por nós.
Caso o comando seja um software feito por uma _third-party_, o executor provavelmente faz uso de fork e execve para executar softwares que não são programados por nós. A resolução de PATH (uma lista de diretórios) se dá nesta parte.

## 3. Subsistemas
Finalmente, as outras partes de um shell são encapsuladas em subsistemas. Podemos dividir esses em algumas categorias:
- Variáveis de ambiente
- Wildcards
- subshells

Variáveis de ambiente são aquelas que podemos setar, unsetar e utilizar seus valores após realizarmos suas expansões (uma expansão nada mais é que substituir um token do tipo identificador por um token adequado do tipo literal).

Wildcards são metacaracteres cuja expansão resultado em, possivelmente, mais de um literal.

Subshells são comandos que são executados em um processo filho e cujo output é passado para o processo pai.

## Roadmap

### Primeira proposta
Acho que faz sentido começar o desenvolvimento do minishell de trás pra frente.

1. Codar dois builtins:
    1.1 echo
    1.2 pwd
2. Codar um protótipo de parser que:
    2.1 Reconheça e popule uma estrutura de dados com os builtins desenvolvidos;
3. Codar um executor que rode builtins:
    3.1 Execute os builtins feitos e retorne o prompt;
    3.2 Mostre uma mensagem de erro caso o parser não reconheça nenhum dos builtins ou exista algum erro na sintaxe deles.
