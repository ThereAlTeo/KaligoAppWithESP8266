package com.mactec.newkaligo.ui.setting;

import android.app.AlertDialog;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.RadioGroup;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.ViewModelProviders;

import com.google.android.material.textfield.TextInputEditText;
import com.mactec.newkaligo.R;
import com.mactec.newkaligo.util.BluetoothCommand;
import com.mactec.newkaligo.util.CycleMode;

public class SettingFragment extends Fragment {

    private SettingViewModel settingViewModel;
    private RadioGroup radioGroup;
    private TextInputEditText inputFotocatalisi;
    private TextInputEditText inputDisinfettante;

    public View onCreateView(@NonNull LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        settingViewModel = ViewModelProviders.of(this).get(SettingViewModel.class);
        View root = inflater.inflate(R.layout.fragment_setting, container, false);

        this.radioGroup = root.findViewById(R.id.radiogroup_dinsinfettante);
        this.inputFotocatalisi = root.findViewById(R.id.inputFotocatalisi);
        this.inputDisinfettante = root.findViewById(R.id.inputDisinfettante);
        this.inputFotocatalisi.setText(this.settingViewModel.getFotocatalisiSecond());
        this.inputDisinfettante.setText(this.settingViewModel.getDisinfettanteSecond());
        this.radioGroup.check(this.settingViewModel.getActualButtonSelected());

        root.findViewById(R.id.radio_dinsinfettante).setOnClickListener(this::onClickedDinsifettante);
        root.findViewById(R.id.radio_fotocalisi).setOnClickListener(this::onClickedFotocatalisi);
        root.findViewById(R.id.radio_nightMode).setOnClickListener(this::onClickedNightMode);

        this.inputFotocatalisi.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) {  }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) {  }

            @Override
            public void afterTextChanged(Editable editable) {
                settingViewModel.onEditableFotocatalisi(editable.toString());
            }
        });
        this.inputDisinfettante.addTextChangedListener(new TextWatcher() {
            @Override
            public void beforeTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void onTextChanged(CharSequence charSequence, int i, int i1, int i2) { }

            @Override
            public void afterTextChanged(Editable editable) {
                settingViewModel.onEditableDisinfettante(editable.toString());
            }
        });

        return root;
    }

    public void onClickedDinsifettante(View v) {
        this.changeRadioButton(R.string.modeChangeToDisinfettante, CycleMode.DISINFETTANTE_MODE, R.id.radio_dinsinfettante);
    }

    public void onClickedFotocatalisi(View v) {
        this.changeRadioButton(R.string.modeChangeToFotocatalisi, CycleMode.FOTOCATALISI_MODE, R.id.radio_fotocalisi);
    }

    public void onClickedNightMode(View v) {
        new AlertDialog.Builder(this.getActivity())
                .setTitle(R.string.checkLiquidContainer)
                .setMessage(R.string.checkLiquidContainerMessage)
                .setPositiveButton(android.R.string.yes, (dialog, which) -> {
                    this.changeRadioButton(R.string.modeChangeToNight, CycleMode.NIGHT_MODE, R.id.radio_nightMode);
                })
                .setNegativeButton(android.R.string.no, (dialog, which) -> {
                    this.radioGroup.check(this.settingViewModel.getActualButtonSelected());
                }).show();
        this.radioGroup.check(this.settingViewModel.getActualButtonSelected());
    }

    private void changeRadioButton(final int text, final CycleMode mode, final int nextMode){
        if(this.settingViewModel.getActualButtonSelected() != nextMode){
            int result = this.settingViewModel.sendMessage(BluetoothCommand.MODE.getCommandToSend(mode.getModeValue()), nextMode, text);

            Toast.makeText(this.getActivity(), result, Toast.LENGTH_SHORT).show();
            this.radioGroup.check(this.settingViewModel.getActualButtonSelected());
        }
    }
}