package com.mactec.newkaligo.bluetooth;

import android.bluetooth.BluetoothSocket;
import android.os.Build;
import android.util.Log;

import androidx.annotation.RequiresApi;

import com.mactec.newkaligo.model.ModelImpl;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.Charset;

public class ConnectedThread extends Thread {
    private final BluetoothSocket bluetoothSocket;
    private InputStream socketInputStream;
    private OutputStream socketOutputStream;
    private Bluetooth bluetoothInstance;

    @RequiresApi(api = Build.VERSION_CODES.N)
    public ConnectedThread(final Bluetooth bluetoothInstance, final BluetoothSocket socket) {
        Log.d(Bluetooth.TAG, "ConnectedThread: Starting.");
        this.bluetoothSocket = socket;
        this.bluetoothInstance = bluetoothInstance;
        try{
            this.socketInputStream = this.bluetoothSocket.getInputStream();
            this.socketOutputStream = this.bluetoothSocket.getOutputStream();
            this.bluetoothInstance.setConnection(true);
        } catch (IOException e){
            this.socketInputStream = null;
            this.socketOutputStream = null;
            this.bluetoothInstance.setConnection(false);
        }
    }

    public void run(){
        byte[] buffer = new byte[Bluetooth.BUFFER_SIZE];  // buffer store for the stream

        // Keep listening to the InputStream until an exception occurs
        while (this.bluetoothInstance.isConnectionEnable()) {
            // Read from the InputStream
            try {
                int bytes = socketInputStream.read(buffer);
                String incomingMessage = new String(buffer, 0, bytes);
                Log.d(Bluetooth.TAG, "InputStream: " + incomingMessage);
                ModelImpl.getInstance().manageMessageFromBluetooth(incomingMessage);
            } catch (IOException e) {
                Log.e(Bluetooth.TAG, "write: Error reading Input Stream. " + e.getMessage() );
                break;
            }
        }
    }

    //Call this from the main activity to send data to the remote device
    public boolean write(byte[] bytes) {
        String text = new String(bytes, Charset.defaultCharset());
        Log.d(Bluetooth.TAG, "write: Writing to outputstream: " + text);
        try {
            socketOutputStream.write(bytes);
            return true;
        } catch (IOException e) {
            Log.e(Bluetooth.TAG, "write: Error writing to output stream. " + e.getMessage());
            return false;
        }
    }

    /* Call this from the main activity to shutdown the connection */
    public void cancel() {
        try {
            if(this.socketInputStream != null)
                this.socketInputStream.close();

            if(this.socketOutputStream != null)
                this.socketOutputStream.close();

            bluetoothSocket.close();
        } catch (IOException ignored) { }
    }
}
