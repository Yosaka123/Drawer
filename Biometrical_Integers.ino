uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
//==============================================================================================
  return finger.fingerID;
}//FIM

// returns -1 if failed, otherwise returns ID #

int getFingerprintIDez() {
  if(bloqueio == 0 && desbloqueio == 0){
    DISPLAY_AGUARDANDO_DIGITAL();
  }
  
  p = finger.getImage();
  
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  if(p == FINGERPRINT_OK){
    desbloqueio = 1;
    i = 15; //INT DO TEMPORIZADOR
    lcd.clear();
  }
  
  while(desbloqueio == 1){
   processo_liberar_gaveta();;
    if (retornar() != 0 && global_confirmar == 1){ //CASO A GAVETA ESCOLHIDA EXISTA
    /*Serial.println(retornar());
    Serial.println(finger.fingerID);*/ 

    byte value;
    value = EEPROM.read(retornar()); //VALUE VAI VERIFICAR SE NO NÚMERO ESCOLHIDO NO TECLADO JÁ TEM ALGO
      
      if(EEPROM.read(1) == finger.fingerID && value == 0 ||
         EEPROM.read(2) == finger.fingerID && value == 0 ||
         EEPROM.read(3) == finger.fingerID && value == 0 ||
         EEPROM.read(4) == finger.fingerID && value == 0 ||
         EEPROM.read(5) == finger.fingerID && value == 0/*||
         EEPROM.read(6) == finger.fingerID && value == 0 ||
         EEPROM.read(7) == finger.fingerID && value == 0 ||
         EEPROM.read(8) == finger.fingerID && value == 0 ||
         EEPROM.read(9) == finger.fingerID && value == 0 ||
         EEPROM.read(10) == finger.fingerID && value == 0 ||
         EEPROM.read(11) == finger.fingerID && value == 0 ||
         EEPROM.read(12) == finger.fingerID && value == 0*/){
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("Devolva o objeto ");
        lcd.setCursor(4,2);
        lcd.print("da gaveta: ");
        lcd.setCursor(15, 2);
        for(int CountVerify = 0; CountVerify < 6; CountVerify++){
          if(EEPROM.read(CountVerify) == finger.fingerID){
            lcd.print(CountVerify);
          }
        }
        auxDevolution = 1;
        delay(2000);
      }
      if(auxDevolution == 1){
        clearData();
        global_confirmar = 0;
      }
    
    if(value == 0 && auxDevolution == 0){ 
      //Libera o item para ser pego e cadastra o ID ============================================================
      EEPROM.write(retornar(), finger.fingerID);
      lcd.setCursor(3,1);
      lcd.print("Gaveta aberta!");
      lcd.setCursor(2,2);
      lcd.print("Retire o objeto!");
      delay(2000);
      lcd.clear();
      global_confirmar = 0;
      desbloqueio = 0;
      aux_Acesso = retornar();

      
      if(aux_Acesso == 1){
        RecebidoUm();
        EEPROM.write(31, finger.fingerID);
        EEPROM.write(500, 82);
        gavetas = SD.open("Um.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("retireti1");
          gavetas.print("Item 1 Retirado por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
        
      }
      if(aux_Acesso == 2){
        RecebidoDois();
        EEPROM.write(61, finger.fingerID);
        EEPROM.write(531, 82); //Retirado
        gavetas = SD.open("Dois.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("retireti2");
          gavetas.print("Item 2 Retirado por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
      }
      if(aux_Acesso == 3){
        RecebidoTres();
        EEPROM.write(91, finger.fingerID);
        EEPROM.write(561, 82); //Retirado
        gavetas = SD.open("Tres.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("retireti3");
          gavetas.print("Item 3 Retirado por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
      }
      if(aux_Acesso == 4){
        RecebidoQuatro();
        EEPROM.write(121, finger.fingerID);
        EEPROM.write(591, 82); //Retirado
        gavetas = SD.open("Quatro.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("retireti4");
          gavetas.print("Item 4 Retirado por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
      }
      if(aux_Acesso == 5){
        RecebidoCinco();
        EEPROM.write(151, finger.fingerID);
        EEPROM.write(621, 82); //Retirado
        gavetas = SD.open("Cinco.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("retireti5");
          gavetas.print("Item 5 Retirado por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
      }
      
    }else{
      if(value == finger.fingerID && auxDevolution == 0){ //==============verifica o ID
        //LIBERA A DEVOLUÇÃO DO ITEM CASO SEJA O MESMO QUE PEGOU
        EEPROM.write(retornar(), 0);
        lcd.setCursor(3,1);
        lcd.print("Gaveta aberta!");
        lcd.setCursor(2,2);
        lcd.print("Devolva o objeto");
        delay(2000);
        lcd.clear();
        global_confirmar = 0;
        desbloqueio = 0;
        clearData();


      aux_Acesso = retornar();
      if(aux_Acesso == 1){
        RecebidoUm();
        EEPROM.write(31, finger.fingerID);
        EEPROM.write(500, 68); //Devolvido
        gavetas = SD.open("Um.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("devoldevol1");
          gavetas.print("Item 1 Devolvido por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
      }
      if(aux_Acesso == 2){
        RecebidoDois();
        EEPROM.write(61, finger.fingerID);
        EEPROM.write(531, 68); //Devolvido
        gavetas = SD.open("Dois.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("devoldevol2");
          gavetas.print("Item 2 Devolvido por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
      }
      if(aux_Acesso == 3){
        RecebidoTres();
        EEPROM.write(91, finger.fingerID);
        EEPROM.write(561, 68); //Devolvido
        gavetas = SD.open("Tres.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("devoldevol3");
          gavetas.print("Item 3 Devolvido por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
      }
      if(aux_Acesso == 4){
        RecebidoQuatro();
        EEPROM.write(121, finger.fingerID);
        EEPROM.write(591, 68); //Devolvido
        gavetas = SD.open("Quatro.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("devoldevol4");
          gavetas.print("Item 4 Devolvido por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
      }
      if(aux_Acesso == 5){
        RecebidoCinco();
        EEPROM.write(151, finger.fingerID);
        EEPROM.write(621, 68); //Devolvido
        gavetas = SD.open("Cinco.txt", FILE_WRITE);
        if (gavetas) {
          Serial.println("devoldevol5");
          gavetas.print("Item 5 Devolvido por: ");
          gavetas.println(finger.fingerID);
          gavetas.close();
        }
      }

    //ESPAÇO PRA CADASTRAR QUE FOI DEVOLVIDO
        
      }else{
        if (value != 0 && auxDevolution == 0){
        //IMPEDE O ACESSO CASO ALGUÉM JÁ TENHA PEGADO O ITEM
        lcd.clear();
        lcd.setCursor(2,1);
        lcd.print("Item ja retirado");
        delay(2000);
        lcd.clear();
        auxDevolution = 1;
        }
      }
    }//-- 
   }
      if((millis() - auxiliartemporizador) >= 1000){
        if(i > 0){
          auxiliartemporizador = millis();
          delay(1000);
        }else{
          lcd.clear();
          desbloqueio = 0;
          delay(100);
        }  
    }
  }
  // found a match!
  /*Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  int variavel = finger.fingerID;
  Serial.print(variavel);
  EEPROM.write(5, variavel);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);*/
  return finger.fingerID; 
}

int anterior;

void RecebidoUm(){
    for(posicaoNumero = 60; posicaoNumero > 31; posicaoNumero--){
    anterior = EEPROM.read(posicaoNumero - 1);
    EEPROM.write(posicaoNumero, anterior);
  } 
    for(posicaoStatus = 530; posicaoStatus > 500; posicaoStatus--){
    anterior = EEPROM.read(posicaoStatus - 1);
    EEPROM.write(posicaoStatus, anterior); 
  } 
}

//82 R
//68 D

void RecebidoDois(){
    for(posicaoNumero = 90; posicaoNumero > 61; posicaoNumero--){
    anterior = EEPROM.read(posicaoNumero - 1);
    EEPROM.write(posicaoNumero, anterior);
  } 
  for(posicaoStatusDois = 560; posicaoStatusDois > 530; posicaoStatusDois--){
    anterior = EEPROM.read(posicaoStatusDois - 1);
    EEPROM.write(posicaoStatusDois, anterior);
  }
}
void RecebidoTres(){
    for(posicaoNumero = 120; posicaoNumero > 91; posicaoNumero--){
    anterior = EEPROM.read(posicaoNumero - 1);
    EEPROM.write(posicaoNumero, anterior);
  } 
  for(posicaoStatusTres = 590; posicaoStatusTres > 561; posicaoStatusTres--){
    anterior = EEPROM.read(posicaoStatusTres - 1);
    EEPROM.write(posicaoStatusTres, anterior);
  }
}
void RecebidoQuatro(){
    for(posicaoNumero = 150; posicaoNumero > 121; posicaoNumero--){
    anterior = EEPROM.read(posicaoNumero - 1);
    EEPROM.write(posicaoNumero, anterior);
  } 
  for(posicaoStatusQuatro = 620; posicaoStatusQuatro > 591; posicaoStatusQuatro--){
    anterior = EEPROM.read(posicaoStatusQuatro - 1);
    EEPROM.write(posicaoStatusQuatro, anterior);
  }
}
void RecebidoCinco(){
    for(posicaoNumero = 180; posicaoNumero > 151; posicaoNumero--){
    anterior = EEPROM.read(posicaoNumero - 1);
    EEPROM.write(posicaoNumero, anterior);
  } 
  for(posicaoStatusCinco = 650; posicaoStatusCinco > 621; posicaoStatusCinco--){
    anterior = EEPROM.read(posicaoStatusCinco - 1);
    EEPROM.write(posicaoStatusCinco, anterior);
  }
}
