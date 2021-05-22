package com.mactec.newkaligo.bluetooth;

import android.bluetooth.BluetoothSocket;
import android.os.Build;
import android.util.Log;

import androidx.annotation.RequiresApi;

import java.io.IOException;

public class ConnectThread extends Thread {

    private final Bluetooth bluetoothInstance;

    public ConnectThread(final Bluetooth bluetoothInstance) {
        this.bluetoothInstance = bluetoothInstance;
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public void run() {
        try {
            Log.i(Bluetooth.TAG, "RUN mConnectThread ");
            Log.d(Bluetooth.TAG, "ConnectThread: Trying to create InsecureRfcommSocket using UUID: " + Bluetooth.MY_UUID);
            // Get a BluetoothSocket for a connection with the given BluetoothDevice
            if(this.bluetoothInstance.getActualDevice().isPresent()){
                BluetoothSocket mmSocket = this.bluetoothInstance.getActualDevice().get().createRfcommSocketToServiceRecord(Bluetooth.MY_UUID);
                // Always cancel discovery because it will slow down a connection
                this.bluetoothInstance.getBluetoothAdapter().cancelDiscovery();
                // Make a connection to the BluetoothSocket
                Log.d(Bluetooth.TAG, "ConnectThread: Trying to connect InsecureRfcommSocket using UUID: " + Bluetooth.MY_UUID);
                // This is a blocking call and will only return on a successful connection or an exception
                mmSocket.connect();
                this.bluetoothInstance.connected(mmSocket);
            }
            Log.d(Bluetooth.TAG, "run: ConnectThread connected.");
        } catch (IOException e) {
            Log.d(Bluetooth.TAG, "run: ConnectThread: Could not connect to UUID: " + Bluetooth.MY_UUID);
        }
    }
}
