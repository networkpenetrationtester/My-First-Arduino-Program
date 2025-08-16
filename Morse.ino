int INTERVAL = 250;  //rate of morse

//only using [0-9] & [A-Z]but since we're using charvalues as indexesi gotta make it continuous | browhat teh fuck why did adding a zero fix this ? I HATE C ALREADY I BARELY UNDERSTAND WTF A POINTER IS
//chat I just realized switch exists and I can just use a chararray instead :skull:
char DICTIONARY[44][6] = {
  "-----",
  ".----",
  "..---",
  "...--",
  "....-",
  ".....",
  "-....",
  "--...",
  "---..",
  "----.",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  ".-",
  "-...",
  "-.-.",
  "-..",
  ".",
  "..-.",
  "--.",
  "....",
  "..",
  ".---",
  "-.-",
  ".-..",
  "--",
  "-.",
  "---",
  ".--.",
  "--.-",
  ".-.",
  "...",
  "-",
  "..-",
  "...-",
  ".--",
  "-..-",
  "-.--",
  "--.."
};

void emitMorse(int light, int duration) {
  if (light) {
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    delay(INTERVAL * duration);
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
  } else {
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    delay(INTERVAL * duration);
  }
}

void createMorse(char string[]) {
  char *c = string;
  for (int i = 0; i < 5; i++) {
    if (*c) {
      switch (*c) {
        case '.':
          emitMorse(1, 1);
          break;
        case '-':
          emitMorse(1, 3);
          break;
        case '/':
          emitMorse(0, 7);
          return;
      }
      c++;
      emitMorse(0, 1);
    }
  }
  emitMorse(0, 3);
}

void encodeSentence(char sentence[]) {
  char *letter = sentence;
  while (*letter) {
    int index = (int) *letter;
    if (index == 32) {
      createMorse("/");
    } else if ((48 <= index && index <= 57) || (65 <= index && index <= 90)) {
      createMorse(DICTIONARY[index - 48]);
    }
    letter++;
  }
}

void setup() {
  // initialize the digital pin as an output.
  pinMode(0, OUTPUT);  //LED on Model B
  pinMode(1, OUTPUT);  //LED on Model A  or Pro
}

void loop() {
  encodeSentence("HELLO WORLD");
  emitMorse(0, 7);
}