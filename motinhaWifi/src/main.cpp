#include <Arduino.h>


#define DEBUG            //Habilita Serial USB
#define SERVO_PADRAO     //Escolher se vai usar servo com controlador proprio ou #define SERMO_MANUAL

#include "/home/thalles/Documents/PlatformIO/Projects/motinha2.0/lib/libs.h"

void setup()
{
  #ifdef DEBUG
    inicializa_serial();
  #endif
  inicializa_pinagem();
  inicializa_interrupcao_encoder();
  inicializa_servo();
  servo_posicao(0);
  servo_power(0);
}

void loop()
{
  static double posicao = 0;
  double velocidade;
  double aceleracao;
  int tempo_amostragem_velocidade = 10;


  
  if (resgata_velocidade_linear_instantanea (&posicao, &velocidade, tempo_amostragem) ) 
      controlador_PID_velocidade            (&velocidade,&aceleracao);
}
