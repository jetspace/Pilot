# JetSpace Pilot
## Voice assistant

## Status:
[![Build Status](https://travis-ci.org/jetspace/Pilot.svg?branch=master)](https://travis-ci.org/jetspace/Pilot)

This is used to control your computer and/or to fetch information

## Commands

Currently there are the following options:
  * check_time : Check if it is night/day/morning/... somewhere 
  * computer_power : toggle shutdown/reboot/logout
  * time_places : Get the current time of a specific place
  * weather_in : Get the current weather in a specific city
  
## Examples

 * `Is it morning in Singapore?`
 * `Log me out of this session.`
 * `Time in New York?`
 * `How is the weather in Miami?`
 
## Technology

Pilot is based on GTK, Python, [wit.ai](http://wit.ai) and some more python modules.
It comes with a GTK frontend (written in C) to control the (python) backend via GUI!
