#define NC              16      //D0      
#define MPU_6050_SCL     5      //D1      //Verde listrado branco
#define MPU_6050_SDA     4      //D2      //Verde
#define MPU_6050_INT     0      //D3      //Preto
#define LED              2      //D4      //
#define PWM_MT_FRENTE    5      //D5      //Azul
#define PWM_MT_TRAS      6      //D6      //Azul listrado
#define SERVO_SINAL     13      //D7      //Laranja
#define ENCODER_INT      2      //D8      //Azul
#define BT_TX            8                //D2
#define BT_RX            9                //D3
#define TIME_RATE       10
#define QTD_AMOST       25
#define OFFSET          90
//#define SERIAL
#define BLUETOOTH

#include <SoftwareSerial.h>
#include "gerar_sinc.h"
#include <Servo.h>
int volante =0;

Servo servo;

int pulse_counter = 0;

int velocidade;

int count;

SoftwareSerial bluetooth(BT_TX, BT_RX); //TX, RX (Bluetooth)


void inicializa_pinagem()
{
    pinMode(NC                  , INPUT );
    pinMode(MPU_6050_SCL        , INPUT );
    //pinMode(MPU_6050_SDA        , INPUT );
    //pinMode(MPU_6050_INT        , INPUT );
    pinMode(LED                 , OUTPUT);
    pinMode(PWM_MT_FRENTE       , OUTPUT);
    pinMode(PWM_MT_TRAS         , OUTPUT);
    pinMode(SERVO_SINAL         , OUTPUT);
    pinMode(ENCODER_INT         , INPUT );
}
void blink(void)
{
  pulse_counter++;
  //bluetooth.println("9");
  //Serial.println("9");
}

void inicializa_interrupcao_encoder()
{
  attachInterrupt(digitalPinToInterrupt(ENCODER_INT), blink, CHANGE);
}

int mede_velocidade(int time)
{
  int distancia  = pulse_counter; //pulse_counter * 0.00145 / (time * 0.001);
  pulse_counter  = 0;
  return distancia;
}


bool resgata_velocidade_linear_instantanea (int *velocidade, int tempo_amostragem)
{
  static unsigned long time_previous=0, time;
  time = millis() - time_previous;

  if (time >= tempo_amostragem)
  {
    *velocidade = mede_velocidade(time);
    time_previous = millis();
    return 1;
  }
  return 0;
}
void ponteH_traseira (int pwm)
{
    if (pwm> 255) pwm =  255;
    if (pwm<-255) pwm = -255;

    if (pwm>0)
    {
        analogWrite(PWM_MT_FRENTE, pwm);
        analogWrite(PWM_MT_TRAS  , LOW);
    }
    else
    {
        analogWrite(PWM_MT_FRENTE, LOW);
        analogWrite(PWM_MT_TRAS  ,-pwm);
    }
}


void aplica_degrau(int amplitude, int tempo)//tempo em segundos
{
  count=0;
  ponteH_traseira((int) amplitude);
  do
  {
    if(resgata_velocidade_linear_instantanea(&velocidade,10))
    {
      #ifdef SERIAL
      Serial.println(velocidade);
      #endif
      
      #ifdef BLUETOOTH
      bluetooth.println(velocidade);
      #endif

      if(bluetooth.available())
      {
        char caracter = bluetooth.read();
        if (caracter == '4') volante -=1;
        else
        {
          if (caracter == '6') volante +=1;
          else
          {
            if (caracter =='5') volante  =0;
          }
        }
      }

      servo.write((int) (OFFSET + volante));
      count++;
    }
    delay(1);
  }
  while (count<(tempo*100));
}

void aplica_sinc()
{
  count=0;
  do
  {
    if(resgata_velocidade_linear_instantanea(&velocidade,10))
    {
      ponteH_traseira(sinc[count]);
      
      #ifdef SERIAL
      Serial.println(velocidade);
      #endif
      
      #ifdef BLUETOOTH
      bluetooth.println(velocidade);
      #endif
      
      count++;
    }
    delay(1);
  }
  while (count<1000);
}

void aplica_familia_degraus()
{
  aplica_degrau( 20,5);
  aplica_degrau(105,4);
  aplica_degrau(121,4);
  aplica_degrau( 89,4);
  aplica_degrau(105,4);
}

void setup()
{
  servo.attach(10);
  servo.write(90);
  gerar_sinc();
  millis();
  inicializa_interrupcao_encoder();
  
  #ifdef BLUETOOTH
    bluetooth.begin(9600);
    bluetooth.println("Ligou");
    bluetooth.print("out = [");
  #endif
  #ifdef SERIAL
    Serial.begin(9600);
    Serial.println("Ligou");
    Serial.print("out = [");
  #endif

  //aplica_degrau();
  //aplica_sinc();
  delay(2000);
  aplica_familia_degraus();
  
  #ifdef BLUETOOTH
    bluetooth.print("]");
  #endif
  #ifdef SERIAL
    Serial.print("]");
  #endif
                                             
  ponteH_traseira(0);
}

void loop()
{
}
