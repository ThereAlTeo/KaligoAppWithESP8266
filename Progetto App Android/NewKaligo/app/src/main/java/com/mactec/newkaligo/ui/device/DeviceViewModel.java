package com.mactec.newkaligo.ui.device;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.os.Build;
import android.util.Log;

import androidx.annotation.RequiresApi;
import androidx.lifecycle.ViewModel;

import com.mactec.newkaligo.bluetooth.Bluetooth;
import com.mactec.newkaligo.util.AndroidSystemUtilities;
import com.mactec.newkaligo.util.DeviceListAdapter;

import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

public class DeviceViewModel extends ViewModel {
    private DeviceListAdapter deviceListAdapter;
    private List<BluetoothDevice> bluetoothDevices;
    private Bluetooth bluetoothInstance;

    @RequiresApi(api = Build.VERSION_CODES.N)
    public DeviceViewModel() {
        this.bluetoothDevices = new ArrayList<>();
        this.bluetoothInstance = Bluetooth.getInstance();
    }

    public List<BluetoothDevice> getBluetoothDevices(){
        return this.bluetoothDevices;
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public void tryConnectionWithDevice(final int index){
        this.bluetoothInstance.getBluetoothAdapter().cancelDiscovery();
        this.deleteDeviceConnection();

        Optional<BluetoothDevice> btDevice = deviceListAdapter.selectActualDevice(index, bluetoothDevices.get(index).getName());

        if(btDevice.isPresent()){
            this.bluetoothInstance.selectActualDevice(btDevice);
        }
    }

    public void cancelDiscovery(){
        if(this.bluetoothInstance.getBluetoothAdapter().isDiscovering()){
            this.bluetoothInstance.getBluetoothAdapter().cancelDiscovery();
            Log.d(AndroidSystemUtilities.TAG, "btnDiscover: Canceling discovery.");
        }
    }

    public void startDiscovery(){
        this.bluetoothInstance.getBluetoothAdapter().startDiscovery();
    }

    public boolean isEnabledBluetooth(){
        return this.bluetoothInstance.deviceCanUseBluetooth() && !this.bluetoothInstance.getBluetoothAdapter().isEnabled();
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public void deleteDeviceConnection(){
        if(this.bluetoothInstance.getActualDevice().isPresent()){
            this.bluetoothInstance.closeConnection();
        }
    }

    public DeviceListAdapter createDeviceList(final Context context, final int layoutResourceID){
        this.deviceListAdapter = new DeviceListAdapter(context, layoutResourceID, this.bluetoothDevices);
        return this.deviceListAdapter;
    }
}