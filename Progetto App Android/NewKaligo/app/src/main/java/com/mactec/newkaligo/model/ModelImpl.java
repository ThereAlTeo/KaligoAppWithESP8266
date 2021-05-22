package com.mactec.newkaligo.model;

import androidx.fragment.app.FragmentActivity;

import com.mactec.newkaligo.R;
import com.mactec.newkaligo.ui.util.ManagementNotification;

import java.util.Arrays;
import java.util.List;

public class ModelImpl implements Model {
    private static final int FOTOCATALI_MIN = 600;
    private static final int DISINFETTANTE_MIN = 10;

    private static Model SINGLETON_MODEL;

    private int fotocatalisiSecond;
    private int disinfettanteSecond;
    private int actualButtonSelected;

    private FragmentActivity activity;

    private ModelImpl(){
        this.disinfettanteSecond = 20;
        this.fotocatalisiSecond = 1800;
        this.actualButtonSelected = R.id.radio_dinsinfettante;
    }

    public static Model getInstance(){
        if(SINGLETON_MODEL == null)
            SINGLETON_MODEL = new ModelImpl();
        return SINGLETON_MODEL;
    }

    @Override
    public int getDisinfettanteSecond() {
        return disinfettanteSecond;
    }

    @Override
    public int getFotocatalisiSecond() {
        return fotocatalisiSecond;
    }

    @Override
    public void setDisinfettanteSecond(final int disinfettanteSecond) {
        this.disinfettanteSecond = disinfettanteSecond;
    }

    @Override
    public void setFotocatalisiSecond(final int fotocatalisiSecond) {
        this.fotocatalisiSecond = fotocatalisiSecond;
    }

    @Override
    public int getInputDisinfettanteSecondMin() {
        return DISINFETTANTE_MIN;
    }

    @Override
    public int getInputFotocatalisiSecondMin() {
        return FOTOCATALI_MIN;
    }

    @Override
    public int getActualButtonSelected() {
        return actualButtonSelected;
    }

    @Override
    public void setActualButtonSelected(final int actualButtonSelected) {
        this.actualButtonSelected = actualButtonSelected;
    }

    @Override
    public void manageMessageFromBluetooth(final String message) {
        List<String> messageItems = Arrays.asList(message.split(":"));

        if ("finishJob".equals(messageItems.get(0)) && this.activity != null) {
            ManagementNotification.createNotification(this.activity, this.activity.getString(R.string.finish_cycle));
        }
    }

    @Override
    public void setMainActivity(FragmentActivity activity) {
        this.activity = activity;
    }
}
