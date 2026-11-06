#include <Arduino.h>
#include <WiFi.h>

#include <ezTime.h>

// Prototipo das funcoes
void conexaoWifi();
void reconexaoWifi();

const char *SSID = "SENAI EDUCACIONAL";
const char *SENHA = "info@134";

const unsigned long tempoConexao = 10000;
const unsigned long tempoReconexao = 5000;

Timezone sp;
String mes;
String diadasemana;
String diasquefaltam;

void setup()
{
  Serial.begin(115200);

  // Conexao Wifi
  conexaoWifi();

  waitForSync();

  // sp.setLocation("America/Sao_Paulo");



  Serial.println(sp.dateTime());
  // Serial.println(sp.dateTime("d/m/Y H:i:s"));
  // if (sp.dateTime("m") == "11")
  // {
  //   mes = "Novembro";
  // }

  // ARRAY                              0            1               2
const String meses [] = {"janeiro","fevereiro", "março", "abril", "maio", "junho", "julho", "agosto", "setembro", "outubro", "novembro", "dezembro"};

mes = meses [sp.month() -1];

//  // if (sp.dateTime("l") == "Friday")
//   {
//     diadasemana = " sexta feira";
//   }

// ARRAY                              0            1               2
const String diasDaSemana [] = {"domingo","segunda-feira", "terça-feira", "quarta-feira", "quinta-feira", "sexta-feira", "sabado",};

diadasemana = diasDaSemana [sp.weekday() -1];




  
    diasquefaltam = 365 - sp.dayOfYear();
  
  
  Serial.print(sp.dateTime("\\H\\o\\j\\e \\e d \\d\\e "));
  Serial.print(mes);
  Serial.print(sp.dateTime(" \\d\\e Y,"));
  Serial.print(diadasemana);
  Serial.print (" e faltam ");
  Serial.print(diasquefaltam);
  Serial.print(sp.dateTime(" \\d\\i\\a\\s \\p\\a\\r\\a \\o \\a\\n\\o \\n\\o\\v\\o "));

  // caracteres uteis
  // Y -> ano completo (2026)
  // y -> ano com dois digitos (26)
  // m -> mes (01-12)
  // d -> dia (01-31)
  // H -> hora (00-23)
  // i -> minuto (00-59)
  // s -> segundo (00-59)
  // l -> dia da semana por extenso
  // D -> dia da semana abreviado
  // F -> nome completo do mes (november)
  // M -> nome abreviado do mes (nov)
  // a/A -> am/pm
  // T -> Sigla do fuso (BRT)

  // Serial.println(sp.minute());
  // Serial.println(sp.second());
  // Serial.println(sp.hour());
  // Serial.println(sp.hourFormat12());
  // Serial.println(sp.day());
  // Serial.println(sp.dayOfYear());
  // Serial.println(sp.month());
  // Serial.println(sp.year());
  // Serial.println(sp.isAM());
  // Serial.println(sp.isPM());
}

void loop()
{
  reconexaoWifi();
}

void conexaoWifi()
{
  Serial.printf("Conectando ao wifi: %s", SSID);

  WiFi.begin(SSID, SENHA);

  unsigned long tempoWifi = millis();

  while (WiFi.status() != WL_CONNECTED && millis() - tempoWifi < tempoConexao)
  {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Wifi conectado com sucesso!");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
  }

  else
  {
    Serial.println("Falha ao se conectar");
  }
}

void reconexaoWifi()
{
  unsigned long tempoAtual = millis();
  unsigned long tempoUltimaConexao = 0;

  if (tempoAtual - tempoUltimaConexao > tempoReconexao)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      Serial.println("Conexao Wifi perdida");
      conexaoWifi();
    }
    tempoUltimaConexao = tempoAtual;
  }
}