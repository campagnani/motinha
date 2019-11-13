#define kp 1
#define kd 0
#define ki 0

#include <math.h>
double dErro_dt (int erroAtual)
{
  static          int   erroAnterior      = 0;
  static unsigned long  tempoAnterior     = 0;
         unsigned long  tempoAtual        = millis();
          
  double dErro = 1000 * (erroAtual - erroAnterior) / (tempoAtual-tempoAnterior);

  tempoAnterior  = tempoAtual;
  erroAnterior   = erroAtual;
  
  return dErro;
}

double iErro_dt (int erroAtual)
{
  static unsigned long  tempoAnterior     = 0;
         unsigned long  tempoAtual        = millis();
  static        double  iErro             = 0;
  
  iErro += erroAtual * (tempoAtual-tempoAnterior)/1000;

  tempoAnterior = tempoAtual;
  return iErro;
}

int controlador_PID(int erro)
{    
    return kp*erro + kd*dErro_dt(erro) + ki*iErro_dt(erro);
}

int controlador_SS(double referencia, double saidaPlanta, double ScA)//ScA tem que ser SATURADO !
{
  static double EstadosA[2]   = {0, 0}; //Vetor de estados estimados
  static double integrador    =      0; //Valor do integrador
  static double anti_windup   =      0; //Valor do anti-windup

  const  double A[2][2] = {{0.704294786861096 , 0 } , { 0.016870530849940 , 1 }};//Matriz A
  const  double B[2]    = {0.269928493599033        ,   0.002856672307105     }; //Matriz B
  const  double C[2]    = {0                        ,   9.163685739927198     }; //Matriz C
  const  double L[2]    = {0.610653949032228        ,   0.097788322092752     }; //Ganho do Obserdavor
  const  double K[2]    = {2.741950191395121        ,  65.124363946536870     }; //Ganho Realimentação de Estados
  const  double Ka      =                               0.913877825841094      ; //Ganho do Integrador
  const  double Kw      =                               0.1                    ; //Ganho do Anti-WindUp

  double saidaEstimada  = C[0]*EstadosA[0]-C[1]*EstadosA[1];
  EstadosA[0]           = A[0][0]*EstadosA[0]+A[0][1]*EstadosA[0]       +        B[0]*ScA        +        L[0]*(saidaPlanta-saidaEstimada); //Observador
  EstadosA[1]           = A[1][0]*EstadosA[1]+A[1][1]*EstadosA[1]       +        B[1]*ScA        +        L[1]*(saidaPlanta-saidaEstimada); //Observador
         
  integrador += (referencia - saidaPlanta)*taxAmo + anti_windup*Kw;         //Integra o erro em função do tempo e soma ação anti-windup
  
  double Sc = integrador*Ka - K[0]*EstadosA[0] -  K[1]*EstadosA[1];                 //Controlador retorna Sc
  anti_windup = ScA - Sc;
  return (int)Sc;
}