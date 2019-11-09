#ifdef SERVO_MANUAL

  #define OFFSET 0
  #define LIMITE 30
  
  void inicializa_servo(){}
  
  void servo_posicao(int angulo)
  {
    if (angulo >  LIMITE) angulo =  LIMITE;
    if (angulo < -LIMITE) angulo = -LIMITE;
  
  }

#endif
