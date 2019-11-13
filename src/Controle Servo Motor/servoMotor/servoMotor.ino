#define taxAmo 0.02 //Define tempo de amostragem
#define PID         //Define Controlador - Comente para Espaço de Sstados (SS)
#define SERIAL      //Define Serial - Comente para Desabilitar

#define FILTRO     10//0 comenta o codigo
#define INVFILTRO   (1/FILTRO) //agilizar conta

#include "sensores_atuadores.h"
#include "controladores.h"
int referencia; //Varialvel global para ser usadada no SETUP e LOOP

void setup()
{
  millis();//Inicia registrador de tempo
  inicializa_pinagem();
  #ifdef SERIAL
    Serial.begin(115200); 
    #ifdef PID
      Serial.println("testePID = [");
    #else
      Serial.println("testeSS = [");
    #endif
    while ( Serial.available()) {Serial.read();} //Esvasie a pilha
    while (!Serial.available()) {}                //Espere algo ser digitado na serial
    while ( Serial.available()) {Serial.read();} //Esvasie a pilha
  #endif
  referencia = leiaAngulo();  
}

void loop()
{
    static unsigned long tempo_anterior = 0, tempo_atual;
    static int ScA=0;//Sinal de controle anterior | Tem que ser inteiro pois o Sinal de controle real é 9bits (-255|+255)

    #if FILTRO>1
      double     angulo = leiaAnguloFiltrado();
    #else
      int        angulo = leiaAngulo();//Sem filtro
    #endif
    
    #ifdef PID
        ScA   = ponteH_servo(controlador_PID(-angulo));
    #else 
        ScA   = ponteh_servo(controlador_SS (referencia , angulo , ScA));
    #endif

    #ifdef SERIAL //Print na serial (formato MATLAB)
      Serial.print(referencia);
      Serial.print("\t");
      Serial.print(angulo);
      Serial.print("\t");
      Serial.print(ScA);
      Serial.println(";");

      //Leia Nova Referencia
      if    ( Serial.available()) {referencia=Serial.read();} 
      while ( Serial.available()) {Serial.read();} //Esvasie a pilha
    #endif

    //Regula Tempo de Amostragem
    do{tempo_atual = millis();} while (tempo_atual - tempo_anterior < taxAmo*1000); 
    tempo_anterior = tempo_atual;
    
}
