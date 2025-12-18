
#define FPSTR(s) (const __FlashStringHelper*)(s)

uint8_t ggg1 = 12;
uint8_t ggg2 = 34;
String ggg3 = "hello!";



struct XxxParam {
    PGM_P name;
    void* var;
    String (*getValue)(void* var);
};


String getValue_INT8(void* var) {
    return String(*(int8_t*)var);
}
constexpr XxxParam buildXxxParam(PGM_P name, int8_t* var) {
    return {name, var, getValue_INT8};
}


String getValue_UINT8(void* var) {
    return String(*(uint8_t*)var);
}
constexpr XxxParam buildXxxParam(PGM_P name, uint8_t* var) {
    return {name, var, getValue_UINT8};
}


String getValue_INT16(void* var) {
    return String(*(int16_t*)var);
}
constexpr XxxParam buildXxxParam(PGM_P name, int16_t* var) {
    return {name, var, getValue_INT16};
}


String getValue_UINT16(void* var) {
    return String(*(uint16_t*)var);
}
constexpr XxxParam buildXxxParam(PGM_P name, uint16_t* var) {
    return {name, var, getValue_UINT16};
}


String getValue_STRING(void* var) {
    return String(*(String*)var);
}
constexpr XxxParam buildXxxParam(PGM_P name, String* var) {
    return {name, var, getValue_STRING};
}


typedef XxxParam* FnParamsGetter(uint8_t index);


class XxxParamsIterrator {
protected:
    uint8_t index = 0;
    FnParamsGetter* paramsGetter;
public:
    void setParamsGetter(FnParamsGetter* getter) {
        paramsGetter = getter;
    }

    XxxParam* next() {
        XxxParam* param = paramsGetter(index);
        if (!param) {
            return nullptr;
        }
        ++index;
        return param;
    }

    void reset() {
        index = 0;
    }
};


void printParam(const XxxParam& param) {
    Serial.print(FPSTR(param.name));
    Serial.print(" ");
    Serial.print(param.getValue(param.var));
    Serial.println();
}

class XXX {
private:
    XxxParamsIterrator params;

public:
    XXX(FnParamsGetter* paramsGetter) {
        params.setParamsGetter(paramsGetter);
    }

    void update() {
        if (Serial.available()) {
            String line = Serial.readStringUntil('\n');
            if (strcmp_P(line.c_str(), PSTR("params")) == 0) {
                cmdParams();
            }
        }
    }

    void cmdParams() {
        XxxParam* param;
        params.reset();
        while(param = params.next()) {
            printParam(*param);
        }
    }
};



#define BEGIN_PARAMS(fn_name) \
                                    XxxParam* fn_name(uint8_t index) { \
                                        const uint8_t COUNTER_BASE = __COUNTER__ + 1; \
                                        static XxxParam param; \
                                        switch (index) {
#define PARAM(var) \
                                            case (__COUNTER__ - COUNTER_BASE): \
                                                param = buildXxxParam(PSTR(#var), &var); \
                                                break;
#define END_PARAMS() \
                                            default: \
                                                return nullptr; \
                                        } \
                                        return &param; \
                                    };





BEGIN_PARAMS(paramsStore)
    PARAM(ggg1)
    PARAM(ggg2)
    PARAM(ggg3)
END_PARAMS()


XXX myXxx(&paramsStore);

void setup() {
    Serial.begin(9600);
}

void loop() {
    myXxx.update();
}


