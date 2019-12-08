import pyaudio
import serial
import numpy as np
import time

FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 44100
CHUNK = 2**15

def createStreamer():
    audio = pyaudio.PyAudio()
    stream = audio.open(format=FORMAT, channels=CHANNELS,rate=RATE, input=True,frames_per_buffer=CHUNK)

    return audio, stream

def createSerialPort():
    mySerial = serial.Serial('/dev/ttyACM0', 9600)
    if (mySerial.is_open == False):
        mySerial.open()
    return mySerial

def pitch(data):
    data = np.fromstring(data,dtype=np.int16)
    data = data * np.hanning(len(data)) # smooth the FFT by windowing data
    fft = abs(np.fft.fft(data).real)
    fft = fft[:int(len(fft)/2)] # keep only first half
    freq = np.fft.fftfreq(CHUNK,1.0/RATE)
    freq = freq[:int(len(freq)/2)] # keep only first half
    freqPeak = freq[np.where(fft==np.max(fft))[0][0]]+1
    return freqPeak

if (__name__ == '__main__'):
    audio, stream = createStreamer()
    mySerial = createSerialPort()
    buffer = []

    while True:
        try:
            data = stream.read(CHUNK)
            freq = pitch(data)

            buffer.append(freq)
            if (len(buffer) > 5):
                buffer.pop(0)

            print(np.min(buffer))
            mySerial.write(str(np.min(buffer))+"\n")
            time.sleep(0.1)

        except:
            stream.close()
            audio.terminate()
            exit()
