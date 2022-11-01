#define Password 4
int rowC = 3;
int trava_GOC = 0;

unsigned int var_menuConsultar = 0;
  unsigned int var_digiteGaveta = 0;
    unsigned int var_verGavetaCV = 0;
      unsigned int var_CIUm, var_CIDois, var_CITres, var_CIQuatro, var_CICinco = 0; //Verifica na consulta individual qual gaveta está ocupada;
   unsigned int var_dispGeral = 0;
  unsigned int var_cadastro = 0;
    unsigned int var_cadastroIniciado = 0;
    unsigned int var_cadastroConcluido = 0;
    
  unsigned int var_verHistorico = 0;
    unsigned int aux_vergavetas, aux_verGavetaDois, aux_verGavetaTres, aux_verGavetaQuatro, aux_verGavetaCinco, trava_verGaveta = 0;
  unsigned int var_verDeletarDados = 0;
    unsigned int var_verMenuDelete = 0;
      unsigned int var_deletarUma = 0;
        unsigned int trava_deletarUma = 0;
      unsigned int var_verMenuDeletarTudo = 0;
        unsigned int var_deletarTudo = 0;
//======================PARTE INICIAL DO LCD================================
void lcdAdmin(){
  lcd.setCursor(0, 3);
  lcd.print("N: ");
}

void admin(){
  if(permitirAcesso == 0 && var_cadastro == 0 && var_menuConsultar == 0 && trava_verGaveta == 0 && var_verDeletarDados == 0 && var_verMenuDelete == 0){
    menuInicial();
  }
  if(var_menuConsultar == 1 && var_cadastro == 0 && var_dispGeral == 0 && var_digiteGaveta == 0 && var_verHistorico == 0 && trava_verGaveta == 0 && var_verDeletarDados == 0){
    menuConsultar();
  }
  if(var_digiteGaveta == 1 && var_cadastro == 0 && var_verHistorico == 0 && var_verGavetaCV == 0 && var_verDeletarDados == 0){
    consultarGaveta();
  }
  if(var_dispGeral == 1){
    menuConsultarOcupados();
  }
  if(var_verGavetaCV == 1 && var_cadastro == 0){
    exibirGavetaConsultada();
  }
  if(var_cadastro == 1 && var_cadastroIniciado == 0){
    continuarCadastro();
  }
  if(var_verHistorico == 1 && trava_verGaveta == 0){
    consultarGaveta();
  }
  if(trava_verGaveta == 1 && var_verDeletarDados == 0){
    exibirHistorico();
  }
  if(var_verDeletarDados == 1 && var_verMenuDelete == 0){
    senhaDeletarDigitais();
  }
  if(var_verMenuDelete == 1 && var_deletarUma == 0 && var_verMenuDeletarTudo == 0){
    menuApagarDigitais();
  }
  if(var_deletarUma == 1 && trava_deletarUma == 0){
    menuDeletarUma();
  }
  if(var_verMenuDeletarTudo == 1 && var_deletarTudo == 0){
    confirmarDeletarTodas(); //CONFIRMAÇÃO PRA DELETAR TODAS AS DIGITAIS
  }
  if(var_deletarTudo == 1){
    menuDeletarTodas();
  }
    lcdAdmin(); //Chama o teclado
    teclado_admin();
}
//==========================================================================

//===========================TECLADO MATRICIAL==============================
char Dados[Password];
byte data_contagem = 0;

void teclado_admin(){
  char tecla_pressionada_admin = tecladoAdmin.getKey(); //VERIFICA SE ALGUMA DAS TECLAS FOI PRESSIONADA
  
  if (tecla_pressionada_admin){ //SE ALGUMA TECLA FOR PRESSIONADA, FAZ
   if(tecla_pressionada_admin != '#'){
     int calcularadmin;
     calcularadmin = 3 + data_contagem;
     lcd.setCursor(calcularadmin, 3);
     Dados[data_contagem] = tecla_pressionada_admin; 
     lcd.print(Dados[data_contagem]);
     data_contagem++;  
      if(calcularadmin > 6){
        limparDados();
      }
   } 
  }
  switch(tecla_pressionada_admin){
    case '*':
    
    
    rowC = 3; trava_GOC = 0;
    limparDados();
    break;
    case '#':
    verificarMenu();
    Consultar();
    Cadastrar();
    Deletar();
    break;
  }
}

void limparDados(){   //APAGA OS NUMEROS QUE ANTES FORAM DIGITADOS
  while (data_contagem != 0){
    Dados[data_contagem--] = 0; //Limpa o array para novos dados
  }
  if (data_contagem == 0){
    lcd.clear();
  }
return;
}
//==========================================================================
void verificarMenu(){
  if(permitirAcesso == 0 && var_menuConsultar == 0 && var_verHistorico == 0 && var_cadastro == 0 && 
    var_verDeletarDados == 0 && var_verMenuDelete == 0 && var_deletarUma == 0){
    if (!strcmp(Dados, "1")) { //Consultar Dados
      Serial.println("Consultar Dados");
      permitirAcesso = 1;
      var_menuConsultar = 1;
      limparDados();
    }
    if (!strcmp(Dados, "2")) { //Cadastrar
      Serial.println("cadastro");
      permitirAcesso = 1;
      var_cadastro = 1;
      limparDados();
    }
    if (!strcmp(Dados, "3")) { //Apagar Digitais
      Serial.println("ApagarDigitais");
      permitirAcesso = 1;
      var_verDeletarDados = 1;
      limparDados();
    }
    if (!strcmp(Dados, "4")) { //Sair do modo administrador
      modoAdministrador = 0;
      limparDados();
    }
  }
  //======
}

void Consultar(){
 if(var_menuConsultar == 1 && var_digiteGaveta == 0 && var_verHistorico == 0 && var_verDeletarDados == 0 && 
    var_verMenuDelete == 0 && var_deletarUma == 0 && var_cadastro == 0 && var_dispGeral == 0 && data_contagem != 0){
    if (!strcmp(Dados, "1")) { //Disponibilidade individual
      Serial.println("Consultar Gaveta");
      var_digiteGaveta = 1;
      limparDados();
    }
    if (!strcmp(Dados, "2")) { //Disponibilidade geral.
      Serial.println("Gavetas Ocupadas");
      var_dispGeral = 1;
      permitirAcesso = 1;
      limparDados();
    }
    if (!strcmp(Dados, "3")) { //historico
      var_verHistorico = 1;
      Serial.print("historico");
      permitirAcesso = 1;
      limparDados();
    }
    if (!strcmp(Dados, "44")) { //voltar ao inicio
      Serial.print("VoltarCG");
      permitirAcesso = 0;
      var_menuConsultar = 0;
      limparDados();
    }
  }
  if(var_dispGeral == 1 && data_contagem != 0){
    if (!strcmp(Dados, "44")) { //voltar ao inicio
      Serial.print("VoltaraoInicioDispGeral");
      permitirAcesso = 0; var_digiteGaveta = 0; var_verGavetaCV = 0; var_verHistorico = 0;  var_deletarUma = 0; var_menuConsultar = 0; var_digiteGaveta = 0;
      var_dispGeral = 0;
      rowC = 3;
      limparDados();
    }
  }
 //======
  if(var_digiteGaveta == 1 && var_verGavetaCV == 0 && var_dispGeral == 0 && var_verHistorico == 0 && var_cadastro == 0 && 
    var_deletarUma == 0 && data_contagem != 0){ //Consulta de ocupacao
    if (!strcmp(Dados, "1")) { //Ver a gaveta 1
      var_verGavetaCV = 1;
      var_CIUm = 1;
      limparDados();
    }
    if (!strcmp(Dados, "2")) { //Ver a gaveta 2
      var_verGavetaCV = 1;
      var_CIDois = 1;
      limparDados();
    }
    if (!strcmp(Dados, "3")) { //Ver a gaveta 3
      var_verGavetaCV = 1;
      var_CITres = 1;
      limparDados();
    }
    if (!strcmp(Dados, "4")) { //Ver a gaveta 4
      var_verGavetaCV = 1;
      var_CIQuatro = 1;
      limparDados();
    }
    if (!strcmp(Dados, "5")) { //Ver a gaveta 5
      var_verGavetaCV = 1;
      var_CICinco = 1;
      limparDados();
    }
    if (!strcmp(Dados, "44")) { //voltar ao inicio
      Serial.print("VoltarVCV");
      permitirAcesso = 0;
      var_digiteGaveta = 0;
      var_verGavetaCV = 0; 
      var_verHistorico = 0;
      var_deletarUma = 0;
      var_menuConsultar = 0;
      var_digiteGaveta = 0;
      limparDados();
    }
   }
  if(var_verGavetaCV == 1 && data_contagem != 0){
    if (!strcmp(Dados, "44")) { //voltar ao inicio
      var_CIUm = 0; var_CIDois = 0; var_CITres = 0; var_CIQuatro = 0; var_CICinco = 0;
      permitirAcesso = 0; var_digiteGaveta = 0; var_verGavetaCV = 0; var_verHistorico = 0;  var_deletarUma = 0; var_menuConsultar = 0; var_digiteGaveta = 0;
      var_verGavetaCV = 0;
      limparDados();
    }
  }
   if(var_verGavetaCV == 0 && var_verHistorico == 0 && var_cadastroIniciado == 0 && var_cadastroConcluido == 0&& var_verDeletarDados == 0 && var_verMenuDelete == 0 && var_dispGeral == 0 && data_contagem != 0){
    if (!strcmp(Dados, "44")) { //voltar ao inicio
      permitirAcesso = 0;
      var_digiteGaveta = 0;
      var_verGavetaCV = 0; 
      var_verHistorico = 0;
      var_deletarUma = 0;
      var_menuConsultar = 0;
      var_digiteGaveta = 0;
      Serial.print("VoltarCV");
      limparDados();
    }
   }
//===========================
   if(var_verHistorico == 1
    && aux_vergavetas == 0 
    && aux_verGavetaDois == 0 
    && aux_verGavetaTres == 0 
    && aux_verGavetaQuatro == 0 
    && aux_verGavetaCinco == 0
    &&  data_contagem != 0){ //Escolher qual gaveta quer ver o histórico
    
    if (!strcmp(Dados, "1")) {
      aux_vergavetas = 1;
      trava_verGaveta = 1;
      limparDados();
    }
    if (!strcmp(Dados, "2")) {
      Serial.println("Historico gaveta 2");
      aux_verGavetaDois = 1;
      trava_verGaveta = 1;
      limparDados();
    }
    if (!strcmp(Dados, "3")) {
      aux_verGavetaTres = 1;
      trava_verGaveta = 1;
      limparDados();
    }
    if (!strcmp(Dados, "4")) {
      aux_verGavetaQuatro = 1;
      trava_verGaveta = 1;
      limparDados();
    }
    if (!strcmp(Dados, "5")) {
      aux_verGavetaCinco = 1;
      trava_verGaveta = 1;
      limparDados();
    }
    if (!strcmp(Dados, "44")) { //voltar ao inicio
      Serial.print("VVVC");
      permitirAcesso = 0;
      var_menuConsultar = 0;
      var_digiteGaveta = 0;
      var_verHistorico = 0;
      var_verGavetaCV = 0;
      trava_verGaveta = 0;
      aux_vergavetas = 0; aux_verGavetaDois = 0; aux_verGavetaTres = 0; aux_verGavetaQuatro = 0; aux_verGavetaCinco = 0;
      limparDados();
    }
   }

//======VER O HISTORICO DA GAVETA======
  if(aux_vergavetas == 1 || aux_verGavetaDois == 1 || aux_verGavetaTres == 1 || aux_verGavetaQuatro == 1 || aux_verGavetaCinco == 1 && data_contagem != 0 ){
    if (!strcmp(Dados, "2")) {
      abc = 0;
      trava = 0;
      lcd.clear();
      limparDados();
    }
    if (!strcmp(Dados, "5")) {
      abc = 0;
      trava = 0;
      posicaoStatus = posicaoStatus - 2;
      posicaoNumero = posicaoNumero - 2;
      limparDados();
    }
    if (!strcmp(Dados, "44")) { //voltar ao inicio
      Serial.print("vh");
      permitirAcesso = 0;
      var_menuConsultar = 0;
      var_digiteGaveta = 0;
      var_verHistorico = 0;
      var_verGavetaCV = 0;
      trava_verGaveta = 0;
      abc = 0;
      trava = 0;
        posicaoStatus = 500; posicaoStatusDois = 531; posicaoStatusTres = 561; posicaoStatusQuatro = 591; posicaoStatusCinco = 620; 
        posicaoNumero = 31; posicaoNumeroDois = 61; posicaoNumeroTres = 91; posicaoNumeroQuarto = 121; posicaoNumeroCinco = 151; 
      aux_vergavetas = 0; aux_verGavetaDois = 0; aux_verGavetaTres = 0; aux_verGavetaQuatro = 0; aux_verGavetaCinco = 0;
      lcd.clear();
      limparDados();
    }
   }
}

void Cadastrar(){
//===========CADASTRO================
  if(var_cadastro == 1 && data_contagem != 0){ //Iniciar o cadastro!
    if (!strcmp(Dados, "1") && var_cadastroConcluido == 0) {
      Serial.println("Cadastro Iniciado");
      var_cadastroIniciado = 1;
      cadastrarDigital();
      limparDados();
    }
    if (!strcmp(Dados, "2")) {
      Serial.println("Cadastro cancelado");
      permitirAcesso = 0;
      var_menuConsultar = 0;
      var_cadastro = 0;
      var_cadastroIniciado = 0;
      var_cadastroConcluido = 0;
      limparDados();
    if (!strcmp(Dados, "44")) {
      Serial.println("Cadastro coisando");
      permitirAcesso = 0;
      var_menuConsultar = 0;
      var_cadastro = 0;
      var_cadastroIniciado = 0;
      var_cadastroConcluido = 0;
      limparDados();
    }
    }
  }
  if(var_cadastroConcluido == 1 || var_cadastroIniciado == 1){
    if (!strcmp(Dados, "44")) {
      Serial.println("Cadastro terminandocancela");
      permitirAcesso = 0;
      var_menuConsultar = 0;
      var_cadastro = 0;
      var_cadastroIniciado = 0;
      var_cadastroConcluido = 0;
      limparDados();
    }
  }
}

void Deletar(){
////==========MENU_DELETAR_DIGITAIS=================
  if(var_verDeletarDados == 1 && var_verMenuDelete == 0 && var_verMenuDeletarTudo == 0 && var_deletarTudo == 0 && data_contagem != 0){
    if (!strcmp(Dados, "167")) {
      var_verMenuDelete = 1;
      Serial.print("Senha d_correta");
      limparDados();
    }
    if (!strcmp(Dados, "44")) {
      Serial.print("vd");
      var_verDeletarDados = 0;
      permitirAcesso = 0;
      var_menuConsultar = 0;
      limparDados();
    }
  }
  if(var_verMenuDelete == 1 && var_deletarUma == 0 && var_verMenuDeletarTudo == 0 && var_deletarTudo == 0 && data_contagem != 0){
    if (!strcmp(Dados, "1")) {  //Apagar um
      Serial.println("Deletar uma apenas");
      var_deletarUma = 1;
      limparDados();
    }
    if (!strcmp(Dados, "2")) { //Apagar tudo
      Serial.println("Deletar tudo");
      var_verMenuDeletarTudo = 1;
      limparDados();
    }
    if (!strcmp(Dados, "44")) {
      Serial.print("VoltarSenha");
      var_verDeletarDados = 0;
      permitirAcesso = 0;
      var_menuConsultar = 0;
      var_verMenuDelete = 0;
      var_deletarUma = 0;
      limparDados();
    }
  }
  if(var_deletarUma == 1 && data_contagem != 0){
    if (Dados != 0) {  //Apagar uma
      Serial.println(Dados);
      lcd.clear();
      trava_deletarUma = 1;
      textoUmaDeletada();
      
      int deletarUma = atoi(Dados);
      finger.deleteModel(deletarUma); //Deleta a impressão //VERIFICAR
      
      var_verDeletarDados = 0; permitirAcesso = 0; var_menuConsultar = 0;
      var_verMenuDelete = 0; var_deletarUma = 0;
      limparDados();
    }
  }
//====
  if(var_verMenuDeletarTudo == 1 && var_deletarTudo == 0 && data_contagem != 0){
    if (!strcmp(Dados, "1")) {
      Serial.println("Deletando tudo");
      //====
      deletarSD();
      finger.emptyDatabase();
      EEPROM.write(const_Cadastro, 0);
      if(var_deletarTudo == 0){
        EEPROM.write(1, 0); EEPROM.write(2, 0); EEPROM.write(3, 0); EEPROM.write(4, 0); EEPROM.write(5, 0); 
        for(int count_Hist = 29; count_Hist < 700; count_Hist++){
          EEPROM.write(count_Hist, 0);
          if(count_Hist == 699){
            var_deletarTudo = 1;
          }
        }
      }
      limparDados();
    }
    if (!strcmp(Dados, "2")) {
      Serial.println("Cancelar deletar tudo");
      var_verDeletarDados = 0; permitirAcesso = 0; var_menuConsultar = 0; var_verMenuDelete = 0; var_deletarUma = 0;
      var_verMenuDeletarTudo = 0;
      limparDados();
    }
  }
  if(var_deletarTudo == 1){
    if (!strcmp(Dados, "44")) {
      Serial.println("Voltar depois de deletar tudo");
      var_verDeletarDados = 0; permitirAcesso = 0; var_menuConsultar = 0;
      var_verMenuDelete = 0; var_deletarUma = 0; var_verMenuDeletarTudo = 0;
      var_deletarTudo = 0;
      limparDados();
    }
  }
}

//==========================================================================

void menuInicial(){
    lcd.setCursor(0,0);
    lcd.print("1. Consultar");
    lcd.setCursor(0,1);
    lcd.print("2. Cadastrar");
    lcd.setCursor(0,2);
    lcd.print("3. Deletar Dados");
}
//====Parte 1. -> Consultar
void menuConsultar(){
  lcd.setCursor(0,0);
  lcd.print("1. Disp. Individual");
  lcd.setCursor(0,1);
  lcd.print("2. Disp. Geral");
  lcd.setCursor(0,2);
  lcd.print("3. Historico");
}

//====Parte 1 - 1 - Consultar gaveta:
void consultarGaveta(){
  lcd.setCursor(0,0);
  lcd.print("Digite a gaveta:");
}
void exibirGavetaConsultada(){
  if(var_CIUm == 1){
  lcd.setCursor(2,1);
  lcd.print("A gaveta 01 esta");
  lcd.setCursor(7,2);
    if(EEPROM.read(1) != 0){
      lcd.print("vazia.");
      lcd.setCursor(0,0);
      lcd.print("ID: ");
      lcd.setCursor(4,0);
      lcd.print(EEPROM.read(31));      
    }else{
      lcd.print("disponivel");
    }
  }
  if(var_CIDois == 1){
  lcd.setCursor(2,1);
  lcd.print("A gaveta 02 esta");
  lcd.setCursor(7,2);
    if(EEPROM.read(2) != 0){
      lcd.print("vazia.");
      lcd.setCursor(0,0);
      lcd.print("ID: ");
      lcd.setCursor(4,0);
      lcd.print(EEPROM.read(61));
    }else{
      lcd.print("disponivel");
    }
  }
  if(var_CITres == 1){
  lcd.setCursor(2,1);
  lcd.print("A gaveta 03 esta");
  lcd.setCursor(7,2);
    if(EEPROM.read(3) != 0){
      lcd.print("vazia.");
      lcd.setCursor(0,0);
      lcd.print("ID: ");
      lcd.setCursor(4,0);
      lcd.print(EEPROM.read(91));
    }else{
      lcd.print("disponivel");
    }
  }
  if(var_CIQuatro == 1){
  lcd.setCursor(2,1);
  lcd.print("A gaveta 04 esta");
  lcd.setCursor(7,2);
    if(EEPROM.read(4) != 0){
      lcd.print("vazia.");
      lcd.setCursor(0,0);
      lcd.print("ID: ");
      lcd.setCursor(4,0);
      lcd.print(EEPROM.read(121));
    }else{
      lcd.print("disponivel");
    }
  }
  if(var_CICinco == 1){
  lcd.setCursor(2,1);
  lcd.print("A gaveta 05 esta");
  lcd.setCursor(7,2);
    if(EEPROM.read(5) != 0){
      lcd.print("vazia.");
      lcd.setCursor(0,0);
      lcd.print("ID: ");
      lcd.setCursor(4,0);
      lcd.print(EEPROM.read(151));
    }else{
      lcd.print("disponivel");
    }
  }
}
//====Parte 1 - 2 - Gavetas ocupadas:
void menuConsultarOcupados(){
  lcd.setCursor(0,0);
  lcd.print("Gavetas ocupadas:");
  lcd.setCursor(0,1);
  lcd.print("G: ");
  
  for(int cont_GOC = 0; cont_GOC < 6; cont_GOC++){
    if(EEPROM.read(cont_GOC) > 0 && trava_GOC == 0){
      lcd.setCursor(rowC,1);
      lcd.print(cont_GOC);
      Serial.println(cont_GOC);
      rowC = rowC + 3;
    }
    if(cont_GOC == 5){
      trava_GOC = 1;
    }
  }
}
//====Parte 1 - 3 - Histórico:

void exibirHistorico(){
  /*
int posicaoStatus = 500; // 500 - 530;
int posicaoStatusDois = 531; // 531 - 560
int posicaoStatusTres = 531; // 561 - 590;
int posicaoStatusQuatro = 591; // 591 - 620;
int posicaoStatusCinco = 620; // 621 - 650;
//===========
int posicaoNumero = 31; // 31 - 60
int posicaoNumeroDois = 61; // 61 - 90
int posicaoNumeroTres = 91; // 91 - 120
int posicaoNumeroQuarto = 121; // 121 - 150
int posicaoNumeroCinco = 151; // 151 - 180*/

  if(aux_vergavetas == 1){
    for(abc = 0; abc < 3; abc++){
      if(trava == 0){
        lcd.setCursor(0, abc);
        lcd.print(EEPROM.read(posicaoNumero+abc));
        lcd.setCursor(6, abc);    
        if(EEPROM.read(posicaoStatus+abc) == 68){
          lcd.print("Devolvido");
        }else{
          if(EEPROM.read(posicaoStatus+abc) == 82){
          lcd.print("Retirado");
          }   
        }
      }
    }
  }
  if(aux_verGavetaDois == 1){
    for(abc = 0; abc < 3; abc++){
      if(trava == 0){
        lcd.setCursor(0, abc);
        lcd.print(EEPROM.read(posicaoNumeroDois+abc));
        lcd.setCursor(6, abc);    
        if(EEPROM.read(posicaoStatusDois+abc) == 68){
          lcd.print("Devolvido");
        }else{
          if(EEPROM.read(posicaoStatusDois+abc) == 82){
          lcd.print("Retirado");
          }   
        }
      }
    }
  }
  if(aux_verGavetaTres == 1){
    for(abc = 0; abc < 3; abc++){
      if(trava == 0){
        lcd.setCursor(0, abc);
        lcd.print(EEPROM.read(posicaoNumeroTres+abc));
        lcd.setCursor(6, abc);    
        if(EEPROM.read(posicaoStatusTres+abc) == 68){
          lcd.print("Devolvido");
        }else{
          if(EEPROM.read(posicaoStatusTres+abc) == 82){
          lcd.print("Retirado");
          }   
        }
      }
    }
  }
  if(aux_verGavetaQuatro == 1){
    for(abc = 0; abc < 3; abc++){
      if(trava == 0){
        lcd.setCursor(0, abc);
        lcd.print(EEPROM.read(posicaoNumeroQuarto+abc));
        lcd.setCursor(6, abc);    
        if(EEPROM.read(posicaoStatusQuatro+abc) == 68){
          lcd.print("Devolvido");
        }else{
          if(EEPROM.read(posicaoStatusQuatro+abc) == 82){
          lcd.print("Retirado");
          }   
        }
      }
    }
  }
  if(aux_verGavetaCinco == 1){
    for(abc = 0; abc < 3; abc++){
      if(trava == 0){
        lcd.setCursor(0, abc);
        lcd.print(EEPROM.read(posicaoNumeroCinco+abc));
        lcd.setCursor(6, abc);    
        if(EEPROM.read(posicaoStatusCinco+abc) == 68){
          lcd.print("Devolvido");
        }else{
          if(EEPROM.read(posicaoStatusCinco+abc) == 82){
          lcd.print("Retirado");
          }   
        }
      }
    }
  }
    if (abc == 3 && trava == 0){
      trava = 1;
      posicaoStatus = posicaoStatus + 1;
      posicaoNumero = posicaoNumero + 1;
    }
}

//=============================================
//====Parte 2. -> Cadastro:
void continuarCadastro(){
  lcd.setCursor(0,0);
  lcd.print("Deseja continuar?");  
  lcd.setCursor(0,1);
  lcd.print("1. Sim / 2. Nao");  
}
void cadastroIniciado(){
  cadastrarDigital();
}
//=============================================
//====Parte 3. -> Apagar Digitais:
void senhaDeletarDigitais(){
  lcd.setCursor(0,0);
  lcd.print("Digite a senha!");  
}
void senhaDeletarIncorreta(){
  lcd.setCursor(0,0);
  lcd.print("Senha errada!");  
}
void menuApagarDigitais(){ 
  lcd.setCursor(0,0);
  lcd.print("1. Deletar uma");
  lcd.setCursor(0,1);
  lcd.print("2. Deletar todas");
  lcd.setCursor(0,2);
}
void menuDeletarUma(){
  lcd.setCursor(0,0);
  lcd.print("Deletar digital:");  
}

void textoUmaDeletada(){
  lcd.setCursor(0,0);
  lcd.print("Digital ");
  lcd.setCursor(8, 0);
  lcd.print(Dados);
  lcd.setCursor(0,1);
  lcd.print("Deletada!");
  delay(3000);
}
void confirmarDeletarTodas(){
  lcd.setCursor(0,0);
  lcd.print("Deseja deletar tudo?");  
  lcd.setCursor(0,1);
  lcd.print("1. Sim / 2. Nao");  
}
void menuDeletarTodas(){
  lcd.setCursor(3,1);
  lcd.print("Todos os dados");  
  lcd.setCursor(2,2);
  lcd.print("Foram deletados.");  
}
//=============================================OUTROS:

void deletarSD(){
  gavetas = SD.open("Um.txt", FILE_WRITE);
  if (gavetas) {
    gavetas.println("======== DADOS DELETADOS ========");
    gavetas.close();
  }
  gavetas = SD.open("Dois.txt", FILE_WRITE);
  if (gavetas) {
    gavetas.println("======== DADOS DELETADOS ========");
    gavetas.close();
  }
  gavetas = SD.open("Tres.txt", FILE_WRITE);
  if (gavetas) {
    gavetas.println("======== DADOS DELETADOS ========");
    gavetas.close();
  }
  gavetas = SD.open("Quatro.txt", FILE_WRITE);
  if (gavetas) {
    gavetas.println("======== DADOS DELETADOS ========");
    gavetas.close();
  }
  gavetas = SD.open("Cinco.txt", FILE_WRITE);
  if (gavetas) {
    gavetas.println("======== DADOS DELETADOS ========");
    gavetas.close();
  }
}