
#include <Arduino.h>
#include <stdlib.h>

#define BUFFER_SIZE 5

int val;
int LED = 13;
int ANALOGLED = 3;

char *buffer;

void setup() {
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, HIGH);
  pinMode(ANALOGLED, OUTPUT);

  buffer = (char *)malloc(BUFFER_SIZE * sizeof(char));

  if (buffer == NULL) {
    return -1;
  }

}

int asciitoint(char *string) {
    char *buffer = (char *)malloc(sizeof(char) * 3);

    for (int i = 1; i < 4; i++) {
        buffer[i-1] = string[i];
    }

    int result = 0;

    for (int i = 0; buffer[i] >= '0' && buffer[i] <= '9' && i < 3; i++) {
        result = result * 10 + (buffer[i] - '0');
    }

    free(buffer);

    return result;
}

int parseSpeed(char *buffer) {
    int result = asciitoint(buffer); 
    return result;
}

void loop() {
  if (Serial.available() >= 5) {
      
    for (int i = 0; i < BUFFER_SIZE; i++) {
      buffer[i] = Serial.read();
    }

    int PWM = parseSpeed(buffer);
    analogWrite(ANALOGLED, PWM);
    delay(0.5);
  }

  Serial.println();
  Serial.println();
  Serial.print("Буфер: ");
  Serial.print(buffer[0]);
  Serial.print(buffer[1]);
  Serial.print(buffer[2]);
  Serial.print(buffer[3]);
  Serial.print(buffer[4]);
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
