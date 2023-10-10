package ru.school21.webcalculator.controllers;

import com.alibaba.fastjson.JSONObject;
import jakarta.validation.Valid;
import javafx.util.Pair;
import org.jetbrains.annotations.NotNull;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;
import ru.school21.webcalculator.models.CreditCalc;
import ru.school21.webcalculator.models.Model;
import ru.school21.webcalculator.services.HistoryService;
import ru.school21.webcalculator.services.SettingsService;

import java.util.ArrayList;
import java.util.prefs.BackingStoreException;


@Controller
public class CalcController {

    static final int NUM_STEPS = 250;
    static final int CODOMAIN_LIMIT = 1000000;
    @Autowired
    private Model model;
    @Autowired
    private CreditCalc creditCalc;
    @Autowired
    private HistoryService historyService;
    @Autowired
    private SettingsService settingsService;

    @GetMapping("/")
    public String homeMain() {
        return "home";
    }

    @ResponseBody
    @GetMapping("/calc")
    public String getDouble(@RequestParam(name = "expr") String expr,
                            @RequestParam(defaultValue = "0.0", required = false, name = "x") Double x) {

        String result;
        try {
            model.initExpression(expr);
            result = String.valueOf(model.calculateValue(x));
        } catch (RuntimeException ex) {
            result = ex.getMessage();
        }

        return result;
    }

    @ResponseBody
    @GetMapping("/credit")
    public void calculateCredit(@RequestParam(name = "sum") double sum,
                                @RequestParam(name = "term") int term,
                                @RequestParam(name = "interest") double interest,
                                @RequestParam(name = "type") boolean type) {
        creditCalc.calculateCredit(sum, term, interest, type ? CreditCalc.PayType.kDiffPay : CreditCalc.PayType.kAnnPay);
    }

    @ResponseBody
    @GetMapping("/credit/payment")
    public String getPayment() {
        return creditCalc.getPayment();
    }

    @ResponseBody
    @GetMapping("/credit/interest")
    public double getSumInterest() {
        return creditCalc.getSumInterest();
    }

    @ResponseBody
    @GetMapping("/credit/main")
    public double getSumMain() {
        return creditCalc.getSumMain();
    }

    @ResponseBody
    @GetMapping("/graph")
    public ArrayList<Pair<Double, Double>> calculateGraph(@RequestParam(name = "expr") String expr,
                                                          @RequestParam(defaultValue = "-10", required = false, name = "int1") Double leftBound,
                                                          @RequestParam(defaultValue = "10", required = false, name = "int2") Double rightBound) {

        ArrayList<Pair<Double, Double>> graph = new ArrayList<>();
        try {
            model.initExpression(expr);
            double sizeStep = (rightBound - leftBound) / (NUM_STEPS - 1);

            for (int i = 0; i < NUM_STEPS; ++i) {
                double x = leftBound + i * sizeStep;
                double result = model.calculateValue(x);
                if (Double.isNaN(result) || Double.isInfinite(result) || Math.abs(result) > CODOMAIN_LIMIT) continue;
                graph.add(new Pair<>(x, result));
            }
        } catch (RuntimeException ex) {
            System.out.println(ex.getMessage());
        }
        return graph;
    }

    @ResponseBody
    @GetMapping("/history/get")
    public ArrayList<String> getHistory() throws BackingStoreException {
        return historyService.getHistory();
    }

    @ResponseBody
    @DeleteMapping("/history/clear")
    public void clearHistory() throws BackingStoreException {
        historyService.clearHistory();
    }

    @ResponseBody
    @PostMapping("/history/save")
    public void saveHistory(@Valid @RequestBody @NotNull JSONObject str) {
        historyService.saveExpression(str.get("data").toString());
    }

    @ResponseBody
    @GetMapping("/setting/save")
    public void saveSetting(@RequestParam(name = "type") int type) {
        settingsService.saveTheme(type);
    }

    @ResponseBody
    @GetMapping("/setting/load")
    public int loadSetting() throws BackingStoreException {
        return settingsService.getTheme();
    }

}
