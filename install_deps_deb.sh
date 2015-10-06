#!/usr/bin/env bash
mkdir -p temp
cd temp

#install python2
sudo apt-get update -qq
sudo apt-get install -qq libgtk-3-dev
sudo apt-get install -qq python2.7

#install pytz
git clone https://github.com/newvem/pytz
cd pytz
python2 setup.py build
sudo python2 setup.py install

cd ..

#install wit
git clone https://github.com/wit-ai/pywit.git
cd pywit
python2 setup.py build
sudo python setup.py install

cd ..

cd ..
