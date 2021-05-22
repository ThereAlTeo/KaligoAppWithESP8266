package com.mactec.newkaligo.model;

import androidx.fragment.app.FragmentActivity;

public interface Model {
    int getDisinfettanteSecond();

    int getFotocatalisiSecond();

    void setDisinfettanteSecond(final int disinfettanteSecond);

    void setFotocatalisiSecond(final int fotocatalisiSecond);

    int getInputDisinfettanteSecondMin();

    int getInputFotocatalisiSecondMin();

    int getActualButtonSelected();

    void setActualButtonSelected(final int actualButtonSelected);

    void manageMessageFromBluetooth(final String message);

    void setMainActivity(final FragmentActivity activity);
}
