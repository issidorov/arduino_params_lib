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

float ggg5 = 0.545;
double ggg6 = 0.343562;


struct XxxParam;

typedef String FnValueGetter(void* var);
typedef void FnValueSetter(void* var, const char* value);
typedef size_t FnValueLoad(unsigned int addr, void* var);
typedef size_t FnValueSave(unsigned int addr, const void* var);
typedef int FnCmpName(const char* str, PGM_P name);
typedef bool FnSubParamGetter(XxxParam* subParam, void* var, const char* fullParamName);

struct XxxParam {
    PGM_P name;
    void* var;
    bool is_tmp_var;
    FnCmpName* cmpName;
    FnSubParamGetter* getSubParam;
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


void clean_last_nullable(char* s) {
    for(int i = strlen(s) - 1; i; --i) {
        if (s[i] == '.') {
            s[i] = NULL;
            break;
        }
        if (s[i] != '0') {
            s[i + 1] = NULL;
            break;
        }
    }
}


String getValue_FLOAT(float* var) {
    char s[8];
    int perc = 2;
    {
        if (*var < 10.) perc = 4;
        else if (*var < 100.) perc = 3;
    }
    dtostrf(*var, 0, perc, s);
    clean_last_nullable(s);
    return String(s);
}
void setValue_FLOAT(float* var, const char* value) {
    *var = atof(value);
}
size_t loadValue_FLOAT(unsigned int addr, float *value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_FLOAT(unsigned int addr, const float *value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const float&) {
    param->getValue = getValue_FLOAT;
    param->setValue = setValue_FLOAT;
    param->loadValue = loadValue_FLOAT;
    param->saveValue = saveValue_FLOAT;
}


String getValue_DOUBLE(double* var) {
    char s[16];
    int perc = 4;
    {
        if (*var < 10.) perc = 6;
        else if (*var < 100.) perc = 5;
    }
    dtostrf(*var, 0, perc, s);
    clean_last_nullable(s);
    return String(s);
}
void setValue_DOUBLE(double* var, const char* value) {
    *var = strtod(value, NULL);
}
size_t loadValue_DOUBLE(unsigned int addr, double *value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_DOUBLE(unsigned int addr, const double *value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const double&) {
    param->getValue = getValue_DOUBLE;
    param->setValue = setValue_DOUBLE;
    param->loadValue = loadValue_DOUBLE;
    param->saveValue = saveValue_DOUBLE;
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
    return i + 1;
}
void XxxParam_fillHandlers(XxxParam* param, const String&) {
    param->getValue = getValue_STRING;
    param->setValue = setValue_STRING;
    param->loadValue = loadValue_STRING;
    param->saveValue = saveValue_STRING;
}


int cmpName_TABLE(const char* str, PGM_P paramName) {
    return strncmp_P(str, paramName, strlen_P(paramName));
}
bool parseFullParamName_TABLE(char* fullParamName, int* index, char** subName) {
    char* pos1 = strchr(fullParamName, '[');
    char* pos2 = strchr(fullParamName, ']');
    char* pos3 = strchr(fullParamName, '.');
    
    if (!pos1 || !pos2 || !pos3) return false;
    if (pos1 > pos2) return false;
    if (pos3 != pos2 + 1) return false;

    *pos2 = 0;
    *index = atoi(pos1 + 1);
    *pos2 = ']';

    *subName = pos3 + 1;

    return true;
}
bool getSubParam_TABLE(XxxParam* subParam, XxxParamTable* var, const char* fullParamName) {
    int index;
    char* subName;
    if(!parseFullParamName_TABLE(fullParamName, &index, &subName)) {
        Serial.println(F("Error: invalid param."));
        return false;
    }

    for (uint8_t ii = 0; var->provider(subParam, ii, index); ++ii) {
        if (strcmp_P(subName, subParam->name) == 0) {
            return true;
        }
    }
    Serial.println(F("Error: param not found."));
    return false;
}
String getValue_TABLE(XxxParamTable* var) {
    uint8_t ii, j;
    unsigned int i;
    unsigned int rows_length = var->rows_length;
    XxxParam param;
    const uint8_t cellWeight = 6;

    Serial.println();
    Serial.print(F(" "));
    for (ii = 0; var->provider(&param, ii, i); ++ii) {
        for (j = cellWeight - strlen_P(param.name); j; --j) {
            Serial.print(F(" "));
        }
        Serial.print(FPSTR(param.name));
    }

    for (i = 0; i < rows_length; ++i) {
        Serial.println();
        Serial.print(i);
        for (ii = 0; var->provider(&param, ii, i); ++ii) {
            String value = param.getValue(param.var);
            for (j = cellWeight - value.length(); j; --j) {
                Serial.print(F(" "));
            }
            Serial.print(value);
        }
    }

    return String("");
}
size_t loadValue_TABLE(unsigned int addr, XxxParamTable* var) {
    size_t size = 0;
    uint8_t ii;
    unsigned int i;
    unsigned int rows_length = var->rows_length;
    XxxParam param;

    for (i = 0; i < rows_length; ++i) {
        for (ii = 0; var->provider(&param, ii, i); ++ii) {
            size += param.loadValue(addr + size, param.var);
        }
    }

    return size;
}
size_t saveValue_TABLE(unsigned int addr, const XxxParamTable* var) {
    size_t size = 0;
    uint8_t ii;
    unsigned int i;
    unsigned int rows_length = var->rows_length;
    XxxParam param;

    for (i = 0; i < rows_length; ++i) {
        for (ii = 0; var->provider(&param, ii, i); ++ii) {
            size += param.saveValue(addr + size, param.var);
        }
    }

    return size;
}
void XxxParam_fillHandlers(XxxParam* param, const XxxParamTable&) {
    param->cmpName = cmpName_TABLE;
    param->getSubParam = getSubParam_TABLE;
    param->getValue = getValue_TABLE;
    param->setValue = nullptr;
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
            if (buf.is_tmp_var) {
                delete buf.var;
            }
        }
    }

private:
    void printParam(const XxxParam& param) {
        Serial.println();
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
            int cmpRes = param.cmpName
                ? param.cmpName(paramName, param.name)
                : strcmp_P(paramName, param.name);

            if (cmpRes == 0) {
                if (param.getSubParam) {
                    XxxParam subParam;
                    if(param.getSubParam(&subParam, param.var, paramName)) {
                        subParam.setValue(subParam.var, newParamValue);
                        Serial.println(F("OK"));
                    }
                } else {
                    param.setValue(param.var, newParamValue);
                    Serial.println(F("OK"));
                }
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
        Serial.println(F("OK"));
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
        Serial.println(F("OK"));
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
            Serial.println();
        }
    }
} XXX;




#define FM_PARAM_TABLE_COLUMN(N, i, p, val) \
                                                        case (N-i-1): \
                                                            _param->name = PSTR(#val); \
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
                                                param->is_tmp_var = false; \
                                                param->cmpName = nullptr; \
                                                param->getSubParam = nullptr; \
                                                XxxParam_fillHandlers(param, var_name); \
                                                break;
#define PARAM_TABLE(var_name, rows_length, ...) \
                                            case (__COUNTER__ - COUNTER_BASE): { \
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
                                                param->is_tmp_var = true; \
                                                XxxParam_fillHandlers(param, *table); \
                                            } break;
#define END_PARAMS() \
                                            default: \
                                                return false; \
                                        } \
                                        return true; \
                                    }





BEGIN_PARAMS()
    PARAM(ggg1)
    PARAM(ggg2)
    PARAM(ggg3)
    PARAM_TABLE(ggg4, 4, a, b, c)
    PARAM(ggg5)
    PARAM(ggg6)
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


