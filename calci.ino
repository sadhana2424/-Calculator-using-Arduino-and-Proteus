#include <Keypad.h>

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'7','8','9','A'},
  {'4','5','6','B'},
  {'1','2','3','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {D1, D2, D5, D6};
byte colPins[COLS] = {D7, D8, D3, D4};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

long num1 = 0;
long num2 = 0;
char op;
bool secondNumber = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Calculator Ready");
}

void loop() {
  char key = keypad.getKey();

  if (key) {
    Serial.println(key);

    if (key >= '0' && key <= '9') {
      if (!secondNumber)
        num1 = num1 * 10 + (key - '0');
      else
        num2 = num2 * 10 + (key - '0');
    }

    else if (key == 'A') { // +
      op = '/';
      secondNumber = true;
    }

    else if (key == 'B') { // -
      op = '*';
      secondNumber = true;
    }

    else if (key == 'C') { // *
      op = '-';
      secondNumber = true;
    }

    else if (key == 'D') { // /
      op = '+';
      secondNumber = true;
    }

    else if (key == '#') { // Calculate
      float result;

      switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': result = (float)num1 / num2; break;
      }

      Serial.print("Result = ");
      Serial.println(result);

      num1 = 0;
      num2 = 0;
      secondNumber = false;
    }

    else if (key == '*') { // Clear
      num1 = 0;
      num2 = 0;
      secondNumber = false;
      Serial.println("Cleared");
    }
  }
}