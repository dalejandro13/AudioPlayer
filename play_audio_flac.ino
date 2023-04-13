/*
//CODIGO PARA REPRODUCIR MP3 (ESTA FUNCIONANDO)
#include <Arduino.h>
#include <AudioFileSourceSD.h>
#include "AudioGeneratorMP3.h"
#include "AudioOutputI2SNoDAC.h"

const int NEW_SAMPLE_RATE = 44100;

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
AudioOutputI2SNoDAC *out;

void setup()
{
  Serial.begin(9600);

  // Configurar el pin 5 como chip select de la memoria SD
  if(!SD.begin(5)) {
    Serial.println("Error al inicializar la memoria SD");
    while(1);
  }

  delay(1000);
  file = new AudioFileSourceSD("/Salsa.mp3");
  out = new AudioOutputI2SNoDAC();
  out->SetPinout(0, 26, 25);
  out->SetBitsPerSample(16);
  out->SetChannels(2);
  out->SetRate(NEW_SAMPLE_RATE);
  mp3 = new AudioGeneratorMP3();
  mp3->begin(file, out);
}

void loop()
{
  if (mp3->isRunning()) {
    if (!mp3->loop()) mp3->stop(); 
  } else {
    Serial.printf("MP3 done\n");
    delay(1000);
  }
}
*/




//CODIGO PARA ARCHIVOS MP3 (ESTA FUNCIONANDO)
#include <AudioFileSourceSD.h>
//#include <AudioOutputI2S.h>
#include "AudioOutputI2SNoDAC.h"
#include <AudioGeneratorMP3.h>

AudioGeneratorMP3 *mp3;
AudioFileSourceSD *file;
//AudioOutputI2S *out;
AudioOutputI2SNoDAC *out;

const int NEW_SAMPLE_RATE = 44100;
bool play = true;
bool releaseResource = false;

void setup() {
  Serial.begin(9600);

  // Configurar el pin 5 como chip select de la memoria SD
  if(!SD.begin(5)) {
    Serial.println("Error al inicializar la memoria SD");
    while(1);
  }

  delay(1000);
  out = new AudioOutputI2SNoDAC(); //new AudioOutputI2S();
  out->SetPinout(0, 26, 25);
  out->SetBitsPerSample(16);
  out->SetChannels(2);
  out->SetRate(NEW_SAMPLE_RATE);
}

void freeResource()
{
  if (file) 
  {
    delete mp3;
    delete file;
    file = nullptr;
  }
}

void loop() {
  if(play)
  {
    play = false;
    file = new AudioFileSourceSD("/01.mp3"); // Abre el archivo de audio desde la memoria SD
    mp3 = new AudioGeneratorMP3();
    if(mp3->begin(file, out))
      Serial.print("Reproducciendo...\n");
  }

  if (mp3->isRunning()) 
  {
    if (!mp3->loop()) 
    {
      Serial.print("mp3 done\n");
      mp3->stop();
      freeResource();
      play = true; //vuelve a reproducir el audio
      delay(2000);
    }
  } 
}




/*
//CODIGO PARA ARCHIVOS FLAC (FUNCIONA BIEN)
#include <AudioFileSourceSD.h>
//#include <AudioOutputI2S.h>
#include "AudioOutputI2SNoDAC.h"
#include <AudioGeneratorFLAC.h>

AudioGeneratorFLAC *flac;
AudioFileSourceSD *file;
//AudioOutputI2S *out;
AudioOutputI2SNoDAC *out;

const int NEW_SAMPLE_RATE = 44100;
bool play = true;

void setup() {
  Serial.begin(9600);
  // Configurar el pin 5 como chip select de la memoria SD
  if(!SD.begin(5)) {
    Serial.println("Error al inicializar la memoria SD");
    while(1);
  }

  delay(2000);
  Serial.print("inicializando\n");
  // Inicializar el objeto AudioOutputI2S para utilizar el PIN 25 como salida DAC
  //out = new AudioOutputI2S();
  out = new AudioOutputI2SNoDAC();
  out->SetPinout(0, 26, 25);
  out->SetBitsPerSample(16);
  out->SetChannels(2);
  out->SetRate(NEW_SAMPLE_RATE);
}

void freeResource()
{
  delete flac;
  delete file;
  file = nullptr;
}

void loop() {
  if(play)
  {
    play = false;
    // Abre el archivo de audio desde la memoria SD
    file = new AudioFileSourceSD("/audio4.flac");
    // Inicializar el objeto AudioGeneratorFLAC para decodificar archivos FLAC
    flac = new AudioGeneratorFLAC();
    if (flac->begin(file, out)) 
      Serial.println("Reproduciendo...");
  }

  // Decodifica y reproduce el archivo de audio    
  if (flac->isRunning()) {
    // Espera hasta que se termine de reproducir el archivo
    if (!flac->loop())
    {
      flac->stop();
      freeResource();
      Serial.println("detenido");
      play = true;
      delay(2000);
    }
  }
}
*/