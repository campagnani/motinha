void ponteH_traseira (int pwm)
{
    if (pwm> 1024) pwm =  1024;
    if (pwm<-1024) pwm = -1024;

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