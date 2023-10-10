package ru.school21.webcalculator.services;

import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.prefs.BackingStoreException;
import java.util.prefs.Preferences;

@Service
public class HistoryService {

    private final Preferences preferences = Preferences.userRoot().node("CalcHistory");

    public void saveExpression(String expr) {
        preferences.put(expr, "");
    }

    public void clearHistory() throws BackingStoreException {
        preferences.clear();
    }

    public ArrayList<String> getHistory() throws BackingStoreException {
        return new ArrayList<>(Arrays.asList(preferences.keys()));
    }
}
