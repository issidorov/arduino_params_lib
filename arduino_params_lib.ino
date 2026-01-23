#include "lib.hpp"

uint8_t ggg1 = 12;
uint8_t ggg2 = 34;
String ggg3 = "hello!";

struct MyGG {
    int a;
    int b;
    int c;
};

MyGG ggg4[10] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {10, 11, 12},
};
unsigned int ggg4_len = 4;

float ggg5 = 0.545;
double ggg6 = 0.343562;

char* ggg7 = strdup("Hello char* string!");
//char* ggg7 = nullptr;

BEGIN_PARAMS()
    PARAM(ggg1)
    PARAM(ggg2)
    PARAM(ggg3)
    PARAM_TABLE(ggg4, ggg4_len, a, b, c)
    PARAM(ggg5)
    PARAM(ggg6)
    PARAM(ggg7)
END_PARAMS()

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Serial.println(ggg1);
    // Serial.println(ggg2);
    // Serial.println(ggg3);
    // delay(3000);
    xxx.update();
}
