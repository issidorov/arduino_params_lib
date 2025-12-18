
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
    void* var;
    XxxType type;

    String getValue() {
        switch (type) {
            case XxxType::INT8:
                return String(*(int8_t*)var);
            case XxxType::UINT8:
                return String(*(uint8_t*)var);
            case XxxType::INT16:
                return String(*(int16_t*)var);
            case XxxType::UINT16:
                return String(*(uint16_t*)var);
            case XxxType::STRING:
                return *(String*)var;
        }
    }
};


template <uint8_t num>
class XxxParamsCollection {
private:
    XxxParam params[num];
    uint8_t count = 0;

public:
    void add(XxxParam param) {
        params[count] = param;
        ++count;
    }

    bool notEmpty() {
        return count > 0;
    }

    void foreach(void (*fn)(XxxParam&)) {
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
    void setParam(PGM_P name, int8_t* var) {
        XxxParam param = {name, var, XxxType::INT8};
        params.add(param);
    }

    void setParam(PGM_P name, uint8_t* var) {
        XxxParam param = {name, var, XxxType::UINT8};
        params.add(param);
    }

    void setParam(PGM_P name, int16_t* var) {
        XxxParam param = {name, var, XxxType::INT16};
        params.add(param);
    }

    void setParam(PGM_P name, uint16_t* var) {
        XxxParam param = {name, var, XxxType::UINT16};
        params.add(param);
    }

    void setParam(PGM_P name, String* var) {
        XxxParam param = {name, var, XxxType::STRING};
        params.add(param);
    }

    void update() {
        if (Serial.available()) {
            char* line = Serial.readStringUntil('\n').c_str();
            if (strcmp_P(line, PSTR("help")) == 0) {
                cmdHelp();
            }
        }
    }

    void cmdHelp() {
        if (params.notEmpty()) {
            params.foreach([](XxxParam& param) {
                Serial.print(FPSTR(param.name));
                Serial.print(" ");
                Serial.print(param.getValue());
                Serial.println();
            });
        } else {
            Serial.println(F("Hello"));
        }
    }
};


XXX<3> myXxx;


void setup() {
    Serial.begin(9600);
    myXxx.setParam(PSTR("ggg1"), &ggg1);
    myXxx.setParam(PSTR("ggg2"), &ggg2);
    myXxx.setParam(PSTR("ggg3"), &ggg3);
}


void loop() {
    myXxx.update();
}




