package com.example.swaram;

import android.app.Activity;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioTrack;
import android.os.Handler;
import android.os.Bundle;

public class RagaPlayer extends Activity {
    private String sruti;
    private double[] swaras;

    private final int duration = 3; // seconds
    private final int sampleRate = 8000;
    private final int numSamples = duration * sampleRate;
    private final double sample[] = new double[numSamples];
    private final byte generatedSnd[] = new byte[2 * numSamples];
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

    Handler handler = new Handler();

    public RagaPlayer(String s, double[] array) {
        this.sruti = s;
        this.swaras = array;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
    }

    protected void onResume() {
        super.onResume();

        // Use a new tread as this can take a while
        final Thread thread = new Thread(new Runnable() {
            public void run() {
                playragam();
                handler.post(new Runnable() {

                    public void run() {
                        playSound();
                    }
                });
            }
        });
        thread.start();
    }

    private static double[] getSwaras(double[] swaras, String sruti) {
        double freq=0;
        if (sruti=="A"){
            freq = A;
        }else if (sruti=="A#") {
            freq = A2;
        }else if (sruti=="B") {
            freq = B;
        }else if (sruti=="C") {
            freq = C;
        }else if (sruti=="C#") {
            freq = C2;
        }else if (sruti=="D") {
            freq = D;
        }else if (sruti=="D#") {
            freq = D2;
        }else if (sruti=="E") {
            freq = E;
        }else if (sruti=="F") {
            freq = F;
        }else if (sruti=="F#") {
            freq = F2;
        }else if (sruti=="G") {
            freq = G;
        }else if (sruti=="G#") {
            freq = G2;
        }
        double[] freqs = new double[swaras.length];
        for (int i=0; i<freqs.length; i++) {
            freqs[i]=freq*swaras[i];
        }
        return freqs;
    }

    public void playragam() {
        // fill out the array
        for (int i = 0; i < swaras.length; ++i) {
            sample[i] = Math.sin(2 * Math.PI * i / (sampleRate/getSwaras(swaras,sruti)[i]));
        }

        // convert to 16 bit pcm sound array
        // assumes the sample buffer is normalised.
        int idx = 0;
        for (final double dVal : sample) {
            // scale to maximum amplitude
            final short val = (short) ((dVal * 32767));
            // in 16 bit wav PCM, first byte is the low order byte
            generatedSnd[idx++] = (byte) (val & 0x00ff);
            generatedSnd[idx++] = (byte) ((val & 0xff00) >>> 8);

        }
    }

    void playSound(){
        final AudioTrack audioTrack = new AudioTrack(AudioManager.STREAM_MUSIC,
                sampleRate, AudioFormat.CHANNEL_CONFIGURATION_MONO,
                AudioFormat.ENCODING_PCM_16BIT, swaras.length,
                AudioTrack.MODE_STATIC);
        audioTrack.write(generatedSnd, 0, generatedSnd.length);
        audioTrack.play();
    }
}
