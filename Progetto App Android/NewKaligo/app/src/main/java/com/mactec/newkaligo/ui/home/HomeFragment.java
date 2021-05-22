package com.mactec.newkaligo.ui.home;

import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.mactec.newkaligo.R;
import com.mactec.newkaligo.util.BluetoothCommand;

public class HomeFragment extends Fragment {

    private HomeViewModel homeViewModel;
    private Button statButton;
    private Button stopButton;
    private Button openBackDoorButton;
    private Button openFrontDoorButton;

    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        homeViewModel = ViewModelProviders.of(this).get(HomeViewModel.class);
        View root = inflater.inflate(R.layout.fragment_home, container, false);

        this.homeViewModel.setMainActivity(this.requireActivity());
        this.statButton = (Button) root.findViewById(R.id.startButton);
        this.stopButton = (Button) root.findViewById(R.id.stopButton);
        this.openBackDoorButton = (Button) root.findViewById(R.id.openBackDoorButton);
        this.openFrontDoorButton = (Button) root.findViewById(R.id.openFrontDoorButton);
        this.initButtonListener();

        return root;
    }

    private void initButtonListener() {
        this.statButton.setOnClickListener(view -> sendMessageToMachine(BluetoothCommand.START, R.string.startCycleButtonTextToast));
        this.stopButton.setOnClickListener(view -> sendMessageToMachine(BluetoothCommand.STOP, R.string.stopButtonTextToast));
        this.openBackDoorButton.setOnClickListener(view -> sendMessageToMachine(BluetoothCommand.OPEN_BACK_DOOR, R.string.openBackDoorButtonTextToast));
        this.openFrontDoorButton.setOnClickListener(view -> sendMessageToMachine(BluetoothCommand.OPEN_FRONT_DOOR, R.string.openFrontDoorButtonTextToast));
    }

    private void sendMessageToMachine(final BluetoothCommand commandSend, final int StringValueID) {
       if(this.homeViewModel.sendMessageToMachine(commandSend.getCommandToSend())){
            Toast.makeText(this.getActivity(), StringValueID, Toast.LENGTH_SHORT).show();
        }else{
            Toast.makeText(this.getActivity(), R.string.deviceNotConnected, Toast.LENGTH_SHORT).show();
        }
    }
}