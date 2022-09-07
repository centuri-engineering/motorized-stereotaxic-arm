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
float DELAY_AFTER_STEP_MS; // delay in ms
float DELAY_AFTER_STEP_MS_RND; // delay in ms
float CORRECT_SPEED_TRANSL;
String INCOMING_STR;
int INCOMING_INT;
String INCOMING_STR2;
bool STARTING = false;
int ESTIMATED_TIME;

void setup()
{
  delay(150);
  Serial.begin(9600);
  /* configure the stepper drive pins as outputs */
  pinMode(EN, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);
  digitalWrite(EN, LOW); //low to enable
  STEPS_FULL_REVO = STEPS_MOTOR * MICRO_STEP;
  STEPS_PER_UM = STEPS_FULL_REVO / DIST_FULL_REVO;
  SPEED_TRANSL_STEPS = SPEED_TRANSL * STEPS_PER_UM;
  DELAY_AFTER_STEP_MS = 1 / SPEED_TRANSL_STEPS * 1000;
  DELAY_AFTER_STEP_MS_RND = round(DELAY_AFTER_STEP_MS);
  CORRECT_SPEED_TRANSL = 1 / DELAY_AFTER_STEP_MS_RND * 1000 / STEPS_PER_UM;

  while (STARTING == false)
  {
    Serial.println("Type the distance (in um), then press 'enter' : ");
    Serial.println("(Positive values => arm will go up; Negative values => arm will go down.)\n");
    while (Serial.available() <= 0) {
    }
    // read the incoming byte:
    INCOMING_STR = Serial.readString();
    INCOMING_INT = INCOMING_STR.toInt();

    Serial.println("Resume:");
    Serial.print("Corrected speed (um/s): ");
    Serial.println(CORRECT_SPEED_TRANSL);
    Serial.print("Distance (um): ");
    Serial.println(INCOMING_INT);
    ESTIMATED_TIME = INCOMING_INT/CORRECT_SPEED_TRANSL*60;
    Serial.print("Estimated time (min) : ");
    Serial.println(ESTIMATED_TIME);
    Serial.println("Type 'y' to contine, 'n' restart process, then press 'enter': \n");

    while (Serial.available() <= 0)
    {
    }
    // read the incoming byte:
    INCOMING_STR2 = Serial.readString();
    if (INCOMING_STR2 == "y\n")
    {
      STARTING = true;
    }
  }
  Serial.println("Let's go! ");

}



void loop()
{
  
  digitalWrite(X_STEP, HIGH);
  delayMicroseconds(31250);
  digitalWrite(X_STEP, LOW);
  delayMicroseconds(31250);
}
