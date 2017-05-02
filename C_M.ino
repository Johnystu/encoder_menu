void CM(byte n)  {

  //if ((!r[n].CS.MODE && r[n].CS.CONTROL && !r[n].CS.INTERLOCK && !r[n].STS.isRun )){
    if (r[n].STS.isRun = 1 ){
     
    startTime = millis();
    stopTime  = startTime + (EEPROM.read(r[n].PAR.V) / EEPROM.read(r[n].PAR.K) * 1000);
  }
  if (r[n].STS.isRun && (stopTime < millis() )){
//  EEPROM.update(r[n].CS.CONTROL, 0);
    r[n].CS.CONTROL = 0;
    r[n].STS.isRun = 0;
   // r[n].CS.INTERLOCK =1;
  }


  
//    else {r[n].STS.isRun = 0;}
//  r[n].STS.inAuto = r[n].CS.MODE;

//  if ( EEPROM.read(r[0].PAR.V) < updateDS(0)){r[0].STS.V = 1;}
//    else {r[0].STS.V = 0;}
//
//  if ( EEPROM.read(r[0].PAR.K) > updateDS(0)){r[0].STS.K = 1;}
//    else {r[0].STS.K = 0;} 
 
  if ( r[n].STS.isRun ){
  digitalWrite(EEPROM.read(r[n].PAR.Pin), HIGH);
  r[n].PAR.PV = (stopTime - millis())/1000;
}
    else {digitalWrite(EEPROM.read(r[n].PAR.Pin), LOW);}     
    
  }
    
