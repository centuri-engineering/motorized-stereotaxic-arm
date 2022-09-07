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
boolean Direction = LOW; /* rotational direction of stepper motors*/
String DirectionStr = "Down"; /* ratational direction of stepper motors*/


int STEPS_MOTOR = 200;
int MICRO_STEP = 16;
float DIST_FULL_REVO = 1000; //Translation distabce in um for 1 complete revolution
float STEPS_FULL_REVO = STEPS_MOTOR * MICRO_STEP;
float STEPS_PER_UM = STEPS_FULL_REVO / DIST_FULL_REVO;
float SPEED_TRANSL = 10; // in um/s
float SPEED_TRANSL_STEPS = SPEED_TRANSL * STEPS_PER_UM; // in steps/s
float DELAY_AFTER_STEP_MS = 1 / SPEED_TRANSL_STEPS * 1000; // delay in ms
float DELAY_AFTER_STEP_MS_RND = round(DELAY_AFTER_STEP_MS); // delay in ms
float CORRECT_SPEED_TRANSL = 1 / DELAY_AFTER_STEP_MS_RND * 1000 / STEPS_PER_UM;
String INCOMING_STR;
int INCOMING_INT;
String INCOMING_STR2;
bool STARTING = true;
int ESTIMATED_TIME;
int FULL_NB_STEPS;
int it;

void setup()
{
  delay(150);
  Serial.begin(9600);
  /* configure the stepper drive pins as outputs */
  pinMode(EN, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  pinMode(X_STEP, OUTPUT);

}
void loop()
{
  while (STARTING == true)
  {
    digitalWrite(EN, HIGH); //low to enable
    Serial.println("Type the distance (in um), then press 'enter' : ");
    Serial.println("(Positive values => arm will go down; Negative values => arm will go up.)\n");
    while (Serial.available() <= 0) {
    }
    // read the incoming byte:
    INCOMING_STR = Serial.readString();
    INCOMING_INT = INCOMING_STR.toInt();

    Serial.println("Resume:");
    Serial.print("Corrected speed (um/s): ");
    Serial.println(CORRECT_SPEED_TRANSL);
    Serial.print("Distance (um): ");
    Serial.println(abs(INCOMING_INT));
    if (INCOMING_INT < 0)
    {Direction = HIGH;
    DirectionStr = "Up";
    }
    else{Direction = LOW;
    DirectionStr = "Down";
    }
    digitalWrite(X_DIR, Direction); 
    Serial.print("Direction : ");
    Serial.println(DirectionStr);
    ESTIMATED_TIME = abs(INCOMING_INT) / CORRECT_SPEED_TRANSL;
    Serial.print("Estimated time : ");
    milisecondsToMinSec(ESTIMATED_TIME);
    FULL_NB_STEPS = STEPS_PER_UM * abs(INCOMING_INT);
    Serial.print("Full number of step : ");
    Serial.println(FULL_NB_STEPS);
    Serial.println("Type 'y' to contine, 'n' restart process, then press 'enter': \n");

    while (Serial.available() <= 0)
    {
    }
    // read the incoming byte:
    INCOMING_STR2 = Serial.readString();
    if (INCOMING_STR2 == "y\n")
    {
      STARTING = false;
      digitalWrite(EN, LOW); //low to enable
      Serial.println("Let's go! ");
    }
  }

  for (it = 1; it <= FULL_NB_STEPS; it++ )
  {
    digitalWrite(X_STEP, HIGH);
    delay(1);
    digitalWrite(X_STEP, LOW);
    delay(1);
    delay(DELAY_AFTER_STEP_MS_RND - 2);
    Serial.println(it);
  }
  Serial.println("It is over!\n");
  STARTING = true;
}

void milisecondsToMinSec (int ESTIMATED_TIME)
{
  int TIME_SEC = ESTIMATED_TIME % 60;
  int TIME_MIN = (ESTIMATED_TIME - TIME_SEC) / 60;
  Serial.print(TIME_MIN);
  Serial.print("min, ");
  Serial.print(TIME_SEC);
  Serial.println("sec");
}
