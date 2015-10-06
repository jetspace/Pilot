from TimeHandler import TimeHandler
class TimeCheckHandler:
    def __init__(self, value):
        self.value = value
        self.city = value['location'][0]['value'].title()
        self.daytime = value['daytime'][0]['value'].title()
        self.th = TimeHandler(self.value)
        self.th.checkDataBase()

    def Result(self):

        if self.daytime == 'Daytime':
            self.daytime == 'Day'

        self.th.lookupNoPrint()
        self.results = self.th.results
        for x in self.results:
            hour = int(self.results[x].strftime('%H'))
            daytime = 'Day'

            day = False

            if(hour > 7 and hour < 21):
                day = True

            if(hour <= 1 or hour >= 23):
                daytime = 'Midnight'
            elif(hour < 3 or hour > 21):
                daytime ='Night'
            elif(hour >= 11 and hour <= 13):
                daytime = 'Midday'
            elif(hour <11 and hour > 3):
                daytime = 'Morning'
            elif(hour <= 17 and hour >= 13):
                daytime = 'Afternoon'
            elif(hour <= 21 and hour >= 17):
                daytime = 'Evening'

            yield "PILOT:START"
            yield "LABEL:<b><big>"+ self.city +"</big></b>"
            if self.daytime == 'Day':
                if day == True:
                    print "LABEL:<b>Yes</b>"
                else:
                    print "LABEL:<b>No</b>"
            else:
                if daytime == self.daytime:
                    print "LABEL:<b>Yes</b>"
                else:
                    print "LABEL:<b>No</b>"

            print "LABEL:<small>" + self.results[x].strftime('%H:%M') + "  (" + daytime + ")" +"</small>"
            yield "PILOT:END"
