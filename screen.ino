void screen(byte id){
  i=0;
  byte s=i;
  unsigned long prevTime=millis();
 
  while(1){ 
    structures(id);
    encoder();
    
    
    
    if (s != i) {
      prevTime=millis();
      s=i;
      }
      
    display.clearDisplay();
    display.setCursor(0,0);
    display.setTextSize(1);

    if (i == -1){i=7;}

    if (i == 0) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.println(r[id].name);
    
    if (i == 1) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("CS.MODE=");
    display.println(r[id].CS.MODE);
    
    if (i == 2) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("CS.CNTL=");
    display.println(r[id].CS.CONTROL);
    
    if (i == 3) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("CS.LOCK=");
    display.println(r[id].CS.INTERLOCK);
    
    if (i == 4) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("PAR.K=");
    display.println(EEPROM.read(r[id].PAR.K));
    
    if (i == 5) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("PAR.V=");
    display.println(EEPROM.read(r[id].PAR.V));
    //display.println(rele1.PAR.Pin);
    
    if (i == 6) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("PAR.Pin=");
    display.println(EEPROM.read(r[id].PAR.Pin));
    
    if (i == 7) {display.setTextColor(BLACK,WHITE);}
    else {display.setTextColor(WHITE);}
    display.print("EXIT");
    
    if (i == 8){i=0;}
    
    display.display();

    if (!Btn && (i == 1 || i == 2 || i == 3)){write_value(id, i); prevTime=millis();}
    if (!Btn && (i == 4 || i == 5 || i == 6)){write_value_analog(id, i); prevTime=millis();}
    if ((!Btn && i == 7) || (millis()-  prevTime>10000)){i = id; break;}


  }//while
} //screen

void write_value_analog(byte id, int n_bit)
{
  digitalWrite(13, HIGH);
  int memEncoder_position = i; //запоминаем значение энкодера
  byte x;//вводим новую переменную
  if (i == 4) {i = EEPROM.read(r[id].PAR.K);}
  if (i == 5) {i = EEPROM.read(r[id].PAR.V);}
  if (i == 6) {i = EEPROM.read(r[id].PAR.Pin);}  
  
  while(!Btn)
  {
    x = i;
    int a=enc.read();                         //  Читаем состояние энкодера в переменную a
    if(a){i=i+a;}                     //  Если энкодер зафиксировал поворот, то ...
       /* i+=a*/                    //  Меняем значение переменной i на 1, т.к. в переменной a находится -1 (при повороте влево), или +1 (при повороте вправо).

    display.clearDisplay();
    display.setCursor(0,0);
    display.print(r[id].name);
    if (memEncoder_position == 4){display.print(".PAR.K="); EEPROM.update(r[id].PAR.K, x);}
    if (memEncoder_position == 5){display.print(".PAR.V="); EEPROM.update(r[id].PAR.V, x);} 
    if (memEncoder_position == 6){display.print(".PAR.Pin="); EEPROM.update(r[id].PAR.Pin, x);}    
    display.println(x);
    display.display();
    
  }//while
  
  i=memEncoder_position; //возвращаем значение энкодера в исходное значение

  digitalWrite(13, LOW);

}


void write_value(byte id, int n_bit)
{
  digitalWrite(13, HIGH);
  int memEncoder_position = i; //запоминаем значение энкодера
  byte eeprom_byte = EEPROM.read(r[id].PAR.EEPROM_ADR); // читем байт из памяти  
  bool eeprom_bit = bitRead(eeprom_byte, memEncoder_position); //вытащили первый бит из байта
  i = eeprom_bit; //присваиваем значение энкодера к прочитанному биту
  bool x;//вводим новую переменную
  
  while(!Btn)
  {

    if (i>1){i=0;}
    if (i<0){i=1;}

    x = i;
    int a=enc.read();                         //  Читаем состояние энкодера в переменную a
    if(a){i=i+a;}                                //  Если энкодер зафиксировал поворот, то ...
                   //  Меняем значение переменной i на 1, т.к. в переменной a находится -1 (при повороте влево), или +1 (при повороте вправо).

    display.clearDisplay();
    display.setCursor(0,0);
    display.print(r[id].name);
    if (memEncoder_position == 1){display.print(".CS.MODE=");}
    if (memEncoder_position == 2){display.print(".CS.CONTROL=");} 
    if (memEncoder_position == 3){display.print(".CS.INTERLOCK=");}   
    display.println(x);
    bitWrite(eeprom_byte, memEncoder_position, x);
    EEPROM.update(r[id].PAR.EEPROM_ADR, eeprom_byte);
    display.display();
  }
  i=memEncoder_position; //возвращаем значение энкодера в исходное

  digitalWrite(13, LOW);
}
