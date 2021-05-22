package com.mactec.newkaligo.ui.home;

import androidx.fragment.app.FragmentActivity;
import androidx.lifecycle.ViewModel;

import com.mactec.newkaligo.bluetooth.Bluetooth;
import com.mactec.newkaligo.model.ModelImpl;

public class HomeViewModel extends ViewModel {
    public HomeViewModel() { }

    public boolean sendMessageToMachine(final String commandSend){
        return Bluetooth.getInstance().tryToSendMessage(commandSend);
    }

    public void setMainActivity(FragmentActivity activity) {
        ModelImpl.getInstance().setMainActivity(activity);
    }
}