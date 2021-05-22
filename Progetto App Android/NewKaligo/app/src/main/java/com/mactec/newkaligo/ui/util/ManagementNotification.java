package com.mactec.newkaligo.ui.util;

import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.content.Context;
import android.os.Build;

import androidx.fragment.app.FragmentActivity;

import com.mactec.newkaligo.R;
import com.mactec.newkaligo.ui.util.factory.NotificationFactory;
import com.mactec.newkaligo.util.AndroidSystemUtilities;

public class ManagementNotification {
    public static void createNotification(final FragmentActivity activity, final String message){
        NotificationManager notificationManager = (NotificationManager) activity.getSystemService(Context.NOTIFICATION_SERVICE);
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            CharSequence name = activity.getString(R.string.channel_name);
            String description = activity.getString(R.string.channel_description);
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel(AndroidSystemUtilities.NOTIFICATION_CHANNEL, name, importance);
            channel.setDescription(description);
            notificationManager.createNotificationChannel(channel);
            notificationManager.notify(0, NotificationFactory.getDefaultNotification(activity, activity.getString(R.string.machine_notification), message));
        }
    }
}
