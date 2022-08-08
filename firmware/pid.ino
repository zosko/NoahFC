#define ROLL_kp 1
#define ROLL_ki 1
#define ROLL_kd 1
double ROLL_previousError = 0;
double ROLL_totalError = 0;

#define PITCH_kp 1
#define PITCH_ki 1
#define PITCH_kd 1
double PITCH_previousError = 0;
double PITCH_totalError = 0;

float elevatorPID() {
  int input = xAngle + ch2;

  int setPoint = 90;
  double error = setPoint - input;

  double Pvalue = error * PITCH_kp;
  double Ivalue = PITCH_totalError * PITCH_ki;
  double Dvalue = (error - PITCH_previousError) * PITCH_kd;

  double PIDvalue = Pvalue + Ivalue + Dvalue;
  PITCH_previousError = error;
  PITCH_totalError += error;

  return PIDvalue;
}

float aleronPID() {
  int input = yAngle + ch1;

  int setPoint = 90;
  double error = setPoint - input;

  double Pvalue = error * ROLL_kp;
  double Ivalue = ROLL_totalError * ROLL_ki;
  double Dvalue = (error - ROLL_previousError) * ROLL_kd;

  double PIDvalue = Pvalue + Ivalue + Dvalue;
  ROLL_previousError = error;
  ROLL_totalError += error;

  return PIDvalue;
}
