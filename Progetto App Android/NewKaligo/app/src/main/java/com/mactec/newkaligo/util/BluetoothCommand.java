package com.mactec.newkaligo.util;

public enum BluetoothCommand {
    START("start"),
    STOP("stop"),
    OPEN_FRONT_DOOR("openFront"),
    OPEN_BACK_DOOR("openBack"),
    MODE("mode"),
    FOTOCATALISI_SECOND_COMMAND("fotocatalisiSecond"),
    SATURATION_SECOND_COMMAND("saturSecond");

    private final String Command;

    BluetoothCommand(final String Command){
        this.Command = Command;
    }

    public String getCommandToSend(final String Value){
        return "-" + this.Command + ":" + Value + "\n";
    }

    public String getCommandToSend(){
        return this.getCommandToSend(String.valueOf(0));
    }
}
