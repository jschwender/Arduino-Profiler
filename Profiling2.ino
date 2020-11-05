/*
   Command profiling for Arduinos
   Programm for measuring the execution time of commands or sequences.
   This was tested using a ATmega32U4 at 5V, 16 MHz clock, like in Arduino micro and others…
   ©2020 J. Schwender
*/

volatile unsigned int loop_runs = 10000;
const unsigned int nb_of_pass = 100;

unsigned long initial_time = 0;
unsigned long final_time = 0;
#if defined(ARDUINO_ARCH_AVR)
String Platform="AVR";
#elif defined(ARDUINO_ARCH_SAM)
String Platform="SAM";
#endif
float duration_dummy_loop;
float dt_max = 0;
float dt_min = 100000000;

typedef struct WP {
  double t ;
  String M;
};
const int WPsize=40;
WP Val[WPsize];
// All variables used for calculations are declared globally and volatile to minimize
// any possible compiler optimisation when performing the same operation multiple times.

volatile int dummy = 0;
volatile int i = 10;
volatile int ix = 0;
volatile float float_1 = 0, float_2 = 0, float_3 = 0;
volatile double double_1 = 0, double_2 = 0, double_3 = 0;
volatile long long_1 = 0, long_2 = 0, long_3 = 0;
volatile int int_1 = 0, int_2 = 0, int_3 = 0;
volatile byte byte_1 = 0, byte_2 = 0, byte_3 = 0;
volatile boolean bool_1 = 0, bool_2 = 0, bool_3 = 0;

void setup() {

  Serial.begin (115200);
  while (!Serial);
  pinMode(9, OUTPUT);
  pinMode(10, INPUT);
}

byte funcByteRetConst() {
  return 234;
}
int funcIntRetConst() {
  return 1234;
}
int funcIntRetVar() {
  return i;
}
double func4() {
  return 3.12345;
}
double func5() {
  return double_1;
}
long func6() {
  return 123466;
}

void runTime(int i) {
  Val[i].t += (float)(final_time - initial_time) / (float)loop_runs - duration_dummy_loop; // The average duration of a dummy loop is calculated

}

void InitRandomNumbers() {
  // STEP 1 (optional): Pick some relevant random numbers to test the command under random conditions. Make sure to pick numbers appropriate for your command (e.g. no negative number for the command "sqrt()")
  randomSeed(micros()*analogRead(0));
  byte_1 = random(0, 256);
  byte_2 = random(1, 256);
  double_1 = random(0, 5.12546789);
  double_2 = random(2, 256) / (double)byte_2;
  int_1 = random(-1000, 1000);
  float_1 = random(10, 256) / (float)byte_1;
  float_2 = random(2, 256) / (float)byte_2;
  long_1 = random(-100000, 100000);
  long_2 = random(-1000, 1000);
}
/*
   We determine the time for the FOR loop, that is overhead for the measurement.
*/
void getLoopOverhead() {
  Val[ix].M = "dummy";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // A dummy instruction is introduced here. If not, the compiler is smart enough to just skip the loop entirely...
  }
  final_time = micros();
  duration_dummy_loop = (float)(final_time - initial_time) / (float)loop_runs;
  Val[ix].t = duration_dummy_loop;         ix++;
}
/*
   Now run the same FOR loop, now with our test command/sequence.
*/
void runByteDiv() {
  Val[ix].M = "b3 = b1 / b2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    byte_3 = byte_1 / byte_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteMul() {
  Val[ix].M = "b3 = b1 * b2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    byte_3 = byte_1 * byte_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteAdd() {
  Val[ix].M = "b3 = b1 + b2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    byte_3 = byte_1 + byte_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteAssGlobVar() {
  Val[ix].M = "b3 = global var";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    byte_3 = nb_of_pass;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteAssConst() {
  Val[ix].M = "b3 = 23";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    byte_3 = 23;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteShl() {
  Val[ix].M = "b3 = b1 << 4";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    byte_3 = byte_1 << 4;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteAND() {
  Val[ix].M = "b3 = b1 & 0x01";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    byte_3 = byte_1 & 0x01;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteAssBit() {
  Val[ix].M = "b3 = bit(3)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    byte_3 = bit(3);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteAssBits() {
  Val[ix].M = "b3 = bit(3) + bit(4) + bit(1)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    byte_3 = bit(3) + bit(4) + bit(1);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runLongDiv() {
  Val[ix].M = "l3 = l1 / l2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    long_3 = long_1 / long_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runLongAdd() {
  Val[ix].M = "l3 = l1 + l2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    long_3 = long_1 + long_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runLongMul() {
  Val[ix].M = "l3 = l1 * l2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    long_3 = long_1 * long_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runFloatMul() {
  Val[ix].M = "fl3 = fl1 / fl2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    float_3 = float_1 / float_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDoubleAssConst() {
  Val[ix].M = "dbl3 = 1.23";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    double_3 = 1.23734682756;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDoubleDiv() {
  Val[ix].M = "dbl3 = dbl1/dbl2;";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    double_3 = double_1 / double_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDoubleMul() {
  Val[ix].M = "dbl3 = dbl1 * dbl2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    double_3 = double_1 * double_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDoubleAdd() {
  Val[ix].M = "dbl3 = dbl1 + dbl2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    double_3 = double_1 + double_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDoublePow() {
  Val[ix].M = "dbl3 = pow(dbl1,dbl2)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    double_3 = pow(double_1, double_2);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDoubleLog() {
  Val[ix].M = "dbl3 = log(dbl2)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    double_3 = log(double_2);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDoubleSqrt() {
  Val[ix].M = "dbl3 = sqrt(dbl1)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    double_3 = sqrt(double_1);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDoubleTan() {
  Val[ix].M = "dbl3 = tan(dbl1)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    double_3 = tan(double_1);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDoubleSin() {
  Val[ix].M = "dbl3 = sin(dbl1)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++; // The dummy instruction is also performed here so that we can remove the effect of the dummy FOR loop accurately.
    double_3 = sin(double_1);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDigitalWriteLow() {
  Val[ix].M = "digitalWrite(9,LOW)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    digitalWrite(9, LOW);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runDigitalWriteHigh() {
  Val[ix].M = "digitalWrite(9,HIGH)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    digitalWrite(9, HIGH);
  }
  final_time = micros();      runTime(ix);         ix++;
}
#if defined(ARDUINO_ARCH_AVR)
void runSetbitPortB() {
  Val[ix].M = "PORTB = PORTB | 2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    PORTB = PORTB | B00000010;  // on a Due this does not work
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runReadbitPortB() {
  Val[ix].M = "bool1 = PORTB & 4";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    bool_1 = PORTB & B00000100;  // on a Due this does not work
  }
  final_time = micros();      runTime(ix);         ix++;
}
#elif defined(ARDUINO_ARCH_SAM)
void runSetbitPortB()  { Val[ix].M = "PORTB = PORTB | 2";Val[ix].t=0;ix++; };
void runReadbitPortB() { Val[ix].M = "bool1 = PORTB & 4";Val[ix].t=0;ix++; };
#endif
void runReadPort() {
  Val[ix].M = "bool1 = digitalRead(10)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    bool_1 = digitalRead(10);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runAnalogRead() {
  Val[ix].M = "int3 = analogRead(A0)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    int_3 = analogRead(A0);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteRand() {
  Val[ix].M = "b3 = random(0,256)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    byte_3 = random(0, 256);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runLongRand() {
  Val[ix].M = "l3 = random(0,100000)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    long_3 = random(0, 100000);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteMinFunc() {
  Val[ix].M = "b3 = min(b1, b2)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    byte_3 = min(byte_1, byte_2);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runCompareDbl() {
  Val[ix].M = "if (dbl1 < dbl2)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    if (double_1 < double_2);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runCompareByte() {
  Val[ix].M = "if ( b1 < b2)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    if ( byte_1 < byte_2);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runAbsInt() {
  Val[ix].M = "int3 = abs(int1)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    int_3 = abs(int_1);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runConstraint() {
  Val[ix].M = "int3 = constrain(int1, 3, 300)";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    int_3 = constrain(int_1, 3, 300);
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteIf() {
  Val[ix].M = "if (b1 < b2) b3=b1; else b3=b2";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    if (byte_1 < byte_2) byte_3 = byte_1; else byte_3 = byte_2;
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runByteCall() {
  Val[ix].M = "b3 = fByteRetConst()";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    byte_3 = funcByteRetConst();
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runIntCall() {
  Val[ix].M = "Int3 = fIntRetConst()";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    int_3 = funcIntRetConst();
  }
  final_time = micros();      runTime(ix);         ix++;
}
void runIntCallRetVar() {
  Val[ix].M = "Int3 = fIntRetVar()";
  dummy = 0;
  initial_time = micros();
  for (unsigned int i = 0; i < loop_runs ; i++) {
    dummy++;
    int_3 = funcIntRetVar();
  }
  final_time = micros();      runTime(ix);         ix++;
}

void runTest() {
  // **************** PUT YOUR COMMAND TO TEST HERE, OR UNCOMMENT A LINE ********************
  //REG_PIOD_SODR = 0x1 << 9;            // [0.221900…0.264700]µs    Ø 0.2536µs (±8.4%)  [4 4] clk  Ø 4 clk  (Due only)
  //REG_PIOD_CODR = 0x1 << 9;            // [0.223100…0.262300]µs    Ø 0.2531µs (±7.7%)  [4 4] clk  Ø 4 clk  (Due only)
  //bitSet(TCCR1A,WGM11);                // [0.314800…0.317600]µs    Ø 0.3160µs (±0.4%)  [5 5] clk  Ø 5 clk
  //int_3 = dummyfunc3();                // [0.504400…0.507200]µs    Ø 0.5057µs (±0.3%)  [8 8] clk  Ø 8 clk
  //double_3 = dummyfunc4();             // [0.757600…0.760000]µs    Ø 0.7584µs (±0.2%)  [12 12] clk  Ø 12 clk
  //double_3 = dummyfunc5();             // [1.010400…1.012400]µs    Ø 1.0112µs (±0.1%)  [16 16] clk  Ø 16 clk
  //long_3 = dummyfunc6();               // [0.757600…0.760400]µs    Ø 0.7585µs (±0.2%)  [12 12] clk  Ø 12 clk
  //int_3 += ((unsigned int)digitalRead(2) & 1)<<(14-i);  // [13.842000…13.847201]µs   Ø 13.8433µs (±0.0%) [221 222] clk  Ø 221 clk
  // **************** PUT YOUR COMMAND TO TEST HERE ********************
}
/*
   Main part
*/
void loop() {
  dt_max = 0;
  dt_min = 100000000;
  for (int j = 0; j < nb_of_pass ; j++) {
    ix = 0;
    InitRandomNumbers();
    loop_runs = 30000;
    getLoopOverhead();
    loop_runs = 1000;
    runByteDiv();
    runByteAdd();
    runByteAssGlobVar();
    runByteAssConst();
    runByteShl();
    runByteAND();
    runByteAssBit();
    runByteIf();
    runLongDiv();
    runLongMul();
    runLongAdd();
    runFloatMul();
    runCompareDbl();
    runCompareByte();
    runDoubleAssConst();
    runDoubleMul();
    runDoubleAdd();
    runByteMinFunc();
    runAbsInt();
    runConstraint();
    runByteCall();
    runIntCall();
    runIntCallRetVar();
    loop_runs = 300;
    runDoubleDiv();
    runDoublePow();
    runDoubleLog();
    runDoubleSqrt();
    runDoubleTan();
    runDoubleSin();
    runAnalogRead();
    runByteRand();
    runLongRand();
    loop_runs = 1000;
    runDigitalWriteLow();
    runDigitalWriteHigh();
    loop_runs = 10000;
    runSetbitPortB();
    runReadbitPortB();
    runReadPort();
  }
  print_final_result();
  wipe_duration();
}
/*
   Output results over serial
*/
void  print_final_result() {
  for (int i = 0; i < ix; i++) {
    Serial.print(i);
    Serial.print(";");
    Serial.print(Platform);
    Serial.print(";");
    Serial.print(Val[i].t / nb_of_pass, 8);
    Serial.print(";");
    Serial.print(Val[i].M); Serial.println(";");
  }
}
void  wipe_duration() {
  for (int i = 0; i < WPsize; i++) {
    Val[i].t = 0;
  }
}
