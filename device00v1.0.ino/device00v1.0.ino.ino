int clockPin = 11;
int latchPin = 12;
int dataPin = 13;

int REG = 3;
int DISP = 3;
byte reg2, reg3;

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin,  OUTPUT);
  
  digitalWrite(latchPin, LOW);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  digitalWrite(latchPin, HIGH);
  
  Serial.begin(9600);
}
/*
ASCII Table ~ Character Map
!, dec: 33, hex: 21, oct: 41, bin: 100001
", dec: 34, hex: 22, oct: 42, bin: 100010
#, dec: 35, hex: 23, oct: 43, bin: 100011
$, dec: 36, hex: 24, oct: 44, bin: 100100
%, dec: 37, hex: 25, oct: 45, bin: 100101
&, dec: 38, hex: 26, oct: 46, bin: 100110
', dec: 39, hex: 27, oct: 47, bin: 100111
(, dec: 40, hex: 28, oct: 50, bin: 101000
), dec: 41, hex: 29, oct: 51, bin: 101001
*, dec: 42, hex: 2A, oct: 52, bin: 101010
+, dec: 43, hex: 2B, oct: 53, bin: 101011
,, dec: 44, hex: 2C, oct: 54, bin: 101100
-, dec: 45, hex: 2D, oct: 55, bin: 101101
., dec: 46, hex: 2E, oct: 56, bin: 101110
/, dec: 47, hex: 2F, oct: 57, bin: 101111
0, dec: 48, hex: 30, oct: 60, bin: 110000
1, dec: 49, hex: 31, oct: 61, bin: 110001
2, dec: 50, hex: 32, oct: 62, bin: 110010
3, dec: 51, hex: 33, oct: 63, bin: 110011
4, dec: 52, hex: 34, oct: 64, bin: 110100
5, dec: 53, hex: 35, oct: 65, bin: 110101
6, dec: 54, hex: 36, oct: 66, bin: 110110
7, dec: 55, hex: 37, oct: 67, bin: 110111
8, dec: 56, hex: 38, oct: 70, bin: 111000
9, dec: 57, hex: 39, oct: 71, bin: 111001
:, dec: 58, hex: 3A, oct: 72, bin: 111010
;, dec: 59, hex: 3B, oct: 73, bin: 111011
<, dec: 60, hex: 3C, oct: 74, bin: 111100
=, dec: 61, hex: 3D, oct: 75, bin: 111101
>, dec: 62, hex: 3E, oct: 76, bin: 111110
?, dec: 63, hex: 3F, oct: 77, bin: 111111
@, dec: 64, hex: 40, oct: 100, bin: 1000000
A, dec: 65, hex: 41, oct: 101, bin: 1000001
B, dec: 66, hex: 42, oct: 102, bin: 1000010
C, dec: 67, hex: 43, oct: 103, bin: 1000011
D, dec: 68, hex: 44, oct: 104, bin: 1000100
E, dec: 69, hex: 45, oct: 105, bin: 1000101
F, dec: 70, hex: 46, oct: 106, bin: 1000110
G, dec: 71, hex: 47, oct: 107, bin: 1000111
H, dec: 72, hex: 48, oct: 110, bin: 1001000
I, dec: 73, hex: 49, oct: 111, bin: 1001001
J, dec: 74, hex: 4A, oct: 112, bin: 1001010
K, dec: 75, hex: 4B, oct: 113, bin: 1001011
L, dec: 76, hex: 4C, oct: 114, bin: 1001100
M, dec: 77, hex: 4D, oct: 115, bin: 1001101
N, dec: 78, hex: 4E, oct: 116, bin: 1001110
O, dec: 79, hex: 4F, oct: 117, bin: 1001111
P, dec: 80, hex: 50, oct: 120, bin: 1010000
Q, dec: 81, hex: 51, oct: 121, bin: 1010001
R, dec: 82, hex: 52, oct: 122, bin: 1010010
S, dec: 83, hex: 53, oct: 123, bin: 1010011
T, dec: 84, hex: 54, oct: 124, bin: 1010100
U, dec: 85, hex: 55, oct: 125, bin: 1010101
V, dec: 86, hex: 56, oct: 126, bin: 1010110
W, dec: 87, hex: 57, oct: 127, bin: 1010111
X, dec: 88, hex: 58, oct: 130, bin: 1011000
Y, dec: 89, hex: 59, oct: 131, bin: 1011001
Z, dec: 90, hex: 5A, oct: 132, bin: 1011010
[, dec: 91, hex: 5B, oct: 133, bin: 1011011
\, dec: 92, hex: 5C, oct: 134, bin: 1011100
], dec: 93, hex: 5D, oct: 135, bin: 1011101
^, dec: 94, hex: 5E, oct: 136, bin: 1011110
_, dec: 95, hex: 5F, oct: 137, bin: 1011111
`, dec: 96, hex: 60, oct: 140, bin: 1100000
a, dec: 97, hex: 61, oct: 141, bin: 1100001
b, dec: 98, hex: 62, oct: 142, bin: 1100010
c, dec: 99, hex: 63, oct: 143, bin: 1100011
d, dec: 100, hex: 64, oct: 144, bin: 1100100
e, dec: 101, hex: 65, oct: 145, bin: 1100101
f, dec: 102, hex: 66, oct: 146, bin: 1100110
g, dec: 103, hex: 67, oct: 147, bin: 1100111
h, dec: 104, hex: 68, oct: 150, bin: 1101000
i, dec: 105, hex: 69, oct: 151, bin: 1101001
j, dec: 106, hex: 6A, oct: 152, bin: 1101010
k, dec: 107, hex: 6B, oct: 153, bin: 1101011
l, dec: 108, hex: 6C, oct: 154, bin: 1101100
m, dec: 109, hex: 6D, oct: 155, bin: 1101101
n, dec: 110, hex: 6E, oct: 156, bin: 1101110
o, dec: 111, hex: 6F, oct: 157, bin: 1101111
p, dec: 112, hex: 70, oct: 160, bin: 1110000
q, dec: 113, hex: 71, oct: 161, bin: 1110001
r, dec: 114, hex: 72, oct: 162, bin: 1110010
s, dec: 115, hex: 73, oct: 163, bin: 1110011
t, dec: 116, hex: 74, oct: 164, bin: 1110100
u, dec: 117, hex: 75, oct: 165, bin: 1110101
v, dec: 118, hex: 76, oct: 166, bin: 1110110
w, dec: 119, hex: 77, oct: 167, bin: 1110111
x, dec: 120, hex: 78, oct: 170, bin: 1111000
y, dec: 121, hex: 79, oct: 171, bin: 1111001
z, dec: 122, hex: 7A, oct: 172, bin: 1111010
{, dec: 123, hex: 7B, oct: 173, bin: 1111011
|, dec: 124, hex: 7C, oct: 174, bin: 1111100
}, dec: 125, hex: 7D, oct: 175, bin: 1111101
~, dec: 126, hex: 7E, oct: 176, bin: 1111110
*/

// __110)1
// 111010_

byte alph[][7] = {
  {B00000000, B00000000, B00000000, B00000000, B00000000, B00000000, B00000000}, // " "
  {B11101000, B10101000, B10101000, B11111000, B00000000, B00000000, B00000000}, //a
  {B11111111, B10010000, B10010000, B11110000, B00000000, B00000000, B00000000}, //b 
  {B01110000, B10001000, B10001000, B10001000, B00000000, B00000000, B00000000}, //c
  {B11110000, B10010000, B10010000, B11111111, B00000000, B00000000, B00000000}, //d
  {B11111000, B10101000, B10101000, B10111000, B00000000, B00000000, B00000000}, //e
  {B10001000, B01111100, B00001010, B00000000, B00000000, B00000000, B00000000}, //f
  {B01011100, B10010100, B10010100, B11111100, B00000000, B00000000, B00000000}, //g
  {B11111111, B00010000, B00010000, B11100000, B00000000, B00000000, B00000000}, //h
  {B01110100, B10000000, B00000000, B00000000, B00000000, B00000000, B00000000}, //i
  {B10000000, B10000000, B01110100, B00000000, B00000000, B00000000, B00000000}, //j
  {B11111100, B00100000, B11011000, B00000000, B00000000, B00000000, B00000000}, //k
  {B01111100, B10000000, B10000000, B00000000, B00000000, B00000000, B00000000}, //l
  {B11111000, B00110000, B01100000, B00110000, B11111000, B00000000, B00000000}, //m
  {B11111000, B00110000, B01100000, B11111000, B00000000, B00000000, B00000000}, //n
  {B01110000, B10001000, B10001000, B10001000, B01110000, B00000000, B00000000}, //o
  {B11111000, B00101000, B00101000, B00101000, B00010000, B00000000, B00000000}, //p
  {B00010000, B00101000, B00101000, B00101000, B11110000, B00000000, B00000000}, //q
  {B11111000, B00100000, B00010000, B00001000, B00001000, B00000000, B00000000}, //r
  {B10010000, B10101000, B10101000, B10101000, B01001000, B00000000, B00000000}, //s
  {B00010000, B01111000, B10010000, B10010000, B00000000, B00000000, B00000000}, //t
  {B01110000, B10000000, B10000000, B01110000, B10000000, B00000000, B00000000}, //u
  {B00110000, B01000000, B10000000, B01000000, B00110000, B00000000, B00000000}, //v
  {B10010000, B01100000, B01100000, B10010000, B00000000, B00000000, B00000000}, //x
  {B11110000, B01000000, B00100000, B01000000, B11110000, B00000000, B11111000}, //w
  {B10010000, B10100000, B01000000, B00100000, B00010000, B00000000, B00000000}, //y
  {B10010000, B10110000, B11110000, B11010000, B10010000, B00000000, B00000000}, //z

};

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
                 B00000000, B00000000, B00000000, B00000000, B00000000};//60

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

void loop() {
  
  int i,j,m;
  char M[] = "fghij";
  int len = strlen(M);
  int time = 200;
  bool scroll;
  alphBuffer(&M[0], &staticM[0], false);

  // for (j=0; j<time; j++){
  //   printBuffer(16, 16+15);
  // }
  // for (j=0; j<time; j++){
  //   printBuffer(16+15, 16+15+14);
  // }

  // for (j=0; j<time; j++){
  //   printBuffer(16+15+14, 16+15+14+10);
  // }

  // for (j=0; j<time; j++){
  //   printsBuffer(0, 30, &staticM[0], time);//, &buffer[0]);
  // }
  printsBuffer(0, 60, &staticM[0], time);//, &buffer[0]);

  
  // for (i=0; i<bufferLen+15; i++){
  //   for (j=0; j<30; j++){
  //     printBuffer(i, i+15);
  //   }
  // }
}
void staticPrint(char *M){
  int x = 0;
}

void alphBuffer(char *M, byte *buff, bool scroll){
  int i, j;
  int len = strlen(M);
  int letters[len]; //to create an array of int with the size of the message
  int lettersLens[len];

  byte *pbuff = buff;
  
  //store each letter index at letters[i]
  getLetters(&M[0], &letters[0], len); 

  //get the size of each letter and store at lettersLens[i]
  getLettersSize(&M[0], &letters[0], &lettersLens[0], len);
  
  // prepare and store buffer
  prepareBuffer(&letters[0], &lettersLens[0], len, &pbuff[0], scroll);

}

void prepareBuffer(int *letters, int *lettersLens, int len, byte *buff, bool scroll){
  int i, j, k=16;

  if (scroll)
    k=16;
  else
    k=0;

  for (i=0; i<len; i++){
    for (j=0; j<lettersLens[i]; j++){
      //buffer[k++] = alph[letters[i]][j];
      buff[k++] = alph[letters[i]][j];
    }

    //buffer[k++] = alph[0][0];
    buff[k++] = alph[0][0];

    bufferLen = k;

    if (k>=315){
      return;
    }
  }
  //Serial.println(k);
  /*
  Serial.println("<------------- debug02 - start ------------->");
  Serial.println("len");
  Serial.println(len);
  Serial.println(bufferD[0], BIN);
  Serial.println(bufferD[k-1], BIN);
  Serial.println("<------------- debug02 - end   ------------->"); Serial.print("\n");
  */
  return;
}


void getLettersSize(char *M, int *letters, int *lettersLens, int len){
  int i, j;

  for (i=0; i<len; i++){
    for (j=0; j<7; j++){
      if(alph[letters[i]][j] == B00000000){
        lettersLens[i] = j;
        break;
      }
    }
  }
  /*
  Serial.println("<------------- debug01 - start ------------->");
  Serial.println("lettersLens 0 and 1");
  Serial.println(lettersLens[0]);
  Serial.println(lettersLens[1]);
  Serial.println("<------------- debug01 - end   ------------->"); Serial.print("\n");
  */
  return;
}

void getLetters(char *M, int *letters, int len){
  int i;
  for (i=0; i<len; i++){ //get each letter and store at letters[i]
    letters[i] = M[i] - 96;
  }
  /*
  Serial.println("<------------- debug00 - start ------------->");
  Serial.println(letters[0]);
  Serial.println(letters[1]);
  Serial.println("<------------- debug00 - end   ------------->"); Serial.print("\n");
  */
  return;
}

void printBuffer(int start, int end){
  int i;
  
  reg2 = B10000000;
  reg3 = B00000000;

  for (i=start; i<end; i++){//i<(start+5*DISP); i++){
    latchLOW();   
    shiftOut(dataPin, clockPin, LSBFIRST, reg3);
    shiftOut(dataPin, clockPin, LSBFIRST, reg2);
    shiftOut(dataPin, clockPin, LSBFIRST, buffer[i]);
    latchHIGH();;

    if (reg2 != B00000001 && reg3 == B00000000){
      reg2 = reg2>>1;
    } else if(reg2 == B00000001){
      reg2 = reg2>>1;
      reg3 = B10000000;
    } else{
      reg3 = reg3>>1;
    }
  }
}

void printsBuffer(int start, int end, byte *buff, int time){
  int counter, i, k;
  int zoneStart, zoneEnd;

  // Serial.println(buff[end], BIN);
  // Serial.println(buff[end+1], BIN);
  // delay(1000);
  for(k=start; k<end+1; k++){
    if(buff[k] == B00000000 && buff[k+1] == B00000000){
      counter = k;
      break;
    }
  }

  // Serial.println(counter/15); delay(1000);

  zoneStart = 0;
  zoneEnd = 0;

  for (i=0; i<counter/15; i++){
    // Serial.println(counter/15);delay(1000);
    zoneEnd += 15;
    //Serial.println(zoneEnd); delay(1000);
  }
  // Serial.println(zoneEnd); delay(1000);

  //staticPrint(0, 15, &staticM[0], 5000);

  for (i=0; i<counter/15; i++){
    Serial.println(i);
    staticPrint(i*15, i*15+15, &staticM[0], time);
  }
}

void staticPrint(int start, int end, byte *buff, int time){
  int i, j, k;
  byte logAND, message;

  for(k=0; k<time; k++){
    reg2 = B10000000;
    reg3 = B00000000;
    for (i=start; i<end; i++){
      // latchLOW();   
      
      logAND =  B10000000;
      for (j=0; j<7; j++){
        message = logAND & buff[i];
        if (message != B00000000){
          latchLOW();
          shiftOut(dataPin, clockPin, LSBFIRST, reg3);
          shiftOut(dataPin, clockPin, LSBFIRST, reg2);
          shiftOut(dataPin, clockPin, LSBFIRST, message);
          latchHIGH();;
          //delay(5);
        }
        logAND = logAND >> 1; 
      }
      // latchHIGH();;

      if (reg2 != B00000001 && reg3 == B00000000){
        reg2 = reg2>>1;
      } else if(reg2 == B00000001){
        reg2 = reg2>>1;
        reg3 = B10000000;
      } else{
        reg3 = reg3>>1;
      }
    }
  }
}

void printDisp(byte *cols){
  byte reg[2];
  int i;
  
  reg[0] = B10000000;
  reg[1] = B00000000;

  for (i=0; i<15; i++){
    latchLOW();   
    shiftOut(dataPin, clockPin, LSBFIRST, reg[1]);
    shiftOut(dataPin, clockPin, LSBFIRST, reg[0]);
    shiftOut(dataPin, clockPin, LSBFIRST, cols[i]);
    latchHIGH();
    //delay(1);

    if (reg[0] != B00000001 && reg[1] == B00000000){
      reg[0] = reg[0]>>1;
    } else if(reg[0] == B00000001){
      reg[0] = reg[0]>>1;
      reg[1] = B10000000;
    } else{
      reg[1] = reg[1]>>1;
    }
  }
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

void clear(void (*latchLOW)(), void (*latchHIGH)()){
  latchLOW();
  for (int i=0; i<REG; i++)
    shiftOut(dataPin, clockPin, LSBFIRST, B00000000);
  latchHIGH();
}
