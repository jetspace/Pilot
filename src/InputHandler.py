import json
class InputHandler:
    def __init__(self, response):
        self.json = json.loads(response)
        self.response = response

        self.intent = self.json['outcomes'][0]['intent']
        self.value = self.json['outcomes'][0]['entities']

    def getIntent(self):
        return self.intent

    def getValue(self):
        return self.value
