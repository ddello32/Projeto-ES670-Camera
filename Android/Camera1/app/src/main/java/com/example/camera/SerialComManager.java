package com.example.camera;

import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.hardware.usb.UsbDevice;
import android.hardware.usb.UsbManager;
import android.util.Log;
import android.widget.Toast;

import com.hoho.android.usbserial.driver.KL25ZSerialDriver;
import com.hoho.android.usbserial.driver.ProbeTable;
import com.hoho.android.usbserial.driver.UsbSerialDriver;
import com.hoho.android.usbserial.driver.UsbSerialPort;
import com.hoho.android.usbserial.driver.UsbSerialProber;

import java.io.IOException;
import java.util.List;

public class SerialComManager {
    boolean opened = false;

    private final Context context;
    private final UsbManager mUsbManager;
    private UsbSerialPort mSerialPort = null;
    static PendingIntent mPermissionIntent;
    private static final String ACTION_USB_PERMISSION = "com.android.example.USB_PERMISSION";
    private final BroadcastReceiver mUsbReceiver = new BroadcastReceiver() {

        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (ACTION_USB_PERMISSION.equals(action)) {
                synchronized (this) {
                    UsbDevice device = (UsbDevice)intent.getParcelableExtra(UsbManager.EXTRA_DEVICE);

                    if (intent.getBooleanExtra(UsbManager.EXTRA_PERMISSION_GRANTED, false)) {
                        if(device != null){
                            try {
                                if(!opened) {
                                    mSerialPort.open(mUsbManager.openDevice(mSerialPort.getDriver().getDevice()));
                                    mSerialPort.setParameters(115200, 8, UsbSerialPort.STOPBITS_1, UsbSerialPort.PARITY_NONE);
                                    opened = true;
                                }
                            } catch (IOException e) {
                                e.printStackTrace();
                                Toast.makeText(context, e.getMessage(), Toast.LENGTH_SHORT).show();
                                e.printStackTrace();
                                try {
                                    mSerialPort.close();
                                } catch (IOException ignored) {
                                    // Ignore.
                                }
                                mSerialPort = null;
                            }
                        }
                    }
                    else {
                        Log.d("USBFUCKYEAH", "permission denied for device " + device);
                    }
                }
            }
        }
    };
    private final UsbSerialProber prober;

    public SerialComManager(Context context){
        this.context = context;
        mUsbManager = (UsbManager) context.getSystemService(Context.USB_SERVICE);
        ProbeTable table = UsbSerialProber.getDefaultProbeTable();
        table.addProduct(0xc251, 0xf002, KL25ZSerialDriver.class);
        table.addProduct(0x2504, 0x0300, KL25ZSerialDriver.class);
        table.addProduct(0x1357, 0x0089, KL25ZSerialDriver.class);
        prober = new UsbSerialProber(table);
    }


    public boolean initUsbConnection() {
        context.registerReceiver(mUsbReceiver, new IntentFilter(ACTION_USB_PERMISSION));
        mPermissionIntent = PendingIntent.getBroadcast(context, 0, new Intent(ACTION_USB_PERMISSION), 0);
        List<UsbSerialDriver> drivers = prober.findAllDrivers(mUsbManager);
        if(drivers == null || drivers.isEmpty()){
            Log.e("PORRA", "No driver");
            Toast.makeText(context, "No driver", Toast.LENGTH_SHORT).show();
        }else{
            for(UsbSerialDriver driver : drivers){
                if(driver.getPorts() != null){
                    for(UsbSerialPort port : driver.getPorts()){
                        mSerialPort = port;
                        try {
                            mUsbManager.requestPermission(mSerialPort.getDriver().getDevice(), mPermissionIntent);
                            return true;
                        } catch (Exception e) {
                            Toast.makeText(context, e.getMessage(), Toast.LENGTH_SHORT).show();
                            e.printStackTrace();
                            try {
                                mSerialPort.close();
                            } catch (IOException ignored) {
                                // Ignore.
                            }
                            mSerialPort = null;
                        }
                    }
                }
            }
        }
        return false;
    }

    public void stopUsbConnection(){
        context.unregisterReceiver(mUsbReceiver);
        if (mSerialPort != null) {
            try {
                mSerialPort.close();
            } catch (IOException e) {
                // Ignore.
            }
            mSerialPort = null;
        }
        opened = false;
    }


    public void usbWrite(String str){
        if(mSerialPort == null) return;
        try {
            mSerialPort.write(str.getBytes(), 100);
        } catch (IOException e) {
            Toast.makeText(context, e.getMessage(), Toast.LENGTH_SHORT).show();
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
