package com.mactec.newkaligo.ui.device;

import android.Manifest;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Build;
import android.os.Bundle;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.ListView;

import androidx.annotation.NonNull;
import androidx.annotation.RequiresApi;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.mactec.newkaligo.R;
import com.mactec.newkaligo.bluetooth.Bluetooth;
import com.mactec.newkaligo.util.AndroidSystemUtilities;

public class DeviceFragment extends Fragment {
    private DeviceViewModel deviceViewModel;
    private ListView listView;
    private BroadcastReceiver broadRecFOUND = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            final String action = intent.getAction();
            Log.d(AndroidSystemUtilities.TAG, "onReceive: ACTION FOUND.");

            if (action != null && action.equals(BluetoothDevice.ACTION_FOUND)) {
                BluetoothDevice device = intent.getParcelableExtra (BluetoothDevice.EXTRA_DEVICE);
                if(device != null && device.getName() != null && !deviceViewModel.getBluetoothDevices().contains(device)) {
                    deviceViewModel.getBluetoothDevices().add(device);
                    Log.d(AndroidSystemUtilities.TAG, "onReceive: " + device.getName() + ": " + device.getAddress());
                    listView.setAdapter(deviceViewModel.createDeviceList(context, R.layout.device_adapter_view));
                }
            }
        }
    };

    @RequiresApi(api = Build.VERSION_CODES.N)
    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        deviceViewModel = ViewModelProviders.of(this).get(DeviceViewModel.class);
        View root = inflater.inflate(R.layout.fragment_device, container, false);
        this.listView = root.findViewById(R.id.device_find);
        Button scanButton = root.findViewById(R.id.scan_device_button);

        this.listView.setOnItemClickListener((adapterView, view, i, l) -> this.deviceViewModel.tryConnectionWithDevice(i));
        scanButton.setOnClickListener(this::btnDiscover);

        try {
            if(this.deviceViewModel.isEnabledBluetooth()){
                this.requireActivity().startActivityForResult(new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE), Bluetooth.ENABLE_BT_REQUEST);
            }

            this.requireActivity().registerReceiver(this.broadRecFOUND, new IntentFilter(BluetoothDevice.ACTION_FOUND));
        }
        catch (IllegalStateException ignored){
            Log.d(AndroidSystemUtilities.TAG, "requireActivity error");
        }
        catch (Exception ignored){}

        return root;
    }

    @RequiresApi(api = Build.VERSION_CODES.M)
    private void btnDiscover(View view) {
        Log.d(AndroidSystemUtilities.TAG, "btnDiscover: Looking for unpaired devices.");

        this.deviceViewModel.cancelDiscovery();
        //check BT permissions in manifest
        checkBTPermissions();

        this.deviceViewModel.deleteDeviceConnection();
        this.deviceViewModel.startDiscovery();
    }

    @Override
    public void onDestroy() {
        Log.d(AndroidSystemUtilities.TAG, "onDestroy: called.");
        super.onDestroy();
        this.requireActivity().unregisterReceiver(this.broadRecFOUND);
    }

    /**
     * This method is required for all devices running API23+
     * Android must programmatically check the permissions for bluetooth. Putting the proper permissions
     * in the manifest is not enough.
     *
     * NOTE: This will only execute on versions > LOLLIPOP because it is not needed otherwise.
     */
    @RequiresApi(api = Build.VERSION_CODES.M)
    private void checkBTPermissions() {
        int permissionCheck = this.requireActivity().checkSelfPermission("Manifest.permission.ACCESS_FINE_LOCATION");
        permissionCheck += this.requireActivity().checkSelfPermission("Manifest.permission.ACCESS_COARSE_LOCATION");
        if (permissionCheck != 0) {
            this.requireActivity().requestPermissions(new String[]{Manifest.permission.ACCESS_FINE_LOCATION, Manifest.permission.ACCESS_COARSE_LOCATION}, 1001); //Any number
        }
    }
}