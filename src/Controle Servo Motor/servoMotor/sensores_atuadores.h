#define PWM_MT_HORARIO      5
#define PWM_MT_ANTIHORARIO  6
#define PWM_ZM             45
#define PWM_SAT           255

#define POTENCIOMETRO       0
#define OFFSET             22



void inicializa_pinagem()
{
    pinMode(PWM_MT_HORARIO     , OUTPUT);
    pinMode(PWM_MT_ANTIHORARIO , OUTPUT);
    pinMode(POTENCIOMETRO      , OUTPUT);
}

int ponteH_servo (int pwm)
{
    if (pwm >  PWM_SAT-PWM_ZM)   pwm  =  PWM_SAT-PWM_ZM;
    if (pwm < -PWM_SAT+PWM_ZM)   pwm  = -PWM_SAT+PWM_ZM;
    int PWM = pwm;
    if (pwm >    0)   pwm +=   PWM_ZM;
    if (pwm <    0)   pwm -=   PWM_ZM;

    if (pwm>0)
    {
        analogWrite(PWM_MT_HORARIO     ,  pwm);
        analogWrite(PWM_MT_ANTIHORARIO ,  LOW);
    }
    else
    {
        analogWrite(PWM_MT_HORARIO     ,  LOW);
        analogWrite(PWM_MT_ANTIHORARIO , -pwm);
    }
    return PWM;
}

int leiaAngulo ()
{
    return analogRead(POTENCIOMETRO)-511+OFFSET;
}

#if FILTRO>1
double leiaAnguloFiltrado()
{
    double saida=0;
    for(int i=0;i<FILTRO;i++) saida += leiaAngulo()*INVFILTRO;
    return saida;
}
#endif
