package com.example.swaram;

import java.io.File;
import java.io.ObjectInputStream;
import java.nio.channels.FileLock;
import java.util.List;
import java.util.Map;

public class Bridge {
    static { System.loadLibrary("c-wrapper"); }
    public static double A = 220;
    public static double A2 = 233.08;
    public static double B = 246.942;
    public static double C = 261.6256;
    public static double C2 = 277.18;
    public static double D = 293.6648;
    public static double D2 = 311.13;
    public static double E = 329.6275;
    public static double F = 349.2282;
    public static double F2 = 369.99;
    public static double G = 391.9954;
    public static double G2 = 415.30;

    public static double INPUT_MAX = 100;
    public static double datasize = 1000;

    private double[] ratios = {1.0, 1.067, 1.125, 1.2, 1.125, 1.2, 1.25, 1.333, 1.406, 1.5, 1.6, 1.6875, 1.8, 1.6875, 1.8, 1.875, 2.0};



//Use Beep function to play a sound at a frequency

    /*ragas*/
    public static double srutis[] = {A, A2, B, C, C2, D, D2, E, F, F2, G, G2};

    /* swaras */
    public static String swaras[] = {"S0", "R1", "R2", "R3", "G1", "G2", "G3", "M1", "M2", "P", "D1", "D2", "D3", "N1", "N2", "N3", "S1"};

  //  public static native void playsruti(double sruti);
    public static native List<Raga> upload_data(List<Raga> data, File x);
    public static native String[] srutis();
    public static native double[] srutivals();
    public static native double[] ratios();
    public native void addraga(List<Raga> data);
    public static native int indexof(double x);
    public static native int indexofchar(String x);
    public static native double[] getScale(Raga ragam);
    public static native int getLength(Raga ragam);
    public static native int search(String input);
    public static native void clearKeyBoardBuffer();
}
