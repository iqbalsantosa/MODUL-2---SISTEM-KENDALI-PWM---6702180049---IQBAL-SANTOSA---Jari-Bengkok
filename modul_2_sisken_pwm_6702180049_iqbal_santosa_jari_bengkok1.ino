/**************************************************/

//Modul Praktikum 2 - Sistem kendali PWM
//Nama          : IQBAL SANTOSA
//Kelompok      : 3
//Nama Tim      : Jari Bengkok
//Anggota 1     : Iqbal Santosa
//Versi Program : 1.0

/**************************************************/
//Deklarasi sensor
int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;
int sensor6 = A5;
int baca_sensor[6];

//Variabel Motor
int pinEnable = 4; //Harus di set high jika ingin mengaktifkan
int pinEnable2 = 2; //Harus di set high jika ingin mengaktifkan
//Variabel Motor kiri
int motor_kiri1 = 5; //input motor driver 1 L293D
int motor_kiri2 = 6; //input motor driver 2 L293D
//Variabel motor kanan
int motor_kanan1 = 3; //input motor driver 3 L293D
int motor_kanan2 = 11;//input motor driver 4 L293D

//Variabel Bantuan
int x;
//Variabel error detection memory
int LastError = 0;

void setup()
{
  //Pin Mode input sensor
  pinMode(sensor1, INPUT); //set pin A0 sebagai input
  pinMode(sensor2, INPUT); //set pin A1 sebagai input
  pinMode(sensor3, INPUT); //set pin A2 sebagai input
  pinMode(sensor4, INPUT); //set pin A3 sebagai input
  pinMode(sensor5, INPUT); //set pin A4 sebagai input
  pinMode(sensor6, INPUT); //set pin A5 sebagai input
  
  //pin mode output motor
  pinMode(pinEnable, OUTPUT);
  pinMode(pinEnable2, OUTPUT);
  pinMode(motor_kiri1, OUTPUT);
  pinMode(motor_kiri2, OUTPUT);
  pinMode(motor_kanan1, OUTPUT);
  pinMode(motor_kanan2, OUTPUT);
  
  //Insialisasi komunikasi serial
  Serial.begin(9600); //default 9600
}

void readsensor(){ //fungsi untuk membaca sensor dan menyimpan nilai
baca_sensor[0] = analogRead(sensor1);
baca_sensor[1] = analogRead(sensor2);
baca_sensor[2] = analogRead(sensor3);
baca_sensor[3] = analogRead(sensor4);
baca_sensor[4] = analogRead(sensor5);
baca_sensor[5] = analogRead(sensor6);
  
  delay(1000);

  for(x=0; x<=5; x++){
    //Serial.print(baca_sensor[x]);
    Serial.print("Sensor");
    Serial.print(x+1);
    Serial.print(": ");
    Serial.print(baca_sensor[x]);
    Serial.print("\n");
    //Serial.print(LastError);
  }  
}

void loop()
{
 readsensor();
  Serial.print("Nilai last error:");
  Serial.println(LastError);
 //Sensor 1 dan 2 mendeteksi gelap, sisanya terang --> Duty cycle 0% motor kiri, 50% motor kanan 
 if (baca_sensor[0] < 34 && baca_sensor[1] < 34 && 
     baca_sensor[2] > 34 && baca_sensor[3] > 34 && 
     baca_sensor[4] > 34 && baca_sensor[5] > 34 ){
 digitalWrite(pinEnable, HIGH);
   //analogWrite(pin value 0-255)
   analogWrite(motor_kiri1, 0);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 127);
   analogWrite(motor_kanan2, 0);
 }
  //Sensor 2 dan 3 mendeteksi gelap, sisanya terang --> Duty cycle 20% motor kiri, 50% motor kanan
  if(baca_sensor[0] > 34 && baca_sensor[1] < 34 &&
     baca_sensor[2] < 34 && baca_sensor[3] > 34 &&
     baca_sensor[4] > 34 && baca_sensor[5] > 34){
   digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 51);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 127);
   analogWrite(motor_kanan2, 0);
  }
  //Sensor 3 dan 4 mendeteksi gelap, sisanya terang --> Duty cycle 60% pada kedua motor (kedua motor aktif) 
  if(baca_sensor[0] > 34 && baca_sensor[1] > 34 &&
     baca_sensor[2] < 34 && baca_sensor[3] < 34 &&
     baca_sensor[4] > 34 && baca_sensor[5] > 34){
  digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 0.6*255);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 0.6*255);
   analogWrite(motor_kanan2, 0);
  }
  //Sensor 4 dan 5 mendeteksi gelap, sisanya terang --> Duty cycle 50% motor kiri, 20% motor kanan
  if(baca_sensor[0] > 34 && baca_sensor[1] > 34 &&
     baca_sensor[2] > 34 && baca_sensor[3] < 34 &&
     baca_sensor[4] < 34 && baca_sensor[5] > 34){
  digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 0.5*255);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 0.2*255);
   analogWrite(motor_kanan2, 0);
  }
  //Sensor 5 dan 6 mendeteksi gelap, sisanya terang --> Duty cycle 50% Motor kiri, 0% motor kanan
  if(baca_sensor[0] > 34 && baca_sensor[1] > 34 &&
     baca_sensor[2] > 34 && baca_sensor[3] > 34 &&
     baca_sensor[4] < 34 && baca_sensor[5] < 34){
  digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 0.5*255);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 0);
   analogWrite(motor_kanan2, 0);
  }
  //Semua sensor mendeteksi terang --> Duty cycle kedua motor 0% (semua motor mati)
  if(baca_sensor[0] > 34 && baca_sensor[1] > 34 &&
     baca_sensor[2] > 34 && baca_sensor[3] > 34 &&
     baca_sensor[4] > 34 && baca_sensor[5] > 34){
  digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 0);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 0);
   analogWrite(motor_kanan2, 0);
    }
  //study kasus 2 : error kondision --> 1 sensor terbaca
  //simpan kondisi terakhir suatu variabel
  
  //Sensor 1 saja yang mendeteksi gelap maka akan mengeksekusi kondisi terakhir yaitu Sensor 1 dan 2 mendeteksi gelap
   if(baca_sensor[0] < 34 && baca_sensor[1] > 34 &&
   baca_sensor[2] > 34 && baca_sensor[3] > 34 &&
   baca_sensor[4] > 34 && baca_sensor[5] > 34){
  
   digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 0);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 127);
   analogWrite(motor_kanan2, 0);
   Serial.print("Error = -2");
   LastError = -2;
    }
   //Sensor 2 saja yang mendeteksi gelap maka akan mengeksekusi kondisi terakhir yaitu Sensor 2 dan 3 mendeteksi gelap	  
   if(baca_sensor[0] > 34 && baca_sensor[1] < 34 &&
   baca_sensor[2] > 34 && baca_sensor[3] > 34 &&
   baca_sensor[4] > 34 && baca_sensor[5] > 34){
   
   digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 51);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 127);
   analogWrite(motor_kanan2, 0);
   Serial.print("Error = -1");
   LastError = -1;
    }
   //Sensor 3 atau 4 saja yang mendeteksi gelap maka akan mengeksekusi kondisi terakhir yaitu Sensor 3 dan 4 mendeteksi gelap
   if(baca_sensor[0] > 34 && baca_sensor[1] > 34 &&
   baca_sensor[2] < 34 || baca_sensor[3] < 34 &&
   baca_sensor[4] > 34 && baca_sensor[5] > 34){
   
   digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 0.6*255);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 0.6*255);
   analogWrite(motor_kanan2, 0);
   Serial.print("Error = 0");
   LastError = 0;
    }
   //Sensor 5 saja yang mendeteksi gelap maka akan mengeksekusi kondisi terakhir yaitu Sensor 4 dan 5 mendeteksi gelap
   if(baca_sensor[0] > 34 && baca_sensor[1] > 34 &&
   baca_sensor[2] > 34 && baca_sensor[3] > 34 &&
   baca_sensor[4] < 34 && baca_sensor[5] > 34){
   
   digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 0.5*255);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 0.2*255);
   analogWrite(motor_kanan2, 0);
   Serial.print("Error = 1");
   LastError = 1;
    }
   //Sensor 6 saja yang mendeteksi gelap maka akan mengeksekusi kondisi terakhir yaitu Sensor 5 dan 6 mendeteksi gelap
   if(baca_sensor[0] > 34 && baca_sensor[1] > 34 &&
   baca_sensor[2] > 34 && baca_sensor[3] > 34 &&
   baca_sensor[4] > 34 && baca_sensor[5] < 34){
   digitalWrite(pinEnable, HIGH);
   analogWrite(motor_kiri1, 0.5*255);
   analogWrite(motor_kiri2, 0);
   
   digitalWrite(pinEnable2, HIGH);
   analogWrite(motor_kanan1, 0);
   analogWrite(motor_kanan2, 0);
   Serial.print("Error = 2");
   LastError = 2;
    }
}