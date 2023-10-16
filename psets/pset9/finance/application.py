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
    portfolio = db.execute("SELECT user_id, SUM(shares) FROM purchase WHERE user_id = ? GROUP BY user_id", session["user_id"])
    stocktotal = 0
    for i in range(len(portfolio)):
        i["name"] = lookup(i["symbol"])["name"]
        i["price"] = lookup(i["symbol"])["price"]
        i["sumtotal"] = lookup(i["symbol"])["price"] * i["SUM(shares)"]
        stocktotal += i["sumtotal"]
    cashtotal = stocktotal + db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    cashuser = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    return render_template("login.html", portfolio = portfolio, cashuser = cashuser[0], cashtotal = cashtotal)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Sorry, missing symbol.")
        elif not lookup(request.form.get("symbol")):
            return apology("Sorry, missing stock.")
        elif int(request.form.get("shares")) <= 0:
            return apology("Sorry, share is not positive integer.")
        elif (db.execute("SELECT cash FROM users WHERE id = ? ", session["user_id"])[0]["cash"]) < (lookup(request.form.get("symbol"))["price"] * int(request.form.get("shares"))):
            return apology("Sorry, insufficient funds.")
        else:
            db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", (lookup(request.form.get("symbol"))["price"] * int(request.form.get("shares"))), session["user_id"])
            db.execute("INSERT INTO purchase (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)", session["user_id"], request.form.get("symbol"), int(request.form.get("shares")), lookup(request.form.get("symbol"))["price"] * int(request.form.get("shares")))
        flash("Stock bought.")
        return redirect("/")
    else:
        return render_template("buy.html")



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
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 418)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


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
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("Sorry, missing symbol.")
        elif not lookup(request.form.get("symbol")):
            return apology("Sorry, missing stock.")
        return render_template("quoted.html", quote = lookup(request.form.get("symbol")))
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("Sorry, missing username.")
        elif not request.form.get("password"):
            return apology("Sorry, missing password.")
        elif not request.form.get("confirmation"):
            return apology("Sorry, missing confirmation.")
        elif len(db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))) == 1:
            return apology("Sorry, username exists.")
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Sorry, password and confirmation don't match.")
        else:
            hash = generate_password_hash(request.form.get("password"), method="pbkdf2:sha256", salt_length=8)
            db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), hash)
            return redirect("/")
    else:
        return render_template("register.html")


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
