#ifdef DEBUG

#define UART_BAUD 115200//9600


void inicializa_serial ()
{
  Serial.begin(UART_BAUD);         //Inicia porta serial com velociade especificada
  delay(10);                        //Delay para acabar de iniciar a conecxão

  /////APRESENTAÇÃO////////////////////////////////////
  Serial.println("");
  Serial.println("");
  Serial.println("Bem Vindo ao Debug da Motinha!");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  Serial.println("Configurações do Wifi:");
  Serial.println("");
  Serial.println("MODO_AP");
  Serial.println("SSID:             motinha");
  Serial.println("Senha:            qwerty123");
  Serial.println("IP:               192.168.1.100");
  Serial.println("Porta:            80");
  Serial.println("Mascara de rede:  255.255.255.0");
  Serial.println("");
  Serial.println("O WIFI_AP esta ligado e pronto para conectar");
  Serial.println("");
  Serial.println("");
  Serial.println("");
  
  while (Serial.available()>0) Serial.read();     //Primeiro garanta que nao tera lixo na pilha do serial
}

void imprimeMPUinfinitamente()
{
    while(true)
    {
        
        delay(1);
        
        if(Serial.available()) break;                //Se algum caracter foi enviado quebre a estrutura de repetição
        
    }
}

int modoDebug()
{
    Serial.println("////////////////////////////////////////////////////////");
    Serial.println("//////////////Voce esta no modo DEBUG!//////////////////");
    Serial.println("////////////////////////////////////////////////////////");
    int sair = 1;
    while(sair)
    {
        Serial.println("Envie a opção que desejar, quando quiser sair envie qualquer caracter da verificação");
        Serial.println("");
        Serial.println("A - Verificar Sensor MPU5060");
        Serial.println("B - Verificar PonteH");
        Serial.println("C - Verificar Servo Motor");
        Serial.println("D - Verificar Conexao TCPIP");
        Serial.println("E - Sair do modo Debug");
        Serial.println("P - PID");
        Serial.println("Z - Executar 'controleViaMatlabWifi()' assistidamente");
        Serial.println("");
        
        while (1)                                                //Estrutura de repetição infinita
        {
            if(Serial.available()>0)break;                      //Se algum caracter for enviado quebre a estrutura de repetição
            delay(250);                                          //+/- 4 verificações por segundo
        }
        char o = Serial.read();                                 //Armazene o caracter lido
        while (Serial.available()>0) Serial.read();            //Se tiver outros caracteres, os desconsidere e esvasia pilha

        switch(o)
        {
            case 'A':
            case 'a':
                //imprimeMPUinfinitamente2();
            break;
      
            
            case 'B':
            case 'b':
                //verificaPonteH();
            break;
            
            case 'C':
            case 'c':
                //verificaServo();
            break;
            
            case 'D':
            case 'd':
                //verificaConecxão();
            break;
            
            case 'E':
            case 'e':
                sair=0;
            break;

            case 'P':
            case 'p':
                sair=0;
                return 0;
            break;
            case 'Z':
            case 'z':
                //fudeu
            break;
            return 1;
        }
    }
}


#endif