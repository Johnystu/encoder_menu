void CM(byte n)  {
    if (r[n].STS.isRun == 1 ){
     
    startTime = millis();
    stopTime  = startTime + (EEPROM.read(r[n].PAR.V) / EEPROM.read(r[n].PAR.K) * 1000);
  }
  if (r[n].STS.isRun && (stopTime < millis() )){
    r[n].CS.CONTROL = 0;
    r[n].STS.isRun = 0;
  }
  
  if ( r[n].STS.isRun ){
    digitalWrite(EEPROM.read(r[n].PAR.Pin), HIGH);
    r[n].PAR.PV = (stopTime - millis())/1000;
  }
    else {digitalWrite(EEPROM.read(r[n].PAR.Pin), LOW);}      
  }
    
