import json
import urllib2

WEATHER_API_KEY = "3d5a8e7d3774e2090889d85d876d8b2d"

class WeatherHandler:

    def __init__(self, value):
        self.value = value
        self.city = value['location'][0]['value'].title()
        self.scity = self.city.replace(' ', '')

        self.getJSON()

    def getJSON(self):
        data = urllib2.urlopen("http://api.openweathermap.org/data/2.5/weather?" + "APPID=" + WEATHER_API_KEY +"&q=" +self.scity + "&units=metric")
        self.content = json.loads(data.read())
        self.temp = self.content['main']['temp']
        self.state = self.content['weather'][0]['main']
        self.country = self.content['sys']['country']

    def printData(self):
        yield "PILOT:START"
        yield "LABEL:<big><b>"+self.city+"</b></big>, " + self.country
        yield "LABEL:<b>" + str(self.temp) + " C</b>"
        yield "LABEL:" +str(self.state)
        yield "LABEL:<a href=\"http://openweathermap.com\"><small><sub>openweathermap.com (CC-BY-SA)</sub></small></a>"
        yield "PILOT:END"
