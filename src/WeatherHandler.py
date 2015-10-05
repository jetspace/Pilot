import json
import urllib2

#WEATHER_API_KEY = "71969b34fbb4fd885db55c3e4503a26f"

class WeatherHandler:

    def __init__(self, value):
        self.value = value
        self.city = value['location'][0]['value'].title()
        self.scity = self.city.replace(' ', '')

        self.getJSON()

    def getJSON(self):
        #+ "&APPID=" + WEATHER_API_KEY
        data = urllib2.urlopen("http://api.openweathermap.org/data/2.5/weather?q=" +self.scity + "&units=metric")
        self.content = json.loads(data.read())
        self.temp = self.content['main']['temp']
        self.state = self.content['weather'][0]['main']

    def printData(self):
        return str(self.temp) + ',' + self.state + ',' + self.city
