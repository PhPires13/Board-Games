# BOARD-GAMES

#### Observações:
- O projeto foi desenvolvido principalmente em sistemas Unix (Linux, MacOS), então está melhor otimizado e testado para os mesmos.

---
## Descrição
- Esse projeto é uma interface de jogos de tabuleiro via terminal, utilizando Paradigma Orientado a Objetos com C++ 11.
- Também possui controle de jogadores e manutenção de estatística.

---
## Funcionamento
- É exibido um menu inicial com as opções disponíveis de comandos.
```
Obs.:
?: parametros opcionais
?!: parametros que podem ser opcionais ou nao dependendo do restante do contexto
R: reversi, tabuleiro: quadrado, par, min 4x4   L: lig4, tabuleiro: min 4x4     V: velha, tabuleiro: 3x3

------------------------------------ MENU ------------------------------------
CJ: Cadastrar Jogador (<Apelido> <Nome> <? Simbolo>)
EJ: Editar Jogador (<Apelido> <Atributo: [N|S]> <?! Novo Valor>)
RJ: Remover Jogador (<Apelido>)
LJ: Listar Jogadores (<? Ordem: [A|N]>)
EP: Executar Partida (<Jogo: (R|L|V)> <Apelido Jogador 1> <Apelido Jogador 2> <? Altura Tabuleiro> <? Largura Tabuleiro>)
FS: Finalizar Sistema

> 
```
- Os comandos em si e os parâmetros com opções pre-definidas, são case-insensitive.
- Porém, os demais parâmetros são case-sensitive.
- Parâmetros opcionais são marcados com ``?``, como descrito, então se não enviados será utilizado um valor padrão.
- Parâmetros que podem ser opcionais ou não, dependendo do contexto, são marcados com ``?!``, por exemplo ao editar o símbolo deixando vazio ele é removido.
- Também são exibidas regras na hora de passar os parâmetros.
- Exemplos de comandos:
  - Cadastrar Jogador: ``CJ joaozinho Joao da Silva *`` ou ``CJ joaozinho Joao da Silva``
  - Editar Jogador: ``EJ joaozinho N Joao da Silva`` ou ``EJ joaozinho S *`` ou ``EJ joaozinho S``
  - Remover Jogador: ``RJ joaozinho``
  - Listar Jogadores: ``LJ`` ou ``lj`` ou ``LJ A`` ou ``lj a`` ou ``LJ N``
  - Executar Partida: ``EP R joaozinho mariazinha`` ou ``EP R joaozinho mariazinha 4 4`` ou ``EP R joaozinho mariazinha 4``

---
## Extras
- ### 1 Jogo da Velha
- ### 2 Símbolo customizado do jogador
  - Ao criar um jogador é possível que este escolha um símbolo para representá-lo no tabuleiro.
  - Com isso também é necessário tratar quais os símbolos válidos, e caso dois jogadores estejam com mesmo símbolo, mudar paar os padrões.
- ### 3 Tabuleiro de tamanho customizado
  - É possível escolher as proporções do tabuleiro, desde que se obedeça às regras de cada jogo, caso contrário é usado o tamanho padrão.
- ### 4 Cores no terminal
  - Para melhor legibilidade, foram utilizadas cores no menu que facilitam a interpretação do usuário.
  - Também foram utilizadas cores nos jogos para uma interfaçe mais lúdica e agradável.
- ### 5 Editar Jogador
  - Foi implementada a funcionalidade de editar um jogador, podendo alterar o nome ou o símbolo, e até remover o símbolo.
- ### 6 Cobertura de testes
  - Foi realizada a análise de cobertura de testes, um extra, mesmo que não solicitado.

---
## Como executar
- Existem arquivos preparados para realizar a compilação e execução das funções do projeto.
- Localizados na pasta raiz do projeto e conforme o sistema operacional:
  - <b>Unix</b>: ``.sh``
  - <b>Windows</b>: ``.bat``


- Se necessário pode ser realizada a execução manual dos comandos internos aos arquivos, porém a mesma NÃO é recomendada, pois pode causar conflitos com os arquivos de armazenamento.

- ### Programa
  - Basta executar alguns dos arquivos ``run``
    - <b>Unix</b>: ```./run.sh```
    - <b>Windows</b>: ```run.bat```

- ### Testes
  - Basta executar alguns dos arquivos ``test``
    - <b>Unix</b>: ```./test.sh```
    - <b>Windows</b>: ```test.bat```

- ### Clean
  - Em caso de necessidade de reset dos arquivos gerados pela compilação, basta executar alguns dos arquivos ``clean``
    - <b>Unix</b>: ```./clean.sh```
    - <b>Windows</b>: ```clean.bat```

- #### Documentar e Cobertura
  - O script para documentar e gerar a cobertura de testes está disponível em caso de necessidade.
    - <b>Unix</b>: ```./document.sh```
    - <b>Unix</b>: ```./coverage.sh```
  - É necessário ter o ``doxygen`` e ``gcovr`` instalados para a execução dos seus respectivos.
---
## Documentação
- ### Código
  - A documentação do código foi gerada utilizando a ferramenta Doxygen.
  - Para acessar basta abrir o arquivo ``index.html`` localizado na pasta ``docs/html``.
- ### Cartão Classe Responsabilidades Colaboradores (CRC)
  - A documentação CRC foi gerada utilizando a ferramenta CRC Card Builder (http://groups.umd.umich.edu/cis/tinytools/cis375/f19/team7/index.html).
  - Para acessar basta abrir o arquivo ``crc.pdf`` localizado na pasta ``docs``.
- ### Cobertura de Testes
  - A documentação da cobertura de testes foi gerada utilizando a ferramenta ``gcovr``.
  - Para acessar basta abrir o arquivo ``relatorio.html`` localizado na pasta ``coverage``.
  - Obs.: a porcentagem de cobertura não consegue ser muito alta devido a considerar grande quantidade de trechos não testáveis, 
  como main e a própria biblioteca de teste, mas os arquivos necessários possuem uma cobertura de testes muito alta. 

---
## Estrutura
- ### Pastas
  - A estrutura do projeto foi dividida em pastas, conforme a seguir:
    - root: contém os arquivos de configuração do projeto.
    - ``src``: contém os arquivos-fontes do projeto.
    - ``include``: contém os arquivos de cabeçalho do projeto.
    - ``tests``: contém os arquivos de teste do projeto.
    - ``docs``: contém a documentação do projeto.
    - ``coverage``: contém a cobertura de testes do projeto.
    - ``bin``: contém os arquivos binários gerados pela compilação do projeto.
    - ``obj``: contém os arquivos intermediários gerados pela compilação do projeto.
    - ``third-party``: contém bibliotecas de terceiros utilizadas no projeto.
  - obs.: dentro de ``bin`` e ``obj`` foram criados o subdiretório ``tests`` para melhorar a organização e separação para compilação e execução do programa e do teste.

- ### Classes
  - A estrutura do projeto foi dividida em classes, conforme a seguir:
    - ``Baord``: classe para executar ações sobre um tabuleiro, desconexo de qualquer ideia de jogo.
    - ``Player``: classe para armazenar informações de um jogador e gerenciar persistência dos mesmos.
    - ``BoardGame``: classe genérica com ideia simples de jogo
      - Possui um ``Board`` e executa ações sobre ele,
      - Possui 2 ``Player`` que participam do jogo.
    - ``Reversi``: classe filha de ``BoardGame`` especializada para o jogo reversi.
    - ``ConnectFour``: classe filha de ``BoardGame`` especializada para o jogo lig4.
    - ``TicTacToe``: classe filha de ``BoardGame`` especializada para o jogo velha.
    - ``Manager``: classe com métodos estáticos para gerenciar a execução do programa.
    - ``Utils``: classe com métodos estáticos de auxílio.
    - ``exceptions``: classes de exceções personalizadas, para padronizar mensagens.

- ### Tests
  - Cada classe possui um arquivo de teste com um ``TEST_SUITE`` próprio.
  - Dentro de cada ``TEST_SUITE`` os métodos são agrupados em ``TEST_CASE`` por codependência. 

---
## Funcionamento
- O programa roda em loop em cima da funcionalidade do ``manager::menu()`` a qual chama respectivas funções para os comandos, 
  cuidando também do seu tratamento de exceções.
- Essas funções por sua vez, tratam uma parte dos dados para encaminhar para o correto procedimento.
- ``CRUD Player``: após tratamento descrito acima, Sào chamas as funções da classe ``Player`` para completar o procedimento.
- ``Executar Partida``: após tratamento descrito acima, é escolhido qual jogo será executado, 
então armazenado em um ponteiro da classe genérica para o correto funcionamento do <i> Dynamic Dispatch </i>
é chamada então a função ``playGame()``, e após o resultado são atualizadas as estatísticas dos jogadores.

---
## Principais Desafios
- Consertar input bagunçado do usuário
- Lidar com parâmetros opcionais, uma vez que sua disposição pode variar.
- Entender como jogar Reversi rsrsrs.
- Realizar tests que dependeriam da interação do usuário.

---
## Requisitos
- ### Compilador g++
  - Linux: ```sudo apt install g++```