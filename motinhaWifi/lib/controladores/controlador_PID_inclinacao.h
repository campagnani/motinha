double dErroInclinacao_dt (double erroAtual)
{
  static double erroAnterior      = 0;
  static double tempoAnterior     = 0;
         double tempoAtual        = millis();
          
  double velocidadeAngular = 1000 * (erroAtual - erroAnterior) / (tempoAtual-tempoAnterior);

  tempoAnterior  = tempoAtual;
  erroAnterior   = erroAtual;
  
  return velocidadeAngular;
}

void controlador_PD_inclinacao(double referencia, double kp, double kd)
{
  if (leuYPR())
  {
    double erro  = referencia - ypr[2]*180/M_PI;
    double dErro = dErroInclinacao_dt(erro);
    
    double sinalDeControle = kp * erro + kd * dErro;
    
    alpha(sinalDeControle);

    #ifdef DEBUG
      Serial.print   (erro);
      Serial.print   ("\t");
      Serial.print   (dErro);
      Serial.print   ("\t");
      Serial.println (sinalDeControle);
    #endif
  }
}
