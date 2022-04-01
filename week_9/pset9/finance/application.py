import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    
    if request.method == 'POST':
        stock = lookup(request.form.get('buysymbol'))
        if not stock:
            return apology('Invalid symbol')
            
        quant = int(request.form.get('quant'))
        if quant < 1:
            return apology('Must buy at least 1 stock')
            
        currentcash = db.execute('SELECT cash FROM users WHERE id = ?', session['user_id'])
            
        if currentcash[0]['cash'] > stock['price'] * quant:
            return apology('Insuffienct funds')
            
        
    
    
    if request.method == 'GET':
        print(session)
        return render_template('buy.html')


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        users = db.execute("SELECT * FROM users")
        return render_template("login.html", users=users)


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    
    if request.method == 'POST':
    
        stock = lookup(request.form.get('usersymbol'))
        
        if not stock:
            return apology("Invalid symbol")
        
        stockname = stock['name']
        symbol = stock['symbol']
        cost = stock['price']
        
        return render_template('quote.html', stockname=stockname, symbol=symbol, cost=cost)
    
    if request.method == 'GET':
        return render_template('quoter.html')

@app.route("/register", methods=["GET", "POST"])
def register():
    
    if request.method == 'POST':
        
        # collect new username
        username = request.form.get('username')
        # check if field not empty
        if not username:
            return apology("Please submit valid username.")
        # check if username already exists
        usercheck = db.execute('SELECT username FROM users WHERE username = ?', username)
        if usercheck:    
            return apology("Username already exists. Please choose new username.")
        
        # collect password
        password = request.form.get('password')
        # check if field not empty
        if not password:
            return apology("Please submit valid password.")
        # check if passwords match
        if password != request.form.get('passwordagain'):
            return apology("Passwords did not match. Please try again.")
        
        # hash password
        hash = generate_password_hash(password)
        
        # store new user info in finance.db
        db.execute('INSERT INTO users (username, hash) VALUES (?, ?)', username, hash)
        
        return redirect('/login')
    
    if request.method == 'GET':
        return render_template('register.html')


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    return apology("TODO")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
