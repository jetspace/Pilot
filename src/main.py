#!/usr/bin/env python2
import json
import wit
import sys
import time

#Project Files
from InputHandler import InputHandler
from TimeHandler import TimeHandler
from TimeCheckHandler import TimeCheckHandler
from WeatherHandler import WeatherHandler


TOKEN="VADPZQ6RGSKSLDDF7NMRHZNPYLRDT56E"

if __name__ == "__main__":
    wit.init()

    voice = False
    usetext = False
    textpos = 0

    y = 0;
    for x in sys.argv:
        if x == "--voice" or x == "-v":
            voice = True
        elif x == "--text" or x == '-t':
            usetext = True
            textpos = y+1
        y = y+1

    response = {}

    if(voice):
        response = wit.voice_query_auto(TOKEN)
    elif(usetext):
        response = wit.text_query(sys.argv[textpos], TOKEN)
    else:
        time.sleep(1)
        response = wit.text_query(raw_input(">> "), TOKEN)

    wit.close()
    time.sleep(0.1)

    inp = InputHandler(response)
    task = inp.getIntent()

    if(task == 'time_places'):
        handle = TimeHandler(inp.getValue())
        for x in handle.lookup():
            print(x)
    elif(task == 'weather_in'):
        handle = WeatherHandler(inp.getValue())
        for x in handle.printData():
            print(x)
    elif(task == 'check_time'):
        handle = TimeCheckHandler(inp.getValue())
        for x in handle.Result():
            print(x)
    else:
        print("ERR: task not recognized [" + task + "]")
        exit(1)

    exit(0)
