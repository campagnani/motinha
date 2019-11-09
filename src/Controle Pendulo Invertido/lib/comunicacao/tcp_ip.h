#include <ESP8266WiFi.h>
#include <WiFiClient.h>

////////////////////////////////////////
////////Configurações do WIFI///////////
////////////////////////////////////////

const char *ssid = "motinha";             // Ponto de acesso
const char *pw   = "qwerty123";           // Senha
IPAddress ip(192, 168, 1, 100);          // IP
IPAddress netmask(255, 255, 255, 0);     // Mascara de Rede

////////////////////////////////////////
//////Configurações de Conexão//////////
////////////////////////////////////////

const int port = 80;                      // Porta
WiFiServer server(port);                  // Declara Classe Servidor na porta especificada
WiFiClient client;                        // Declara Classe Cliente

////////////////////////////////////////
/////////Variaveis de Bulfer////////////
////////////////////////////////////////

#define bufferSize 8192                   //Tamanho do Vetor de Dados de Envio/Recebimento

uint8_t buf1[bufferSize];                 //Cria vetor de recebimento
uint8_t i1=0;                             //Contador de bytes de recebimento

uint8_t buf2[bufferSize];                 //Cria vetor de envio
uint8_t i2=0;                             //Contador de bytes de envio

////////////////////////////////////////
///////////////Funções//////////////////
////////////////////////////////////////

void inicia_Wifi_AP_TCP()
{
    WiFi.mode(WIFI_AP);                  // AP mode (phone connects directly to ESP) (no router)
    WiFi.softAPConfig(ip, ip, netmask);  // configure ip address for softAP 
    WiFi.softAP(ssid, pw);               // configure ssid and password for softAP
    server.begin();                       // start TCP server 
}
/*
void receberComando()//se disponivel
{
    while(client.available())
    {
        buf1[i1] = (uint8_t) client.read(); // read char from client (RoboRemo app)
        if(i1<bufferSize-1) i1++;
        else break;
    }
}*/
/*
void enviaComando()//se possivel
{
    if (client.connected())                                         //Se o cliente ainda esta conectado faça:
    {
        buf2[i2] = (byte)  (angleABS & 0x00FF);        2++;        //Escreve o byte
        buf2[i2] = (byte) ((angleABS & 0xFF00) >> 8); i2++;        //Escreve o byte
        client.write((char*)buf2, i2);                             //Agora envie pelo WiFi.
        i2 = 0;                                                    //Zere a variavel de referencia para o vetor
    }
}
 */
