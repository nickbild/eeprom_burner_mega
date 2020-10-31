#include <avr/pgmspace.h>

int ad0 = 53;
int ad1 = 51;
int ad2 = 49;
int ad3 = 47;
int ad4 = 45;
int ad5 = 43;
int ad6 = 41;
int ad7 = 39;
int ad8 = 37;
int ad9 = 35;
int ad10 = 33;
int ad11 = 31;
int ad12 = 29;
int ad13 = 27;
int ad14 = 25;

int d0 = 52;
int d1 = 50;
int d2 = 48;
int d3 = 46;
int d4 = 44;
int d5 = 42;
int d6 = 40;
int d7 = 38;

int ce = 30;
int oe = 28;
int we = 26;

const byte data[34] PROGMEM = {120, 169, 127, 141, 254, 127, 169, 255, 141, 242, 127, 169, 255, 141, 243, 127, 169, 0, 141, 240, 127, 169, 0, 141, 241, 127, 169, 34, 141, 0, 127, 32, 26, 128};

void setup() {
  pinMode(ad0, OUTPUT);
  pinMode(ad1, OUTPUT);
  pinMode(ad2, OUTPUT);
  pinMode(ad3, OUTPUT);
  pinMode(ad4, OUTPUT);
  pinMode(ad5, OUTPUT);
  pinMode(ad6, OUTPUT);
  pinMode(ad7, OUTPUT);
  pinMode(ad8, OUTPUT);
  pinMode(ad9, OUTPUT);
  pinMode(ad10, OUTPUT);
  pinMode(ad11, OUTPUT);
  pinMode(ad12, OUTPUT);
  pinMode(ad13, OUTPUT);
  pinMode(ad14, OUTPUT);
  
  pinMode(ce, OUTPUT);
  pinMode(oe, OUTPUT);
  pinMode(we, OUTPUT);

  // Disable chip.
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  digitalWrite(oe, HIGH);
  delay(10);

  Serial.begin(9600);
}

void loop(){
  delay(2000);
   
  Serial.println("Starting write.");

  // Write program.
  for (unsigned int i=0; i<sizeof(data); i++) {
    write(i, pgm_read_byte_near(data + i));
  }

  // NMI Interrupt address.
  // little endian
  write(32762, 0);
  write(32763, 0);

  // Starting address of program (write to FFFC-FFFD).
  // little endian
  write(32764, 0);
  write(32765, 128);

  // Interrupt address.
  // little endian
  write(32766, 0);
  write(32767, 0);

  Serial.println("Done writing.");

  validate();

  while(true) {}

}

void write(unsigned int addr, byte data) {
  // From datasheet:
  // A low pulse on the WE or CE input with CE or WE low (respectively) and OE high initiates a write cycle. The address is latched on the falling edge of CE or WE,
  // whichever occurs last. The data is latched by the first rising edge of CE or WE.

  setWriteMode();

  delay(5);
  
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  digitalWrite(oe, HIGH);
  delay(1);

  // Set address and data.
  digitalWrite(ad0, bitRead(addr, 0));
  digitalWrite(ad1, bitRead(addr, 1));
  digitalWrite(ad2, bitRead(addr, 2));
  digitalWrite(ad3, bitRead(addr, 3));
  digitalWrite(ad4, bitRead(addr, 4));
  digitalWrite(ad5, bitRead(addr, 5));
  digitalWrite(ad6, bitRead(addr, 6));
  digitalWrite(ad7, bitRead(addr, 7));
  digitalWrite(ad8, bitRead(addr, 8));
  digitalWrite(ad9, bitRead(addr, 9));
  digitalWrite(ad10, bitRead(addr, 10));
  digitalWrite(ad11, bitRead(addr, 11));
  digitalWrite(ad12, bitRead(addr, 12));
  digitalWrite(ad13, bitRead(addr, 13));
  digitalWrite(ad14, bitRead(addr, 14));

  digitalWrite(d0, bitRead(data, 0));
  digitalWrite(d1, bitRead(data, 1));
  digitalWrite(d2, bitRead(data, 2));
  digitalWrite(d3, bitRead(data, 3));
  digitalWrite(d4, bitRead(data, 4));
  digitalWrite(d5, bitRead(data, 5));
  digitalWrite(d6, bitRead(data, 6));
  digitalWrite(d7, bitRead(data, 7));
  
  delay(1);
  digitalWrite(ce, LOW);
  delay(1);

  digitalWrite(we, LOW);
  delay(1);
  
  digitalWrite(we, HIGH);
  digitalWrite(ce, HIGH);
  delay(1);
}

void validate() {
  setReadMode();

  delay(5);

  for (unsigned int addr=0; addr<sizeof(data); addr++) {
    digitalWrite(we, HIGH);
    digitalWrite(ce, HIGH);
    digitalWrite(oe, HIGH);
    delay(1);
  
    // Set address.
    digitalWrite(ad0, bitRead(addr, 0));
    digitalWrite(ad1, bitRead(addr, 1));
    digitalWrite(ad2, bitRead(addr, 2));
    digitalWrite(ad3, bitRead(addr, 3));
    digitalWrite(ad4, bitRead(addr, 4));
    digitalWrite(ad5, bitRead(addr, 5));
    digitalWrite(ad6, bitRead(addr, 6));
    digitalWrite(ad7, bitRead(addr, 7));
    digitalWrite(ad8, bitRead(addr, 8));
    digitalWrite(ad9, bitRead(addr, 9));
    digitalWrite(ad10, bitRead(addr, 10));
    digitalWrite(ad11, bitRead(addr, 11));
    digitalWrite(ad12, bitRead(addr, 12));
    digitalWrite(ad13, bitRead(addr, 13));
    digitalWrite(ad14, bitRead(addr, 14));
      
    delay(1);
    digitalWrite(ce, LOW);
    delay(1);
  
    digitalWrite(oe, LOW);
    delay(1);

    String temp = String(digitalRead(d7)) + String(digitalRead(d6)) + String(digitalRead(d5)) + String(digitalRead(d4)) + String(digitalRead(d3)) + String(digitalRead(d2)) + String(digitalRead(d1)) + String(digitalRead(d0));
    int temp_i = strtol( temp.c_str(), NULL, 2 );
    Serial.println(temp_i);

    delay(1);
    digitalWrite(oe, HIGH);
    digitalWrite(ce, HIGH);
    delay(1);
  }

  Serial.println("Vectors:");
  for (unsigned int addr=32762; addr<32768; addr++) {
    digitalWrite(we, HIGH);
    digitalWrite(ce, HIGH);
    digitalWrite(oe, HIGH);
    delay(1);
  
    // Set address.
    digitalWrite(ad0, bitRead(addr, 0));
    digitalWrite(ad1, bitRead(addr, 1));
    digitalWrite(ad2, bitRead(addr, 2));
    digitalWrite(ad3, bitRead(addr, 3));
    digitalWrite(ad4, bitRead(addr, 4));
    digitalWrite(ad5, bitRead(addr, 5));
    digitalWrite(ad6, bitRead(addr, 6));
    digitalWrite(ad7, bitRead(addr, 7));
    digitalWrite(ad8, bitRead(addr, 8));
    digitalWrite(ad9, bitRead(addr, 9));
    digitalWrite(ad10, bitRead(addr, 10));
    digitalWrite(ad11, bitRead(addr, 11));
    digitalWrite(ad12, bitRead(addr, 12));
    digitalWrite(ad13, bitRead(addr, 13));
    digitalWrite(ad14, bitRead(addr, 14));
      
    delay(1);
    digitalWrite(ce, LOW);
    delay(1);
  
    digitalWrite(oe, LOW);
    delay(1);

    String temp = String(digitalRead(d7)) + String(digitalRead(d6)) + String(digitalRead(d5)) + String(digitalRead(d4)) + String(digitalRead(d3)) + String(digitalRead(d2)) + String(digitalRead(d1)) + String(digitalRead(d0));
    int temp_i = strtol( temp.c_str(), NULL, 2 );
    Serial.println(temp_i);
    
    delay(1);
    digitalWrite(oe, HIGH);
    digitalWrite(ce, HIGH);
    delay(1);
  }
}

void setWriteMode() {
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
}

void setReadMode() {
  pinMode(d0, INPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
  pinMode(d5, INPUT);
  pinMode(d6, INPUT);
  pinMode(d7, INPUT);
}
