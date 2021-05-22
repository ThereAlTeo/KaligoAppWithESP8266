package com.mactec.newkaligo.bluetooth;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Build;

import androidx.annotation.RequiresApi;

import com.mactec.newkaligo.R;

import java.util.Optional;
import java.util.UUID;

public class Bluetooth {
    public static final String TAG = "BluetoothConnectionServ";
    public static final UUID MY_UUID = UUID.fromString("00001101-0000-1000-8000-00805F9B34FB");
    public static final int BUFFER_SIZE = 1024;
    public static final int ENABLE_BT_REQUEST = 1;

    private static Bluetooth BLUETOOTH_SINGLETON;
    private BluetoothAdapter bluetoothAdapter;
    private Optional<BluetoothDevice> actualDevice;
    private ConnectedThread connectedThread;
    private boolean connectionEnable;

    @RequiresApi(api = Build.VERSION_CODES.N)
    private Bluetooth(){
        this.connectionEnable = false;
        this.bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        this.actualDevice = Optional.empty();
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public void setConnection(boolean connectionIsEnable) {
        this.connectionEnable = connectionIsEnable;
        if(!this.connectionEnable){
            this.actualDevice = Optional.empty();
        }
    }

    public boolean isConnectionEnable() {
        return connectionEnable;
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public static Bluetooth getInstance(){
        if(BLUETOOTH_SINGLETON == null)
            BLUETOOTH_SINGLETON = new Bluetooth();

        return BLUETOOTH_SINGLETON;
    }

    public BluetoothAdapter getBluetoothAdapter(){
        return this.bluetoothAdapter;
    }

    public void selectActualDevice(final Optional<BluetoothDevice> actualDevice){
        this.actualDevice = actualDevice;
        new ConnectThread(this).start();
    }

    public Optional<BluetoothDevice> getActualDevice(){
        return this.actualDevice;
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public void closeConnection(){
        this.setConnection(false);
        this.getConnectedThread().cancel();
    }

    public boolean deviceCanUseBluetooth(){
        return this.bluetoothAdapter != null;
    }

    public void connected(final BluetoothSocket bluetoothSocket){
        this.connectedThread = new ConnectedThread(this, bluetoothSocket);
        this.connectedThread.start();
    }

    public ConnectedThread getConnectedThread() {
        return connectedThread;
    }

    public boolean tryToSendMessage(final String commandSend){
        if(this.isConnectionEnable()) {
            return this.getConnectedThread().write(commandSend.getBytes());
        }

        return false;
    }
}
