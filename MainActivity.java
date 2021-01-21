package com.example.swaram;

import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.media.MediaPlayer;
import android.net.wifi.p2p.WifiP2pManager;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.ArrayAdapter;
import android.widget.AdapterView;
import android.widget.Spinner;
import android.widget.Toast;
import android.content.Intent;
import java.io.File;
import java.util.List;

import com.example.swaram.Bridge;

public class MainActivity extends AppCompatActivity {
    public List<Raga> database;
    public Spinner ragalist;
    public Spinner srutilist;
    public ArrayAdapter<String> ragaadapter;
    public ArrayAdapter<CharSequence> srutiadapter;
    public int ragalist_selectedID;
    public int srutilist_selectedID;

    protected void onCreate(Bundle savedInstanceState, List<Raga> database, List<String> srutis) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        createSrutiList();
        createRagaList();
        final Button play = (Button) findViewById(R.id.play);
        play.setOnClickListener(new View.OnClickListener() {
                public void onClick(View view) {
                    if (ragalist.getSelectedItemPosition()>=0 && srutilist.getSelectedItemPosition()>=0) {
                        onItemSelected(ragaadapter,srutiadapter,view,ragalist.getSelectedItemPosition(),srutilist.getSelectedItemPosition(),R.id.Select_raga,R.id.Select_sruti);
                        RagaPlayer player = new RagaPlayer(srutilist.getSelectedItem().toString(), Bridge.getScale((Raga)ragalist.getSelectedItem()));
                    }
                }
            }
        );
    }

    protected void createRagaList() {
        /*
        int i=0;
        while(database.get(i) !=null) {
            System.out.println(database.get(i).name);
        }*/
        database = Bridge.upload_data(database, new File("C:\\srira\\Desktop\\'Raga Player App'\\all-ragas-alphabetical.txt"));
        String[] items = new String[database.size()];
        for (int i = 0; database.get(i) !=null; i++) {
            Log.d("MainActivity",database.get(i).name);
            items[i] = database.get(i).name;
        }
        ragaadapter= new ArrayAdapter<String>(this, android.R.layout.simple_spinner_item, items);
        ragaadapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        ragalist = findViewById(R.id.Select_raga);
        ragalist.setOnItemSelectedListener((AdapterView.OnItemSelectedListener) this);
        ragalist_selectedID = ragalist.getSelectedItemPosition();
        ragalist.setAdapter(ragaadapter);
        for (int i = 0; database.get(i) !=null; i++) {
            Log.d("MainActivity",database.get(i).name);
            ragaadapter.add(database.get(i).name);
            ragaadapter.notifyDataSetChanged();
        }
    }


    protected void createSrutiList() {
        srutilist = (Spinner) findViewById(R.id.Select_sruti);
        srutiadapter = ArrayAdapter.createFromResource(this, R.array.srutis, android.R.layout.simple_spinner_item);
        srutiadapter.setDropDownViewResource(android.R.layout.simple_spinner_dropdown_item);
        srutilist.setOnItemSelectedListener((AdapterView.OnItemSelectedListener) this);
        srutilist_selectedID = srutilist.getSelectedItemPosition();
        srutilist.setAdapter(srutiadapter);
        srutilist.setSelection(srutilist_selectedID);
    }


    public void onItemSelected(ArrayAdapter<String> ragas, ArrayAdapter<CharSequence> srutis, View arg1, int ragaposition, int srutiposition, long ragaid, long srutiid) {
        Toast.makeText(getApplicationContext(), "Playing"+ragas.getItem(ragaposition)+"in sruti"+srutis.getItem(srutiposition), Toast.LENGTH_LONG).show();
    }

    public void onNothingSelected(AdapterView<?> parent) {

    }


    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
}
