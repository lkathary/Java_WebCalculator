package ru.school21.webcalculator.models;

import org.springframework.stereotype.Component;

import java.util.ArrayList;
import java.util.List;

@Component
public class CreditCalc {
    public enum PayType {kDiffPay, kAnnPay}

    static {
        System.loadLibrary("model");
    }

    public class Payment {
        double remainder;
        double main;
        double interest;

        public Payment(double remainder, double main, double interest) {
            this.remainder = remainder;
            this.main = main;
            this.interest = interest;
        }

        public String toRecord() {
            return String.format("%-,6.2f", main + interest) + "\t\t"
                    + String.format("%-,6.2f", main) + "\t\t"
                    + String.format("%-,6.2f", interest) + "\t\t\t"
                    + String.format("%-,6.2f", remainder);
        }

        @Override
        public String toString() {
            return "\nPayment{" +
                    "remainder=" + remainder +
                    ", main=" + main +
                    ", interest=" + interest +
                    '}';
        }
    }

    private final List<Payment> payments = new ArrayList<>();
    private String payment;
    private double sumMain = 0;
    private double sumInterest = 0;

    public List<Payment> getPayments() {
        return payments;
    }

    public String getPayment() {
        return payment;
    }

    public double getSumMain() {
        return sumMain;
    }

    public double getSumInterest() {
        return sumInterest;
    }

    public void calculateCredit(double sum, int num, double interest, PayType type) {
        payments.clear();
        createPayments(sum, num, interest, type.ordinal());
        sumMain = 0;
        sumInterest = 0;
        if (type == PayType.kAnnPay) {
            payment = String.format("%-,6.2f", payments.get(1).main + payments.get(1).interest);
        } else {
            payment = String.format("%-,6.2f", payments.get(1).main + payments.get(1).interest) + " ... "
                    + String.format("%-,6.2f", payments.get(num).main + payments.get(num).interest);
        }
        for (int i = 1; i <= num; ++i) {
            sumMain += payments.get(i).main;
            sumInterest += payments.get(i).interest;
        }
        sumMain = Math.round(sumMain * 100.0) / 100.0;
        sumInterest = Math.round(sumInterest * 100.0) / 100.0;
    }

    public native void createPayments(double sum, int num, double interest, int type);
}
