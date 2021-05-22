package com.mactec.newkaligo.ui.util.factory;

import android.app.Notification;
import android.content.Context;
import android.media.RingtoneManager;
import android.os.Build;

import androidx.annotation.RequiresApi;
import androidx.core.app.NotificationCompat;

import com.mactec.newkaligo.MainActivity;
import com.mactec.newkaligo.R;
import com.mactec.newkaligo.util.AndroidSystemUtilities;

public class NotificationFactory {
    @RequiresApi(api = Build.VERSION_CODES.O)
    public static Notification getDefaultNotification(final Context context, final String title, final String text){
        return new Notification.Builder(context, AndroidSystemUtilities.NOTIFICATION_CHANNEL)
                .setSmallIcon(R.drawable.ic_baseline_message_24)
                .setContentTitle(title)
                .setContentText(text)
                .setSound(RingtoneManager.getDefaultUri(RingtoneManager.TYPE_NOTIFICATION))
                .setVibrate(new long[]{0,500})
                .build();
    }
}
