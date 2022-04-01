import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session, url_for

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")

@app.route("/", methods=["GET", "POST"])
def index():
    # TODO: Display the entries in the database on index.html
    birthdays = db.execute("SELECT * FROM birthdays")
    return render_template("index.html", birthdays=birthdays)
    
@app.route("/add", methods=["GET", "POST"])        
def add():
    name = request.args.get("name")
    if not name:
        return redirect(url_for('error', errorType = 'name'))
        
    month = request.args.get("month")
    if not month:
        return redirect(url_for('error', errortype = 'month'))
        
    day = request.args.get("day")
    if not day:
        return redirect(url_for('error', errorType = 'day'))
    
    db.execute("INSERT INTO birthdays (name, month, day) VALUES (?, ?, ?)", name, month, day)
    return redirect("/")
    
@app.route('/remove/<int:birthId>', methods=["POST"])
def remove(birthId):
    if request.method == 'POST':
        db.execute("DELETE FROM birthdays WHERE id = (?)", birthId)
        return redirect('/')
        
@app.route("/error/<errorType>", methods=["GET"])
def error(errorType):
    return render_template("error.html", message = errorType)
    
@app.route("/search")
def search ():
    user = request.args.get("search")
    birthdays = db.execute("SELECT * FROM birthdays WHERE name = ?", user)
    if not birthdays:
        return redirect('/')
    return render_template("index.html", birthdays=birthdays)