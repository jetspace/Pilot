from collections import defaultdict
from datetime import datetime
from urllib import urlretrieve
from urlparse import urljoin
from zipfile import ZipFile
import os
import pytz # git clone https://github.com/newvem/pytz && cd pytz && python2 setup.py build && sudo python2 setup.py install

tzdatabase = 'http://download.geonames.org/export/dump/'
tzfile = "cities15000.zip" # all cities with >15000 people
base = 'cities15000'
tzdbdir = "./"


class TimeHandler:
    def __init__(self, value):
        self.value = value
        self.city = value['location'][0]['value'].title()
        self.checkDataBase()

    def checkDataBase(self):
        if not os.path.exists(tzdbdir+tzfile):
            urlretrieve(urljoin(tzdatabase, tzfile), tzdbdir + tzfile) # Download database if not available


    # see http://stackoverflow.com/questions/16505501/get-timezone-from-city-in-python-django
    def lookup(self):
        data = defaultdict(set)
        with ZipFile(tzdbdir + tzfile) as zf, zf.open(base + ".txt") as file:
            for line in file:
                fields = line.split(b'\t')
                if(fields):
                    name, asciiname, alternatenames = fields[1:4]
                    timezone = fields[-2].decode('utf-8').strip()
                    if(timezone):
                        for city in [name, asciiname] + alternatenames.split(b','):
                            city = city.decode('utf-8').strip()
                            if(city):
                                data[city].add(timezone)
        for name in data[self.city]:
            now = datetime.now(pytz.timezone(name))
            #yield str(now.strftime('%s')) + ',' + str(now.strftime('%Z%z')) + ',' + self.city + ','+ str(name)
            yield "PILOT:START"
            yield "LABEL:<big><b>" + str(now.strftime('%H:%M')) + "</b></big>"
            yield "LABEL:" + self.city;
            yield "LABEL: <small><i>" + str(name) + "</i></small>"
            yield "PILOT:END"

    def lookupNoPrint(self):
        data = defaultdict(set)
        with ZipFile(tzdbdir + tzfile) as zf, zf.open(base + ".txt") as file:
            for line in file:
                fields = line.split(b'\t')
                if(fields):
                    name, asciiname, alternatenames = fields[1:4]
                    timezone = fields[-2].decode('utf-8').strip()
                    if(timezone):
                        for city in [name, asciiname] + alternatenames.split(b','):
                            city = city.decode('utf-8').strip()
                            if(city):
                                data[city].add(timezone)
        self.results = {}
        for name in data[self.city]:
            self.results[self.city] = datetime.now(pytz.timezone(name))
