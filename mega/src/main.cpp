/* 
 * Код для Кубка РТК: Арктика
 * Команда Happy
 * 10.11.2022
 * 
 * Команды движения:
 * 1   -  49:   Назад
 * 50  -  99:   Вперед
 * 100 - 149:   Направо 
 * 150 - 199:   Налево
 * 
 * Команды функций:
 *       201:   Автоматика
 *         0:   Стоп
 */

/***************************************************************
                           Библиотеки
****************************************************************/

#include <SoftwareSerial.h> // Библиотека для подключения APC220
#include <Arduino.h>

/***************************************************************
                              Пины
****************************************************************/

//Пины подключения APC220
#define SET 8
#define AUX 9
#define TDX 10
#define RDX 11
#define EN 12
#define VCC 13

//Пины подключения DBH-12V
#define ENA 6
#define IN1A 2
#define IN2A 3

#define ENB 7
#define IN1B 4
#define IN2B 5

//Пины подключения IR датчиков
#define IRL 26 //A2
#define IRR 28 //A3
#define VCC_IR 30 //A5
#define GND_IR 32 //A4

//Переменные приема-передачи данных
int in_data = 0;
int out_in_data = 0;
bool debag = 1;

bool LD = 0;
bool RD = 0;


/***************************************************************
                         Экземпляры класса
****************************************************************/

SoftwareSerial APCport(TDX, RDX);

/***************************************************************
                              Setup
****************************************************************/

void setup() {
  //Инициализация портов
  if (debag == 1) {
    Serial.begin(9600); //Отладка по USB
  }
  APCport.begin(9600); //Прием-передача данных
  APCport.setTimeout(30);

  // Настрока портов
  pinMode(ENA, OUTPUT);
  pinMode(IN1A, OUTPUT);
  pinMode(IN2A, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN1B, OUTPUT);
  pinMode(IN2B, OUTPUT);

  pinMode(VCC_IR, OUTPUT);
  pinMode(GND_IR, OUTPUT);

  digitalWrite(VCC_IR, HIGH);
  digitalWrite(GND_IR, LOW);

  pinMode(IRL, INPUT);
  pinMode(IRR, INPUT);
  
  pinMode(SET, OUTPUT);
  pinMode(AUX, INPUT);
  pinMode(EN, OUTPUT);
  pinMode(VCC, OUTPUT);

  digitalWrite(SET, HIGH);
  digitalWrite(VCC, HIGH);
  digitalWrite(EN, HIGH);

  delay(1000);

}

void forward(int speed) {
  digitalWrite(IN1A, HIGH);
  digitalWrite(IN2A, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN1B, HIGH);
  digitalWrite(IN2B, LOW);
  analogWrite(ENB, speed);
}

void back(int speed) {
  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN1B, LOW);
  digitalWrite(IN2B, HIGH);
  analogWrite(ENB, speed);
}

void stop() {
  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, LOW);
  analogWrite(ENA, 0);
  
  digitalWrite(IN1B, LOW);
  digitalWrite(IN2B, LOW);
  analogWrite(ENB, 0);
}

void left(int speed) {
  digitalWrite(IN1A, LOW);
  digitalWrite(IN2A, HIGH);
  analogWrite(ENA, speed);

  digitalWrite(IN1B, HIGH);
  digitalWrite(IN2B, LOW);
  analogWrite(ENB, speed);
}

void right(int speed) {
  digitalWrite(IN1A, HIGH);
  digitalWrite(IN2A, LOW);
  analogWrite(ENA, speed);

  digitalWrite(IN1B, LOW);
  digitalWrite(IN2B, HIGH);
  analogWrite(ENB, speed);
}

void Automove()  {
  in_data = 0;
  while (in_data == 0)
  {
    if (APCport.available() > 0) {
      in_data = APCport.parseInt();
    }
    delay(3);
    LD = digitalRead(IRL);
    RD = digitalRead(IRR);
      if ((LD == 0) && (RD == 1)) right(120);
      if ((RD == 0) && (LD == 1)) left(120);
      if ((LD == 1) && (RD == 1)) forward(80);
      if ((LD == 0) && (RD == 0)) forward(80);
    delay(5);
    stop();
  }
}

void loop() {
  
  if (APCport.available() > 0) {
    in_data = APCport.parseInt();
    if (debag == 1){
      //delay(15);
      Serial.println(in_data);
    }
  }


  if ( in_data >= 0 && in_data <= 199)
  {
    if (in_data >= 50 && in_data <= 99) {
      forward( map(in_data, 50, 99, 75, 255));
    }
    if (in_data >= 1 && in_data <= 49) {
      back(map( in_data, 1, 49, 75, 255));
    }
    if (in_data >= 150 && in_data <= 199) {
      left(map( in_data, 150, 199, 75, 255));
    }
    if (in_data >= 100 && in_data <= 149) {
      right(map( in_data, 100, 149, 75, 255));
    }
  }

  if (in_data == 401)
  {
    Automove();
  }

  if (in_data == 0)
  {
    stop();
  }

  delay(5);
  in_data = 0;

}
