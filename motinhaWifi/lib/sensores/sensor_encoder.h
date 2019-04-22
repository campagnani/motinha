//Biblioteca Encoder por Interrupção com filtro de media
//
//Author: Thalles Oliveira Campagnani







////////////////////////////////////////////////////////////////////////
///////////////////////Definições///////////////////////////////////////
////////////////////////////////////////////////////////////////////////

#define TIME_RATE 10                                                  //Define o periodo de amostragem
#define QTD_AMOST 25                                                  //Define a quantidade de amostragens a serem feitas medias







////////////////////////////////////////////////////////////////////////
///////////////////////Variaveis Globais////////////////////////////////
////////////////////////////////////////////////////////////////////////

int pulse_counter = 0;                                                //Variavel Global (não é possivel ultilizar ponteiro) a ser usada no scorpo da interrupçao E no resto do codigo 








////////////////////////////////////////////////////////////////////////
///////////////////////Funções Interrupção//////////////////////////////
////////////////////////////////////////////////////////////////////////

void blink(void)                                                      //FUNÇÃO que a interrupção a chama
{
  pulse_counter++;                                                    //Incrementa Pulso
}


void inicializa_interrupcao_encoder()                                 //
{
  attachInterrupt(digitalPinToInterrupt(ENCODER_INT), blink, CHANGE);           //Atrela o pino 15 (encoder) a interrupçao, chama a função blink, sempre que um evento de mudança de estado do pino acontecer)
}











////////////////////////////////////////////////////////////////////////
///////////////////////Funções Normais//////////////////////////////////
////////////////////////////////////////////////////////////////////////



double mede_distancia_velocidade(double *posicao, int time)
{
  double distancia  = pulse_counter * 0.00145;
  pulse_counter  = 0;
  *posicao+=distancia;
  return distancia / (time * 0.001);
}


bool resgata_velocidade_linear_instantanea (double *posicao, double *velocidade, int tempo_amostragem)                                    //
{
  static unsigned long time_previous=0, time;                         //Variaveis de tempo
  time = millis() - time_previous;                                    //Calcula a diferença de tempo que a ultima vez que o codigo acabou de ser executado
  
  if (time >= tempo_amostragem)                                       //Se o tempo atual (-) o tempo anterior foi maior que 1 segundo faça
  {
    *velocidade = mede_velocidade(&posicao, time);                   //Salva a velocidade intantanea em uma posição do vetor

    #ifdef DEBUG
        Serial.print(Velocidade Instantanea: )
        Serial.println(*velocidade);                                      //Imprime Velocidade Media
    #endif

    time_previous = millis();                                         //Salva o novo tempo atual na variavel tempo anterior
 
    return 1;
  }
  return 0;
}



bool resgata_velocidade_acelecao_linear_filtrada(double *velocidade, double *aceleracao)                                    //
{
  static unsigned long time_previous=0, time;                         //Variaveis de tempo

  time = millis() - time_previous;                                    //Calcula a diferença de tempo que a ultima vez que o codigo acabou de ser executado
  
  if (time >= TIME_RATE)                                              //Se o tempo atual (-) o tempo anterior foi maior que 1 segundo faça
  {
    static double velocidadeMedia[QTD_AMOST];                         //Vetor que armazena velocidades instantaneas
    static int count=0;                                               //Varialvel contador de posições do vetor

    velocidadeMedia[count] = mede_velocidade(time);                   //Salva a velocidade intantanea em uma posição do vetor
 
    *velocidade = 0;
    for(int i=0;i<QTD_AMOST;i++)  *velocidade += velocidadeMedia[i];  //Soma todas as velocidades
    *velocidade /= QTD_AMOST;

    if(count==(QTD_AMOST-1)) *aceleracao = (velocidadeMedia[count] - velocidadeMedia[0]      )  / (time*QTD_AMOST*0.001); //Tira a aceleração de media entre a primeira e ultima leitura
    else                     *aceleracao = (velocidadeMedia[count] - velocidadeMedia[count+1])  / (time*QTD_AMOST*0.001); //Idem

    #ifdef DEBUG
      Serial.print(*velocidade);                                      //Imprime Velocidade Media
      Serial.print("\t");                                             //Imprime tablatura
      Serial.println(*aceleracao);                                    //IMprime Aceleração Media
    #endif

    count++;                                                          //Incrementa 1 no contador;
    if (count>=QTD_AMOST) count=0;                                    //Se o contador for maior ou igual a vetor reseta ele
    time_previous = millis();                                         //Salva o novo tempo atual na variavel tempo anterior
    return 1;
  }
  return 0;
}
