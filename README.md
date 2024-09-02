Updated July 18, 2024

Round Robin

Advantages: The data refresh rate of the serial port output is more accurate

Among them ICM42688_RR_Hz.ino and ICM42688_IIC_RR.ino can change the output frequency by modifying timeSlice

You can burn ICM42688_RR_Hz.ino and then view the actual number of refreshes in one second in the serial port

Tested, 250Hz is the best, 500Hz and above is not allowed.
 
 
 
 
 
 Arsuino_ESP_ICM42688_I2C


First of all, I have ESP32-S3 microcontroller, which is characterized by iomux, so I need to specify two pins for SDA, SCL, and modify the code as


void setup() {

  Wire.setPins(16, 17);//(SDA,SCL)
  
  Wire.begin();
  
  ...........
  
  }

16 and 17 are the pins you wish to designate as.



Officially entering the topic, first, use I2C_Scan.ino, open the serial port monitor, and check the I2C address

As shown in Fig

![Clip_2024-07-14_16-40-41](https://github.com/user-attachments/assets/2dab749a-7217-4f08-ad75-d392e37b9dc7)



As you can see, I have two I2C addresses, as long as, this is your 16, 17 pin is already connected with the pin of the ICM42688,

Here I use 0x69.

At this point, open[https://github.com/finani/ICM42688]

add to your arduino as requested, using his example code, I'm using basic_I2C.ino,

![Clip_2024-07-14_16-47-36](https://github.com/user-attachments/assets/ea25ab25-0e6b-432b-bef2-a33c56aa7cef)


Change the 0x68 to 0x69 and add Wire.setPins(16, 17);

After burning, open the serial port monitor to view, note that if the serial port monitor does not print correctly at this time, you need to change some programming rules in the toolbar

![PixPin_2024-07-14_16-12-16](https://github.com/user-attachments/assets/cbbf4d27-9fa2-46ce-aa95-9e4135b1cc40)

