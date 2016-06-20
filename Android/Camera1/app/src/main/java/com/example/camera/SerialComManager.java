package com.example.camera;

import android.content.Context;
import android.hardware.usb.UsbManager;
import android.util.Log;
import android.widget.Toast;

import com.hoho.android.usbserial.driver.CdcAcmSerialDriver;
import com.hoho.android.usbserial.driver.ProbeTable;
import com.hoho.android.usbserial.driver.UsbSerialDriver;
import com.hoho.android.usbserial.driver.UsbSerialPort;
import com.hoho.android.usbserial.driver.UsbSerialProber;

import java.io.IOException;
import java.util.List;

public class SerialComManager {

    private final Context context;
    private final UsbManager mUsbManager;
    private UsbSerialPort mSerialPort = null;
    private final UsbSerialProber prober;

    public SerialComManager(Context context){
        this.context = context;
        mUsbManager = (UsbManager) context.getSystemService(Context.USB_SERVICE);
        ProbeTable table = UsbSerialProber.getDefaultProbeTable();
        table.addProduct(0xc251, 0xf002, CdcAcmSerialDriver.class);
        table.addProduct(0x2504, 0x0300, CdcAcmSerialDriver.class);
        prober = new UsbSerialProber(table);
    }


    public boolean initUsbConnection() {
        List<UsbSerialDriver> drivers = prober.findAllDrivers(mUsbManager);
        if(drivers == null || drivers.isEmpty()){
            Log.e("SerialComManager", "No driver");
            Toast.makeText(context, "No driver", Toast.LENGTH_SHORT).show();
        }else{
            for(UsbSerialDriver driver : drivers){
                if(driver.getPorts() != null){
                    for(UsbSerialPort port : driver.getPorts()){
                        mSerialPort = port;
                        try {
                            mSerialPort.open(mUsbManager.openDevice(mSerialPort.getDriver().getDevice()));
                            mSerialPort.setParameters(115200, 8, UsbSerialPort.STOPBITS_1, UsbSerialPort.PARITY_NONE);
                            return true;
                        } catch (IOException e) {
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
        if (mSerialPort != null) {
            try {
                mSerialPort.close();
            } catch (IOException e) {
                // Ignore.
            }
            mSerialPort = null;
        }
    }


    public void usbWrite(String str){
        if(mSerialPort == null) return;
        try {
            mSerialPort.write(str.getBytes(), 100);
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
    }
}
