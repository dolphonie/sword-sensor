# Created by Patrick Kao

from flask import Flask
from flask_ngrok import run_with_ngrok

app = Flask(__name__)

@app.route("/")
def hello():
    return "Hello World!"

if __name__ == '__main__':
    app.run()