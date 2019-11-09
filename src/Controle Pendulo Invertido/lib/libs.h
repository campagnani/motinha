#ifdef SERVO_MANUAL

    #define NC                     16      //D0      
    #define MPU_6050_SCL            5      //D1      //Verde listrado branco
    #define MPU_6050_SDA            4      //D2      //Verde
    #define MPU_6050_INT            0      //D3      //Preto
    #define ENCODER_INT             2      //D4      //Azul
    #define PWM_MT_FRENTE          14      //D5      //Azul
    #define PWM_MT_TRAS            12      //D6      //Azul listrado
    #define PWM_MD_HORARIO         13      //D7      //Verde
    #define PWM_MD_ANTI_HORARIO    15      //D8      //Verde Claro
    
    void inicializa_pinagem()
    {
        pinMode(NC                  , INPUT );
        pinMode(MPU_6050_SCL        , INPUT );
        pinMode(MPU_6050_SDA        , INPUT );
        pinMode(MPU_6050_INT        , INPUT );
        pinMode(ENCODER_INT         , INPUT );
        pinMode(PWM_MT_FRENTE       , OUTPUT);
        pinMode(PWM_MT_TRAS         , OUTPUT);
        pinMode(PWM_MD_HORARIO      , OUTPUT);
        pinMode(PWM_MD_ANTI_HORARIO , OUTPUT);
    }
    
    #include "atuadores/atuador_servo_manual.h" //servo manual depende das definições
#endif


#ifdef SERVO_PADRAO

    #include "lib/atuadores/atuador_servo_comum.h"
    #define NC              16      //D0      
    #define MPU_6050_SCL     5      //D1      //Verde listrado branco
    #define MPU_6050_SDA     4      //D2      //Verde
    #define MPU_6050_Int     0      //D3      //Preto
    #define LED              2      //D4      //
    #define PWM_MT_FRENTE   14      //D5      //Azul
    #define PWM_MT_TRAS     12      //D6      //Azul listrado
    #define SERVO_SINAL     13      //D7      //Laranja
    #define ENCODER_INT     15      //D8      //Azul
    
    void inicializa_pinagem()
    {
        pinMode(NC                  , INPUT );
        pinMode(MPU_6050_SCL        , INPUT );
        pinMode(MPU_6050_SDA        , INPUT );
        pinMode(MPU_6050_INT        , INPUT );
        pinMode(LED                 , OUTPUT);
        pinMode(PWM_MT_FRENTE       , OUTPUT);
        pinMode(PWM_MT_TRAS         , OUTPUT);
        pinMode(SERVO_SINAL         , OUTPUT);
        pinMode(ENCODER_INT         , INPUT );
    }

#endif   


#include "lib/atuadores/atuador_servo_comum.h"
#include "lib/atuadores/atuador_motor_trazeiro.h"

#include "lib/sensores/sensor_potenciometro.h"
#include "lib/sensores/sensor_MPU6050_DMP.h"
#include "lib/sensores/sensor_encoder.h"

#include "lib/controladores/controlador_PID_velocidade.h"

#include "lib/comunicacao/tcp_ip.h"
#include "lib/comunicacao/serial_debug.h"
#include "lib/comunicacao/comunicacao.h"