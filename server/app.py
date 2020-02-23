import sys
import datetime
from flask import Flask, render_template, request
from flask_socketio import SocketIO, emit

sys.path.append('__HOME__/server')

from database import Database

app = Flask(__name__)
socketio = SocketIO(app)


@app.route("/")
def hello():
    return render_template("server_template.html")


@app.route("/post", methods=['GET', 'POST'])
def get_request():
    if request.method == "POST":
        data = request.form["data"]
    else:
        data = request.args["data"]

    print(data)
    response = Database.add_entry(data)
    socketio.emit("server response", {"data": response}, namespace="/socket")
    return "Success"


@socketio.on("connect", namespace="/socket")
def server_connect():
    emit("server response", {"data": "Connected"})


@socketio.on("disconnect", namespace="/socket")
def server_connect():
    emit("server response", {"data": "Disconnected"})


if __name__ == '__main__':
    socketio.run(app)
