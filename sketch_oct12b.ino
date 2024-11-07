#define PIN_ENA 9 // Вывод управления скоростью вращения мотора №1
#define PIN_ENB 3 // Вывод управления скоростью вращения мотора №2
#define PIN_IN1 6 // Вывод управления направлением вращения мотора №1
#define PIN_IN2 7 // Вывод управления направлением вращения мотора №1
#define PIN_IN3 5 // Вывод управления направлением вращения мотора №2
#define PIN_IN4 4 // Вывод управления направлением вращения мотора №2





#include <Arduino.h>
#include <stdlib.h>

#define BUFFER_SIZE 6

int val;
// int LED = 13;
// int ANALOGLED = 3;
int move;
char *buffer;

void setup() {
  pinMode(PIN_ENA, OUTPUT);
  pinMode(PIN_ENB, OUTPUT);
  pinMode(PIN_IN1, OUTPUT);
  pinMode(PIN_IN2, OUTPUT);
  pinMode(PIN_IN3, OUTPUT);
  pinMode(PIN_IN4, OUTPUT);
  // Команда остановки двум моторам
  digitalWrite(PIN_IN1, HIGH);
  digitalWrite(PIN_IN2, LOW);
  digitalWrite(PIN_IN3, LOW);
  digitalWrite(PIN_IN4, HIGH);
  Serial.begin(9600);
  // pinMode(LED, OUTPUT);
  // digitalWrite(LED, HIGH);
  // pinMode(ANALOGLED, OUTPUT);

  buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

  if (buffer == NULL) {
    return -1;
  }

}

int asciitoint(char *string) {
    char *buffer = (char *)malloc(sizeof(char) * 3);

    for (int i = 2; i < 5; i++) {
        buffer[i-2] = string[i];
    }

    int result = 0;

    for (int i = 0; buffer[i] >= '0' && buffer[i] <= '9' && i < 3; i++) {
        result = result * 10 + (buffer[i] - '0');
    }

    free(buffer);

    return result;
}

int parseMove(char *buffer) {
  switch (buffer[1]) {
    case 'U':
      digitalWrite(PIN_IN1, HIGH);
      digitalWrite(PIN_IN2, LOW);
      digitalWrite(PIN_IN3, HIGH);
      digitalWrite(PIN_IN4, LOW);
      return 0;
    case 'D':
      digitalWrite(PIN_IN1, LOW);
      digitalWrite(PIN_IN2, HIGH);
      digitalWrite(PIN_IN3, LOW);
      digitalWrite(PIN_IN4, HIGH);
      return 1;
    case 'R':
      digitalWrite(PIN_IN1, LOW);
      digitalWrite(PIN_IN2, HIGH);
      digitalWrite(PIN_IN3, HIGH);
      digitalWrite(PIN_IN4, LOW);
      return 2;
    case 'L':
      digitalWrite(PIN_IN1, HIGH);
      digitalWrite(PIN_IN2, LOW);
      digitalWrite(PIN_IN3, LOW);
      digitalWrite(PIN_IN4, HIGH);
      return 2;
    case 'S':
      digitalWrite(PIN_IN1, LOW);
      digitalWrite(PIN_IN2, LOW);
      digitalWrite(PIN_IN3, LOW);
      digitalWrite(PIN_IN4, LOW);
      return -1;
  }
}

int parseSpeed(char *buffer) {
    int result = asciitoint(buffer); 
    return result;
}

void loop() {
  if (Serial.available() >= BUFFER_SIZE) {
      
    for (int i = 0; i < BUFFER_SIZE; i++) {
      buffer[i] = Serial.read();
    }

    move = parseMove(buffer);
    int PWM = parseSpeed(buffer);
    analogWrite(PIN_ENA, PWM);
    analogWrite(PIN_ENB, PWM);

  }

  Serial.println();
  Serial.println();
  Serial.print("Буфер: ");
  Serial.print(buffer[0]);
  Serial.print(buffer[1]);
  Serial.print(buffer[2]);
  Serial.print(buffer[3]);
  Serial.print(buffer[4]);
  Serial.print(buffer[5]);
  Serial.println();
  Serial.print(move);
  Serial.println();
  Serial.println();
}











// void setup() {
//   Serial.begin(9600);

//   pinMode(LED, OUTPUT);
//   digitalWrite(LED, HIGH);
//   pinMode(ANALOGLED, OUTPUT);

//   // Настройка таймера 1 для работы с прерыванием по сравнению с OCR1A
//   // Режим работы: CTC (Clear Timer on Compare Match)
//   TCCR1B |= (1 << WGM12); 

//   // Предделитель 64 (для задержки 10 миллисекунд)
//   TCCR1B |= (1 << CS11) | (1 << CS10); 

//   // Настройка значения сравнительного регистра OCR1A
//   // Для 10 миллисекунд при 16 МГц: 16000000 / 64 = 250000
//   // 250000 * 0.01 (для 10 миллисекунд) = 2500
//   OCR1A = 2500; 

//   // Включение прерывания сравнения
//   TIMSK1 |= (1 << OCIE1A);

// }
















// int val;
// int LED = 13;
// int ANALOGLED = 3;

// char buffer[5];
// short int bufferIndex = 0;

// bool flagS, flagE = 0;

// short int vCounter = 0;

// void changePWM() {
//   int result = atoi(buffer);
//   analogWrite(ANALOGLED, result);
//   for (int i = 0; i < 3; i++) 
//     buffer[i] = 0;
// }

// void changePWM2() {
//   if (vCounter == 3) 
//       return;
  
//   int digits;

//   switch (vCounter) {
//     case 0:
//       digits = 3;
//       break;
//     case 1:
//       digits = 2;
//       break;
//     case 2:
//       digits = 1;
//       break;
//   }

//   int startDigit = 5 - digits; // элемент в массиве где начинается число; 3 это всего чисел в массиве
//   int index = startDigit - 1; // индекс элемента в массиве

//   for (index; index < 3; index++) {

//   }
// }

// ISR(TIMER1_COMPA_vect) {
//   changePWM();
//   TIFR1 |= (1 << OCF1A);
// }

// void setup() {
//   Serial.begin(9600);

//   pinMode(LED, OUTPUT);
//   digitalWrite(LED, HIGH);
//   pinMode(ANALOGLED, OUTPUT);

//   TCCR1B |= (1 << WGM12); 
//   TCCR1B |= (1 << CS11) | (1 << CS10); 
//   OCR1A = 2500; 
//   TIMSK1 |= (1 << OCIE1A);

// }

// void loop() {
//   if (Serial.available()) {
//       buffer[bufferIndex] = Serial.read();

//       if (buffer[bufferIndex] == 'A') {
//         flagS = 1;
//         ++bufferIndex;
//       }

//       if (buffer[bufferIndex] == 'V') {
//         ++vCounter;
//         ++bufferIndex;
//       }

//       if (buffer[bufferIndex] == 'E') {
//         flagE = 1;
//         bufferIndex = 0;
//       }

//       if (flagS && flagE) {
//         changePWM
//       }
//   }

//   Serial.print("Буфер: ");
//   Serial.print(buffer[0]);
//   Serial.println();
//   Serial.print(buffer[1]);
//   Serial.println();
//   Serial.print(buffer[2]);
//   Serial.println();
// }
