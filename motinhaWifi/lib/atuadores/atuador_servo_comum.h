#ifdef SERVO_PADRAO

  #include <Servo.h>

  Servo servo;

  #define OFFSET 0
  #define LIMITE 30
  
  void inicializa_servo()
  {
    servo.attach(SERVO_SINAL);
  }
  
  void servo_posicao(int angulo)
  {
    if (angulo >  LIMITE) angulo =  LIMITE;
    if (angulo < -LIMITE) angulo = -LIMITE;
  
    servo.write(angulo + 90 + OFFSET);
  }

#endif
