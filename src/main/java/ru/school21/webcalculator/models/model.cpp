#include "model.h"
#include "ru_school21_webcalculator_models_Model.h"
#include "ru_school21_webcalculator_models_CreditCalc.h"


namespace s21 {

int model::check_str(const std::string& str) {
    int num_brackets = 0;
    for (auto& it : str) {
        if (it == '(') {
            ++num_brackets;
        } else if (it == ')') {
            --num_brackets;
        }
        if (num_brackets < 0) return -1;
    }
    return num_brackets > 0 ? 1 : 0;
}

void model::input(const std::string& str) {
#if defined(linux) || defined(__linux)
    setlocale(LC_ALL, "en_US.UTF-8");
#endif
    parsing(str);
    polish_notation();
}

void model::show() {
    std::cout << "\nExpression:\n";
    for (auto& it : expr_) {
        std::cout << "[" << str_type[it.type_] << "]    ";
        std::cout << "\tpriority: " << it.priority_ << "\tvalue=" << it.value_  << std::endl;
    }
}

void model::parsing(std::string str) {
    std::regex pattern("([0-9]+([.][0-9]*)?|[.][0-9]*)(?:[eE][-+]?[0-9]+)?|[-/\\+\\*\\(\\)\\^]|x|"
                        "mod|cos|sin|tan|acos|asin|atan|sqrt|ln|log");
    std::smatch result;
    for (; std::regex_search(str, result, pattern);  str = result.suffix().str()) {
        //  std::cout << result.str()<< " ";
        if (result.str()[0] >= '0' && result.str()[0] <= '9') {
            expr_.push_back(lexeme(kNumber, 0, std::stod(result.str())));
        } else if (result.str()[0] == '.') {
            expr_.push_back(lexeme(kNumber, 0, std::stod("0" + result.str())));
        } else if (result.str() =="x") {expr_.push_back(lexeme(kVariable, 0, 0));}
        else if (result.str() =="+") expr_.push_back(lexeme(kPlus, 1, 0));
        else if (result.str() =="-") expr_.push_back(lexeme(kMinus, 1, 0));
        else if (result.str() =="*") expr_.push_back(lexeme(kMul, 2, 0));
        else if (result.str() =="/") expr_.push_back(lexeme(kDiv, 2, 0));
        else if (result.str() =="mod") expr_.push_back(lexeme(kMod, 2, 0));
        else if (result.str() =="^") expr_.push_back(lexeme(kExp, 3, 0));
        else if (result.str() =="(") expr_.push_back(lexeme(kLeftBr, 0, 0));
        else if (result.str() ==")") expr_.push_back(lexeme(kRightBr, 0, 0));
        else if (result.str() =="cos") expr_.push_back(lexeme(kCos, 0, 0));
        else if (result.str() =="sin") expr_.push_back(lexeme(kSin, 0, 0));
        else if (result.str() =="tan") expr_.push_back(lexeme(kTan, 0, 0));
        else if (result.str() =="acos") expr_.push_back(lexeme(kAcos, 0, 0));
        else if (result.str() =="asin") expr_.push_back(lexeme(kAsin, 0, 0));
        else if (result.str() =="atan") expr_.push_back(lexeme(kAtan, 0, 0));
        else if (result.str() =="sqrt") expr_.push_back(lexeme(kSqrt, 0, 0));
        else if (result.str() =="ln") expr_.push_back(lexeme(kLn, 0, 0));
        else if (result.str() =="log") expr_.push_back(lexeme(kLog, 0, 0));
    }
    expr_.push_back(lexeme(kNan, 0, 0));
    //  std::cout << std::endl;
    uno_fix();
}

void model::uno_fix() {
    int uno_flag = 1;
    for (auto& it : expr_) {
        if (it.type_ == kPlus) {
            if (uno_flag) {
                it.type_ = kUnPlus;
                it.priority_ = 4;
            }
            uno_flag = 1;
        } else if (it.type_ == kMinus) {
            if (uno_flag) {
                it.type_ = kUnMinus;
                it.priority_ = 4;
            }
            uno_flag = 1; }
        else if (it.type_ == kMul) uno_flag = 1;
        else if (it.type_ == kDiv) uno_flag = 1;
        else if (it.type_ == kMod) uno_flag = 1;
        else if (it.type_ == kExp) uno_flag = 1;
        else if (it.type_ == kLeftBr) uno_flag = 1;
        else if (it.type_ == kRightBr) uno_flag = 0;
        else if (it.type_ == kNumber) uno_flag = 0;
        else if (it.type_ == kVariable) uno_flag = 0;
    }
}

void model::polish_notation() {
    std::list<lexeme> moscow_;
    std::list<lexeme> taxis_;
    for (auto& it : expr_) {
        if (it.type_ == kNumber || it.type_ == kVariable) {
            moscow_.push_back(it);
        } else if (it.type_ == kUnPlus) {
            taxis_.push_back(it);
        } else if (it.type_ == kUnMinus) {
            taxis_.push_back(it);
        } else if (it.type_ == kCos || it.type_ == kSin || it.type_ == kTan) {
            taxis_.push_back(it);
        } else if (it.type_ == kAcos || it.type_ == kAsin || it.type_ == kAtan) {
            taxis_.push_back(it);
        } else if (it.type_ == kSqrt || it.type_ == kLn || it.type_ == kLog) {
            taxis_.push_back(it);
        } else if (it.type_ == kLeftBr) {
            taxis_.push_back(it);
        } else if (it.type_ == kPlus || it.type_ == kMinus || it.type_ == kExp ||
            it.type_ == kMul || it.type_ == kDiv || it.type_ == kMod) {
            for (auto it_t = taxis_.end(); it_t != taxis_.begin() &&
                (--it_t)->priority_ >= it.priority_ && it_t->type_ != kLeftBr; ) {
                moscow_.push_back(*it_t);
                taxis_.pop_back();
                it_t = taxis_.end();
            }
            taxis_.push_back(it);
        } else if (it.type_ == kRightBr) {
            for (auto it_t = taxis_.end(); it_t != taxis_.begin() && (--it_t)->type_ != kLeftBr; ) {
                moscow_.push_back(*it_t);
                taxis_.pop_back();
                it_t = taxis_.end();
            }
            taxis_.pop_back();                                                              // kLeftBr
            if (taxis_.begin() != taxis_.end()) {
                auto it_t = taxis_.end();
                if ((--it_t)->type_ == kCos || it_t->type_ == kSin || it_t->type_ == kTan ||
                        it_t->type_ == kAcos || it_t->type_ == kAsin || it_t->type_ == kAtan ||
                        it_t->type_ == kSqrt || it_t->type_ == kLn || it_t->type_ == kLog) {
                    moscow_.push_back(*it_t);
                    taxis_.pop_back();
                }
            }
        } else if (it.type_ == kNan) {
            for (auto it_t = taxis_.end(); it_t != taxis_.begin(); ) {
                moscow_.push_back(*(--it_t));
                taxis_.pop_back();
                it_t = taxis_.end();
            }
        }
    }
    expr_.swap(moscow_);
}

}   // namespace s21

//JNIEXPORT void JNICALL Java_com_example_calculator_models_Model_parsingStr(JNIEnv* env, jobject obj, jstring jstr) {

JNIEXPORT void JNICALL Java_ru_school21_webcalculator_models_Model_parsingStr(JNIEnv* env, jobject obj, jstring jstr) {
    const char* cstr = env->GetStringUTFChars(jstr, NULL);
    std::string str = std::string(cstr);

    s21::model model_instance;
    int result = model_instance.check_str(str);
    if (!result) {
        model_instance.input(str);

        jclass cls_model = env->GetObjectClass(obj);
        jfieldID fid_expr = env->GetFieldID(cls_model, "expression", "Ljava/util/List;");
        jobject obj_expr = env->GetObjectField(obj, fid_expr);
        jclass cls_list = env->GetObjectClass(obj_expr);
        jmethodID midAdd = env->GetMethodID(cls_list, "add", "(Ljava/lang/Object;)Z");

        jclass cls_lexeme = env->FindClass("ru/school21/webcalculator/models/Model$Lexeme");
        jmethodID midConstr = env->GetMethodID(cls_lexeme, "<init>", "(Lru/school21/webcalculator/models/Model;IID)V");

        for (auto& it : model_instance.getExpression()) {
            env->CallObjectMethod(obj_expr, midAdd,
            env->NewObject(cls_lexeme, midConstr, obj, it.type_, it.priority_, it.value_));
        }
        env->ReleaseStringUTFChars(jstr, cstr);
    } else if (result < 0) {
        env->ReleaseStringUTFChars(jstr, cstr);
        env->ThrowNew(env->FindClass("java/lang/RuntimeException"), s21::kCrossBrackets);
    } else {
        env->ReleaseStringUTFChars(jstr, cstr);
        env->ThrowNew(env->FindClass("java/lang/RuntimeException"), s21::kUnclosedBracket);
    }
}

namespace s21 {

std::vector<payment>& CreditCalc::CreatePayments(double sum, size_t num, double interest, pay_type type) {
    type_ = type;
    payts_.push_back(payment(sum, 0, 0));
    if (type == kDiffPay) {
        for (size_t i = 1; i <= num; ++i) {
            double interest_payment = payts_[i - 1].remainder_ * interest / 12;
            double main_payment = payts_[i - 1].remainder_ / (num - i + 1);
            double remainder_payment = payts_[i - 1].remainder_ - main_payment;
            payts_.push_back(payment(remainder_payment, main_payment, interest_payment));
            sum_main_ += payts_[i].main_;
            sum_interest_ += payts_[i].interest_;
        }
    } else if (type == kAnnPay) {
        interest /= 12;
        for (size_t i = 1; i <= num; ++i) {
            double interest_payment = payts_[i - 1].remainder_ * interest;
            double main_payment = sum * (interest  + interest /
                                    (pow(interest + 1, num) - 1)) - interest_payment;
            double remainder_payment = payts_[i - 1].remainder_ - main_payment;
            payts_.push_back(payment(remainder_payment, main_payment, interest_payment));
            sum_interest_ += round(interest_payment * 100) / 100;
            sum_main_ += round(main_payment * 100) / 100;
        }
    }
    return payts_;
}

void CreditCalc::Show() {
    std::cout << "\ntype: " << type_ << " size: " << payts_.size() << std::endl;
    for (auto& it : payts_) {
        std::cout  << "main: " << it.main_ << "\tinterest: " << it.interest_;
        std::cout << "\trem: " << it.remainder_  << std::endl;
    }
    std::cout << "sum_main: " << sum_main_ << "\tsum_interest: " << sum_interest_ << std::endl;
}

}   // namespace s21

//JNIEXPORT void JNICALL Java_com_example_calculator_models_CreditCalc_createPayments
JNIEXPORT void JNICALL Java_ru_school21_webcalculator_models_CreditCalc_createPayments
  (JNIEnv* env, jobject obj, jdouble sum, jint num, jdouble interest , jint type) {

    s21::CreditCalc credit_instance;
    auto result = (type ? credit_instance.CreatePayments(sum, num, interest, s21::kAnnPay) :
                          credit_instance.CreatePayments(sum, num, interest, s21::kDiffPay));

    jclass cls_credit = env->GetObjectClass(obj);
    jfieldID fid_pays = env->GetFieldID(cls_credit, "payments", "Ljava/util/List;");
    jobject obj_pays = env->GetObjectField(obj, fid_pays);
    jclass cls_list = env->GetObjectClass(obj_pays);
    jmethodID midAdd = env->GetMethodID(cls_list, "add", "(Ljava/lang/Object;)Z");

    jclass cls_payment = env->FindClass("ru/school21/webcalculator/models/CreditCalc$Payment");
    jmethodID midConstr = env->GetMethodID(cls_payment, "<init>", "(Lru/school21/webcalculator/models/CreditCalc;DDD)V");

    for (auto& it : result) {
        env->CallObjectMethod(obj_pays, midAdd,
        env->NewObject(cls_payment, midConstr, obj, it.remainder_, it.main_, it.interest_));
    }
}
