# Descrição (Módulo Arrecadador)
Este projeto tem como objetivo desenvolver uma máquina de coleta capaz de interagir com o usuário e receber diversos de donativos, como roupas, alimentos não-perecíveis, dinheiro, livros entre outros.
O módulo arrecadador é um trabalho inspirado nos projetos de captação de recursos, sendo sites, dispositívos e/ou aplicativos que captam e repassam recursos para instituições filantrópicas, ONGs, 
causas sociais, animais e ambientais. Exemplos desses projetos são o Dipjar e o GoodBox. Abaixo é possível ver a ultima versão do módulo arrecadador.  

![ezgif com-gif-maker](https://user-images.githubusercontent.com/75312838/103468280-39e7d700-4d36-11eb-90fc-1b968b94aad9.gif)

Para que o projeto seja capaz de realizar o que se propõe, conta com diferentes sistemas para tarefaz específicas. Como motrado no GIF acima, os sistemas são: o sistema de navegação, responsável por ser a IHM; o sistema de recebimento não-monetário, responsável por receber donativos como roupas, alimentos não perecíveis entre outros; o sistema de validação monetária, que recebe os valores financeiros da moeda nacional e o sistema dispensador de brindes, responável por retornar algo para o doador. Abaixo segue o esquemático geral do trabalho, bem como de cada sistema.

# Esquemático geral do trabalho

![Diagrama da integração do projeto 3](https://user-images.githubusercontent.com/75312838/103486239-2b073000-4ddb-11eb-97f1-232428b81571.png)

# Sistemas de navegação

O sistema de navegação tem por finalidade servir de interface entre o usuário e a máquina, permitindo que o usuário acesse as funções do projeto, como doação de itens não-monetários, doação monetária e recebimento de brindes. O sistema é composto por um monitor LCD, quatro botões normalmente abertos (NA) e a placa ESP-32. As Figura mostram o circuito do sistema.

![sistema de navegação](https://user-images.githubusercontent.com/75312838/103486359-02336a80-4ddc-11eb-895b-620597ddd540.jpg)

