package com.mactec.newkaligo.ui.setting;

import androidx.lifecycle.ViewModel;

import com.mactec.newkaligo.R;
import com.mactec.newkaligo.bluetooth.Bluetooth;
import com.mactec.newkaligo.model.Model;
import com.mactec.newkaligo.model.ModelImpl;
import com.mactec.newkaligo.util.BluetoothCommand;

public class SettingViewModel extends ViewModel {
    private Bluetooth bluetooth;
    private Model model;

    public SettingViewModel() {
        this.bluetooth = Bluetooth.getInstance();
        this.model = ModelImpl.getInstance();
    }

    public int getActualButtonSelected() {
        return this.model.getActualButtonSelected();
    }

    public void setActualButtonSelected(int actualButtonSelected) {
        this.model.setActualButtonSelected(actualButtonSelected);
    }

    public int sendMessage(final String message, final int nextMode, final int defaultText){
        if(this.bluetooth.isConnectionEnable()){
            if (this.bluetooth.getConnectedThread().write(message.getBytes())){
                this.setActualButtonSelected(nextMode);
                return defaultText;
            }
            return R.string.notPossibleChangeMode;
        }
        return R.string.deviceNotConnected;
    }

    public String getFotocatalisiSecond(){
        return String.valueOf(this.model.getFotocatalisiSecond());
    }

    public String getDisinfettanteSecond(){
        return String.valueOf(this.model.getDisinfettanteSecond());
    }

    private int checkAndCompareValueInsert(final String value, final int compareTo){
        try{
            if(!value.equals("")){
                int parseValue = Integer.parseInt(value);
                if(parseValue >= compareTo){
                    return parseValue;
                }
            }
        }
        catch (Exception ignored){}
        return 0;
    }

    public void onEditableFotocatalisi(final String editableValue){
        int compareVal = this.checkAndCompareValueInsert(editableValue, this.model.getInputFotocatalisiSecondMin());

        if(compareVal > 0 && this.changeModeSecond(BluetoothCommand.FOTOCATALISI_SECOND_COMMAND.getCommandToSend(editableValue))){
            this.model.setFotocatalisiSecond(compareVal);
        }
    }

    public void onEditableDisinfettante(final String editableValue){
        int compareVal = this.checkAndCompareValueInsert(editableValue, this.model.getInputDisinfettanteSecondMin());

        if(compareVal > 0 && this.changeModeSecond(BluetoothCommand.SATURATION_SECOND_COMMAND.getCommandToSend(editableValue))){
            this.model.setDisinfettanteSecond(compareVal);
        }
    }

    private boolean changeModeSecond(final String modeSecond) {
        return this.bluetooth.tryToSendMessage(modeSecond);
    }
}