void encoder(){
  int a=enc.read();                         //  Читаем состояние энкодера в переменную a
    if(a){                                    //  Если энкодер зафиксировал поворот, то ...
        i=i+a;   /* i+=a*/                    //  Меняем значение переменной i на 1, т.к. в переменной a находится -1 (при повороте влево), или +1 (при повороте вправо).
                    //  Выводим значение переменной i
    } 
    
}

float updateDS(byte Pin){ // добавляем функцию read
       
  //       int iPin = Pin;
  //     data=analogRead(pin);  // считываем показания датчика в переменную data
  sensors.requestTemperatures(); // Send the command to get temperatures
  return (sensors.getTempCByIndex(Pin));  

 } 

unsigned int EEPROM_uint_read(int addr) {    
  byte raw[2];
  for(byte i = 0; i < 2; i++) raw[i] = EEPROM.read(addr+i);
  unsigned int &num = (unsigned int&)raw;
  return num;
}

void EEPROM_uint_write(int addr, unsigned int num) {
  byte raw[2];
  (unsigned int&)raw = num;
  for(byte i = 0; i < 2; i++) EEPROM.write(addr+i, raw[i]);
}
