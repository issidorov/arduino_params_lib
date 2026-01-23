#include <Arduino.h>
#include <EEPROM.h>
#include "lib.hpp"

#define FPSTR(s) (const __FlashStringHelper*)(s)

XXX xxx;


class XXX_CmdAbstract {
public:
    virtual PGM_P getName() = 0;
    virtual void run(char** args, int args_len) = 0;
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



class XxxParam_INT8 : public XxxParam {
public:
    int8_t* var;

    XxxParam_INT8(int8_t* var) : var(var) {}

    String getValue() override {
        return String(*this->var);
    }

    void setValue(const char* value) override {
        *this->var = atoi(value);
    }

    size_t loadValue(unsigned int addr) override {
        return EEPROM_get(addr, this->var);
    }

    size_t saveValue(unsigned int addr) override {
        return EEPROM_put(addr, this->var);
    }
};

XxxParam* createXxxParam(int8_t* var) {
    return new XxxParam_INT8(var);
}



class XxxParam_UINT8 : public XxxParam {
public:
    uint8_t* var;

    XxxParam_UINT8(uint8_t* var) : var(var) {}

    String getValue() override {
        return String(*this->var);
    }

    void setValue(const char* value) override {
        *this->var = atoi(value);
    }

    size_t loadValue(unsigned int addr) override {
        return EEPROM_get(addr, this->var);
    }

    size_t saveValue(unsigned int addr) override {
        return EEPROM_put(addr, this->var);
    }
};

XxxParam* createXxxParam(uint8_t* var) {
    return new XxxParam_UINT8(var);
}


class XxxParam_INT16 : public XxxParam {
public:
    int16_t* var;

    XxxParam_INT16(int16_t* var) : var(var) {}

    String getValue() override {
        return String(*this->var);
    }

    void setValue(const char* value) override {
        *this->var = atol(value);
    }

    size_t loadValue(unsigned int addr) override {
        return EEPROM_get(addr, this->var);
    }

    size_t saveValue(unsigned int addr) override {
        return EEPROM_put(addr, this->var);
    }
};

XxxParam* createXxxParam(int16_t* var) {
    return new XxxParam_INT16(var);
}


class XxxParam_UINT16 : public XxxParam {
public:
    uint16_t* var;

    XxxParam_UINT16(uint16_t* var) : var(var) {}

    String getValue() override {
        return String(*this->var);
    }
    void setValue(const char* value) override {
        *this->var = atol(value);
    }
    size_t loadValue(unsigned int addr) override {
        return EEPROM_get(addr, this->var);
    }
    size_t saveValue(unsigned int addr) override {
        return EEPROM_put(addr, this->var);
    }
};

XxxParam* createXxxParam(uint16_t* var) {
    return new XxxParam_INT16(var);
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


class XxxParam_FLOAT : public XxxParam {
public:
    float* var;

    XxxParam_FLOAT(float* var) : var(var) {}
    
    String getValue() override {
        char s[8];
        int perc = 2;
        {
            if (*this->var < 10.) perc = 4;
            else if (*this->var < 100.) perc = 3;
        }
        dtostrf(*this->var, 0, perc, s);
        clean_last_nullable(s);
        return String(s);
    }

    void setValue(const char* value) override {
        *this->var = atof(value);
    }

    size_t loadValue(unsigned int addr) override {
        return EEPROM_get(addr, this->var);
    }

    size_t saveValue(unsigned int addr) override {
        return EEPROM_put(addr, this->var);
    }
};

XxxParam* createXxxParam(float* var) {
    return new XxxParam_FLOAT(var);
}


class XxxParam_DOUBLE : public XxxParam {
public:
    double* var;

    XxxParam_DOUBLE(double* var) : var(var) {}

    String getValue() override {
        char s[16];
        int perc = 4;
        {
            if (*this->var < 10.) perc = 6;
            else if (*this->var < 100.) perc = 5;
        }
        dtostrf(*this->var, 0, perc, s);
        clean_last_nullable(s);
        return String(s);
    }

    void setValue(const char* value) override {
        *this->var = strtod(value, NULL);
    }

    size_t loadValue(unsigned int addr) override {
        return EEPROM_get(addr, this->var);
    }

    size_t saveValue(unsigned int addr) override {
        return EEPROM_put(addr, this->var);
    }
};

XxxParam* createXxxParam(double* var) {
    return new XxxParam_DOUBLE(var);
}



class XxxParam_STRING : public XxxParam {
public:
    String* var;

    XxxParam_STRING(String* var) : var(var) {}

    String getValue() override {
        return String(*this->var);
    }

    void setValue(const char* value) override {
        *this->var = value;
    }

    size_t loadValue(unsigned int addr) override {
        size_t i;
        char c;
        char* buf;
        for (i = 0; EEPROM.read(addr + i); ++i);
        buf = malloc(i + 1);
        if (buf) {
            for (i = 0; buf[i] = EEPROM.read(addr + i); ++i);
            *this->var = buf;
            free(buf);
        }
        return i + 1;
    }

    size_t saveValue(unsigned int addr) override {
        size_t i;
        char c;
        for (i = 0; ; ++i) {
            c = (*this->var).c_str()[i];
            EEPROM.write(addr + i, c);
            if (!c) {
                break;
            }
        }
        return i + 1;
    }
};

XxxParam* createXxxParam(String* var) {
    return new XxxParam_STRING(var);
}



class XxxParam_CHAR_STRING : public XxxParam {
public:
    char** var;

    XxxParam_CHAR_STRING(char** var) : var(var) {}

    String getValue() override {
        return *this->var ? String(*this->var) : String();
    }

    void setValue(const char* value) override {
        free(*this->var);
        *this->var = strdup(value);
    }

    size_t loadValue(unsigned int addr) override {
        size_t i;
        char c;
        char* buf;
        for (i = 0; EEPROM.read(addr + i); ++i);
        buf = malloc(i + 1);
        if (buf) {
            for (i = 0; buf[i] = EEPROM.read(addr + i); ++i);
            this->setValue(buf);
            free(buf);
        }
        return i + 1;
    }

    size_t saveValue(unsigned int addr) override {
        size_t i;
        char c;
        for (i = 0; ; ++i) {
            c = *this->var ? (*this->var)[i] : NULL;
            EEPROM.write(addr + i, c);
            if (!c) {
                break;
            }
        }
        return i + 1;
    }
};

XxxParam* createXxxParam(char** var) {
    return new XxxParam_CHAR_STRING(var);
}



class XxxParam_TABLE : public XxxParam {
public:
    XxxParamTable* var;

    XxxParam_TABLE(XxxParamTable* var) : var(var) {}

    ~XxxParam_TABLE() {
        delete this->var;
    }

    int cmpName(const char* str) {
        return strncmp_P(str, this->name, strlen_P(this->name));
    }

    static bool parseFullParamName_TABLE(char* fullParamName, int* index, char** subName) {
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

    XxxParam* getSubParam(const char* fullParamName) {
        int index;
        char* subName;
        XxxParam* subParam;

        if(!parseFullParamName_TABLE(fullParamName, &index, &subName)) {
            Serial.println(F("Error: invalid param."));
            return nullptr;
        }

        for (uint8_t ii = 0; subParam = this->var->provider(ii, index); ++ii) {
            if (strcmp_P(subName, subParam->name) == 0) {
                return subParam;
            }
        }
        Serial.println(F("Error: param not found."));
        return nullptr;
    }

    String getValue() {
        uint8_t ii, j;
        unsigned int i;
        unsigned int rows_length = *this->var->rows_length;
        XxxParam* subParam;
        const uint8_t cellWeight = 6;

        Serial.println();
        Serial.print(F(" "));
        for (ii = 0; subParam = this->var->provider(ii, i); ++ii) {
            for (j = cellWeight - strlen_P(subParam->name); j; --j) {
                Serial.print(F(" "));
            }
            Serial.print(FPSTR(subParam->name));
            delete subParam;
        }

        for (i = 0; i < rows_length; ++i) {
            Serial.println();
            Serial.print(i);
            for (ii = 0; subParam = this->var->provider(ii, i); ++ii) {
                String value = subParam->getValue();
                for (j = cellWeight - value.length(); j; --j) {
                    Serial.print(F(" "));
                }
                Serial.print(value);
                delete subParam;
            }
        }

        return String("");
    }
    
    void setValue(const char* value) {}

    size_t loadValue(unsigned int addr) {
        size_t size = 0;
        uint8_t ii;
        unsigned int i;
        unsigned int rows_length;
        XxxParam* subParam;

        size += EEPROM_get(addr, this->var->rows_length);
        rows_length = *(this->var->rows_length);

        for (i = 0; i < rows_length; ++i) {
            for (ii = 0; subParam = this->var->provider(ii, i); ++ii) {
                size += subParam->loadValue(addr + size);
                delete subParam;
            }
        }

        return size;
    }

    size_t saveValue(unsigned int addr) {
        size_t size = 0;
        uint8_t ii;
        unsigned int i;
        unsigned int rows_length = *this->var->rows_length;
        XxxParam* subParam;

        size += EEPROM_put(addr, this->var->rows_length);

        for (i = 0; i < rows_length; ++i) {
            for (ii = 0; subParam = this->var->provider(ii, i); ++ii) {
                size += subParam->saveValue(addr + size);
                delete subParam;
            }
        }

        return size;
    }
};

XxxParam* createXxxParam(XxxParamTable* var) {
    return new XxxParam_TABLE(var);
}


typedef XxxParam* FnParamsGetter(uint8_t index);


class XxxParamsIterrator {
protected:
    uint8_t index = 0;
    FnParamsGetter* paramsGetter;
public:
    XxxParamsIterrator(FnParamsGetter* paramsGetter) : paramsGetter(paramsGetter) {}

    XxxParam* next() {
        return paramsGetter(index++);
    }

    void reset() {
        index = 0;
    }
};


class CmdParams: public XXX_CmdAbstract {
public:
    PGM_P getName() override {
        return PSTR("params");
    }

    void run(char** args, int args_len) override {
        XxxParamsIterrator itter(XxxParamsStore);
        XxxParam* param;
        while (param = itter.next()) {
            printParam(param);
            delete param;
        }
    }

private:
    static void printParam(const XxxParam* param) {
        Serial.println();
        Serial.print(FPSTR(param->name));
        Serial.print(" ");
        Serial.print(param->getValue());
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
        XxxParam* param;
        while (param = itter.next()) {
            if (param->cmpName(paramName) == 0) {
                if (param->is_tmp_var) {
                    XxxParam* subParam;
                    if(subParam = param->getSubParam(paramName)) {
                        subParam->setValue(newParamValue);
                        delete subParam;
                        Serial.println(F("OK"));
                    }
                } else {
                    param->setValue(newParamValue);
                    Serial.println(F("OK"));
                }
                break;
            }
            delete param;
        }
    }
};


class CmdLoad: public XXX_CmdAbstract {
public:
    PGM_P getName() override {
        return PSTR("load");
    }

    void run(char** args, int args_len) override {
        XxxParamsIterrator itter(XxxParamsStore);
        XxxParam* param;
        unsigned int addr = 0;
        while (param = itter.next()) {
            addr += param->loadValue(addr);
            delete param;
        }
        Serial.println(F("OK"));
    }
};


class CmdSave: public XXX_CmdAbstract {
public:
    PGM_P getName() override {
        return PSTR("save");
    }

    void run(char** args, int args_len) override {
        XxxParamsIterrator itter(XxxParamsStore);
        XxxParam* param;
        unsigned int addr = 0;
        while (param = itter.next()) {
            addr += param->saveValue(addr);
            delete param;
        }
        Serial.println(F("OK"));
    }
};



typedef void CmdHandler(char** args, int args_len);

bool hasTables = false;

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

XxxParam* XXX_get_table_param_and_index(char* fullParamName, int* index) {
    XxxParam* param;
    char* paramName;

    if (!XXX_parse_table_param_name_and_index(fullParamName, &paramName, index)) {
        Serial.print(F("Error: arg "));
        Serial.print(fullParamName);
        Serial.println(F(" is invalid."));
        return;
    }

    XxxParamsIterrator itter(XxxParamsStore);
    bool isParamFinded = false;
    while (param = itter.next()) {
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

    return param;
}

class CmdInsert : public XXX_CmdAbstract {
public:
    PGM_P getName() override {
        return PSTR("insert");
    }

    void run(char** args, int args_len) override {
        int row_index;
        XxxParam_TABLE* param;

        if (!(param = XXX_get_table_param_and_index(args[0], &row_index))) {
            return;
        }

        XxxParamTable* table = param->var;

        if (row_index < 0 || row_index > *table->rows_length) {
            Serial.print(F("Error: index "));
            Serial.print(row_index);
            Serial.println(F(" is invalid."));
            delete param;
            return;
        }

        if (
            !table->hasSubParam(args_len - 2, 0)
            || table->hasSubParam(args_len - 1, 0)
        ) {
            Serial.print(F("Error: invalid args count."));
            delete param;
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

        XxxParam* subParam;
        int col_index;
        for (int i = 1; i < args_len; ++i) {
            col_index = i - 1;
            subParam = table->provider(col_index, row_index);
            subParam->setValue(args[i]);
            delete subParam;
        }

        Serial.println(F("OK"));
        delete param;
    }
};

class CmdDelete : public XXX_CmdAbstract {
    PGM_P getName() override {
        return PSTR("delete");
    }

    void run(char** args, int args_len) override {
        int row_index;
        XxxParam_TABLE* param;
        
        if (!(param = XXX_get_table_param_and_index(args[0], &row_index))) {
            return;
        }

        XxxParamTable* table = param->var;

        if (row_index < 0 || row_index > *table->rows_length - 1) {
            Serial.print(F("Error: index "));
            Serial.print(row_index);
            Serial.println(F(" is invalid."));
            delete param;
            return;
        }

        memmove(
            table->var + table->row_size * row_index,
            table->var + table->row_size * (row_index + 1),
            table->row_size * (*table->rows_length - row_index - 1)
        );
        --*table->rows_length;

        Serial.println(F("OK"));
        delete param;
    }
};



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
    while (itter.next()) {}
}


XXX_CmdAbstract* getCmd(int index) {
    switch (index) {
        case 0:
            return new CmdParams();
        case 1:
            return new CmdLoad();
        case 2:
            return new CmdSave();
        case 3:
            return hasTables ? new CmdInsert() : nullptr;
        case 4:
            return hasTables ? new CmdDelete() : nullptr;
        default:
            return nullptr;
    }
}


void XXX::update() {
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
            int args_len;
            char* cmdName = line;
            if (p) {
                p[0] = NULL;
                p = &p[1];
            }
            char** args = str_split(p, args_len);
            if (args || !args_len) {
                XXX_CmdAbstract* cmd;
                for (int i = 0; cmd = getCmd(i); ++i) {
                    if (strcmp_P(cmdName, cmd->getName()) == 0) {
                        cmd->run(args, args_len);
                    }
                    delete cmd;
                }
                free(args);
            }
        }
        free(line);
        Serial.println();
    }
}

