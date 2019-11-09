void controlador_PID_velocidade (double *referencia, double *velocidade, double *aceleracao)
{
  double erro = (*referencia) - (*velocidade);

  if (erro >  0.5) erro =  0.5;
  if (erro < -0.5) erro = -0.5;
  
  int sinalDeControle =  650 + erro * 1000;
  
  ponte_H(sinalDeControle);
  
  #ifdef DEBUG
    Serial.print(sinalDeControle);
    Serial.print("\t");
  #endif
}