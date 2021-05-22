package com.mactec.newkaligo.util;

public enum CycleMode {
    FOTOCATALISI_MODE( 0),
    DISINFETTANTE_MODE(1),
    NIGHT_MODE(2);

    private final int modeValue;

    CycleMode(final int value){
        this.modeValue = value;
    }

    public String getModeValue(){
        return String.valueOf(this.modeValue);
    }
}
