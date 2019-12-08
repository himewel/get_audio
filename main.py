import pyaudio
import serial
import numpy as np
import time
from scipy import fft, arange

FORMAT = pyaudio.paFloat32
CHANNELS = 1
RATE = 44100
CHUNK = 1024
RECORD_SECONDS = 10
window = np.blackman(CHUNK)

def createStreamer():
    audio = pyaudio.PyAudio()
    stream = audio.open(format=FORMAT, channels=CHANNELS,rate=RATE, input=True)

    return audio, stream

def createSerialPort():
    mySerial = serial.Serial('/dev/ttyACM1', 9600)
    #mySerial.open()
    return mySerial

if (__name__ == '__main__'):
    audio, stream = createStreamer()
    mySerial = createSerialPort()

    while True:
        try:
            data = stream.read(CHUNK)
            indata = np.array(np.fromstring(data,'Float32'))*window
            # Take the fft and square each value
            fftData = abs(np.fft.rfft(indata))**2
            # find the maximum
            which = fftData[1:].argmax() + 1
            # use quadratic interpolation around the max
            y0,y1,y2 = np.log(fftData[which-1:which+2:])
            x1 = (y2 - y0) * .5 / (2 * y1 - y2 - y0)
            # find the frequency and output it
            thefreq = (which+x1)*RATE/CHUNK

            print(thefreq)
            mySerial.write(str(thefreq)+"\n" if (thefreq > 80) else str(80)+"\n")
        except KeyboardInterrupt:
            stream.close()
            audio.terminate()
            mySerial.close()
            raise
