void logData(int sensor, float velocity, unsigned long timer)
{
  File logFile;
  int id = timer/1000;
  String fileName = "PLOG.TXT";
  if(SD.exists(fileName))
  {
    Serial.println("logging...");
  }
  else
  {
    Serial.println("creating " + fileName);
  }

  logFile = SD.open(fileName, FILE_WRITE);
  if(logFile)
  {
    logFile.print(sensor);
    logFile.print("\t");
    logFile.print(velocity);
    logFile.print("\t");
    logFile.println(timer);
    logFile.close();
  }
  else
  {
    Serial.println("could not log");
    logFile.close();  
  }
}

