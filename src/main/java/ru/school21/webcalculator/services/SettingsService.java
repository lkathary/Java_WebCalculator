package ru.school21.webcalculator.services;

import org.springframework.stereotype.Service;

import java.util.prefs.Preferences;

@Service
public class SettingsService {

    private final Preferences preferences = Preferences.userRoot().node("CalcSettings");

    public void saveTheme(int type) {
        preferences.putInt("theme", type);
    }

    public int getTheme() {
        return preferences.getInt("theme", 0);
    }
}
