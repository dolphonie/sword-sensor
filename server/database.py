import json


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
        if Database.data is None:
            Database.load()
        Database.data.append(data)
        Database.save()
        return Database.string_response(data)

    @staticmethod
    def reset():
        Database.data = []
        Database.save()

    @staticmethod
    def string_response(data):
        return ">>> " + data
