uint8_t cadastrarDigital()
{
  int id;
  int p = -1;
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        lcd.clear();
        lcd.print("Imagem capturada");
        break;
      case FINGERPRINT_NOFINGER:
        lcd.clear();
        lcd.print("Coloque o dedo");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        lcd.clear();
        lcd.print("Erro de comunicacao");
        break;
      case FINGERPRINT_IMAGEFAIL:
        lcd.clear();
        lcd.print("Erro de imagem");
        break;
      default:
        lcd.clear();
        lcd.print("Erro desconhecido");
        break;
    }
  }
  // OK success!
  p = finger.image2Tz(1);
  switch (p)
  {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.print("Imagem capturada");
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.clear();
      lcd.print("Imagem incorreta");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.print("Erro de comunicacao");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      //Serial.println("Nao foi possivel encontrar recursos de impressao digital");
      lcd.clear();
      lcd.print("Erro de recursos");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      //Serial.println("Nao foi possivel encontrar recursos de impressao digital");
      lcd.clear();
      lcd.print("Erro de recursos");
      return p;
    default:
      lcd.clear();
      lcd.print("Erro desconhecido");
      return p;
  }
  //Serial.println("Remova o dedo do sensor");
  lcd.clear();
  lcd.print("Remova o dedo");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  p = -1;
  //Serial.println("Coloque o mesmo dedo novamente");
  lcd.clear();
  lcd.print("Coloque o dedo");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
      case FINGERPRINT_OK:
        //Serial.println("Imagem capturada");
        lcd.clear();
        lcd.print("Imagem capturada");
        break;
      case FINGERPRINT_NOFINGER:
        //Serial.print(".");
        lcd.clear();
        lcd.print("Coloque o dedo");
        break;
      case FINGERPRINT_PACKETRECIEVEERR:
        //Serial.println("Erro de comunicacao");
        lcd.clear();
        lcd.print("Erro de comunicacao");
        break;
      case FINGERPRINT_IMAGEFAIL:
        lcd.clear();
        lcd.print("Imagem incorreta");
        break;
      default:
        //Serial.println("Erro desconhecido");
        lcd.clear();
        lcd.print("Erro desconhecido");
        break;
    }
  }
  // OK success!
  
  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      lcd.clear();
      lcd.print("Imagem capturada");
      break;
    case FINGERPRINT_IMAGEMESS:
      lcd.clear();
      lcd.print("Imagem incorreta");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      lcd.clear();
      lcd.print("Erro de comunicacao");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      lcd.clear();
      lcd.print("Erro de recursos");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      lcd.clear();
      lcd.print("Erro de recursos");
      return p;
    default:
      lcd.clear();
      lcd.print("Erro desconhecido");
      return p;
  }
  // OK converted!
  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    lcd.clear();
    lcd.print("Digitais correspondem");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
    lcd.print("Erro de comunicacao");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    //Serial.println("Digitais nao correspondem");
    lcd.clear();
    lcd.print("Digitais diferentes!");
    return p;
  } else {
    lcd.clear();
    lcd.print("Erro desconhecido");
    return p;
  }
  
  byte varSignin;
  varSignin = EEPROM.read(const_Cadastro);
  id = varSignin + 1;
  EEPROM.write(const_Cadastro, id);
  //Serial.println(id);
  p = finger.storeModel(id);
  var_cadastroConcluido = 1;
  lcd.clear();
  limparDados();


  
  if (p == FINGERPRINT_OK) {
    //Serial.println("Impressao Digital Armazenada!");
    while(var_cadastro == 1 && var_cadastroConcluido == 1){
      lcd.setCursor(0,0);
      lcd.print("Sucesso");
      lcd.setCursor(10,2);
      lcd.print("ID: ");
      lcd.setCursor(14,2);
      lcd.print(id);
      lcdAdmin();
      teclado_admin();
    }


    /*desbloqueio = 0;
    var_menuConsultar = 0;
    var_digiteGaveta = 0;
    var_verHistorico = 0;
    var_cadastro = 0;
    permitirAcesso = 0;
    var_cadastro = 0;*/
    
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    lcd.clear();
    lcd.print("Erro de comunicacao");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    //Serial.println("Nao foi possivel armazenar nesta localizacao");
    lcd.clear();
    lcd.print("Erro armazenando");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    //Serial.println("Erro gravando na memoria flash");
    lcd.clear();
    lcd.print("Erro gravando");
    return p;
  } else {
    lcd.clear();
    lcd.print("Erro desconhecido");
    return p;
  }
  return true;
}
