package com.example.AudioProcess_Spring;

import org.springframework.stereotype.Component;

@Component
public class Fpga {

    public void message1(){
        System.out.println("✅ End-of-transmission signal sent.");
    }

    public void message2() throws InterruptedException {
        for(int i =0; i<1000;i++){
            System.out.println(" 📤 Sent packet " + i);
           
        }
        System.out.println("🔃Audio is sending to FPGA");
        Thread.sleep(1000);
        System.out.println("✅Audio sucessfully sent to FPGA ");
    }
    public void message3(){
        System.out.println("✅Received Encrypted Audio");
    }
}
