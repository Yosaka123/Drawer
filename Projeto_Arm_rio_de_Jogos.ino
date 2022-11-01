#include <Wire.h> //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA DO DISPLAY LCD
#include <Keypad.h> //INCLUSÃO DE BIBLIOTECA - Teclado Matricial
#include <Adafruit_Fingerprint.h> //INCLUSÃO DA BIBLIOTECA DO SENSOR
#include <EEPROM.h> //INCLUSÃO DA BIBLIOTECA PARA USO DA EEPROM
#include <SPI.h>
#include <SD.h>

File gavetas;

#define Password_Lenght 4
#define const_Cadastro 20

#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

char Data[Password_Lenght];
byte data_count = 0;

unsigned int auxiliartemporizador = millis();
float i = 15;
int auxiliar_confirmar;

//========================TECLADO MATRICIAL=====================================================
const byte qtdLinhas = 4; //QUANTIDADE DE LINHAS DO TECLADO
const byte qtdColunas = 3; //QUANTIDADE DE COLUNAS DO TECLADO

//CONSTRUÇÃO DA MATRIZ DE CARACTERES
char matriz_teclas[qtdLinhas][qtdColunas] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
 
byte PinosqtdLinhas[qtdLinhas] = {5,6,7,8}; //PINOS UTILIZADOS PELAS LINHAS
byte PinosqtdColunas[qtdColunas] = {2,3,4}; //PINOS UTILIZADOS PELAS COLUNAS
//========================TECLADO MATRICIAL===================================================== 

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE); //ENDEREÇO DO I2C E DEMAIS INFORMAÇÕES
Keypad meuteclado = Keypad(makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas); 
Keypad tecladoAdmin = Keypad(makeKeymap(matriz_teclas), PinosqtdLinhas, PinosqtdColunas, qtdLinhas, qtdColunas); 

void welcome_lcd(){
  lcd.setCursor(8,1);
  lcd.print("Ola!");
  delay(3000);
  lcd.clear();
  lcd.setCursor(2,1);
  lcd.print("Armario de jogos");
  delay(3000);
  lcd.clear();
  lcd.setCursor(3,1);
  lcd.print("Tenha uma boa");
  lcd.setCursor(4,2);
  lcd.print("experiencia");
  delay(3000);
  lcd.clear();
}

void DISPLAY_AGUARDANDO_DIGITAL(){
  lcd.setCursor(5,1); //SETA A POSIÇÃO DO CURSOR
  lcd.print("Aguardando");
  lcd.setCursor(6,2);
  lcd.print("digital.");
}

void display_biometria(){
  lcd.setCursor(0,1); //SETA A POSIÇÃO DO CURSOR
  lcd.print("Insira o codigo da ");
  lcd.setCursor(0,2);
  lcd.print("gaveta: ");
}

void processo_liberar_gaveta(){
  display_biometria();
  char tecla_pressionada = meuteclado.getKey(); //VERIFICA SE ALGUMA DAS TECLAS FOI PRESSIONADA
  
  if (tecla_pressionada){ //SE ALGUMA TECLA FOR PRESSIONADA, FAZ
    //Serial.print("Tecla pressionada : "); //IMPRIME O TEXTO NO MONITOR SERIAL
    //Serial.println(tecla_pressionada); //IMPRIME NO MONITOR SERIAL A TECLA PRESSIONADA
   
   if(tecla_pressionada != '#'){
     int calculo;
     calculo = 8 + data_count;
     lcd.setCursor(calculo, 2);
     Data[data_count] = tecla_pressionada; 
     lcd.print(Data[data_count]);
     //Serial.println(Data[data_count]);
     data_count++;  
     if(calculo > 13){
       clearData();
     }
   } 
  }
  switch(tecla_pressionada){
    case '*':
    clearData();
    break;
    case '#':
    auxiliar_confirmar = 1;
    confirmar();
    break;
  }
  if((millis() - auxiliartemporizador) >= 1000){
    if(i > 0){
      auxiliartemporizador = millis();
      lcd.setCursor(18,3);
      lcd.print(i);
      lcd.setCursor(0,0);
      lcd.print("            ");
      i--;
    }else{
      lcd.clear();
    }
  }
} //FIM DO VOID DE PROCESSO

uint8_t p = 0;
int global_confirmar = 0;
unsigned int auxDevolution = 0;
unsigned int modoAdministrador = 0;
unsigned int desbloqueio = 0;
unsigned int bloqueio = 0;

void confirmar(){
  if(p == FINGERPRINT_OK){
    if (!strcmp(Data, "1")) {
    global_confirmar = 1;
    auxDevolution = 0;
    clearData();
    }else{
    if (!strcmp(Data, "2")) {
    global_confirmar = 1;
    auxDevolution = 0;
    clearData();
    }else{
    if (!strcmp(Data, "3")) {
    global_confirmar = 1;
    auxDevolution = 0;
    clearData();
    }else{
    if (!strcmp(Data, "4")) {
    global_confirmar = 1;
    auxDevolution = 0;
    clearData();
    }else{
    if (!strcmp(Data, "5")) {
    global_confirmar = 1;
    auxDevolution = 0;
    clearData();
    }else{
    if(!strcmp(Data, "415")){
      lcd.clear();
      modoAdministrador = 1;
      global_confirmar = 0;
      desbloqueio = 0;
      lcd.clear();
      clearData();
    }else{
      lcd.clear();
      lcd.setCursor(1,1);
      lcd.print("Codigo inexistente");
      global_confirmar = 0;
      //desbloqueio = 0;
      delay(3000);
      lcd.clear();
      clearData();
    }
    }
    }
    }
    }
    }
  }
}

int retornar(){ //Retorna o valor digitado no teclado
  int output, output2, output3, output4, output5;
  output = strcmp(Data, "1");
  output2 = strcmp(Data, "2");
  output3 = strcmp(Data, "3");
  output4 = strcmp(Data, "4");
  output5 = strcmp(Data, "5");
  
  if (output == 0 || output2 == 0 || output3 == 0 || output4 == 0 || output5 == 0){ 
    int rankMax = atoi(Data);
    return rankMax;
  }
}

void clearData(){
  while (data_count != 0){
    Data[data_count--] = 0; //clear array for new data
  }
  if (data_count == 0){
    lcd.clear();
  }
return;
}

void setup(){  
  lcd.begin(20,4);
  Serial.begin(9600);
  finger.begin(57600);

  if (!SD.begin(53)) {
    Serial.println("initialization SD failed!");
    while (1);
  }
  Serial.println("initialization SD done.");
  
  /*for(int auxaux = 0; auxaux < 700; auxaux++){
    Serial.print(auxaux);
    Serial.print("  ");
    Serial.println(EEPROM.read(auxaux));
    
  }*/
  
  if (finger.verifyPassword()) {
    lcd.clear();
    /*delay(2000);
    lcd.setCursor(1,1);
    lcd.print("Sensor encontrado");
    delay(2000);
    lcd.clear();
    welcome_lcd();*/
  }else{
    while(!finger.verifyPassword()){
      lcd.setCursor(1,1);
      lcd.print("Sensor desligado");
      delay(2000);
    }
  }
}

int posicaoStatus = 500; // 500 - 530;
int posicaoStatusDois = 531; // 531 - 560
int posicaoStatusTres = 561; // 561 - 590;
int posicaoStatusQuatro = 591; // 591 - 620;
int posicaoStatusCinco = 620; // 621 - 650;
//===========
int posicaoNumero = 31; // 31 - 60
int posicaoNumeroDois = 61; // 61 - 90
int posicaoNumeroTres = 91; // 91 - 120
int posicaoNumeroQuarto = 121; // 121 - 150
int posicaoNumeroCinco = 151; // 151 - 180

int trava = 0;
int abc = 0;

unsigned int permitirAcesso = 0;
unsigned int aux_Acesso = 0; //Libera o cadastro pro histórico

void loop() {
  byte templateUsando;
  finger.getTemplateCount();
  templateUsando = finger.templateCount;

   if(!finger.verifyPassword()){
    lcd.setCursor(1,1);
    lcd.print("Sensor desligado");
    delay(2000);
  }else{
    //admin();
    //modoAdministrador = 1;

    if(templateUsando == 0 && modoAdministrador == 0){
      admin();
      modoAdministrador = 1;
    }else{
      if(modoAdministrador == 0){
        getFingerprintIDez();
        delay(50);
      }else{
        admin(); //----> Chama o modo administrador 
      }
    }
  }
}
