# Descrição (Módulo Arrecadador)
Este projeto tem como objetivo desenvolver uma máquina de coleta capaz de interagir com o usuário e receber diversos de donativos, como roupas, alimentos não-perecíveis, dinheiro, livros entre outros.
O módulo arrecadador é um trabalho inspirado nos projetos de captação de recursos, sendo sites, dispositívos e/ou aplicativos que captam e repassam recursos para instituições filantrópicas, ONGs, 
causas sociais, animais e ambientais. Exemplos desses projetos são o Dipjar e o GoodBox. Abaixo é possível ver a ultima versão do módulo arrecadador.  

![ezgif com-gif-maker](https://user-images.githubusercontent.com/75312838/103468280-39e7d700-4d36-11eb-90fc-1b968b94aad9.gif)

Para que o projeto seja capaz de realizar o que se propõe, conta com diferentes sistemas para tarefaz específicas. Como motrado no GIF acima, os sistemas são: o sistema de navegação, responsável por ser a IHM; o sistema de recebimento não-monetário, responsável por receber donativos como roupas, alimentos não perecíveis entre outros; o sistema de validação monetária, que recebe os valores financeiros da moeda nacional e o sistema dispensador de brindes, responável por retornar algo para o doador. Abaixo segue o esquemático geral do trabalho, bem como de cada sistema.

# Esquemático geral do trabalho

![Diagrama da integração do projeto 3](https://user-images.githubusercontent.com/75312838/103486239-2b073000-4ddb-11eb-97f1-232428b81571.png)

# Sistema de navegação

O sistema de navegação tem por finalidade servir de interface entre o usuário e a máquina, permitindo que o usuário acesse as funções do projeto, como doação de itens não-monetários, doação monetária e recebimento de brindes. O sistema é composto por um monitor LCD, quatro botões normalmente abertos (NA) e a placa ESP-32.Abaixo é posível visualizar o circuito do sistema.

![sistema de navegação](https://user-images.githubusercontent.com/75312838/103486359-02336a80-4ddc-11eb-895b-620597ddd540.jpg)

Dentre as ferramentas de controle VGA acessíveis na internet cabe aqui um destaque a biblioteca utilizada no projeto para criação das telas e interfaceamento homem/máquina, sendo esta, a biblioteca bitluni ESP32Lib para IDE Arduino da bitluni, criada por Matthias Balwierz. A biblioteca apresenta grande flexibilidade de exibição permitindo trabalhar com controle de 3 ou 14bits, ou seja 3 ou 14 saídas para o controle de cor (RGB) e resolução, contando ainda com exibição de elementos 3D e sprites. (BITLUNI, 2019).

A montagem utilizada para o controle VGA foi a montagem de 3 bits, sendo esta, a ligação mais simples que a biblioteca oferece e suficiente para exibição das informações desejadas. Por se tratar do método mais simples se utiliza de apenas um cabo VGA com uma saída macho e a própria ESP-32. A Figura mostra os detalhes da conexão entre a ESP-32 e o monitor LCD, através de um cabo VGA.

![conexão VGA](https://user-images.githubusercontent.com/75312838/103486486-0ad87080-4ddd-11eb-831c-be0eee93bcf8.jpg)

# Sistema de recebimento não-monetário

O sistema de recebimento não-monetário pode ser descrito como um armazenador automático. Consiste de um armazenador físico, semelhante a um baú, com duas rampas frontais onde os itens são depositados, nas Figuras pode ser visto seu esquema elétrico e sua constituição, respectivamente.

Para que o sistema de recebimento não-monetário funcione adequadamente ele deve abrir a rampa correspondente ao tipo de doação solicitada, realizar a contagem dos itens depositados e fechar as rampas quando for finalizado. Para tal, o sistema conta com 4 servomotores como atuadores, sendo dois, de maior torque, para a abertura e fechamento das rampas e 2, de menor torque, para o travamento; 4 sensores óticos, sendo 2 para realizar a contagem dos itens doados e 2 para verificação de segurança; 2 sensores indutivos, responsáveis pela sinalização do fim de curso das rampas para o controlador; circuito de alimentação e o Arduino Mega como controlador.   

![sistema de recebimento nãp-monetário](https://user-images.githubusercontent.com/75312838/103486622-ec26a980-4ddd-11eb-892e-3ca1ce94cde5.jpg)

# Sistema dispensador de brindes

Composta por um dispositivo dispensador, amplamente utilizado em máquinas de vendas de refrigerantes, lanches e conveniências; um motor de passo NEMA17, escolhido pelo seu torque e precisão, responsável por realizar o trabalho de movimentação dos itens; uma mola de movimentação; um driver A4988, sendo a interface de controle entre a plataforma controladora e o motor de passo; dois sensores óticos difusos responsáveis pelo reconhecimento dos itens dispensados e, por último, o Arduino Mega como sistema embarcado. A Figura 20 mostra o diagrama esquemático do sistema.

![Sistema dispensador de brindes](https://user-images.githubusercontent.com/75312838/103486749-df568580-4dde-11eb-98ef-df1b67a531e4.jpg)

# Sistema de validação monetária

Pensado para o recebimento da maioria dos valores monetários da moeda nacional, esse sistema de validação monetária conta com um validador de cédulas, um validador de moedas, circuitos de comunicação, um relé de alimentação e um sistema embarcado responsável pela leitura de sinais e tomada de decisão, sendo este o Arduino Mega; A Figura mostra o circuito esquemático deste sistema.

![sistema de validação monetária](https://user-images.githubusercontent.com/75312838/103486813-6146ae80-4ddf-11eb-9442-796f1de3883f.jpg)

Para que fosse possível realizar a leitura dos sinais dos componentes de validação monetária, foi necessário previamente conhecer o comportamento dos mesmos, bem como posteriormente desenvolver um circuito de interface entre os validadores e a placa microcontrolada, Arduino Mega.

O validador de cédula funciona a partir da identificação da cédula inserida pela fenda de abertura frontal, onde passa pelos sensores responsáveis pela validação da mesma, contudo uma vez identificada, o BV20 envia um número de pulsos equivalentes ao valor da nota, ou seja, 2 pulsos para a cédula de R$ 2,00, 5 pulsos para cédula de R$ 5,00 e assim sucessivamente até 100 pulsos para a cédula de R$ 100,00 (INNOVATIVE TECHNOLOGY, 2018, p. 36).

O validador de moedas MEC26 apresenta um comportamento semelhante ao BV20. Sua saída apresenta um número de pulsos distinto para cada valor de moeda, programados previamente pelo operador, e para o projeto as moedas de R$ 1,00, 50, 25 e 10 centavos apresentam respectivamente 1, 6, 3 e 9 pulsos (VINCE, 2017). 

Uma vez enviados os dados referentes aos valores monetários lidos, se torna necessário o recebimento e a interpretação deste sinal pela plataforma microcontrolada. A priori, para realizar a leitura do sinal do BV20, bem como do MEC26, foi utilizada uma entrada digital do Arduino com resistor de pull-up, porém este método se mostrou falho em muitas medições, pois, os validadores apresentaram um sinal de tensão de aproximadamente 1,2V para nível alto e 0V para nível baixo, estando abaixo do nível lógico do Arduino. Para converter o sinal para o mesmo nível lógico do Arduino foi utilizado um drive intermediário para comunicação, sendo este um comparador de tensão simples. A Figura 22 representa o circuito utilizado.

![circuito de integração dos validadores](https://user-images.githubusercontent.com/75312838/103486867-d6b27f00-4ddf-11eb-9803-2d0a6fde6d09.jpg)

# Hardware de integração entre a ESP-32 e o Arduino Mega 2560

O circuito de integração permite que todas as informações trocadas sejam transmitidas de forma segura e precisa, funciona como um elo, permitindo que todos os sistemas se comuniquem para que as funções sejam executadas de forma satisfatória.

O circuito trata-se de um conversor digital bidirecional de 5V para 3,3V e 3,3V para 5V. Sua utilização é necessária para que haja um correto nivelamento de tensão na comunicação entre a ESP-32 e o Arduino Mega 2560, uma vez que as saídas digitais da ESP-32 apresentam um nível de tensão de 3,3V e o Arduino mega uma nível de 5V.















