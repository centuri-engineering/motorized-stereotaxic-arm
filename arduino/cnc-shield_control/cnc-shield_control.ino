#define EN 8 /* enable pin for all stepper outputs*/
#define X_DIR 5 /* direction-pin for X-axis */
#define X_STEP 2 /* step-pin for X-axis */
#define Y_DIR 6 /* direction-pin for Y-axis*/
#define Y_STEP 3 /* step-pin for Y-axis */
#define Z_DIR 7 /* direction-pin for Z-axis */
#define Z_STEP 4 /* step-pin for Z-axis */
#define A_DIR 13 /*direction-pin for A-axis */
#define A_STEP 12 /* step-pin for A-axis */
int Count = 0; /* counter to count number of steps made */
boolean Direction = LOW; /* ratational direction of stepper motors*/

int STEPS_MOTOR = 200;
int MICRO_STEP = 16;
float DIST_FULL_REVO = 1000; //Translation distabce in um for 1 complete revolution
float STEPS_FULL_REVO;
float STEPS_PER_UM;
float SPEED_TRANSL = 10; // in um/s
float SPEED_TRANSL_STEPS; // in steps/s
float DELAY_AFTER_STEP;


void setup()
{
  Serial.begin(9600);
  /* configure the stepper drive pins as outputs */
  pinMode(EN, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  digitalWrite(EN, LOW); //low to enable
  STEPS_FULL_REVO = STEPS_MOTOR*MICRO_STEP;
  Serial.println(STEPS_FULL_REVO);
  STEPS_PER_UM = STEPS_FULL_REVO/DIST_FULL_REVO;
  Serial.println(STEPS_PER_UM);
  SPEED_TRANSL_STEPS = SPEED_TRANSL*STEPS_PER_UM;
  Serial.println(SPEED_TRANSL_STEPS);
  DELAY_AFTER_STEP = 1/SPEED_TRANSL_STEPS;
  Serial.println(DELAY_AFTER_STEP, DEC);
}
void loop()
{
  //Serial.println("here ");
    if (Serial.available() > 0) {
    // read the incoming byte:
    Serial.print("I received: ");
  }
  
  digitalWrite(X_STEP, HIGH);
  delayMicroseconds(31250);
  digitalWrite(X_STEP, LOW);
  delayMicroseconds(31250);
}
