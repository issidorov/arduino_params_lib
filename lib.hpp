#include <FOR_MACRO.h>

class XxxParam;


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


XxxParam* createXxxParam(PGM_P name, int8_t* var);
XxxParam* createXxxParam(PGM_P name, uint8_t* var);
XxxParam* createXxxParam(PGM_P name, int16_t* var);
XxxParam* createXxxParam(PGM_P name, uint16_t* var);
XxxParam* createXxxParam(PGM_P name, float* var);
XxxParam* createXxxParam(PGM_P name, double* var);
XxxParam* createXxxParam(PGM_P name, String* var);
XxxParam* createXxxParam(PGM_P name, char** var);
XxxParam* createXxxParam(PGM_P name, XxxParamTable* var);


class XXX {
public:
    void update();
};

extern XXX xxx;

extern bool hasTables;

XxxParam* XxxParamsStore(uint8_t index);


#define FM_PARAM_TABLE_COLUMN(N, i, p, val) \
                                                        case (N-i-1): \
                                                            return createXxxParam(PSTR(#val), &(p[row_index].val)); \


#define BEGIN_PARAMS() \
                                    XxxParam* XxxParamsStore(uint8_t index) { \
                                        const uint8_t COUNTER_BASE = __COUNTER__ + 1; \
                                        switch (index) {
#define PARAM(var_name) \
                                            case (__COUNTER__ - COUNTER_BASE): \
                                                return createXxxParam(PSTR(#var_name), &var_name);
#define PARAM_TABLE(var_name, rows_length, ...) \
                                            case (__COUNTER__ - COUNTER_BASE): { \
                                                hasTables = true; \
                                                XxxParamTable* table = new XxxParamTable(&rows_length); \
                                                table->var = &var_name; \
                                                table->row_size = sizeof(var_name[0]); \
                                                table->provider = [](uint8_t col_index, unsigned int row_index) -> XxxParam* { \
                                                    switch (col_index) { \
                                                        FOR_MACRO(FM_PARAM_TABLE_COLUMN, var_name, __VA_ARGS__) \
                                                    } \
                                                    return nullptr; \
                                                }; \
                                                return createXxxParam(PSTR(#var_name), table); \
                                            }
#define END_PARAMS() \
                                        } \
                                        return nullptr; \
                                    }

