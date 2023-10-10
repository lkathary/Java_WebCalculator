#ifndef SRC_MODEL_H_
#define SRC_MODEL_H_

#include <cmath>
#include <iostream>
#include <jni.h>
#include <list>
#include <regex>                                                                 // NOLINT(*)

namespace s21 {

const char* str_type[] = {
                            "NAN",
                            "NUMBER",
                            "VARIABLE",
                            "PLUS",
                            "MINUS",
                            "MUL",
                            "DIV",
                            "MOD",
                            "EXP",
                            "UN_PLUS",
                            "UN_MINUS",
                            "LEFT_BR",
                            "RIGHT_BR",
                            "COS",
                            "SIN",
                            "TAN",
                            "ACOS",
                            "ASIN",
                            "ATAN",
                            "SQRT",
                            "LN",
                            "LOG"
};

constexpr const char* kCrossBrackets = "CROSS BRACKETS";
constexpr const char* kUnclosedBracket = "UNCLOSED BRACKET";

typedef enum {
    kNan, kNumber, kVariable, kPlus, kMinus, kMul, kDiv, kMod, kExp, kUnPlus, kUnMinus,
    kLeftBr, kRightBr, kCos, kSin, kTan, kAcos, kAsin, kAtan, kSqrt, kLn, kLog
} lexeme_type;

class model {
    struct lexeme {
     lexeme_type type_;
     int priority_;
     double value_;
     lexeme(lexeme_type type, int priority, double value) :
        type_(type), priority_(priority), value_(value) {}
    };

 public:
    model() = default;
    ~model() = default;

    int check_str(const std::string& str);
    void input(const std::string& str);
    void show();
    std::list<lexeme>& getExpression() {return expr_;}

 private:
    std::list<lexeme> expr_;

    void parsing(std::string str);
    void uno_fix();
    void polish_notation();
};

//  -----------------------

typedef enum {kDiffPay, kAnnPay} pay_type;

struct payment {
     double remainder_;
     double main_;
     double interest_;
     payment(double remainder, double main, double interest) :
                    remainder_(remainder), main_(main), interest_(interest) {}
};

class CreditCalc {

 public:
      CreditCalc() : type_(kAnnPay), sum_main_(0), sum_interest_(0) {}
      ~CreditCalc() = default;
      pay_type GetType() {return type_;}
      double GetSumMain() {return sum_main_;}
      double GetSumInterest() {return sum_interest_;}
      std::vector<payment>& GetPayt() {return payts_;}
      std::vector<payment>& CreatePayments(double sum, size_t num, double interest, pay_type type);
      void Clear();
      void Show();

 private:
      pay_type type_;
      double sum_main_;
      double sum_interest_;
      std::vector<payment> payts_;
};

}  // namespace s21

#endif   // SRC_MODEL_H_
