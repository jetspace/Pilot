import os
class PowerHandler:
    def __init__(self, value):
        self.value = value
        self.mode = value['computerpower'][0]['value']

    def perform(self):
        if(self.mode == "poweroff"):
            os.system("side-session --shutdown")
        elif(self.mode == "reboot"):
            os.system("side-session --reboot")
        elif(self.mode == "logout"):
            os.system("side-session --logout")
        else:
            print "WARNING: unsupported action " + self.mode + "detected!"
