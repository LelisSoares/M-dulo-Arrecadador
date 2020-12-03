
// constantes/variaveis/funções = Malha Ejetora de Brindes (INICIO)============================ 
/*
Requisito de Software:
*não pode ejetar mais que 21 itens;
*deve manter atualizada a quantidade de itens;
*caso o numero de itens a serem ejetados ultrapasse o numero do estoque, o dispensador deve informar quantos itens pode ejetar e assim fazer;
*
*quando o Arduino mega receber 'p' da serial ele deve ejetar um item e enviar 'p' para p ESP32
*/
#define ENABLE          22
#define RESET           24
#define PASSO           26
#define SENTIDO         28

#define FIM_DE_CURSO    30
#define FIM_DE_CURSO2   32
#define ITENS_ESTOQUE   34

#define minuto  60*1000000
unsigned int ppv =  200;

// RPM = 60/tempo_de_passo*200;
// tempo_de_passo=60/RPM*200;

// Sentido para frente = digitalWrite(SENTIDO,0);
// Sentido para trás   = digitalWrite(SENTIDO,1);

int itens = 1;
int total_de_itens = 19;
int ejetados = 0;
int restante = 0;

int NEMA_17(int RPM,int itens);

// constantes/variaveis/funções = Malha Ejetora de Brindes (FIM)============================


// constantes/variaveis/funções = Malha de Validação Monetária (INICIO)============================ 
#define MOEDA 13
#define CEDULA 12
#define RELE 50
#define T 2000
//controle de bug (inicia contando 1 Real)
byte primeiro_bug = 0; 

unsigned long tiM,taM;
bool key1M = 1;
bool primeiro_pulsoM = 0;
byte contM = 0;
byte cont_geralM = 0;
float total = 0;

unsigned long tiC;
bool key1C = 1;
bool primeiro_pulsoC = 0;
byte contC = 0;
byte cont_geralC = 0;

int validador();
byte malha_monetaria_ativa=0;
// constantes/variaveis/funções = Malha de Validação Monetária (FIM)============================ 

int brinde =0;

void setup() {
  Serial.begin(115200);
  pinMode(MOEDA,INPUT_PULLUP);
  pinMode(CEDULA,INPUT_PULLUP);
  pinMode(ENABLE,OUTPUT);
  pinMode(RESET,OUTPUT);
  pinMode(PASSO,OUTPUT);
  pinMode(SENTIDO,OUTPUT);
  pinMode(RELE,OUTPUT);
  pinMode(FIM_DE_CURSO,INPUT_PULLUP);
  pinMode(FIM_DE_CURSO2,INPUT_PULLUP);
//PROCEDIMENTO DE ROTINA=========(Malha Ejetora)==================  
  digitalWrite(RESET, LOW);     
  delay(1);              
  digitalWrite(RESET, HIGH); 
  delay(10); 

//PROCEDIMENTO DE ROTINA=========(Malha Ejetora)==================     
   //   Serial.print("Estoque: ");
     // Serial.print(total_de_itens);
      //Serial.println(" itens.");
      digitalWrite(ENABLE,1);
      delay(5000);

}

void loop() {
  brinde = total/5;

  if(Serial.available()!=0){
    char l = Serial.read();
    if(l=='C'){                               //===ATIVA MALHA EJETORA
      digitalWrite(RELE,1);
      delay(5000);
      Serial.write('g');
      malha_monetaria_ativa=2;
    }  
    if(l=='I'){                                 
      digitalWrite(RELE,1);
      delay(5000);
      Serial.write('i');
      malha_monetaria_ativa=3;
    }
    if(l=='Z'){
       total = 0;
       digitalWrite(RELE,0);
       Serial.write('z');
       malha_monetaria_ativa=0;
       delay(1000);
    }  
     if(l=='E'){                          //Caractere para teste do sistema dispensador
       NEMA_17(80,1);
       malha_monetaria_ativa=0;
       delay(1000);
    }       

    //============Para a Malha Monetária====================
 
  }

  while(malha_monetaria_ativa!=0){
        validador();    
  }
}

int NEMA_17(int RPM,int itens){

  if(ejetados==21)return 0;
  unsigned int tempo_de_passo= 0;
  tempo_de_passo= minuto/(ppv*RPM);
  
  digitalWrite(ENABLE,0);
  
  for(int i = 1; i <= itens; i++){
    
    
    while(digitalRead(FIM_DE_CURSO)==0){
      digitalWrite(SENTIDO,1);
      digitalWrite(PASSO,1);
      digitalWrite(PASSO,0);
      delayMicroseconds(tempo_de_passo);
      
      if(Serial.available()!=0){
        char l = Serial.read();
        if(l=='c'){
          //Serial.println("OPERACAO CANCELADA!");
          delay(2000);
          return 0;
        }
      }
      
    }
      delay(500);
      
   ejetados++;
   restante = total_de_itens-ejetados;
   
   /*Serial.print("Itens ejetado: ");
   Serial.println(ejetados);
   Serial.print("Restante: ");
   Serial.println(restante);*/
  
  }
  
 for(int x = 0; x<75; x++){
      digitalWrite(SENTIDO,0);
      digitalWrite(PASSO,1);
      digitalWrite(PASSO,0);
      delayMicroseconds(tempo_de_passo);
      
      if(Serial.available()!=0){
        char l = Serial.read();
        if(l=='c'){
          //Serial.println("OPERACAO CANCELADA!");
          delay(2000);
          return 0;
        }
      }
      
    }
      delay(1000);
      digitalWrite(ENABLE,1);
      //Serial.write('p');
}

int validador(){

   if(Serial.available()!=0){
     char l = Serial.read();
     if(l=='Z'){
       if((total/5)>=1&&malha_monetaria_ativa==3){
        brinde = total/5;
        total = 0;
        digitalWrite(RELE,0);
        NEMA_17(80,brinde); 
        Serial.write('z');
        malha_monetaria_ativa=0;
        delay(1000);
        return 0;
     }
       else{
        digitalWrite(RELE,0);
        Serial.write('z');
        malha_monetaria_ativa=0;
        delay(1000);
        total = 0;
        return 0;
       }
       
     }
   }
  taM = millis();
  /*
  Serial.print(digitalRead(MOEDA));Serial.print(" - ");
  Serial.print(contM);Serial.print(" - ");
  Serial.print(digitalRead(CEDULA));Serial.print(" - ");
  Serial.println(contC);*/
  Serial.println("   ");
  //Serial.print(total);
  //Serial.print(" R$");
 // Serial.println(" ");
  
  if(digitalRead(MOEDA)==1){

    if(key1M==1){
      contM++; tiM=taM;
    }

    if(primeiro_pulsoM==0)primeiro_pulsoM=1;
    
    key1M = 0;

  }

  else{key1M = 1;}

  if(primeiro_pulsoM==1 && taM-tiM>500){
    cont_geralM=contM;
    contM = 0;
    primeiro_pulsoM=0;
  }

  if(contM==0&&cont_geralM!=0){
    
    if(cont_geralM>2 && cont_geralM<=3){
      Serial.write('3');
      //Serial.println(" Moeda de 25 centavos    ");
      total+=0.25;
      cont_geralM=0;
      delay(T);
    }

    if(cont_geralM>4 && cont_geralM<=6){
      Serial.write('4');
      //Serial.println(" Moeda de 50 centavos    ");
      total+=0.5;
      cont_geralM=0;
      delay(T);
    }

    if(cont_geralM>6 && cont_geralM<=9){
      Serial.write('2');
      //Serial.println(" Moeda de 10 centavos    ");
      total+=0.1; 
      cont_geralM=0;
      delay(T);
    }

    if(cont_geralM==1){
      if(primeiro_bug==2){
        Serial.write('5');
        //Serial.println(" Moeda de 1 Real         ");
        total+=1;
        cont_geralM=0;
        delay(T);
      }
      if(primeiro_bug==0)primeiro_bug=1;
    }

  }

  if(primeiro_bug==1){total=0; primeiro_bug=2;}

//==============================================


  if(digitalRead(CEDULA)==1){

    if(key1C==1){
      contC++; tiC=taM;
    }

    if(primeiro_pulsoC==0)primeiro_pulsoC=1;
    
    key1C = 0;

  }

  else{key1C = 1;}

  if(primeiro_pulsoC==1 && taM-tiC>500){
    cont_geralC=contC;
    contC = 0;
    primeiro_pulsoC=0;
  }

  if(contC==0&&cont_geralC!=0){
    
    if(cont_geralC==2){
      Serial.write('a');
      //Serial.println(" Cedula de 2,00 R$      ");
      total+=2;
      cont_geralC=0;
      delay(T);
    }
    if(cont_geralC==5){
      Serial.write('b');
      //Serial.println(" Cedula de 5,00 R$      ");
      total+=5;
      cont_geralC=0;
      delay(T);
    }
    if(cont_geralC==10){
      Serial.write('c');
      //Serial.println(" Cedula de 10,00 R$     ");
      total+=10;
      cont_geralC=0;
      delay(T);
    }
    if(cont_geralC==20){
      Serial.write('d');
      //Serial.println(" Cedula de 20,00 R$     ");
      total+=20;
      cont_geralC=0;
      delay(T);
    }
    if(cont_geralC==50){
      Serial.write('e');
      //Serial.println(" Cedula de 50,00 R$     ");
      total+=50;
      cont_geralC=0;
      delay(T);
    }
    if(cont_geralC==100){
      Serial.write('f');
      //Serial.println(" Cedula de 100,00 R$    ");
      total+=100;
      cont_geralC=0;
      delay(T);
    }
    
  }
}
