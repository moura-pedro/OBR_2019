#include <Wire.h>  // i2c RPI and Arduino
#include <Servo.h> // Cam 

//            --- motors ---
#define ENA 7     //Left Motor Speed
#define ENB 2     //Right Motor Speed

//            --- H-Bridge ---
#define IN1 6     //Forward - Left Motor
#define IN2 5     //Backwards - Left Motor
#define IN3 4     //Forward - Right Motor
#define IN4 3     //Backwards - Right Motor

//            --- sensors ---
#define LLsens 46
#define Llsens 48
#define Mdsens 49
#define Rrsens 50
#define RRsens 51

Servo myservo;  
String Sensor_Value = ""; // Sensors Reading
String dataReceived = "";
long int num = 0;
char func = 'z';
bool DE;

void setup()
{
  Serial.begin(115200);
  myservo.attach(A0);
  Wire.begin(0x18);
  Wire.onReceive(receiveData);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}
void loop()
{
  Sensor();
  myservo.write(35);
  melb();
  
}

void Forward(int LMS, int RMS) 
{
  digitalWrite (IN1, HIGH);      
  digitalWrite (IN2, LOW);       
  digitalWrite (IN3, HIGH);      
  digitalWrite (IN4, LOW);       
  analogWrite  (ENA, LMS);
  analogWrite  (ENB, RMS);
}
void Backwards(int LMS, int RMS)
{
  digitalWrite (IN1, LOW);       
  digitalWrite (IN2, HIGH);      
  digitalWrite (IN3, LOW);       
  digitalWrite (IN4, HIGH);      
  analogWrite  (ENA, LMS);
  analogWrite  (ENB, RMS);
}
void Left_Turn(int LMS, int RMS)
{
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  analogWrite  (ENA, LMS);
  analogWrite  (ENB, RMS);
}
void Right_Turn(int LMS, int RMS)
{
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  analogWrite  (ENA, LMS);
  analogWrite  (ENB, RMS);
}
void Sensor()
{
  Sensor_Value = "";
  Sensor_Value += digitalRead(LLsens);
  Sensor_Value += digitalRead(Llsens);
  Sensor_Value += digitalRead(Mdsens);
  Sensor_Value += digitalRead(Rrsens);
  Sensor_Value += digitalRead(RRsens);

//                                  --- NO sensor case ---
  if (Sensor_Value == "00000")
  {
    Forward(205, 205);
  }

//                                  --- ONE sensor cases ---
  else if (Sensor_Value == "10000")
  {
    Forward(100, 255);
  }
  
  else if (Sensor_Value == "01000")
  {
    Left_Turn(220, 255);
  }
  
  else if (Sensor_Value == "00100")
  {
    Forward(245, 245);
  }
  
  else if (Sensor_Value == "00010")
  {
    Right_Turn(255, 220);
  }
  
  else if (Sensor_Value == "00001")
  {
    Forward(255, 100);
  }

//                                    --- TWO sensors cases ---
  else if (Sensor_Value == "11000")
  {
    delay(500);
    Left_Turn(255, 255);
    delay(890);
  }
  
  else if (Sensor_Value == "00011")
  {
    delay(500);
    Right_Turn(255, 255);
    delay(890);
  }
  
  else if (Sensor_Value == "10100")
  {
    Left_Turn(255, 255);
  }
  
  else if (Sensor_Value == "01100")
  {
    Left_Turn(200,255);
  }
    
  else if (Sensor_Value == "01010")
  {
    Forward(245,245);
  }
    
  else if (Sensor_Value == "00110")
  {
    Right_Turn(255,200);
  }
    
  else if (Sensor_Value == "00101")
  {
    Right_Turn(255, 255);
  }

//                                     --- THREE sensors cases ---  
 
  else if (Sensor_Value == "11010")
  {
    Left_Turn(255, 255);
    DE = 1;
  }

  else if (Sensor_Value == "01110")
  {
    Forward(255, 255);
  }
  
  else if (Sensor_Value == "01101")
  {
    Left_Turn(190,190);
  }
  
  else if (Sensor_Value == "01011")
  {
    Right_Turn(255, 255);
    DE = 0;
  }
  
  else if (Sensor_Value == "00111")
  {
    Forward(255, 255);
  }

//                                     --- FOUR sensors cases ---  
  
  else if (Sensor_Value == "11011")
  {
    if (DE == 1)
    {
      Left_Turn(255, 255);
    }
    else 
    {
      Right_Turn(255, 255);
    }
  }
  
//                                     --- FIVE sensors case ---  
  
  else if (Sensor_Value == "11111")
  {
    Forward(235, 235);
  }
  
  Serial.println(func);
  
  }
void melb()
{
//     --- right green case ---
  if (func == 'r')
  {
    Serial.println("Rightttt");
    while (Sensor_Value != "11100" && Sensor_Value != "11111" && Sensor_Value != "11011")
    {
      Sensor_Value = "";
      Sensor_Value += digitalRead(LLsens);
      Sensor_Value += digitalRead(Llsens);
      Sensor_Value += digitalRead(Mdsens);
      Sensor_Value += digitalRead(Rrsens);
      Sensor_Value += digitalRead(RRsens);
      Forward(155, 155);
    }
    delay(500);
    Serial.println("OOUUUUTTT");
    Right_Turn(255, 255);
    delay(890);
  }
  
//         --- left green case ---  
  else if (func == 'l')
  {
    Serial.println("LEEEEEFFFTTT");
    while (Sensor_Value != "11100" && Sensor_Value != "11111" && Sensor_Value != "11011")
    {
      Sensor_Value = "";
      Sensor_Value += digitalRead(LLsens);
      Sensor_Value += digitalRead(Llsens);
      Sensor_Value += digitalRead(Mdsens);
      Sensor_Value += digitalRead(Rrsens);
      Sensor_Value += digitalRead(RRsens);
      Forward(155, 155);
    }
    Serial.println("OUUTTTTT");
    delay(500);
    Left_Turn(255, 255);
    delay(890);
  }
}

//        --- raspiberry communication ---  

void receiveData(int byteCount)
  {

    num = 0;
    while (Wire.available()) {
    dataReceived += (char)Wire.read();
  }

  int n = dataReceived.length();
  for (int w = 1; w < n; w = w + 1)
  {
    if (w == 1)
    {
      func = dataReceived[w];
    }
    else
    {
      int a = (int)dataReceived[w] - 48;
      num = num + round(pow(10, (n - 1 - w)) * a);
    }
  }
  //Serial.println(func);
  //Serial.println(dataReceived);
  //Serial.print(" - ");
  //Serial.println(num);
  dataReceived = "";
}
