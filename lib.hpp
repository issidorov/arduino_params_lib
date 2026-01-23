#include <FOR_MACRO.h>

class XxxParam {
public:
    PGM_P name;
    bool is_tmp_var;

    virtual int cmpName(const char* str) {
        return strcmp_P(str, this->name);
    }

    virtual XxxParam* getSubParam(const char* fullParamName) {
        return nullptr;
    }

    virtual String getValue() = 0;

    virtual void setValue(const char* value) = 0;

    virtual size_t loadValue(unsigned int addr) = 0;

    virtual size_t saveValue(unsigned int addr) = 0;
};


typedef XxxParam* XxxParamTable_provider_fn(uint8_t col_index, unsigned int row_index);

class XxxParamTable {
public:
    unsigned int* rows_length;
    void* var;
    size_t row_size;
    XxxParamTable_provider_fn* provider = nullptr;

    XxxParamTable(unsigned int* rows_length) : rows_length(rows_length) {}

    bool hasSubParam(uint8_t col_index, unsigned int row_index) {
        XxxParam* subParam = this->provider(col_index, row_index);
        delete subParam;
        return subParam != nullptr;
    }
};


XxxParam* createXxxParam(int8_t* var);
XxxParam* createXxxParam(uint8_t* var);
XxxParam* createXxxParam(int16_t* var);
XxxParam* createXxxParam(uint16_t* var);
XxxParam* createXxxParam(float* var);
XxxParam* createXxxParam(double* var);
XxxParam* createXxxParam(String* var);
XxxParam* createXxxParam(char** var);
XxxParam* createXxxParam(XxxParamTable* var);


class XXX {
public:
    void update();
};

extern XXX xxx;

extern bool hasTables;

XxxParam* XxxParamsStore(uint8_t index);


#define FM_PARAM_TABLE_COLUMN(N, i, p, val) \
                                                        case (N-i-1): { \
                                                            subParam = createXxxParam(&(p[row_index].val)); \
                                                            subParam->name = PSTR(#val); \
                                                        } break;


#define BEGIN_PARAMS() \
                                    XxxParam* XxxParamsStore(uint8_t index) { \
                                        XxxParam* param; \
                                        const uint8_t COUNTER_BASE = __COUNTER__ + 1; \
                                        switch (index) {
#define PARAM(var_name) \
                                            case (__COUNTER__ - COUNTER_BASE): { \
                                                param = createXxxParam(&var_name); \
                                                param->name = PSTR(#var_name); \
                                                param->is_tmp_var = false; \
                                            } break;
#define PARAM_TABLE(var_name, rows_length, ...) \
                                            case (__COUNTER__ - COUNTER_BASE): { \
                                                hasTables = true; \
                                                XxxParamTable* table = new XxxParamTable(&rows_length); \
                                                table->var = &var_name; \
                                                table->row_size = sizeof(var_name[0]); \
                                                table->provider = [](uint8_t col_index, unsigned int row_index) -> XxxParam* { \
                                                    XxxParam* subParam; \
                                                    switch (col_index) { \
                                                        FOR_MACRO(FM_PARAM_TABLE_COLUMN, var_name, __VA_ARGS__) \
                                                        default: \
                                                            return nullptr; \
                                                    } \
                                                    return subParam; \
                                                }; \
                                                param = createXxxParam(table); \
                                                param->name = PSTR(#var_name); \
                                                param->is_tmp_var = true; \
                                            } break;
#define END_PARAMS() \
                                            default: \
                                                return nullptr; \
                                        } \
                                        return param; \
                                    }

