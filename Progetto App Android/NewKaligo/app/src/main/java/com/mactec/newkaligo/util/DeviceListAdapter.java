package com.mactec.newkaligo.util;

import android.bluetooth.BluetoothDevice;
import android.content.Context;
import android.os.Build;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.TextView;

import androidx.annotation.RequiresApi;

import com.mactec.newkaligo.R;
import com.mactec.newkaligo.bluetooth.Bluetooth;

import java.util.List;
import java.util.Optional;

public class DeviceListAdapter extends ArrayAdapter<BluetoothDevice> {
    private LayoutInflater mLayoutInflater;
    private List<BluetoothDevice> mDevices;
    private int  mViewResourceId;

    public DeviceListAdapter(Context context, int tvResourceId, List<BluetoothDevice> devices){
        super(context, tvResourceId, devices);
        this.mDevices = devices;
        mLayoutInflater = (LayoutInflater) context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        mViewResourceId = tvResourceId;
    }

    public View getView(int position, View convertView, ViewGroup parent) {
        convertView = mLayoutInflater.inflate(mViewResourceId, null);

        BluetoothDevice device = mDevices.get(position);

        if (device != null) {
            TextView deviceName = convertView.findViewById(R.id.tvDeviceName);
            TextView deviceAdress = convertView.findViewById(R.id.tvDeviceAddress);

            if (deviceName != null) {
                deviceName.setText(device.getName());
            }
            if (deviceAdress != null) {
                deviceAdress.setText(device.getAddress());
            }
        }
        return convertView;
    }

    @RequiresApi(api = Build.VERSION_CODES.N)
    public Optional<BluetoothDevice> selectActualDevice(final int index, final String name){
        Optional<BluetoothDevice> bluetoothDevice = Optional.empty();
        if(this.mDevices.size() > index && index >= 0){

            for (BluetoothDevice device : this.mDevices) {
                if(device.getName() != null && device.getName().equals(name)){
                    bluetoothDevice = Optional.of(device);
                    break;
                }
            }

            /*if(bluetoothDevice != null){
                Bluetooth.getInstance().selectActualDevice(bluetoothDevice);
                return true;
            }*/
        }

        return bluetoothDevice;
    }
}
