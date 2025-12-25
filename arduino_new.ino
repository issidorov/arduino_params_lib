#include <EEPROM.h>
#include <FOR_MACRO.h>

#define FPSTR(s) (const __FlashStringHelper*)(s)

uint8_t ggg1 = 12;
uint8_t ggg2 = 34;
String ggg3 = "hello!";

struct MyGG {
    int a;
    int b;
    int c;
};

MyGG ggg4[] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9},
    {10, 11, 12},
};


typedef String FnValueGetter(void* var);
typedef void FnValueSetter(void* var, const char* value);
typedef size_t FnValueLoad(unsigned int addr, void* var);
typedef size_t FnValueSave(unsigned int addr, const void* var);

struct XxxParam {
    PGM_P name;
    void* var;
    FnValueGetter* getValue;
    FnValueSetter* setValue;
    FnValueLoad* loadValue;
    FnValueSave* saveValue;
};

bool XxxParamsStore(XxxParam* buf, uint8_t index);



typedef bool XxxParamTable_provider_fn(XxxParam* param, uint8_t col_index, unsigned int row_index);

class XxxParamTable {
public:
    unsigned int rows_length;
    XxxParamTable_provider_fn* provider = nullptr;

    XxxParamTable(unsigned int rows_length) : rows_length(rows_length) {}
};



template< typename T >
size_t EEPROM_get( unsigned int addr, T* value ) {
    unsigned int i;
    for( i = 0 ; i < sizeof(T) ; ++i ) {
        *(value + i) = EEPROM.read(addr + i);
    }
    return sizeof(T);
}

template< typename T >
size_t EEPROM_put( unsigned int addr, const T* value ) {
    unsigned int i, e;
    for( i = 0 ; i < sizeof(T) ; ++i ) {
        EEPROM.write(addr + i, *(value + i));
    }
    return sizeof(T);
}



String getValue_INT8(void* var) {
    return String(*(int8_t*)var);
}
void setValue_INT8(int8_t* var, const char* value) {
    *var = atoi(value);
}
size_t loadValue_INT8(unsigned int addr, int8_t *value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_INT8(unsigned int addr, const int8_t *value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const int8_t&) {
    param->getValue = getValue_INT8;
    param->setValue = setValue_INT8;
    param->loadValue = loadValue_INT8;
    param->saveValue = saveValue_INT8;
}


String getValue_UINT8(void* var) {
    return String(*(uint8_t*)var);
}
void setValue_UINT8(uint8_t* var, const char* value) {
    *var = atoi(value);
}
size_t loadValue_UINT8(unsigned int addr, uint8_t *value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_UINT8(unsigned int addr, const uint8_t *value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const uint8_t&) {
    param->getValue = getValue_UINT8;
    param->setValue = setValue_UINT8;
    param->loadValue = loadValue_UINT8;
    param->saveValue = saveValue_UINT8;
}


String getValue_INT16(void* var) {
    return String(*(int16_t*)var);
}
void setValue_INT16(int16_t* var, const char* value) {
    *var = atol(value);
}
size_t loadValue_INT16(unsigned int addr, int16_t *value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_INT16(unsigned int addr, const int16_t *value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const int16_t&) {
    param->getValue = getValue_INT16;
    param->setValue = setValue_INT16;
    param->loadValue = loadValue_INT16;
    param->saveValue = saveValue_INT16;
}


String getValue_UINT16(void* var) {
    return String(*(uint16_t*)var);
}
void setValue_UINT16(uint16_t* var, const char* value) {
    *var = atol(value);
}
size_t loadValue_UINT16(unsigned int addr, uint16_t *value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_UINT16(unsigned int addr, const uint16_t *value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const uint16_t&) {
    param->getValue = getValue_UINT16;
    param->setValue = setValue_UINT16;
    param->loadValue = loadValue_UINT16;
    param->saveValue = saveValue_UINT16;
}


String getValue_STRING(void* var) {
    return String(*(String*)var);
}
void setValue_STRING(String* var, const char* value) {
    *var = value;
}
size_t loadValue_STRING(unsigned int addr, String* var) {
    size_t i;
    char c;
    char* buf;
    for (i = 0; EEPROM.read(addr + i); ++i);
    buf = malloc(i);
    if (buf) {
        for (i = 0; buf[i] = EEPROM.read(addr + i); ++i);
        *var = buf;
        free(buf);
    }
    return i;
}
size_t saveValue_STRING(unsigned int addr, const String* var) {
    size_t i;
    char c;
    for (i = 0; ; ++i) {
        c = (*var).c_str()[i];
        EEPROM.write(addr + i, c);
        if (!c) {
            break;
        }
    }
    return i;
}
void XxxParam_fillHandlers(XxxParam* param, const String&) {
    param->getValue = getValue_STRING;
    param->setValue = setValue_STRING;
    param->loadValue = loadValue_STRING;
    param->saveValue = saveValue_STRING;
}


String getValue_TABLE(XxxParamTable* var) {
    // uint8_t ii;
    // unsigned int i;
    // unsigned int rows_length = var->rows_length;
    // XxxParam param;

    // Serial.println();
    // for (i = 0; i < rows_length; ++i) {
    //     Serial.print(i);
    //     for (ii = 0; var->provider(&param, ii, i); ++ii) {
    //         Serial.print(F("    "));
    //         Serial.print(param.getValue(param.var));
    //         delay(500);
    //     }
    //     Serial.println();
    // }

    return String("");
}
void setValue_TABLE(void* var, const char* value) {
    //*var = value;
}
size_t loadValue_TABLE(unsigned int addr, XxxParamTable* var) {
    return 0;
}
size_t saveValue_TABLE(unsigned int addr, const XxxParamTable* var) {
    return 0;
}
void XxxParam_fillHandlers(XxxParam* param, const XxxParamTable&) {
    param->getValue = getValue_TABLE;
    param->setValue = setValue_TABLE;
    param->loadValue = loadValue_TABLE;
    param->saveValue = saveValue_TABLE;
}




typedef bool FnParamsGetter(XxxParam* buf, uint8_t index);


class XxxParamsIterrator {
protected:
    uint8_t index = 0;
    FnParamsGetter* paramsGetter;
public:
    XxxParamsIterrator(FnParamsGetter* paramsGetter) : paramsGetter(paramsGetter) {}

    bool next(XxxParam* buf) {
        return paramsGetter(buf, index++);
    }

    void reset() {
        index = 0;
    }
};


class CmdParams {
public:
    void run() {
        XxxParamsIterrator itter(XxxParamsStore);
        XxxParam buf;
        while (itter.next(&buf)) {
            printParam(buf);
            delete buf.var; // todo; delete XxxParamTable
        }
    }

private:
    void printParam(const XxxParam& param) {
        Serial.print(FPSTR(param.name));
        Serial.print(" ");
        Serial.print(param.getValue(param.var));
        Serial.println();
    }
};


class CmdSetParam {
public:
    void run(char* paramName, char* newParamValue) {
        Serial.print(F("name="));
        Serial.print(paramName);
        Serial.print(F("   "));
        Serial.print(F("value="));
        Serial.print(newParamValue);
        Serial.println();
        
        XxxParamsIterrator itter(XxxParamsStore);
        XxxParam param;
        while (itter.next(&param)) {
            if (strcmp_P(paramName, param.name) == 0) {
                param.setValue(param.var, newParamValue);
                Serial.println(F("OK"));
                break;
            }
        }
    }
};


class CmdLoad {
public:
    void run() {
        XxxParamsIterrator itter(XxxParamsStore);
        XxxParam param;
        unsigned int addr = 0;
        while (itter.next(&param)) {
            addr += param.loadValue(addr, param.var);
        }
    }
};


class CmdSave {
public:
    void run() {
        XxxParamsIterrator itter(XxxParamsStore);
        XxxParam param;
        unsigned int addr = 0;
        while (itter.next(&param)) {
            addr += param.saveValue(addr, param.var);
        }
    }
};


class XXX {
public:
    void update() {
        if (Serial.available()) {
            char* line = strdup(Serial.readStringUntil('\n').c_str());
            char* p = strpbrk_P(line, PSTR("= "));
            if (p[0] == '=') {
                p[0] = NULL;
                char* paramName = line;
                char* newParamValue = &p[1];

                CmdSetParam cmd;
                cmd.run(paramName, newParamValue);
            } else {
                if (strcmp_P(line, PSTR("params")) == 0) {
                    CmdParams cmd;
                    cmd.run();
                }
                if (strcmp_P(line, PSTR("load")) == 0) {
                    CmdLoad cmd;
                    cmd.run();
                }
                if (strcmp_P(line, PSTR("save")) == 0) {
                    CmdSave cmd;
                    cmd.run();
                }
            }
            free(line);
        }
    }
} XXX;




#define FM_PARAM_TABLE_COLUMN(N, i, p, val) \
                                                        case (N-i-1): \
                                                            _param->var = &(p[row_index].val); \
                                                            XxxParam_fillHandlers(_param, p[row_index].val); \
                                                            break;


#define BEGIN_PARAMS() \
                                    bool XxxParamsStore(XxxParam* param, uint8_t index) { \
                                        const uint8_t COUNTER_BASE = __COUNTER__ + 1; \
                                        switch (index) {
#define PARAM(var_name) \
                                            case (__COUNTER__ - COUNTER_BASE): \
                                                param->name = PSTR(#var_name); \
                                                param->var = &var_name; \
                                                XxxParam_fillHandlers(param, var_name); \
                                                break;
#define PARAM_TABLE(var_name, rows_length, ...) \
                                            case (__COUNTER__ - COUNTER_BASE): \
                                                XxxParamTable* table = new XxxParamTable(rows_length); \
                                                table->provider = [](XxxParam* _param, uint8_t col_index, unsigned int row_index) -> bool { \
                                                    switch (col_index) { \
                                                        FOR_MACRO(FM_PARAM_TABLE_COLUMN, var_name, __VA_ARGS__) \
                                                        default: \
                                                            return false; \
                                                    } \
                                                    return true; \
                                                }; \
                                                param->name = PSTR(#var_name); \
                                                param->var = table; \
                                                XxxParam_fillHandlers(param, *table); \
                                                break;
#define END_PARAMS() \
                                            default: \
                                                return false; \
                                        } \
                                        return true; \
                                    }





BEGIN_PARAMS()
    // PARAM(ggg1)
    // PARAM(ggg2)
    // PARAM(ggg3)
    PARAM_TABLE(ggg4, 4, a, b, c)
END_PARAMS()

void setup() {
    Serial.begin(9600);
}

void loop() {
    // Serial.println(ggg1);
    // Serial.println(ggg2);
    // Serial.println(ggg3);
    // delay(3000);
    XXX.update();
}


