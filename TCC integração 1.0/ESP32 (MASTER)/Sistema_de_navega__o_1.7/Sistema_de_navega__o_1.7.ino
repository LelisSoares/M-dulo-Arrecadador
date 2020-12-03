/*
  códigos de valores para moedas:
  
  *moeda de 5 cents   = 1 
  *moeda de 10 cents  = 2
  *moeda de 25 cents  = 3
  *moeda de 50 cents  = 4
  *moeda de 1 real    = 5

  códigos de valores para cédulas:
  
  *cédula de 2 R$   = a
  *cédula de 5 R$   = b 
  *cédula de 10 R$  = c 
  *cédula de 20 R$  = d 
  *cédula de 50 R$  = e 
  *cédula de 100 R$ = f 
 
 */



#include <ESP32Lib.h>
#include <Ressources/CodePage437_8x14.h>
#include <Ressources/CodePage437_8x19.h>
#include <Ressources/CodePage437_9x16.h>

//pin configuration               
const int redPin = 14;            // vermelho/laranja
const int greenPin = 19;          // verde riscado/verde
const int bluePin = 27;           // branco/azul
const int hsyncPin = 32;          // verde/cinza
const int vsyncPin = 33;          // laranja/amarelo

//VGA Device
VGA3Bit vga;
void tela_Menu();
void tela_Alimentos();
void tela_Roupas();
void tela_Monetaria();
void tela_Brindes();
void tela_Agradecimento();
void tela_Erro(int a);
int indicadores(int a);
void tela_aguarde();
int confirma_dados(int tela);
char espera_dados;
bool finalizar_confirma_dados = 1;

float moeda = 0;
float cedula = 0;
int brinde = 0;

//================INSTRUÇÔES==========================
int Ntela = 0;            //tela_Menu()           = 1    
                          //tela_Alimentos()      = 2
                          //tela_Roupas()         = 3   
                          //tela_Monetaria()      = 4
                          //tela_Brindes()        = 5
                          //tela_Agradecimento()  = 6
                          //tela_Erro()           = 7
                          //void tela_aguarde()   = 8
bool pisca = 0;           
char sorriso = 2;
int intervalo = 500;
//====================================================
unsigned long ta = 0;

#define BT3 21
#define BT4 18

bool bt3 = 0;
bool bt4 = 0;
bool bt4_ejetar_finalizar = 0;
bool restringe_acesso = 0;
bool aguarda_fim = 0;
bool trava = 0;
bool habilita_dados_do_validador = 0; 
byte tela_atual = 0;


void setup()
{
  Serial.begin(115200);
  pinMode(BT3,INPUT);
  pinMode(BT4,INPUT);
  vga.init(vga.MODE640x400, redPin, greenPin, bluePin, hsyncPin, vsyncPin);
  tela_Menu();
}

void loop(){

  ta = millis();

//===========INICIO=====================Chama tela_Monetaria()=========
  if(digitalRead(BT3)==1&&restringe_acesso==0){                  
     delay(200);
          while(1){
          if(digitalRead(BT3)==0){bt3=1;break;}
          }
  }
  if(bt3==1){
    vga.clear();
    confirma_dados(5);
    bt3=0;
    habilita_dados_do_validador = 1; 
  }
//===========FIM==========================Chama tela_Monetaria()=========

//===========INICIO=====================Chama tela_Brindes(), finaliza ou ejeta=========
  if(digitalRead(BT4)==1){                  
     delay(200);
          while(1){
          if(digitalRead(BT4)==0){bt4=1;break;}
          }
  }
  if(bt4==1){
    if(bt4_ejetar_finalizar==1&&trava==0){
      vga.clear();
      tela_Agradecimento();
      delay(3000);
      vga.clear();
      confirma_dados(1);
      bt4=0;
      trava=1;
    }
    if(bt4_ejetar_finalizar==0&&trava==0){
      vga.clear();
      confirma_dados(4);
      bt4=0;
      trava=1;
      habilita_dados_do_validador = 1; 
    }
    
  }
//===========FIM==========================Chama tela_Brindes(), finaliza ou ejeta=========
  if(ta%intervalo==0&&Ntela!=0){
    indicadores(Ntela);
  }

  if(habilita_dados_do_validador==0){
    moeda=0;cedula=0;brinde=0;
  }

  if(Serial.available()!=0&&habilita_dados_do_validador==1){
    char m = Serial.read();
    if(m =='a'){
      if(tela_atual==4){
        cedula+=2;
        tela_Monetaria();
      }
      if(tela_atual==5){
        cedula+=2;
        tela_Brindes();
      }
    }
    if(m =='b'){
      if(tela_atual==4){
        cedula+=5;
        tela_Monetaria();
      }
      if(tela_atual==5){
        cedula+=5;
        tela_Brindes();
      }
    }
    if(m =='c'){
      if(tela_atual==4){
        cedula+=10;
        tela_Monetaria();
      }
      if(tela_atual==5){
        cedula+=10;
        tela_Brindes();
      }
    }
    if(m =='d'){
      if(tela_atual==4){
        cedula+=20;
        tela_Monetaria();
      }
      if(tela_atual==5){
        cedula+=20;
        tela_Brindes();
      }
    }
    if(m =='e'){
      if(tela_atual==4){
        cedula+=50;
        tela_Monetaria();
      }
      if(tela_atual==5){
        cedula+=50;
        tela_Brindes();
      }
    }
    if(m =='f'){
      if(tela_atual==4){
        cedula+=100;
        tela_Monetaria();
      }
      if(tela_atual==5){
        cedula+=100;
        tela_Brindes();
      }
    }

    if(m =='1'){
      if(tela_atual==4){
        moeda+=0.05;
        tela_Monetaria();
      }
      if(tela_atual==5){
        moeda+=0.05;
        tela_Brindes();
      }
    }
    if(m =='2'){
      if(tela_atual==4){
        moeda+=0.1;
        tela_Monetaria();
      }
      if(tela_atual==5){
        moeda+=0.1;
        tela_Brindes();
      }
    }
    if(m =='3'){
      if(tela_atual==4){
        moeda+=0.25;
        tela_Monetaria();
      }
      if(tela_atual==5){
        moeda+=0.25;
        tela_Brindes();
      }
    }
    if(m =='4'){
      if(tela_atual==4){
        moeda+=0.5;
        tela_Monetaria();
      }
      if(tela_atual==5){
        moeda+=0.5;
        tela_Brindes();
      }
    }
    if(m =='5'){
      if(tela_atual==4){
        moeda+=1;
        tela_Monetaria();
      }
      if(tela_atual==5){
        moeda+=1;
        tela_Brindes();
      }
    }
    
  }
  
  trava=0;
}
//---------------------------------------------------------------------------//1
void tela_Menu(){
  indicadores(Ntela=1);
  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0, 0,0)); 
  vga.setCursor(225,20);  
  vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0)); 
  vga.println("   MODULO ARRECADADOR");  
  
  vga.setTextColor(vga.RGB(255, 255, 0), vga.RGB(0,0,255)); 
  vga.setCursor(60,70);
  vga.println("Doar alimentos. ");
  vga.setCursor(60,150);
  vga.println("Doar roupas.    ");
  vga.setCursor(60,230);
  vga.println("Doar dinheiro.  ");  
  vga.setCursor(60,310);
  vga.println("Comprar brindes.");
}
//---------------------------------------------------------------------------//2
void tela_Alimentos(){
  indicadores(Ntela=2);
  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0, 0,0)); 
  vga.setCursor(225,20);  
  vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0)); 
  vga.println("   MODULO ARRECADADOR"); 
  vga.setCursor(265,50);  
  vga.setTextColor(vga.RGB(255, 255, 0), vga.RGB(0,0,255)); 
  vga.println("Doar alimentos");   
  

  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0,0,0)); 
  vga.setCursor(300-40,180);
  vga.println("TOTAL:");

  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(0,250 , 0), vga.RGB(0,0,0)); 
  vga.setCursor(355-40,180);
  vga.print(0);
  vga.println(" itens");
 
  vga.setTextColor(vga.RGB(240, 240, 240), vga.RGB(255,0,0)); 
  vga.setCursor(60,310);
  vga.println("Finalizar.");
}
//---------------------------------------------------------------------------//3
void tela_Roupas(){
  indicadores(Ntela=3);
  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0, 0,0)); 
  vga.setCursor(225,20);  
  vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0)); 
  vga.println("   MODULO ARRECADADOR"); 
  vga.setCursor(270,50);  
  vga.setTextColor(vga.RGB(255, 255, 0), vga.RGB(0,0,255)); 
  vga.println("Doar Roupas");   
  

  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0,0,0)); 
  vga.setCursor(300-40,180);
  vga.println("TOTAL:");

  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(0,250 , 0), vga.RGB(0,0,0)); 
  vga.setCursor(355-40,180);
  vga.print(0);
  vga.println(" itens");
   
  vga.setTextColor(vga.RGB(240, 240, 240), vga.RGB(255,0,0)); 
  vga.setCursor(60,310);
  vga.println("Finalizar.");
}
//---------------------------------------------------------------------------//4
void tela_Monetaria(){
  indicadores(Ntela=4);
  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0, 0,0)); 
  vga.setCursor(225,20);  
  vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0)); 
  vga.println("   MODULO ARRECADADOR");  
  vga.setCursor(270,50);  
  vga.setTextColor(vga.RGB(255, 255, 0), vga.RGB(0,0,255)); 
  vga.println("Doar dinheiro");  
  

  vga.setFont(CodePage437_8x14);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0,0,0)); 
  vga.setCursor(100,100);
  vga.println("Moeda:");  
  vga.setCursor(380,100);
  vga.println("Cedula:"); 
  vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,128)); 
  vga.setCursor(180,100);
  vga.print(moeda);
  vga.println(" R$");
  vga.setCursor(470,100);
  vga.print(cedula);
  vga.println(" R$");

  vga.setTextColor(vga.RGB(0,255,255), vga.RGB(0,0,0)); 
  vga.setCursor(315,100);
  vga.print("|");

  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0,0,0)); 
  vga.setCursor(300-40,180);
  vga.println("TOTAL:");

  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(0,250 , 0), vga.RGB(0,0,0)); 
  vga.setCursor(355-40,180);
  vga.print(cedula+moeda);
  vga.println(" R$");
   
  vga.setTextColor(vga.RGB(240, 240, 240), vga.RGB(255,0,0)); 
  vga.setCursor(60,310);
  vga.println("Finalizar.");
}
//---------------------------------------------------------------------------//5
void tela_Brindes(){
  brinde=(moeda+cedula)/5;
  if(brinde>=1){
      vga.clear();indicadores(Ntela=100);
      vga.setTextColor(vga.RGB(240, 240, 240), vga.RGB(0,255,0)); 
      vga.setCursor(60,310);
      vga.println("Ejetar e finalizar.");
  }
  else{indicadores(Ntela=5);
  vga.setTextColor(vga.RGB(240, 240, 240), vga.RGB(255,0,0)); 
  vga.setCursor(60,310);
  vga.println("Finalizar.");
  }
  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0, 0,0)); 
  vga.setCursor(225,20);  
  vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0)); 
  vga.println("   MODULO ARRECADADOR"); 
  vga.setCursor(261,50);  
  vga.setTextColor(vga.RGB(255, 255, 0), vga.RGB(0,0,255)); 
  vga.println("Comprar brindes");
  vga.setCursor(260,80);  
  vga.setTextColor(vga.RGB(0, 255, 0), vga.RGB(0,0,0)); 
  vga.println("Brinde = 5,00 R$");   
  

  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0,0,0)); 
  vga.setCursor(300-40,140);
  vga.println("TOTAL:");

  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(0,250 , 0), vga.RGB(0,0,0)); 
  vga.setCursor(355-40,140);
  vga.print(cedula+moeda);
  vga.println(" R$");



  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(230, 230, 250), vga.RGB(0,0,0)); 
  vga.setCursor(300-40,180);
  vga.println("TOTAL:");

  vga.setFont(CodePage437_8x19);
  vga.setTextColor(vga.RGB(0,250 , 0), vga.RGB(0,0,0)); 
  vga.setCursor(355-40,180);
  vga.print(brinde);
  vga.println(" Brindes");

  
}
//---------------------------------------------------------------------------//6
void tela_Agradecimento(){                                                 
  indicadores(Ntela=0);
  vga.setFont(CodePage437_8x19);
  vga.setCursor(225,90);  
  vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0)); 
  vga.println("    Muito Obrigado!"); 

  vga.setFont(CodePage437_8x19);
  vga.setCursor(190,130);  
  vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,255)); 
  vga.println("Sua ajuda e' muito importante!");  
}
//---------------------------------------------------------------------------//7
void tela_Erro(int a){                                                     
  vga.setFont(CodePage437_8x19);
  vga.setCursor(300,70);  
  vga.setTextColor(vga.RGB(255, 255, 255), vga.RGB(255,0,0)); 
  vga.println("Erro"); 
}
//---------------------------------------------------------------------------//8
void tela_aguarde(){
  indicadores(Ntela=8);
  vga.setFont(CodePage437_8x19);
  vga.setCursor(225,130);  
  vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0)); 
  vga.println("  Por favor aguarde!"); 
}

int confirma_dados(int tela){

  tela_aguarde();
  if(tela==4){
    Serial.write('I');
    espera_dados = 'i';
  }
  if(tela==5){
    Serial.write('C');
    espera_dados = 'g';
  }
  if(tela==1){
    Serial.write('Z');
    espera_dados = 'z';
  }

  while(finalizar_confirma_dados==1){
    ta=millis();
    if(ta%intervalo==0&&Ntela!=0){
    indicadores(Ntela);
    }
    
    if(Serial.available()!=0){
      char l = Serial.read();
        if(l=='i'){
          if(tela==4){
            vga.clear(); tela_Brindes(); tela_atual=5;
            restringe_acesso = 1; bt4_ejetar_finalizar = 1; 
            finalizar_confirma_dados=0;
          }
        }

        if(l=='g'){
          if(tela==5){
            vga.clear(); tela_Monetaria(); tela_atual=4;
            restringe_acesso = 1; bt4_ejetar_finalizar = 1;
            finalizar_confirma_dados=0;
          }
        }
        if(espera_dados=='z'){
          if(tela==1){
            vga.clear(); tela_Menu();
            restringe_acesso = 0; bt4_ejetar_finalizar = 0;
            finalizar_confirma_dados=0;
            habilita_dados_do_validador = 0; 
            moeda=0; brinde=0;
          }
          
        }
      
    }
  }
  finalizar_confirma_dados=1;
}


int indicadores(int a){
  
  if(a==1){
    if(pisca==0){vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0));}
    else{vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,255,0)); }
    vga.setCursor(40,70);
    vga.println(" ");
    vga.setCursor(40,150);
    vga.println(" ");
    vga.setCursor(40,230);
    vga.println(" ");
    vga.setCursor(40,310);
    vga.println(" ");
  }

  if(a==2||a==3||a==4||a==5){
    if(pisca==0){vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0));}
    else{vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(255,0,0)); }
    vga.setCursor(40,310);
    vga.println(" ");
  }

  if(a==8){
    vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0));
    if(pisca==1){
      vga.setCursor(260,160);
      vga.println("                      ");
    }

    else{
      vga.setCursor(260,160);
      vga.println(sorriso);
      vga.setCursor(310,160);
      vga.println(sorriso);
      vga.setCursor(360,160);
      vga.println(sorriso);
    }
  }

  if(a==100){
    if(pisca==0){vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,0,0));}
    else{vga.setTextColor(vga.RGB(255, 140, 0), vga.RGB(0,255,0)); }
    vga.setCursor(40,310);
    vga.println(" ");
  }


  pisca=!pisca;
}
