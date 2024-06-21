#pragma once

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/*****************************************************************************
 * BNF 如下：
 *
 *	<if statement>		:= 'if' '(' <check_statement> ')' <statement>+ {<elif_statement>} {<else_statement>} 'fi'
 *	<check_statement>	:= <left_val> <op> <right_val> { <LOR> <left_val> <op> <right_val> }
 *	<left_val>			:= number | 'VAL'
 *	<right_val>			:= number | 'VAL'
 *	<op>				:= '&&' | '||' | '=='
 *	<elif_statement>	:= 'elif' '(' <check_statement> ')' <statement>+ {<elif_statement>} {<else_statement>}
 *	<else_statement>	:= 'else'	<statement>+
 *	<statement>			:= functional '(' [arg] {',' arg} ')' ';'
 *
 ******************************************************************************/

// 添加函数流程
// 1、在符号id中添加该函数名称作为ID
// 2、在enum hash中添加该函数的hash					hash可通过另一个项目生成
// 3、在InitSymbolFromFuntional中添加函数
// 4、在next获取到变量token时对该函数进行比较				case 中的内容可通过另一个项目生成

typedef enum {
    None,
    Number,
    String,
    Value,
    Functional,
    Keyword,
    Cmp,
} SymbolsType;


typedef enum {
    // NONE = 0,用来标识错误
    IF = 1,
    ELSE,
    ELIF,
    FI,
    VAL,
    LLB,
    RLB,
    LT,
    GT,
    LE,
    GE,
    ASSIGNMENT,
    EQUAL,
    COMMA,
    SEMICOLON,
    AND,
    OR,
    LAND,
    LOR,
    FUNC1 = 32,
    FUNC2,
    FUNC3,
    PRINTPOINTER
} SymbolsId;

typedef struct Symbol {
    SymbolsType type;
    char *begin, *end;
    int id;
    int val;
} Symbol;

typedef struct {
    int val;
    int is_string;
} Arg;

// SymbolId 处的定义用全大写，相应的hash用大小写混写
// HashEnum 应当使用另一个项目生成，防止输入错误以及hash冲突
enum HashEnum {
    PrintPointer = -1431804668,
    Fi = 597,
    If = 624,
    Val = 3998,
    Elif = 59624,
    Else = 59723,
    Func1 = 615711,
    Func2 = 615712,
    Func3 = 615713,
};


/*****************************************************************************
 * 用于计算hash，区别在于本函数参数使用两个char *作范围，无需NUL结尾
 ******************************************************************************/
int RangeStringToHash(char *begin, char *end) {
    int ret_hash = 0;
    while (begin != end) {
        ret_hash = ret_hash * 10 + *begin - '0';
        begin++;
    }
    return ret_hash;
}

extern int code_line; // code_line 定义在下面，需要func的时候，本条 extern 语句可以删除
/*****************************************************************************
 * 测试函数,func1,func2,func3,测试函数调用和匹配不同类型的参数
 ******************************************************************************/
int func1(int arg1, int arg2) {
    printf("func1函数在第%d行被调用，参数1为%d，参数2为%d\n", code_line, arg1, arg2);
    return arg1 + arg2;
}
void func2(int arg) { printf("func2函数在第%d行被调用，参数为%d\n", code_line, arg); }
void func3(char *str) { printf("func3在第%d行被调用，参数是%s\n", code_line, str); }
void printPointer(int *x) { printf("地址是%p\n", x); }

/*****************************************************************************
 * 测试函数,用来快速打印token
 ******************************************************************************/
void Print(char *begin, char *end) {
    char buf[255] = "";
    strncpy(buf, begin, end - begin);
    printf("%s \n", buf);
}

/*****************************************************************************
 * 测试函数,用来从文本读取代码文本,返回的char *由malloc获取，使用完毕应当调用free释放
 ******************************************************************************/
char *ReadFileToBuf(const char *path) {

    FILE *file = fopen(path, "r");

    if (file == NULL)
        return NULL;

    fseek(file, 0, SEEK_END);
    long len = ftell(file);
    if (len == -1L) {
        return NULL;
    }
    char *buf = malloc(len + 1);
    if (buf == NULL)
        return NULL;
    rewind(file);
    len = fread(buf, 1, len, file);
    buf[len] = '\0';

    fclose(file);
    return buf;
}

/*****************************************************************************
 * 作用：将获取的使用两个指针表示的字符串token转为以NUL结尾的字符串
 * 参数：begin表示需要转换的字符串的开头，end表示需要转换的字符串的结尾
 * 返回值：一个malloc出来的char *，内容为begin和end之前的字符，最后一个字节为NUL
 *（该指针为malloc的指针，使用后需要释放）
 ******************************************************************************/
char *RangePCharToPChar(char *begin, char *end) {
    char *ret = malloc(end - begin + 1);
    if (ret == NULL)
        return NULL;
    strncpy(ret, begin, end - begin);
    ret[end - begin] = '\0';
    return ret;
}

// 全局变量定义
// 符号表里存放的实际只有 关键字if elif else 和 函数 （不支持变量定义所以不存在变量
Symbol symbols[128], cur_symbol;
char *str;
int code_line;

// 参数列表，vs不支持VLA以及const int作大小因此使用define
#define ARGS_COUNT (8)
Arg args[ARGS_COUNT];


/*****************************************************************************
 * 作用：词法分析
 * 返回值：根据当前处理的token返回相应的symbol，该symbol中保存该token的type、id、val等信息
 ******************************************************************************/
Symbol Next(void) {
    Symbol token;
    token.begin = token.end = NULL;
    token.type = None;
    while (*str) {
        if (*str <= '9' && *str >= '0') {
            int val = 0;
            token.begin = str;
            while (*str <= '9' && *str >= '0') {
                val = val * 10 + *str - '0';
                str++;
            }
            token.val = val;
            token.end = str;
            token.type = Number;
            return token;
        }
        else if (*str <= 'z' && *str >= 'a' || *str <= 'Z' && *str >= 'A') {
            token.begin = str;
            while (*str <= 'z' && *str >= 'a' || *str <= 'Z' && *str >= 'A' || *str <= '9' && *str >= '0') {
                str++;
            }
            token.end = str;


            // 变量存在三种情况
            // 1、关键字 if elif else VAL
            // 2、函数名
            switch (RangeStringToHash(token.begin, token.end)) {
            // 关键字
            case If:
                token.type = Keyword;
                token.id = IF;
                return token;
            case Elif:
                token.type = Keyword;
                token.id = IF; // elif 被认为是 if
                return token;
            case Else:
                token.type = Keyword;
                token.id = ELSE;
                return token;
            case Fi:
                token.type = Keyword;
                token.id = FI;
                return token;
            case Val:
                token.type = Keyword;
                token.id = VAL;
                return token;

            // 函数
            case Func1:
                token.type = Functional;
                token.id = FUNC1;
                return token;
            case Func2:
                token.type = Functional;
                token.id = FUNC2;
                return token;
            case Func3:
                token.type = Functional;
                token.id = FUNC3;
                return token;
            case PrintPointer:
                token.type = Functional;
                token.id = PRINTPOINTER;
                return token;
            default:
                printf("解析到变量，但不支持变量定义");
                token.type = Value;
                return token;
            }
        }
        else
            switch (*str) {
            case '(':
                token.type = Keyword;
                token.id = LLB;
                token.begin = str;
                token.end = ++str;
                return token;
            case ')':
                token.type = Keyword;
                token.id = RLB;
                token.begin = str;
                token.end = ++str;
                return token;
            case '>': {
                token.begin = str;
                if (*(str + 1) == '=') {
                    token.id = GE;
                    str++;
                }
                else {
                    token.id = GT;
                }
                token.type = Cmp;
                token.end = ++str;
                return token;
            }
            case '<': {
                token.begin = str;
                if (*(str + 1) == '=') {
                    token.id = LE;
                    str++;
                }
                else {
                    token.id = LT;
                }
                token.type = Cmp;
                token.end = ++str;
                return token;
            }
            case '=': {
                token.begin = str;
                if (*(str + 1) == '=') {
                    token.id = EQUAL;
                    str++;
                }
                else {
                    token.id = ASSIGNMENT;
                }
                token.type = Cmp;
                token.end = ++str;
                return token;
            }
            case ',':
                token.type = Keyword;
                token.id = COMMA;
                token.begin = str;
                token.end = ++str;
                return token;
            case ';':
                token.type = Keyword;
                token.id = SEMICOLON;
                token.begin = str;
                token.end = ++str;
                return token;
            case '"':
                // begin 指向第一个",end指向第二个"的后一个元素
                token.type = String;
                token.begin = ++str;
                while (*str != '"') {
                    str++;
                }
                token.end = str++;
                return token;

            case '\n':
                code_line++;
            case ' ':
            case '\t':
            case '\r':
                str++;
                return token;

            case '&': {
                token.begin = str;
                token.id = AND;
                if (*(str + 1) == '&') {
                    token.id = LAND;
                    str++;
                }
                token.type = Keyword;
                token.end = ++str;
                return token;
            }
            case '|': {
                token.begin = str;
                token.id = OR;
                if (*(str + 1) == '|') {
                    token.id = LOR;
                    str++;
                }
                token.type = Keyword;
                token.end = ++str;
                return token;
            }
            default:
                printf("next不支持该token\n");
                return token;
            }
    }
    return token;
}


/*****************************************************************************
 * 作用：获取下一个类型非空(即，不为空白符、制表符、换行符等)的token
 * 返回值：获取到的token信息
 ******************************************************************************/
Symbol Match(void) {
    Symbol symbol;
    do {
        symbol = Next();
    }
    while (symbol.type == None && *str != '\0');

    if (*str == '\0') {
        memset(&symbol, 0, sizeof(Symbol));
    }
    cur_symbol = symbol;
    return symbol;
}


/*****************************************************************************
 * 作用：获取下一个token，并判断是否为指定Id
 * 参数：SymbolId类型，为想要获取的token的id
 * 返回值：获取成功时返回获取到的token信息，否则表示获取到意料之外的符号，返回一个token，id和type均置为None
 ******************************************************************************/
Symbol MatchById(SymbolsId symbol_id) {

    Symbol symbol;
    do {
        symbol = Next();
    }
    while (symbol.type == None && *str != '\0');

    if (*str == '\0') {
        memset(&symbol, 0, sizeof(Symbol));
        cur_symbol = symbol;
        return symbol;
    }

    if (symbol.id != symbol_id) {
        printf("错误的预期符号 by id\n");
        symbol.id = symbol.type = None;
    }
    cur_symbol = symbol;
    return symbol;
}


/*****************************************************************************
 * 作用：获取下一个token，并判断是否为指定类型
 * 参数：SymbolType类型，为想要获取的token的type
 * 返回值：获取成功时返回获取到的token信息，否则表示获取到意料之外的符号，返回一个token，id和type均置为None
 ******************************************************************************/
Symbol MatchByType(SymbolsType symbol_type) {

    Symbol symbol;
    do {
        symbol = Next();
    }
    while (symbol.type == None && *str != '\0');

    if (*str == '\0') {
        memset(&symbol, 0, sizeof(Symbol));
        cur_symbol = symbol;
        return symbol;
    }
    if (symbol.type != symbol_type) {
        printf("错误的预期符号 by type\n");
        symbol.id = symbol.type = None;
    }
    cur_symbol = symbol;
    return symbol;
}


/*****************************************************************************
 * 作用：获取下一个Id为指定Id的token,中间获取到的Id不为指定id的token都将被舍弃
 * 参数：SymbolId类型，为想要获取的token的id
 * 返回值：获取成功时返回获取到的token信息，否则表示遇到代码文本结尾空字符，返回一个token，该token所在内存被写0
 ******************************************************************************/
Symbol MatchUntilById(SymbolsId symbol_id) {
    Symbol symbol;
    do {
        symbol = Next();
    }
    while (symbol.id != symbol_id && *str != '\0');
    if (*str == '\0') {
        memset(&symbol, 0, sizeof(Symbol));
    }
    cur_symbol = symbol;

    return symbol;
}


/*****************************************************************************
 * 作用：获取下一个Type为指定Type的token,中间获取到的Type不为指定type的token都将被舍弃
 * 参数：SymbolType类型，为想要获取的token的类型
 * 返回值：获取成功时返回获取到的token信息，否则表示遇到代码文本结尾空字符，返回一个token，该token所在内存被写0
 ******************************************************************************/
Symbol MatchUntilByType(SymbolsType symbol_type) {
    Symbol symbol;
    do {
        symbol = Next();
    }
    while (symbol.type != symbol_type && *str != '\0');
    if (*str == '\0') {
        memset(&symbol, 0, sizeof(Symbol));
    }
    cur_symbol = symbol;
    return symbol;
}


/*****************************************************************************
 * 作用：获取下一个id为IF、ELSE、FI之一的token,中间获取到的Type不为指定type的token都将被舍弃
 * 返回值：获取成功时返回获取到的token信息，否则表示遇到代码文本结尾空字符，返回一个token，该token所在内存被写0
 ******************************************************************************/
Symbol MatchUntilByIFOrElse() {
    Symbol symbol;
    do {
        symbol = Next();
    }
    while (!(symbol.id == IF || symbol.id == ELSE || symbol.id == FI) && *str != '\0');
    if (*str == '0') {
        memset(&symbol, 0, sizeof(Symbol));
    }
    cur_symbol = symbol;
    return symbol;
}


/*****************************************************************************
 * 作用：获取下一个类型不为None的token，中间获取的类型为None的token都将被丢弃
 ******************************************************************************/
void IgnoreNoneToken() {
    Symbol symbol;
    do {
        symbol = Next();
    }
    while (symbol.type == None && *str != '\0');
    cur_symbol = symbol;
}


/*****************************************************************************
 * 作用：将代码文本指针移动到本行结尾的'\n'上,中间内容全部忽略
 ******************************************************************************/
void IgnoreOneLine() {
    while (*str != '\n' && *str != '\0') {
        str++;
    }
}

/*****************************************************************************
 * 作用：判断left_val op right_val 的结果
 * 参数1：左侧操作数
 * 参数2：比较运算符，可以是下列四种之一: <   <=   >   >=
 * 参数3：右侧操作数
 * 结果：如果left_val op right_val 的结果为真，返回1。否则返回0
 ******************************************************************************/
int CheckByTwoValue(int left_val, SymbolsId op, int right_val) {
    int result = 0;
    switch (op) {
    case LT: // <
        if (left_val < right_val)
            result = 1;
        break;
    case LE: // <=
        if (left_val <= right_val)
            result = 1;
        break;
    case GT: // >
        if (left_val > right_val)
            result = 1;
        break;
    case GE: // >=
        if (left_val >= right_val)
            result = 1;
        break;
    case EQUAL:
        if (left_val == right_val)
            result = 1;
        break;
    }

    return result;
}


/*****************************************************************************
 * 作用：从src中获取一个如下格式的判断语句（left_val op right_val），并交给 CheckByTwoValue 解析该语句结果
 * 结果：如果left_val op right_val 的结果为真，返回1。否则返回0
 ******************************************************************************/
int CheckExpression() {
    // MatchByType(Keyword);
    Symbol left_val = Match();
    Symbol op = Match();
    Symbol right_val = Match();

    // VAL op number
    if (left_val.type == Keyword) {
        return CheckByTwoValue(symbols[VAL].val, op.id, right_val.val);
    }
    // number op VAL
    else if (left_val.type == Number) {
        return CheckByTwoValue(left_val.val, op.id, symbols[VAL].val);
    }
    else {
        printf("错误的条件格式\n");
        return 0;
    }
}

/*****************************************************************************
 * 作用：不断从str中获取如下格式的判断语句（left_val op right_val）,并交给CheckExpression进行判断，
 *	     对返回的判断结果不断做相应位运算,直到获取到token ')'，判断结束，返回判断结果
 *
 * 结果：返回判断语句是否成立，成立返回1，不成立返回0
 ******************************************************************************/
int CheckAllExpression() {

    int ret = CheckExpression();

    while (1) {
        Match();
        switch (cur_symbol.id) {
        case LAND: {
            int rhs = CheckExpression();
            ret &= rhs;
            break;
        }
        case LOR: {
            int rhs = CheckExpression();
            ret |= rhs;
            break;
        }
        default:
            // RLB  ')'    异常的结尾会使cur_symbol.id 置为None,也会跳出while
            return ret;
            break;
        }
    }
    return ret;
}


/*****************************************************************************
 * 作用：有些函数执行时需要字符串参数，但是next解析出的token没有空字符结尾，因此使用RangePCharToPChar
 *		对字符串数据进行封装，但是该函数返回的指针为malloc的指针，因此应当在函数执行完成后释放这些内存
 ******************************************************************************/
void FreeArgsMemory() {
    // 参数中遇到字符串申请的内存
    for (int i = 0; i < ARGS_COUNT; ++i) {
        if (args[i].is_string == 0)
            return;
        if (args[i].val != (int)NULL) {
            free((void *)args[i].val);
            args[i].val = (int)NULL;
            args[i].is_string = 0;
        }
    }
}


/*****************************************************************************
 * 作用：有些函数执行时需要字符串参数，但是next解析出的token没有空字符结尾，因此使用RangePCharToPChar
 *		对字符串数据进行封装，但是该函数返回的指针为malloc的指针，因此应当在函数执行完成后释放这些内存
 ******************************************************************************/
void MatchAllArg() {
    int i = 0;
    // 第一次match会匹配掉‘(’，之后会匹配','或者‘）’
    while (Match().id != RLB) {
        // 判断，如果是数字就直接赋值
        Symbol arg = Match();
        if (arg.type == Number) {
            args[i].val = arg.val;
        }
        else if (arg.type == String) {
            args[i].val = (int)RangePCharToPChar(arg.begin, arg.end);
            args[i].is_string = 1;
        }
        else {
            printf("错误的参数\n");
            return;
        }
        i++;
        // 如果是字符串就malloc一段内存，指针给args[i].val , args[i].flag 置为 1，表示是字符串
    }
}

/*****************************************************************************
 * 作用：语句分析，支持两种语句，if和函数调用, 根据当前token判断执行那种语句的处理
 ******************************************************************************/
void Statement(void) {

    if (cur_symbol.id == IF) {
        // 获取if 条件
        MatchById(LLB);
        int result = CheckAllExpression();

        // 条件成立需要执行if下的语句
        if (result == 1) {
            while (Match().type == Functional)
                Statement();

            MatchUntilById(FI);
            return;
        }

        // 如果if 未命中，需匹配到下一个elif（if）、else 、fi，也就说忽略本条if下的所有语句
        switch (MatchUntilByIFOrElse().id) {

        case IF:
            Statement();
            return;
        case ELSE: {
            while (Match().type == Functional)
                Statement();
            return;
        }
        case FI:
            return;
        default:
            printf("意外的条件控制符\n");
            return;
        }

        return;
    }

    else if (cur_symbol.type == Functional) {

        // 不能写为MatchAllArg();
        // ((int
        // (*)())symbols[cur_symbol.id].val)(args[0].val,args[1].val,args[2].val,args[3].val,args[4].val,args[5].val);

        // 因为cur_symbol在MatchAllArg的时候已经更改，函数地址丢失，无法正常调用
        int (*func)() = ((int (*)())symbols[cur_symbol.id].val);
        MatchAllArg();
        int ret = func(args[0].val, args[1].val, args[2].val, args[3].val, args[4].val, args[5].val);
        FreeArgsMemory();
        MatchById(SEMICOLON);


        // switch (cur_symbol.id) {
        // case FUNC1: {
        //	MatchById(LLB);
        //	Symbol arg1 = MatchByType(Number);
        //	MatchById(COMMA);
        //	Symbol arg2 = MatchByType(Number);
        //	MatchById(RLB);
        //	MatchById(SEMICOLON);
        //	func1(arg1.val, arg2.val);
        //	break;
        // }
        // case FUNC2: {
        //	MatchById(LLB);
        //	Symbol arg1 = MatchByType(Number);
        //	MatchById(RLB);
        //	MatchById(SEMICOLON);
        //	func2(arg1.val);
        //	break;
        // }
        // case FUNC3: {
        //	MatchById(LLB);
        //	Symbol arg1 = MatchByType(String);
        //	MatchById(RLB);
        //	MatchById(SEMICOLON);
        //	char* buf = RangePCharToPChar(arg1.begin, arg1.end);
        //	func3(buf);
        //	free(buf);
        // }
        // default:
        //	break;
        // }
    }
}


// val 数值变化时调用, 设置str作为代码分析的入口
void AnalyseSliderVale(char *pstr, int val) {

    // 每次重新运行时都需要重新初始化
    symbols[VAL].val = val;
    str = pstr;
    code_line = 1;

    while (*str) {
        Symbol token = Match();

        switch (token.type) {
        case Number: {
            Print(token.begin, token.end);
            printf("意外获取到数字，值是%d\n", token.val);
            break;
        }
        case Keyword: {
            if (token.id == IF) {
                Statement();
            }
            else if (token.id == VAL) {
                printf("意外获取到关键字VAL,值为%d\n", symbols[VAL].val);
            }
            else {
                printf("意外获取到符号\n");
            }
            break;
        }
        case Value: {
            Print(token.begin, token.end);
            printf("意外获取到变量\n");
            break;
        }
        case Functional: {
            Statement();
            break;
        }

        default:
            break;
        }
    }
}

/*****************************************************************************
 * 作用：初始化符号表中的关键字,设置符号表中相应元素的类型为Keyword,id为相应SymbolsId,以及bgin和end用于获取hash
 ******************************************************************************/
void InitKeywordsFromSymbols() {
#define INIT_KEY_SYMBOLS(key, str, len)                                                                                \
    symbols[key].type = Keyword;                                                                                       \
    symbols[key].id = IF;                                                                                              \
    symbols[key].begin = &str[0];                                                                                      \
    symbols[key].end = symbols[key].begin + len;

    INIT_KEY_SYMBOLS(IF, "if", 2);
    INIT_KEY_SYMBOLS(IF, "fi", 2);
    INIT_KEY_SYMBOLS(VAL, "VAL", 3);
    INIT_KEY_SYMBOLS(ELIF, "elif", 4);
    INIT_KEY_SYMBOLS(ELSE, "else", 4);
#undef INIT_KEY_WORDS
}

/*****************************************************************************
 * 作用：初始化符号表中的函数，设置符号表中相应元素的类型为Functional,id为相应SymbolsId,以及begin和end用于获取hash
 ******************************************************************************/
void InitFunctionalFromSymbols() {
#define INIT_FUNCTIONAL_SYMBOLS(key, str, len)                                                                         \
    symbols[key].type = Functional;                                                                                    \
    symbols[key].id = key;                                                                                             \
    symbols[key].begin = &#str[0];                                                                                     \
    symbols[key].end = symbols[key].begin + len;                                                                       \
    symbols[key].val = (int)&str;

    INIT_FUNCTIONAL_SYMBOLS(FUNC1, func1, 5);
    INIT_FUNCTIONAL_SYMBOLS(FUNC2, func2, 5);
    INIT_FUNCTIONAL_SYMBOLS(FUNC3, func3, 5);
    INIT_FUNCTIONAL_SYMBOLS(PRINTPOINTER, printPointer, 12);

#undef INIT_FUNCIONAL_SYMBOLS
}

/*****************************************************************************
 * 作用：初始化符号表
 *      调用 InitKeywordsFromSymbos 初始化符号表中的关键字，
 *      调用 InitFunctionalFromSymbols 初始化符号表中的函数
 ******************************************************************************/
void InitSymbol() {
    InitKeywordsFromSymbols();
    InitFunctionalFromSymbols();
}


int main(int argc, char *argv[]) {

    // 在第一次解析之前需要初始化符号表一次,也可以重复初始化，以为其值固定
    InitSymbol();

    for (int i = 0; i < 6; ++i) {
        char *command = ReadFileToBuf("./command.txt");

        int val = i;
        printf("val is %d\n", val);
        AnalyseSliderVale(command, val);
        free(command);

        for (long long tmp = 0; tmp < 10000000000; ++tmp)
            ;

        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    }


    return 0;
}
