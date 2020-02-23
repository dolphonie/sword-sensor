import json
import datetime

class Database:
    """ Static interface for communicating with database. """
    fp = "data.json"
    data = None

    def __init__(self):
        Database.load()

    def __repr__(self):
        return Database.data

    def __str__(self):
        return str(Database.data)

    @staticmethod
    def load():
        try:
            with open(Database.fp) as f:
                Database.data = json.load(f)
        except:
            Database.reset()

    @staticmethod
    def save():
        with open(Database.fp, "w") as f:
            json.dump(Database.data, f)

    @staticmethod
    def add_entry(data):
        # add time field
        time = datetime.datetime.now()

        formatted = "{}, {}".format(data, time)
        if Database.data is None:
            Database.load()
        Database.data.append(formatted)
        Database.save()
        return Database.string_response(formatted)

    @staticmethod
    def reset():
        Database.data = []
        Database.save()

    @staticmethod
    def string_response(data):
        fields = data.split(",")
        return ">>> Detected hit by player {} on {} at time {}".format(fields[0], fields[1], fields[2])
