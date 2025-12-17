
#define FPSTR(s) (const __FlashStringHelper*)(s)

uint8_t ggg1 = 12;
uint8_t ggg2 = 34;
String ggg3 = "hello!";


class XxxParam {
public:
    PGM_P name;
    virtual String getValue();
};


class XxxParam_INT8: public XxxParam {
public:
    int8_t* var;

    XxxParam_INT8(PGM_P name, int8_t* var) {
        this->name = name;
        this->var = var;
    }

    String getValue() {
        return String(*this->var);
    }
};


class XxxParam_UINT8: public XxxParam {
public:
    uint8_t* var;

    XxxParam_UINT8(PGM_P name, uint8_t* var) {
        this->name = name;
        this->var = var;
    }

    String getValue() {
        return String(*this->var);
    }
};


class XxxParam_INT16: public XxxParam {
public:
    int16_t* var;

    XxxParam_INT16(PGM_P name, int16_t* var) {
        this->name = name;
        this->var = var;
    }

    String getValue() {
        return String(*this->var);
    }
};


class XxxParam_UINT16: public XxxParam {
public:
    uint16_t* var;

    XxxParam_UINT16(PGM_P name, uint16_t* var) {
        this->name = name;
        this->var = var;
    }

    String getValue() {
        return String(*this->var);
    }
};


class XxxParam_STRING: public XxxParam {
public:
    String* var;

    XxxParam_STRING(PGM_P name, String* var) {
        this->name = name;
        this->var = var;
    }

    String getValue() {
        return *this->var;
    }
};


template <uint8_t num>
class XxxParamsCollection {
private:
    XxxParam* params[num];
    uint8_t count = 0;

public:
    void add(XxxParam* param) {
        params[count] = param;
        ++count;
    }

    bool notEmpty() {
        return params[0];
    }

    void foreach(void (*fn)(XxxParam*)) {
        uint8_t i;
        for (i = 0; i < count; i++) {
            fn(params[i]);
        }
    }
};


template <uint8_t num>
class XXX {
private:
    XxxParamsCollection<num> params;

public:
    void appendParam(PGM_P name, int8_t* var) {
        XxxParam* param = new XxxParam_INT8(name, var);
        params.add(param);
    }

    void appendParam(PGM_P name, uint8_t* var) {
        XxxParam* param = new XxxParam_UINT8(name, var);
        params.add(param);
    }

    void appendParam(PGM_P name, int16_t* var) {
        XxxParam* param = new XxxParam_INT16(name, var);
        params.add(param);
    }

    void appendParam(PGM_P name, uint16_t* var) {
        XxxParam* param = new XxxParam_UINT16(name, var);
        params.add(param);
    }

    void appendParam(PGM_P name, String* var) {
        XxxParam* param = new XxxParam_STRING(name, var);
        params.add(param);
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
        if (params.notEmpty()) {
            params.foreach([](XxxParam* param) {
                Serial.print(FPSTR(param->name));
                Serial.print(" ");
                Serial.print(param->getValue());
                Serial.println();
            });
        } else {
            Serial.println(F("Hello"));
        }
    }
};


XXX<10> myXxx;


void setup() {
    Serial.begin(9600);
    myXxx.appendParam(PSTR("ggg1"), &ggg1);
    myXxx.appendParam(PSTR("ggg2"), &ggg2);
    myXxx.appendParam(PSTR("ggg3"), &ggg3);
}


void loop() {
    myXxx.update();
}




