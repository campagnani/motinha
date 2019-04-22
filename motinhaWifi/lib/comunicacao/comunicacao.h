double referencia_angulo = 0;
double kp=1.5;
double kd=0.1;

int vez=0;     //Variavel para alterar entre escrever e ler
int debug=0;   //Ativa debug

int sairAll=1;



bool esperaDecisao(int tempo) //0=inf
{
    Serial.println("Esperando Conectar (ou aperte qualquer tecla para usar a serial)");
    
    int contador = 0;
    int inf      = 1;//logica inversa
    
    if (tempo ==0) inf=0;
    
    while (contador<=tempo*4)
    {c
        if(client.connected())                                       //Se o cliente conectou:
        {
            Serial.println("\nConectou!\n");                        //Escreva isso no serial
            return 0;                                                //E quebre a estrutura de repetição
        }
        else client = server.available();                            //Se não: torne o possivel o cliente conectar

        if(Serial.available())                                      //Se foi digitado algo na serial
        {
            while (Serial.available()) Serial.read();              //Primeiro esvasie a pilha                    
            Serial.println("\nVocê escolheu Serial\n");             //Escreva isso no serial
            return 1;                                                //E quebre a estrutura de repetição
        }

        
        contador+= inf;
        delay(250);                                                  // (+/-) 4 verificações por segundo
    }
}


void imprimeTCP()
{
    while (client.connected())                                         //Enquanto o cliente ainda esta conectado faça:
    {
        if (leuYPR())                                                  //Se foi possivel ler YRP
        {
            int angleABS = 900 + ypr[2] * 1800/M_PI;                   //Aumente a resolução convertendo para graus*10
            if (angleABS <    0) angleABS =    0;                      //Limete inferiormente
            if (angleABS > 1800) angleABS = 1800;                      //Limite superiormente
    
            buf2[i2] = (byte)  (angleABS & 0x00FF);       i2++;        //Escreve o byte mais  significativo referente ao angulo no vetor
            buf2[i2] = (byte) ((angleABS & 0xFF00) >> 8); i2++;        //Escreve o byte menos significativo referente ao angulo no vetor
            client.write((char*)buf2, i2);                             //Agora envie pelo WiFi.
            i2 = 0;                                                    //Zere a variavel de referencia para o vetor
    
            piscaLED();                                                //Pisque o LED
        }
    }
}

void imprimeTCP_SemLerDMP_SeConectado()
{
    if (client.connected())                                        //Enquanto o cliente ainda esta conectado faça:
    {
        int angleABS = 900 + ypr[2] * 1800/M_PI;                   //Aumente a resolução convertendo para graus*10
        if (angleABS <    0) angleABS =    0;                      //Limete inferiormente
        if (angleABS > 1800) angleABS = 1800;                      //Limite superiormente

        buf2[i2] = (byte)  (angleABS & 0x00FF);       i2++;        //Escreve o byte mais  significativo referente ao angulo no vetor
        buf2[i2] = (byte) ((angleABS & 0xFF00) >> 8); i2++;        //Escreve o byte menos significativo referente ao angulo no vetor
        client.write((char*)buf2, i2);                             //Agora envie pelo WiFi.
        i2 = 0;                                                    //Zere a variavel de referencia para o vetor

        piscaLED();                                                //Pisque o LED
    }
}

void imprimeSerial_SemLerDMP()
{
    
        double angleZ = ypr[2] * 180/M_PI;
        Serial.print(angleZ);
        Serial.print(" \t");
        Serial.print(millis());
        Serial.println(";");
        piscaLED();
 
}


void imprimeSerial()
{
    if (leuYPR())
    {
        double angleZ = ypr[2] * 180/M_PI;
        Serial.print(angleZ);
        Serial.print(" \t");
        Serial.print(millis());
        Serial.println(";");
        piscaLED();
    }
}

void recebeTCP()
{
    if(client.available())
    {
        kp = client.read()*5/255;
        Serial.print("Leu KP:  ");
        Serial.println(kp);
    }
    if(client.available())
    {
        kd = client.read()*5/255;
        Serial.print("Leu KD:  ");
        Serial.println(kd);
    }
    //if(client.available())           referencia    =    (client.read()-127) *5/255;
}

