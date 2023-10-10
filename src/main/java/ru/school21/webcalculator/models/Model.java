package ru.school21.webcalculator.models;

import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;
import java.util.Stack;

import static java.lang.Math.*;

@Component
public class Model {
    public static final String CALC_ERROR = "INCORRECT EXPRESSION";

    enum LexemeType {
        kNan, kNumber, kVariable, kPlus, kMinus, kMul, kDiv, kMod, kExp, kUnPlus, kUnMinus,
        kLeftBr, kRightBr, kCos, kSin, kTan, kAcos, kAsin, kAtan, kSqrt, kLn, kLog
    }

    static {
        System.loadLibrary("model");
    }

    public class Lexeme {
        LexemeType type;
        int priority;
        double value;

        public Lexeme(int type, int priority, double value) {
            this.type = LexemeType.values()[type];
            this.priority = priority;
            this.value = value;
        }

        @Override
        public String toString() {
            return "\nLexeme{" +
                    "type=" + type +
                    ", priority=" + priority +
                    ", value=" + value +
                    '}';
        }
    }

    private final List<Lexeme> expression = new ArrayList<>();

    public void showExpression() {
        System.out.println(expression);
    }

    public void clearExpression() {
        expression.clear();
    }

    public void initExpression(String str) {
        expression.clear();
        parsingStr(str);
    }

    private native void parsingStr(String str);

    public double calculateValue(double value) {
        if (expression.isEmpty()) throw new RuntimeException(CALC_ERROR);
        Stack<Double> result = new Stack<>();
        for (Lexeme it : expression) {
            if (it.type == LexemeType.kNumber) {
                result.push(it.value);
            } else if (it.type == LexemeType.kVariable) {
                result.push(value);
            } else if (!result.empty()) {
                if (it.type == LexemeType.kUnPlus) {;
                } else if (it.type == LexemeType.kUnMinus) {
                    result.push(-result.pop());
                } else if (it.type == LexemeType.kCos) {
                    result.push(cos(result.pop()));
                } else if (it.type == LexemeType.kSin) {
                    result.push(sin(result.pop()));
                } else if (it.type == LexemeType.kTan) {
                    result.push(tan(result.pop()));
                } else if (it.type == LexemeType.kAcos) {
                    result.push(acos(result.pop()));
                } else if (it.type == LexemeType.kAsin) {
                    result.push(asin(result.pop()));
                } else if (it.type == LexemeType.kAtan) {
                    result.push(atan(result.pop()));
                } else if (it.type == LexemeType.kSqrt) {
                    result.push(sqrt(result.pop()));
                } else if (it.type == LexemeType.kLn) {
                    result.push(log(result.pop()));
                } else if (it.type == LexemeType.kLog) {
                    result.push(log10(result.pop()));
                } else {
                    if (result.size() > 1) {
                        double arg_one = result.pop();
                        if (it.type == LexemeType.kPlus) result.push(result.pop() + arg_one);
                        else if (it.type == LexemeType.kMinus) result.push(result.pop() - arg_one);
                        else if (it.type == LexemeType.kMul) result.push(result.pop() * arg_one);
                        else if (it.type == LexemeType.kDiv) result.push(result.pop() / arg_one);
                        else if (it.type == LexemeType.kMod) result.push(result.pop() % arg_one);
                        else if (it.type == LexemeType.kExp) result.push(pow(result.pop(), arg_one));
                    } else {
                        throw new RuntimeException(CALC_ERROR);
                    }
                }
            } else {
                throw new RuntimeException(CALC_ERROR);
            }
        }
        if (result.size() != 1) {
            throw new RuntimeException(CALC_ERROR);
        }
        return result.peek();
    }
}
