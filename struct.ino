void eeprom_str_adr()
{
  r[0].name = "rele 0"; //имя устройства
  r[0].PAR.EEPROM_ADR = 0;    //адресс памяти байта на контрольные сигналы
  r[0].PAR.K = 100; //адресс памяти байта ошибки LowLow
  r[0].PAR.V = 102; //адресс памяти байта ошибки HiHi
  r[0].PAR.Pin =   104; //адресс памяти номера pin 

  r[1].name = "rele 1";
  r[1].PAR.EEPROM_ADR = 1; 
  r[1].PAR.K = 110;
  r[1].PAR.V = 112;
  r[1].PAR.Pin =   114;
    
  r[2].name = "rele 2";
  r[2].PAR.EEPROM_ADR = 2; 
  r[2].PAR.K = 120;
  r[2].PAR.V = 122;
  r[2].PAR.Pin =   124;    
    
    
}

void structures(byte n)
{

  byte r_byte; //байт для записи значения из eeproom
  r_byte = EEPROM.read(r[n].PAR.EEPROM_ADR); //запихнули сюда прочитанный байт из eeproom
  r[n].CS.MODE = bitRead(r_byte, 1); //читаем первый бит
  r[n].CS.CONTROL = bitRead(r_byte, 2);  //читаем второй бит
  r[n].CS.INTERLOCK = bitRead(r_byte, 3);  //

}
