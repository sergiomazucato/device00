// board variables
int clockPin = 11;
int latchPin = 12;
int dataPin = 13;
int buttonPin = 2;

// interruption variables
volatile int interruptionCounter = 0;
volatile bool buttonState = false;
// end interruption variables

// harware variables
int REG = 3;
int DISP = 3;
byte reg2, reg3;

//fake server variables
float consumeServer = 1.2;
char msgServer[] = "abcdefghijklmnopqrstuvwxyz";
int msgLenServer = strlen(msgServer);

// system variables
volatile float consume = 2.1;
String consumeASCII = String(consume,1) + "l";

byte alph[][7] = {
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // " "
  {B10111100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // !
  {B00000001, B00000010, B00000001, B00000010, B00000000, B00000000, B00000000}, // "
  {B01010000, B11111000, B01010000, B11111000, B01010000, B00000000, B00000000}, // #
  {B01001000, B01010100, B11111110, B01010100, B11111110, B01010100, B00100100}, // $
  {B10011000, B01011000, B00100000, B11010000, B11001000, B00000000, B00000000}, // %
  {B01100100, B10011010, B10010010, B10100100, B01000000, B10100000, B00000000}, // &
  {B00000110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // '
  {B00110000, B01001000, B10000100, B00000000, B00000000, B00000000, B00000000}, // (
  {B10000100, B01001000, B00110000, B00000000, B00000000, B00000000, B00000000}, // )
  {B00101000, B00010000, B01111100, B00010000, B00101000, B00000000, B00000000}, // *
  {B00100000, B01110000, B00100000, B00000000, B00000000, B00000000, B00000000}, // +
  {B10000000, B01000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // ,
  {B00100000, B00100000, B00100000, B00000000, B00000000, B00000000, B00000000}, // -
  {B10000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // .
  {B10000000, B01000000, B00100000, B00010000, B00001000, B00000000, B00000000}, // /
  {B01111000, B11000100, B10110100, B10001100, B01111000, B00000000, B00000000}, // 0
  {B10001000, B11111100, B10000000, B00000000, B00000000, B00000000, B00000000}, // 1
  {B11001000, B10100100, B10010100, B10001000, B00000000, B00000000, B00000000}, // 2
  {B10100100, B10110100, B10101100, B01000100, B00000000, B00000000, B00000000}, // 3
  {B00110000, B00101000, B00100100, B11111100, B00000000, B00000000, B00000000}, // 4
  {B01011100, B10010100, B10010100, B01100100, B00000000, B00000000, B00000000}, // 5
  {B11110000, B10101000, B10100100, B11100100, B00000000, B00000000, B00000000}, // 6
  {B11000100, B00100100, B00010100, B00001100, B00000100, B00000000, B00000000}, // 7
  {B01011000, B10100100, B10100100, B10100100, B01011000, B00000000, B00000000}, // 8
  {B00001000, B10010100, B10010100, B10010100, B01111000, B00000000, B00000000}, // 9
  {B10100000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // :
  {B10000000, B01010000, B00000000, B00000000, B00000000, B00000000, B00000000}, // ;
  {B00100000, B01010000, B10001000, B00000000, B00000000, B00000000, B00000000}, // <
  {B10100000, B10100000, B10100000, B00000000, B00000000, B00000000, B00000000}, // =
  {B10001000, B01010000, B00100000, B00000000, B00000000, B00000000, B00000000}, // >
  {B00001000, B10100100, B00010100, B00001000, B00000000, B00000000, B00000000}, // ?
  {B01111100, B10000010, B10010010, B10101010, B10111010, B10000010, B00111100}, // @
  {B11101000, B10101000, B10101000, B11111000, B00000000, B00000000, B00000000}, // A
  {B11111111, B10010000, B10010000, B11110000, B00000000, B00000000, B00000000}, // B 
  {B01110000, B10001000, B10001000, B10001000, B00000000, B00000000, B00000000}, // C
  {B11110000, B10010000, B10010000, B11111111, B00000000, B00000000, B00000000}, // D
  {B11111000, B10101000, B10101000, B10111000, B00000000, B00000000, B00000000}, // E
  {B10001000, B01111100, B00001010, B00000000, B00000000, B00000000, B00000000}, // F
  {B01011100, B10010100, B10010100, B11111100, B00000000, B00000000, B00000000}, // G
  {B11111111, B00010000, B00010000, B11100000, B00000000, B00000000, B00000000}, // H
  {B01110100, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // I
  {B10000000, B10000000, B01110100, B00000000, B00000000, B00000000, B00000000}, // J
  {B11111100, B00100000, B11011000, B00000000, B00000000, B00000000, B00000000}, // K
  {B01111100, B10000000, B10000000, B00000000, B00000000, B00000000, B00000000}, // L
  {B11111000, B00110000, B01100000, B00110000, B11111000, B00000000, B00000000}, // M
  {B11111000, B00110000, B01100000, B11111000, B00000000, B00000000, B00000000}, // N
  {B01110000, B10001000, B10001000, B10001000, B01110000, B00000000, B00000000}, // O
  {B11111000, B00101000, B00101000, B00101000, B00010000, B00000000, B00000000}, // P
  {B00010000, B00101000, B00101000, B00101000, B11110000, B00000000, B00000000}, // Q
  {B11111000, B00100000, B00010000, B00001000, B00001000, B00000000, B00000000}, // R
  {B10010000, B10101000, B10101000, B10101000, B01001000, B00000000, B00000000}, // S
  {B00010000, B01111000, B10010000, B10010000, B00000000, B00000000, B00000000}, // T
  {B01110000, B10000000, B10000000, B01110000, B10000000, B00000000, B00000000}, // U
  {B00110000, B01000000, B10000000, B01000000, B00110000, B00000000, B00000000}, // V
  {B10010000, B01100000, B01100000, B10010000, B00000000, B00000000, B00000000}, // X
  {B11110000, B01000000, B00100000, B01000000, B11110000, B00000000, B11111000}, // W
  {B10010000, B10100000, B01000000, B00100000, B00010000, B00000000, B00000000}, // Y
  {B10010000, B10110000, B11110000, B11010000, B10010000, B00000000, B00000000}, // Z
  {B11111110, B10000010, B00000000, B00000000, B00000000, B00000000, B00000000}, // [
  {B00001000, B00010000, B00100000, B01000000, B10000000, B00000000, B00000000}, //"\"
  {B10000010, B11111110, B00000000, B00000000, B00000000, B00000000, B00000000}, // ]
  {B00000100, B00000010, B00000100, B00000000, B00000000, B00000000, B00000000}, // ^
  {B10000000, B10000000, B10000000, B00000000, B00000000, B00000000, B00000000}, // _
  {B00000010, B00000100, B00000000, B00000000, B00000000, B00000000, B00000000}, // `
  {B00100000, B01010100, B01010100, B01010100, B01111000, B00000000, B00000000}, //a
  {B01111110, B01001000, B01001000, B01001000, B00110000, B00000000, B00000000}, //b
  {B00110000, B01001000, B01001000, B01001000, B00000000, B00000000, B00000000}, //c
  {B00110000, B01001000, B01001000, B01001000, B01111110, B00000000, B00000000}, //d
  {B00111000, B01010100, B01010100, B01010100, B00011000, B00000000, B00000000}, //e
  {B00000100, B01111110, B00000101, B00000000, B00000000, B00000000, B00000000}, //f
  {B00011000, B10100100, B10100100, B10100100, B01111000, B00000000, B00000000}, //g
  {B01111110, B00010000, B00010000, B00010000, B01100000, B00000000, B00000000}, //h
  {B01110100, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, //i
  {B10000000, B01111010, B00000000, B00000000, B00000000, B00000000, B00000000}, //j 
  {B01111110, B00010000, B00101000, B01000100, B00000000, B00000000, B00000000}, //k
  {B01111110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, //l
  {B01111000, B00001000, B01110000, B00001000, B01110000, B00000000, B00000000}, //m
  {B01111000, B00001000, B00001000, B01110000, B00000000, B00000000, B00000000}, //n
  {B00110000, B01001000, B01001000, B01001000, B00110000, B00000000, B00000000}, //o
  {B11111000, B00100100, B00100100, B00100100, B00011000, B00000000, B00000000}, //p
  {B00011000, B00100100, B00100100, B00100100, B11111000, B00000000, B00000000}, //q
  {B01110000, B00001000, B00001000, B00001000, B00000000, B00000000, B00000000}, //r
  {B01001000, B01010100, B01010100, B01010100, B00100100, B00000000, B00000000}, //s
  {B00000100, B00111110, B01000100, B00100000, B00000000, B00000000, B00000000}, //t
  {B00111000, B01000000, B01000000, B01000000, B00111000, B00000000, B00000000}, //u
  {B00011000, B00100000, B01000000, B00100000, B00011000, B00000000, B00000000}, //v
  {B00111000, B01000000, B00111000, B01000000, B00111000, B00000000, B00000000}, //w
  {B01010000, B00100000, B00100000, B00100000, B01010000, B00000000, B00000000}, //x
  {B00011100, B10100000, B10100000, B10100000, B01111100, B00000000, B00000000}, //y
  {B01001000, B01101000, B01111000, B01011000, B01001000, B00000000, B00000000}, //z
  {B00010000, B01101100, B10000010, B00000000, B00000000, B00000000, B00000000}, // {
  {B11111110, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // |
  {B10000010, B01101100, B00010000, B00000000, B00000000, B00000000, B00000000}, // }
  {B10000000, B01000000, B01000000, B10000000, B10000000, B01000000, B00000000}  // ~
};

volatile byte interM[]=  {B00000000, B00000000, B00000000, B00000000, B00000000, //05
                 B00000000, B00000000, B00000000, B00000000, B00000000, //10
                 B00000000, B00000000, B00000000, B00000000, B00000000, //15
                 B00000000, B00000000, B00000000, B00000000, B00000000};//20
volatile int interMLen;

byte staticM[]= {B00000000, B00000000, B00000000, B00000000, B00000000, //05
                 B00000000, B00000000, B00000000, B00000000, B00000000, //10
                 B00000000, B00000000, B00000000, B00000000, B00000000, //15
                 B00000000, B00000000, B00000000, B00000000, B00000000, //20
                 B00000000, B00000000, B00000000, B00000000, B00000000, //25
                 B00000000, B00000000, B00000000, B00000000, B00000000, //30
                 B00000000, B00000000, B00000000, B00000000, B00000000, //35
                 B00000000, B00000000, B00000000, B00000000, B00000000, //40
                 B00000000, B00000000, B00000000, B00000000, B00000000, //45
                 B00000000, B00000000, B00000000, B00000000, B00000000, //50
                 B00000000, B00000000, B00000000, B00000000, B00000000, //55
                 B00000000, B00000000, B00000000, B00000000, B00000000, //60
                 B00000000, B00000000, B00000000, B00000000, B00000000, //65
                 B00000000, B00000000, B00000000, B00000000, B00000000, //70
                 B00000000, B00000000, B00000000, B00000000, B00000000, //75
                 B00000000, B00000000, B00000000, B00000000, B00000000, //80
                 B00000000, B00000000, B00000000, B00000000, B00000000, //85
                 B00000000, B00000000, B00000000, B00000000, B00000000, //90
                 B00000000, B00000000, B00000000, B00000000, B00000000, //95
                 B00000000, B00000000, B00000000, B00000000, B00000000, //100
                 B00000000, B00000000, B00000000, B00000000, B00000000, //105
                 B00000000, B00000000, B00000000, B00000000, B00000000, //110
                 B00000000, B00000000, B00000000, B00000000, B00000000, //115
                 B00000000, B00000000, B00000000, B00000000, B00000000, //120
                 B00000000, B00000000, B00000000, B00000000, B00000000, //125
                 B00000000, B00000000, B00000000, B00000000, B00000000, //130
                 B00000000, B00000000, B00000000, B00000000, B00000000, //135
                 B00000000, B00000000, B00000000, B00000000, B00000000, //140
                 B00000000, B00000000, B00000000, B00000000, B00000000, //145
                 B00000000, B00000000, B00000000, B00000000, B00000000, //150
                 B00000000, B00000000, B00000000, B00000000, B00000000, //155
                 B00000000, B00000000, B00000000, B00000000, B00000000, //160
                 B00000000, B00000000, B00000000, B00000000, B00000000, //165
                 B00000000, B00000000, B00000000, B00000000, B00000000, //170
                 B00000000, B00000000, B00000000, B00000000, B00000000, //175
                 B00000000, B00000000, B00000000, B00000000, B00000000, //180
                 B00000000, B00000000, B00000000, B00000000, B00000000, //185
                 B00000000, B00000000, B00000000, B00000000, B00000000, //190
                 B00000000, B00000000, B00000000, B00000000, B00000000, //195
                 B00000000, B00000000, B00000000, B00000000, B00000000};//200
int staticMLen;

byte buffer[]= {B00000000, B00000000, B00000000, B00000000, B00000000, //05 
                B00000000, B00000000, B00000000, B00000000, B00000000, //10
                B00000000, B00000000, B00000000, B00000000, B00000000, //15
                B00000000, B00000000, B00000000, B00000000, B00000000, //20
                B00000000, B00000000, B00000000, B00000000, B00000000, //25
                B00000000, B00000000, B00000000, B00000000, B00000000, //30
                B00000000, B00000000, B00000000, B00000000, B00000000, //35
                B00000000, B00000000, B00000000, B00000000, B00000000, //40
                B00000000, B00000000, B00000000, B00000000, B00000000, //45
                B00000000, B00000000, B00000000, B00000000, B00000000, //50
                B00000000, B00000000, B00000000, B00000000, B00000000, //55
                B00000000, B00000000, B00000000, B00000000, B00000000, //60
                B00000000, B00000000, B00000000, B00000000, B00000000, //65
                B00000000, B00000000, B00000000, B00000000, B00000000, //70
                B00000000, B00000000, B00000000, B00000000, B00000000, //75
                B00000000, B00000000, B00000000, B00000000, B00000000, //80
                B00000000, B00000000, B00000000, B00000000, B00000000, //85
                B00000000, B00000000, B00000000, B00000000, B00000000, //90
                B00000000, B00000000, B00000000, B00000000, B00000000, //95
                B00000000, B00000000, B00000000, B00000000, B00000000, //100
                B00000000, B00000000, B00000000, B00000000, B00000000, //105
                B00000000, B00000000, B00000000, B00000000, B00000000, //110
                B00000000, B00000000, B00000000, B00000000, B00000000, //115
                B00000000, B00000000, B00000000, B00000000, B00000000, //120
                B00000000, B00000000, B00000000, B00000000, B00000000, //125
                B00000000, B00000000, B00000000, B00000000, B00000000, //130
                B00000000, B00000000, B00000000, B00000000, B00000000, //135
                B00000000, B00000000, B00000000, B00000000, B00000000, //140
                B00000000, B00000000, B00000000, B00000000, B00000000, //145
                B00000000, B00000000, B00000000, B00000000, B00000000, //150
                B00000000, B00000000, B00000000, B00000000, B00000000, //155
                B00000000, B00000000, B00000000, B00000000, B00000000, //160
                B00000000, B00000000, B00000000, B00000000, B00000000, //165
                B00000000, B00000000, B00000000, B00000000, B00000000, //170
                B00000000, B00000000, B00000000, B00000000, B00000000, //175
                B00000000, B00000000, B00000000, B00000000, B00000000, //180
                B00000000, B00000000, B00000000, B00000000, B00000000, //185
                B00000000, B00000000, B00000000, B00000000, B00000000, //190
                B00000000, B00000000, B00000000, B00000000, B00000000, //195
                B00000000, B00000000, B00000000, B00000000, B00000000, //200
                B00000000, B00000000, B00000000, B00000000, B00000000, //205
                B00000000, B00000000, B00000000, B00000000, B00000000, //210
                B00000000, B00000000, B00000000, B00000000, B00000000, //215
                B00000000, B00000000, B00000000, B00000000, B00000000, //220
                B00000000, B00000000, B00000000, B00000000, B00000000, //225
                B00000000, B00000000, B00000000, B00000000, B00000000, //230
                B00000000, B00000000, B00000000, B00000000, B00000000, //240
                B00000000, B00000000, B00000000, B00000000, B00000000, //245
                B00000000, B00000000, B00000000, B00000000, B00000000, //250
                B00000000, B00000000, B00000000, B00000000, B00000000, //255
                B00000000, B00000000, B00000000, B00000000, B00000000, //260
                B00000000, B00000000, B00000000, B00000000, B00000000, //265
                B00000000, B00000000, B00000000, B00000000, B00000000, //270
                B00000000, B00000000, B00000000, B00000000, B00000000, //275
                B00000000, B00000000, B00000000, B00000000, B00000000, //280
                B00000000, B00000000, B00000000, B00000000, B00000000, //285
                B00000000, B00000000, B00000000, B00000000, B00000000, //290
                B00000000, B00000000, B00000000, B00000000, B00000000, //295
                B00000000, B00000000, B00000000, B00000000, B00000000, //300
                B00000000, B00000000, B00000000, B00000000, B00000000, //305
                B00000000, B00000000, B00000000, B00000000, B00000000, //310
                B00000000, B00000000, B00000000, B00000000, B00000000, //315
                B00000000, B00000000, B00000000, B00000000, B00000000, //320
                B00000000, B00000000, B00000000, B00000000, B00000000, //325
                B00000000, B00000000, B00000000, B00000000, B00000000};//330
int bufferLen = 0;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);
  pinMode(buttonPin,  INPUT);
  
  latchLOW();
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  latchHIGH();

  attachInterrupt(0, pin_ISR, FALLING); //define the interruption
  
  Serial.begin(9600);
}

int counter = 1; //to fake the server

void loop() {
  
  bool serverDown = false;
  bool externalMessage = true;
  int msgLen;
  char msg[100];
  
  while (serverDown == false){
    // Serial.println("Event: Server not Down");
    consumeASCII = getServerConsume();
    alphBuffer(&consumeASCII[0], &staticM[0], &staticMLen, false); //to buffer the consume
    // Serial.println("Event: bufferUpdated");
    printStaticBuffer(&consumeASCII[0], &staticM[0], 1000, false);//to print the consume
    // Serial.println("Event: ConsumeASCII printed");

    if (counter%2 == 0){
      externalMessage = true;
      counter++;
    }
    else{
      externalMessage = false;
      counter++;
    }

    if (externalMessage == true){
      // Serial.println("Event: externalMessage");
      msgLen = getServerMessageLen();    
      getServerMessage(&msg[0]);
      alphBuffer(&msg[0], &buffer[0], &bufferLen, true);
      printScrollBuffer(&buffer[0], 200);
      externalMessage == false;
      // Serial.println("Event: External Message");
      // Serial.println(msg); Serial.println("");
    }

    consumeASCII = getServerConsume();
    // Serial.println("Event: getServerConsume");
    serverDown = getServerState();
    // Serial.println("Event: getServerState");
    Serial.println("");
    // delay(500);
  }
}

void pin_ISR(){ // interruption 0
  
  Serial.println("Event: Interruption!");
  
  char msg[] = "+1 !!";

  //buttonState = digitalRead(buttonPin);
  interruptionCounter++;

  alphBuffer(&msg[0], &interM[0], &interMLen, false);
  printStaticBuffer(&msg[0], &interM[0], 200, true);
  
  // Serial.println("static print done");

  consumeServer = consume + 0.6;
  
  Serial.println("Event: Interruption finished.");
  Serial.println("");
}

int getServerMessageLen(){
  // call server and get the message len
  return msgLenServer;
}

char getServerMessage(char *msg){
  // call server and get the message
  int i;

  for(i=0; i<=msgLenServer; i++){
    msg[i] = msgServer[i];
  }
  return;
}

String getServerConsume(){
  // call server and ask for the consume
  consume = consumeServer;
  return (String(consumeServer,1) + "l");
}

bool getServerState(){
  // call server and check its state
  return false;
}

void alphBuffer(char *M, byte *buff, int *buffLen, bool scroll){
  int i, j;
  int len = strlen(M);
  int letters[len]; //to create an array of int with the size of the message
  int lettersLens[len];

  byte *pbuff = buff;
  int *pbuffLen = buffLen;
  
  //store each letter index at letters[i]
  getLetters(&M[0], &letters[0], len); 

  //get the size of each letter and store at lettersLens[i]
  getLettersSize(&M[0], &letters[0], &lettersLens[0], len);
  
  // prepare and store buffer
  prepareBuffer(&letters[0], &lettersLens[0], len, &pbuff[0], pbuffLen, scroll);

}

void prepareBuffer(int *letters, int *lettersLens, int len, byte *buff, int *buffLen, bool scroll){
  int i, j, k=16;

  if (scroll)
    k=5*DISP+1;
  else
    k=0;

  for (i=0; i<len; i++){
    for (j=0; j<lettersLens[i]; j++){
      buff[k++] = alph[letters[i]][j];
    }

    buff[k++] = alph[0][0];

    if (k>=315){
      *buffLen = k;
      return;
    }
  }
  
  *buffLen = k;
  return;
}

void getLettersSize(char *M, int *letters, int *lettersLens, int len){
  int i, j;

  for (i=0; i<len; i++){
    for (j=0; j<7; j++){
      if(letters[i] == 0){ //to find space (" ")
        lettersLens[i] = 1;
        break;
      }
      else if(alph[letters[i]][j] == B00000000){
        lettersLens[i] = j;
        break;
      }
    }
  }
  return;
}

void getLetters(char *M, int *letters, int len){
  int i;
  for (i=0; i<len; i++){ //get each letter and store at letters[i]
    letters[i] = M[i] - 32;
  }
  return;
}

void printScrollBuffer(byte *buff, int time){
  int i;
  Serial.println(bufferLen);

  for (i=0; i<bufferLen+15; i++){
     staticPrint(i, i+15, &buff[0], time);
  }
}

int getZones(int len, int *lettersLens){
  int i, counter=0, zone=0;

  for (i=0; i<len; i++){
    counter = counter + lettersLens[i] + 1;
  }

  // Serial.println("Debug 03:");
  // Serial.println("counter");
  // Serial.println(counter);
  // Serial.println("");

  while (counter>0){
    zone++;
    counter-= DISP*5;
  }

  // Serial.println("Debug 01:");
  // Serial.println("zone");
  // Serial.println(zone);
  // Serial.println("");

  return(zone);
}

void printStaticBuffer(char *M, byte *buff, int time, bool interrupt){
  int i, j, zone, counter, temp;
  int len = strlen(M);
  int letters[len]; //to store the letters index
  int lettersLens[len]; //to store the letters length

  // Serial.println("Debug 02:");
  // Serial.println("Len");
  // Serial.println(len);
  // Serial.println("");

  getLetters(&M[0], &letters[0], len);
  getLettersSize(&M[0], &letters[0], &lettersLens[0], len);

  zone = getZones(len, &lettersLens[0]);
  int zoneS[zone], zoneE[zone];
  
  counter=zoneS[0]=temp = 0;
  
  for (i=0; i<zone; i++){
    counter = 0;
    
    for (j=zoneS[i]; j<zoneS[i]+5*DISP; j++){
      counter = counter + lettersLens[temp] + 1;
      temp++;
      
      if ((counter-1) > 5*DISP){
        temp--;
        counter = counter-lettersLens[temp]-1;
        zoneE[i] = zoneS[i]+counter;

        if (i != zone-1){ //to find the last zone
          zoneS[i+1] = zoneE[i];
        }
        break;
      }
    }    
  }
  
  if(interrupt==true){
    staticInterruptPrint(zoneS[0], zoneE[0], &buff[0], 300); 
    //new function due the lack of timers =/
  }
  else{
    for (i=0; i<zone; i++){
      // staticPrint(zoneS[i], zoneE[i], &buff[0], time);
      staticInterruptPrint(zoneS[i], zoneE[i], &buff[0], 300);
    }
  }
}

void staticPrint(int start, int end, byte *buff, int timeInterval){
  int i, j, k;
  unsigned long actualTime = millis();
  unsigned long startTime = actualTime;

  byte logAND, message;

  while((actualTime-startTime) < timeInterval){
    reg2 = B10000000;
    reg3 = B00000000;

    for (i=start; i<end; i++){
      logAND =  B10000000;
      
      for (j=0; j<7; j++){
        message = logAND & buff[i];
        
        if (message != B00000000){
          latchLOW();
          shiftOut(dataPin, clockPin, LSBFIRST, reg3);
          shiftOut(dataPin, clockPin, LSBFIRST, reg2);
          shiftOut(dataPin, clockPin, LSBFIRST, message);
          latchHIGH();
          //delay(5);
        }
        logAND = logAND >> 1;
      }

      if (reg2 != B00000001 && reg3 == B00000000){
        reg2 = reg2>>1;
      } else if(reg2 == B00000001){
        reg2 = reg2>>1;
        reg3 = B10000000;
      } else{
        reg3 = reg3>>1;
      }
    }
    actualTime = millis();
  }
  clear();
}

void staticInterruptPrint(int start, int end, byte *buff, int timesPrinted){
  int i, j, counter = 0;
  byte logAND, message;

  while(counter++ < timesPrinted){
    reg2 = B10000000;
    reg3 = B00000000;

    for (i=start; i<end; i++){
      logAND =  B10000000;
      
      for (j=0; j<7; j++){
        message = logAND & buff[i];
        
        if (message != B00000000){
          latchLOW();
          shiftOut(dataPin, clockPin, LSBFIRST, reg3);
          shiftOut(dataPin, clockPin, LSBFIRST, reg2);
          shiftOut(dataPin, clockPin, LSBFIRST, message);
          latchHIGH();
          //delay(5);
        }
        logAND = logAND >> 1; 
      }
      
      if (reg2 != B00000001 && reg3 == B00000000){
        reg2 = reg2>>1;
      } 
      else if(reg2 == B00000001){
        reg2 = reg2>>1;
        reg3 = B10000000;
      } 
      else{
        reg3 = reg3>>1;
      }
    }
  }
  clear();
}


/*
void test2D(void (*latchLOW)(), void (*latchHIGH)()){
  int i, j;
  byte dotColReg2 = B10000000;
  byte dotColReg3 = B00000000;
  byte dotRow = B10000000;
  
  for (j=0; j<=5*REG; j++){
    for (i=0; i<=7; i++){
      latchLOW();
      shiftOut(dataPin, clockPin, LSBFIRST, dotColReg3);
      shiftOut(dataPin, clockPin, LSBFIRST, dotColReg2);
      shiftOut(dataPin, clockPin, LSBFIRST, dotRow);
      latchHIGH();
      delay(100);

      dotRow = dotRow>>1;
      if (dotRow == B00000000)
        dotRow = B10000000;
    }

    dotColReg2 = dotColReg2 >> 1;
    dotColReg3 = dotColReg3 >> 1;
    if (dotColReg2 == B00000000 && dotColReg3 == B00000000)
      dotColReg3 = dotColReg3 | B10000000; 
      if (dotColReg3 == B00000001)
        return;
  }
}

void testRow(){
  int i;
  byte states = B10000000;
  byte reg2 = B10000000;
  byte reg3 = B00000000;

  for (i=0; i<8; i++){
    latchLOW();   
    shiftOut(dataPin, clockPin, LSBFIRST, reg3);
    shiftOut(dataPin, clockPin, LSBFIRST, reg2);
    shiftOut(dataPin, clockPin, LSBFIRST, states);
    latchHIGH();

    reg2 = reg2>>1;
    //states = states>>1;
  }
}
*/

void latchLOW(){
  digitalWrite(latchPin, LOW);
}

void latchHIGH(){
  digitalWrite(latchPin, HIGH);
}

void clear(){//void (*latchLOW)(), void (*latchHIGH)()){
  latchLOW();
  for (int i=0; i<5*DISP; i++)
    shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  latchHIGH();
}
