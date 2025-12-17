
#define FPSTR(s) (const __FlashStringHelper*)(s)

uint8_t ggg1 = 12;
uint8_t ggg2 = 34;
String ggg3 = "hello!";

enum class XxxType {
    INT8,
    UINT8,
    INT16,
    UINT16,
    STRING,
};

struct XxxParam {
    PGM_P name;
    XxxType type;
    void* var;
};

class XXX {
private:
    XxxParam* params[10] = {};
    uint8_t paramsCount = 0;

public:
    void appendParam(PGM_P name, int8_t* var) {
        doAppendParam(name, XxxType::INT8, var);
    }

    void appendParam(PGM_P name, uint8_t* var) {
        doAppendParam(name, XxxType::UINT8, var);
    }

    void appendParam(PGM_P name, int16_t* var) {
        doAppendParam(name, XxxType::INT16, var);
    }

    void appendParam(PGM_P name, uint16_t* var) {
        doAppendParam(name, XxxType::UINT16, var);
    }

    void appendParam(PGM_P name, String* var) {
        doAppendParam(name, XxxType::STRING, var);
    }

    void doAppendParam(PGM_P name, XxxType type, void* var) {
        auto param = new XxxParam();
        param->name = name;
        param->type = type;
        param->var = var;
        params[paramsCount] = param;
        ++paramsCount;
    }

    void update() {
        if (Serial.available()) {
            String line = Serial.readStringUntil('\n');
            if (line == "help") {
                cmdHelp();
            }
        }
    }

    void cmdHelp() {
        if (params[0]) {
            for (uint8_t i = 0; params[i]; i++) {
                XxxParam* param = params[i];
                Serial.print(FPSTR(param->name));
                Serial.print(" ");
                Serial.print(getParamValue(param));
                Serial.println();
            }
        } else {
            Serial.println(F("Hello"));
        }
    }

    String getParamValue(XxxParam* param) {
        switch (param->type) {
            case XxxType::INT8:
                return String(*(int8_t*)param->var);
            case XxxType::UINT8:
                return String(*(uint8_t*)param->var);
            case XxxType::INT16:
                return String(*(int16_t*)param->var);
            case XxxType::UINT16:
                return String(*(uint16_t*)param->var);
            case XxxType::STRING:
                return String(*(String*)param->var);
        }
    }
};


XXX myXxx;


void setup() {
    Serial.begin(9600);
    myXxx.appendParam(PSTR("ggg1"), &ggg1);
    myXxx.appendParam(PSTR("ggg2"), &ggg2);
    myXxx.appendParam(PSTR("ggg3"), &ggg3);
}


void loop() {
    myXxx.update();
}




