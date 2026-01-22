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
    unsigned int* rows_length;
    void* var;
    size_t row_size;
    XxxParamTable_provider_fn* provider = nullptr;

    XxxParamTable(unsigned int* rows_length) : rows_length(rows_length) {}
};



template< typename T >
size_t EEPROM_get( unsigned int addr, T* value ) {
    unsigned int i;
    char* ptr = (char*) value;
    for( i = 0 ; i < sizeof(T) ; ++i ) {
        ptr[i] = EEPROM.read(addr + i);
    }
    return sizeof(T);
}

template< typename T >
size_t EEPROM_put( unsigned int addr, const T* value ) {
    unsigned int i, e;
    char* ptr = (char*) value;
    for( i = 0 ; i < sizeof(T) ; ++i ) {
        EEPROM.write(addr + i, ptr[i]);
    }
    return sizeof(T);
}



String getValue_INT8(void* var) {
    return String(*(int8_t*)var);
}
void setValue_INT8(int8_t* var, const char* value) {
    *var = atoi(value);
}
size_t loadValue_INT8(unsigned int addr, int8_t* value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_INT8(unsigned int addr, const int8_t* value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const int8_t*) {
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
size_t loadValue_UINT8(unsigned int addr, uint8_t* value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_UINT8(unsigned int addr, const uint8_t* value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const uint8_t*) {
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
size_t loadValue_INT16(unsigned int addr, int16_t* value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_INT16(unsigned int addr, const int16_t* value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const int16_t*) {
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
size_t loadValue_UINT16(unsigned int addr, uint16_t* value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_UINT16(unsigned int addr, const uint16_t* value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const uint16_t*) {
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
size_t loadValue_FLOAT(unsigned int addr, float* value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_FLOAT(unsigned int addr, const float* value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const float*) {
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
size_t loadValue_DOUBLE(unsigned int addr, double* value) {
    return EEPROM_get(addr, value);
}
size_t saveValue_DOUBLE(unsigned int addr, const double* value) {
    return EEPROM_put(addr, value);
}
void XxxParam_fillHandlers(XxxParam* param, const double*) {
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
    buf = malloc(i + 1);
    if (buf) {
        for (i = 0; buf[i] = EEPROM.read(addr + i); ++i);
        *var = buf;
        free(buf);
    }
    return i + 1;
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
void XxxParam_fillHandlers(XxxParam* param, const String*) {
    param->getValue = getValue_STRING;
    param->setValue = setValue_STRING;
    param->loadValue = loadValue_STRING;
    param->saveValue = saveValue_STRING;
}


String getValue_CHAR_STRING(char** var) {
    return *var ? String(*var) : String();
}
void setValue_CHAR_STRING(char** var, const char* value) {
    free(*var);
    *var = strdup(value);
}
size_t loadValue_CHAR_STRING(unsigned int addr, char** var) {
    size_t i;
    char c;
    char* buf;
    for (i = 0; EEPROM.read(addr + i); ++i);
    buf = malloc(i + 1);
    if (buf) {
        for (i = 0; buf[i] = EEPROM.read(addr + i); ++i);
        setValue_CHAR_STRING(var, buf);
        free(buf);
    }
    return i + 1;
}
size_t saveValue_CHAR_STRING(unsigned int addr, const char** var) {
    size_t i;
    char c;
    for (i = 0; ; ++i) {
        c = *var ? (*var)[i] : NULL;
        EEPROM.write(addr + i, c);
        if (!c) {
            break;
        }
    }
    return i + 1;
}
void XxxParam_fillHandlers(XxxParam* param, const char**) {
    param->getValue = getValue_CHAR_STRING;
    param->setValue = setValue_CHAR_STRING;
    param->loadValue = loadValue_CHAR_STRING;
    param->saveValue = saveValue_CHAR_STRING;
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
    unsigned int rows_length = *(var->rows_length);
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
    unsigned int rows_length;
    XxxParam param;

    size += EEPROM_get(addr, var->rows_length);
    rows_length = *(var->rows_length);

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
    unsigned int rows_length = *(var->rows_length);
    XxxParam param;

    size += EEPROM_put(addr, var->rows_length);

    for (i = 0; i < rows_length; ++i) {
        for (ii = 0; var->provider(&param, ii, i); ++ii) {
            size += param.saveValue(addr + size, param.var);
        }
    }

    return size;
}
void XxxParam_fillHandlers(XxxParam* param, const XxxParamTable*) {
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



typedef void CmdHandler(char** args, int args_len);

CmdHandler* XXX_cmd_insert = nullptr;
CmdHandler* XXX_cmd_delete = nullptr;

bool XXX_parse_table_param_name_and_index(char* fullParamName, char** paramName, int* index) {
    char* pos1 = strchr(fullParamName, '[');
    char* pos2 = strchr(fullParamName, ']');
    if (!pos1 || !pos2) return false;
    if (pos2 < pos1) return false;
    if (pos2[1] != NULL) return false;
    if (pos1 == fullParamName) return false;

    size_t paramName_size = pos1 - fullParamName + 1;
    *paramName = malloc(paramName_size);
    strlcpy(*paramName, fullParamName, paramName_size);
    
    size_t index_str_size = pos2 - pos1;
    char* index_str = malloc(index_str_size);
    strlcpy(index_str, &pos1[1], index_str_size);
    *index = atoi(index_str);
    free(index_str);

    return true;
}

bool XXX_get_table_param_and_index(char* fullParamName, XxxParam* param, int* index) {
    char* paramName;

    if (!XXX_parse_table_param_name_and_index(fullParamName, &paramName, index)) {
        Serial.print(F("Error: arg "));
        Serial.print(fullParamName);
        Serial.println(F(" is invalid."));
        return;
    }

    XxxParamsIterrator itter(XxxParamsStore);
    bool isParamFinded = false;
    while (itter.next(param)) {
        int cmpRes = strcmp_P(paramName, param->name);
        if (cmpRes == 0) {
            isParamFinded = true;
            break;
        }
    }

    if (!isParamFinded) {
        Serial.print(F("Error: param "));
        Serial.print(paramName);
        Serial.println(F(" not found."));
    }

    free(paramName);

    return isParamFinded;
}

void XXX_cmd_insert_impl(char** args, int args_len) {
    int row_index;
    XxxParam param;
    
    if (!XXX_get_table_param_and_index(args[0], &param, &row_index)) {
        return;
    }

    XxxParamTable* table = param.var;

    if (row_index < 0 || row_index > *table->rows_length) {
        Serial.print(F("Error: index "));
        Serial.print(row_index);
        Serial.println(F(" is invalid."));
        return;
    }

    if (
        !table->provider(nullptr, args_len - 2, 0)
        || table->provider(nullptr, args_len - 1, 0)
    ) {
        Serial.print(F("Error: invalid args count."));
        return;
    }

    if (row_index < *table->rows_length) {
        memmove(
            table->var + table->row_size * (row_index + 1),
            table->var + table->row_size * row_index,
            table->row_size * (*table->rows_length - row_index)
        );
    }
    ++*table->rows_length;

    XxxParam subParam;
    int col_index;
    for (int i = 1; i < args_len; ++i) {
        col_index = i - 1;
        table->provider(&subParam, col_index, row_index);
        subParam.setValue(subParam.var, args[i]);
    }

    Serial.println(F("OK"));
}

void XXX_cmd_delete_impl(char** args, int args_len) {
        int row_index;
    XxxParam param;
    
    if (!XXX_get_table_param_and_index(args[0], &param, &row_index)) {
        return;
    }

    XxxParamTable* table = param.var;

    if (row_index < 0 || row_index > *table->rows_length - 1) {
        Serial.print(F("Error: index "));
        Serial.print(row_index);
        Serial.println(F(" is invalid."));
        return;
    }

    memmove(
        table->var + table->row_size * row_index,
        table->var + table->row_size * (row_index + 1),
        table->row_size * (*table->rows_length - row_index - 1)
    );
    --*table->rows_length;

    Serial.println(F("OK"));
}



char** str_split(char* str, int& res_len) {    
    int i, j;
    int last_whitespace_i;

    j = 0;
    if (str) {
        last_whitespace_i = -1;
        for (i = 0; str[i]; ++i) {
            if (str[i] != ' ' && last_whitespace_i == i - 1) {
                ++j;
            }
            if (str[i] == ' ') {
                last_whitespace_i = i;
            }
        }
    }

    res_len = j;
    if (!res_len) {
        return nullptr;
    }

    char** res_arr = malloc(sizeof(char*) * j);
    if (!res_arr) {
        Serial.println(F("Error: no memory!"));
        return nullptr;
    }

    j = 0;
    last_whitespace_i = -1;
    for (i = 0; str[i]; ++i) {
        if (str[i] != ' ' && last_whitespace_i == i - 1) {
            res_arr[j] = &str[i];
            ++j;
        }
        if (str[i] == ' ') {
            str[i] = NULL;
            last_whitespace_i = i;
        }
    }

    return res_arr;
}

bool XXX_inited = false;

void XXX_init() {
    XxxParamsIterrator itter(XxxParamsStore);
    while (itter.next(nullptr)) {}
}

struct XXX {
    void update() {
        if (Serial.available()) {
            char* line = strdup(Serial.readStringUntil('\n').c_str());

            if (!XXX_inited) {
                XXX_init();
                XXX_inited = true;
            }

            char* p = strpbrk_P(line, PSTR("= "));
            if (p && p[0] == '=') {
                p[0] = NULL;
                char* paramName = line;
                char* newParamValue = &p[1];

                CmdSetParam cmd;
                cmd.run(paramName, newParamValue);
            } else {
                char* cmdName;
                int args_len;
                if (p) {
                    p[0] = NULL;
                    cmdName = line;
                    p = &p[1];
                }
                char** args = str_split(p, args_len);
                if (args || !args_len) {
                    if (strcmp_P(cmdName, PSTR("params")) == 0) {
                        CmdParams cmd;
                        cmd.run();
                    }
                    if (strcmp_P(cmdName, PSTR("load")) == 0) {
                        CmdLoad cmd;
                        cmd.run();
                    }
                    if (strcmp_P(cmdName, PSTR("save")) == 0) {
                        CmdSave cmd;
                        cmd.run();
                    }
                    if (XXX_cmd_insert && strcmp_P(cmdName, PSTR("insert")) == 0) {
                        (*XXX_cmd_insert)(args, args_len);
                    }
                    if (XXX_cmd_delete && strcmp_P(cmdName, PSTR("delete")) == 0) {
                        (*XXX_cmd_delete)(args, args_len);
                    }
                    free(args);
                }
            }
            free(line);
            Serial.println();
        }
    }
} XXX;




#define FM_PARAM_TABLE_COLUMN(N, i, p, val) \
                                                        case (N-i-1): \
                                                            if (_param) { \
                                                                _param->name = PSTR(#val); \
                                                                _param->var = &(p[row_index].val); \
                                                                XxxParam_fillHandlers(_param, &(p[row_index].val)); \
                                                            } \
                                                            break;


#define BEGIN_PARAMS() \
                                    bool XxxParamsStore(XxxParam* param, uint8_t index) { \
                                        const uint8_t COUNTER_BASE = __COUNTER__ + 1; \
                                        switch (index) {
#define PARAM(var_name) \
                                            case (__COUNTER__ - COUNTER_BASE): \
                                                if (param) { \
                                                    param->name = PSTR(#var_name); \
                                                    param->var = &var_name; \
                                                    param->is_tmp_var = false; \
                                                    param->cmpName = nullptr; \
                                                    param->getSubParam = nullptr; \
                                                    XxxParam_fillHandlers(param, &var_name); \
                                                } \
                                                break;
#define PARAM_TABLE(var_name, rows_length, ...) \
                                            case (__COUNTER__ - COUNTER_BASE): \
                                                XXX_cmd_insert = XXX_cmd_insert_impl; \
                                                XXX_cmd_delete = XXX_cmd_delete_impl; \
                                                if (param) { \
                                                    XxxParamTable* table = new XxxParamTable(&rows_length); \
                                                    table->var = &var_name; \
                                                    table->row_size = sizeof(var_name[0]); \
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
                                                    XxxParam_fillHandlers(param, table); \
                                                } \
                                                break;
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
    XXX.update();
}


