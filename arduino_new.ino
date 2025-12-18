
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



class XXX {
private:
    const XxxParam** params;

public:
    XXX(const XxxParam** params) {
        this->params = params;
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
        uint8_t i;
        XxxParam param;
        for (i = 0; ; ++i) {
            XxxParam* param_p = pgm_read_ptr(&params[i]);
            if (!param_p) break;
            memcpy_P(&param, param_p, sizeof(XxxParam));
            printParam(param);
        }
        if (!i) {
            Serial.println(F("Not has params!"));
        }
    }

    void printParam(const XxxParam& param) {
        Serial.print(FPSTR(param.name));
        Serial.print(" ");
        Serial.print(param.getValue(param.var));
        Serial.println();
    }
};



#define XXX_PARAM(var) \
    const char var ## _name[] PROGMEM = #var; \
    const XxxParam var ## _param PROGMEM = buildXxxParam(var ## _name, &var); \

XXX_PARAM(ggg1);
XXX_PARAM(ggg2);
XXX_PARAM(ggg3);

const XxxParam* const params_X[] PROGMEM = {
    &ggg1_param,
    &ggg2_param,
    &ggg3_param,
    nullptr,
};

XXX myXxx(params_X);


void setup() {
    Serial.begin(9600);
}


void loop() {
    myXxx.update();
}




