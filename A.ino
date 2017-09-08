int trig1 = 24;
int trig2 = 27;
int trig3 = 22;

int echo1 = 25; // Front D1 , T1
int echo2 = 26; // Left  D2 , T2
int echo3 = 23; // Right D3 , T3

//int IR = 8;

int L1 = 29;  // Left Moter Forwerd
int L2 = 28;  // Left Moter Backwerd
int R1 = 30;  // Right Moter Forwerd
int R2 = 31; // Right Moter Backwerd

long T1, T2, T3;
long D1, D2, D3;

int s = 10; // Minimum Distance
int t = 80; // Robot Stop Delay

#define encoder0Pin_left 2  // yellow
#define encoder0Pin_right 3   // yellow
volatile int count_left, countold_left;
volatile int count_right, countold_right;

void sensor1_left()
{

  count_left++;
}

void sensor1_right()
{

  count_right++;
}

void turn_right(int wait) {
  count_left = 0;
  while (count_left < wait) {

    digitalWrite(L1, HIGH);
    analogWrite(7, 85);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW);
    digitalWrite(R2, HIGH);
    analogWrite(6, 85);
    Serial.print("left = ");
    Serial.println(count_left);
  }

}

void turn_left(int wait) {
  count_right = 0;
  while (count_right < wait) {
    digitalWrite(L1, LOW);
    digitalWrite(L2, HIGH);
    analogWrite(7, 85);
    digitalWrite(R1, HIGH);
    analogWrite(6, 85);
    digitalWrite(R2, LOW);
    Serial.print("right = ");
    Serial.println(count_right);
  }

}

void setup() {
  count_left = 0;
  countold_left = 0;
  digitalPinToInterrupt(3);
  pinMode(encoder0Pin_left, INPUT_PULLUP);
  attachInterrupt(0, sensor1_left, FALLING);

  count_right = 0;
  countold_right = 0;
  pinMode(encoder0Pin_right, INPUT_PULLUP);
  attachInterrupt(1, sensor1_right, FALLING);

  pinMode(trig1, OUTPUT);
  pinMode(trig2, OUTPUT);
  pinMode(trig3, OUTPUT);

  pinMode(echo1, INPUT);
  pinMode(echo2, INPUT);
  pinMode(echo3, INPUT);

  //pinMode(IR, INPUT);

  pinMode(30, OUTPUT);
  pinMode(31, OUTPUT);
  pinMode(29, OUTPUT);
  pinMode(28, OUTPUT);

  pinMode(6, OUTPUT); //left PWM
  pinMode(7, OUTPUT); //right PWM

  Serial.begin(115200);


}

void loop() {

  digitalWrite(trig1, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1, LOW);
  T1 = pulseIn(echo1, HIGH); // Front Time
  D1 = T1 * 0.034 / 2; // front Distence (cm)

  digitalWrite(trig2, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2, LOW);
  T2 = pulseIn(echo2, HIGH); // Left Time
  D2 = T2 * 0.034 / 2; // Left Distence (cm)

  digitalWrite(trig3, LOW);
  delayMicroseconds(2);
  digitalWrite(trig3, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig3, LOW);
  T3 = pulseIn(echo3, HIGH); // Right Time
  D3 = T3 * 0.034 / 2; // Right Distence (cm)

  Serial.print("D1=");
  Serial.print(D1);      // \t \t \t \t \t \t \t \t \t \t
  Serial.print(" \t");
  Serial.print("D2=");
  Serial.print(D2);
  Serial.print(" \t");
  Serial.print("D3=");
  Serial.println(D3);
  //  /////////////////////////////////////////////////////////////////////////////////////////////////////////////

  if ( D1 > s && D2 > s && D3 > s ) {

    digitalWrite(L1, HIGH); // Left Wheel Forward
    analogWrite(6, 120);
    digitalWrite(L2, LOW);
    digitalWrite(R1, HIGH); // Right Wheel Forward
    analogWrite(7, 120);
    digitalWrite(R2, LOW);  // Therefor Robot go forward
    delay(30);
  }

  //  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //  //Left Turn Bit

  if ( D1 > s  && D2 > s && D3 < s) //> lakuna thama seen 1
  {

    digitalWrite(L1, LOW); // Left Wheel Forward
    analogWrite(6, 0);
    digitalWrite(L2, HIGH);
    analogWrite(6, 130);
    digitalWrite(R1, HIGH);  // Right Wheel Stop
    analogWrite(7, 130);
    digitalWrite(R2, LOW);  // Therefor Robot Turned Right
    analogWrite(7, 0);
    delay(20);
    digitalWrite(L1, HIGH); // Left Wheel Forward
    analogWrite(7, 130);
    digitalWrite(L2, LOW);
    digitalWrite(R1, HIGH); // Right Wheel Forward
    analogWrite(6, 130);
    digitalWrite(R2, LOW);  // Therefor Robot go forward
    delay(10);
  }


  //  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Right Turn Bit

  if ( D1 > s  && D2 < D3 && D3 > s) //<lakuna thama seen 1
  {

    digitalWrite(L1, HIGH);  // Left Wheel Stop
    analogWrite(6, 130);
    digitalWrite(L2, LOW);
    analogWrite(6, 0);
    digitalWrite(R1, LOW); // Right Wheel Forward
    analogWrite(7, 0);
    digitalWrite(R2, HIGH);  // Therefor Robot Turned Left
    analogWrite(7, 130);
    delay(20);
    digitalWrite(L1, HIGH); // Left Wheel Forward
    analogWrite(6, 130);
    digitalWrite(L2, LOW);
    digitalWrite(R1, HIGH); // Right Wheel Forward
    analogWrite(7, 130);
    digitalWrite(R2, LOW);  // Therefor Robot go forward
    delay(10);
  }
  //  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //
  //  // Robot Near The Infrontof Barrier


  if (D1 < s && D2 > s && D3 < D2) {
    digitalWrite(L1, LOW);  //backward karala
    analogWrite(6, 0);
    digitalWrite(L2, HIGH);
    analogWrite(6, 140);
    digitalWrite(R1, LOW);
    analogWrite(7, 0);
    digitalWrite(R2, HIGH);
    analogWrite(7, 140);
    delay(100);  // Robot Stop 't' Time

    digitalWrite(L1, LOW); // Left Wheel Forward
    analogWrite(6, 0);
    digitalWrite(L2, HIGH);
    analogWrite(6, 130);
    digitalWrite(R1, HIGH); // Right Wheel Forward
    analogWrite(7, 130);
    digitalWrite(R2, LOW);  // Therefor Robot go forward
    analogWrite(7, 0);
    delay(1000); // Robot Turn Right 't'
    /*
        digitalWrite(L1, LOW); // Left Wheel Forward
        analogWrite(6, 0);
        digitalWrite(L2, HIGH);
        analogWrite(6, 130);
        digitalWrite(R1, HIGH);  // Right Wheel Stop
        analogWrite(7, 150);
        digitalWrite(R2, LOW);  // Therefor Robot Turned Right
        analogWrite(7, 0);
        delay(t); // Robot Turn Left 't' Time
    */

  }
  else if (D1 < s  && D2 < D3 && D3 > s) {
    digitalWrite(L1, LOW);  //backward karala
    analogWrite(6, 0);
    digitalWrite(L2, HIGH);
    analogWrite(6, 140);
    digitalWrite(R1, LOW);
    analogWrite(7, 0);
    digitalWrite(R2, HIGH);
    analogWrite(7, 140);
    delay(100);  // Robot Stop 't' Time

    digitalWrite(L1, HIGH); // Left Wheel Forward
    analogWrite(6, 130);
    digitalWrite(L2, LOW);
    digitalWrite(R1, LOW); // Right Wheel Forward
    analogWrite(7, 0);
    digitalWrite(R2, HIGH);  // Therefor Robot go forward
    analogWrite(7, 130);
    delay(1000); // Robot Turn Right 't'
    ////////////////////////////////////////////////////
    /* digitalWrite(L1, HIGH); // Left Wheel Forward
      analogWrite(6, 150);
      digitalWrite(L2, LOW);
      digitalWrite(R1, HIGH); // Right Wheel Forward
      analogWrite(7, 130);
      digitalWrite(R2, LOW);  // Therefor Robot go forward
      delay(t); // Robot Turn Right 't' Time
    */
  }

  //  /////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////


}
