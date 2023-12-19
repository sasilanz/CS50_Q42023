import os
import sys
from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd
from datetime import datetime

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """4 Show portfolio of stocks"""
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
        user_id=session["user_id"],
    )
    # get users cash balance
    cash = db.execute(
        "SELECT cash from users WHERE id = :user_id", user_id=session["user_id"]
    )[0]["cash"]

    # variables for total values
    total_value = cash
    grand_total = cash

    # collect price and value by iterating over stocks
    for stock in stocks:
        quote = lookup(stock["symbol"])
        stock["name"] = quote["name"]
        stock["price"] = quote["price"]
        stock["value"] = stock["price"] * stock["total_shares"]
        total_value += stock["value"]
        grand_total += stock["value"]

    # convert cash, total_value and grand_total to USD
    cash_usd = usd(cash)
    total_value_usd = usd(total_value)
    grand_total_usd = usd(grand_total)

    return render_template(
        "index.html",
        stocks=stocks,
        cash=cash_usd,
        total_value=total_value_usd,
        grand_total=grand_total,
    )

    return apology("TODO")


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """3 Buy shares of stock"""
    if request.method == "POST":
        # get the user input
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")

        # input validataion
        if not symbol or not shares:
            return apology(
                "please provide a stock symbol and the number of shares", 400
            )

        # shares must be a positive int
        try:
            shares = int(shares)
            if shares <= 0:
                raise ValueError("Shares must be a positive number", 400)
        except ValueError:
            return apology("number of shares must be a positive integer", 400)

        # lookup the stock information
        quote = lookup(symbol)
        if not quote:
            return apology("invalid stock symbol", 400)

        # check users cash balance from the database
        user_cash = db.execute(
            "SELECT cash FROM users WHERE id = :user_id", user_id=session["user_id"]
        )[0]["cash"]

        # total cost of shares
        price = quote["price"]
        total_cost = shares * price
        # does user have enough cash balance
        if total_cost > user_cash:
            return apology("not enough cash available", 403)

        # update users cash balance
        new_cash_balance = user_cash - total_cost
        db.execute(
            "UPDATE users SET cash = :new_cash_balance WHERE id = :user_id",
            new_cash_balance=new_cash_balance,
            user_id=session["user_id"],
        )

        # update the history table in the Database
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, price, timestamp) VALUES (:user_id, :symbol, :shares, :price, :timestamp)",
            user_id=session["user_id"],
            symbol=symbol,
            shares=shares,
            price=price,
            timestamp=datetime.now(),
        )

        # just for fun, let flash indicate, that you spent money ;-)
        flash(f"You just bought {shares} shares of {symbol} for {usd(total_cost)}!")
        # redirect to homepage root
        return redirect("/")
    # if route is accessed via GET, render the buy.html template
    return render_template("buy.html")


@app.route("/history", methods=["GET"])
@login_required
def history():
    """6 Show history of transactions"""

    transactions = db.execute(
        "SELECT * FROM transactions WHERE user_id = :user_id ORDER BY timestamp DESC",
        user_id=session["user_id"],
    )

    # convert transaction price to USD
    for transaction in transactions:
        transaction["price_usd"] = usd(transaction["price"])

    return render_template("history.html", transactions=transactions)


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
        # Create password hash

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

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
    """2 Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol is None:
            return apology("Please provide a stock symbol", 400)

        # lookup stock info
        quote = lookup(symbol)
        if quote is None:
            return apology("Not a valid stock symbol", 400)

        return render_template("quote.html", quote=quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """1 Register user"""
    # Forget any user_id
    session.clear()

    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure that registration data are provided
        if not username or not password or not confirmation:
            return apology("must provide username, password and confirmation", 400)

        # Ensure password and confirmation match
        if password != confirmation:
            return apology("passwords do not match", 400)

        # query db for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # check, if user already exists
        if len(rows) != 0:
            return apology("username already exists", 400)

        # Generate Password Hash
        hash = generate_password_hash(request.form.get("password"))

        # Enter new user to the database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # query db for newly inserted user
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        # remember user who is logged in
        session["user_id"] = rows[0]["id"]

        # redirect user to homepage
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """5 Sell shares of stock"""
    # Get user's stocks
    stocks = db.execute(
        "SELECT symbol, SUM(shares) as total_shares FROM transactions WHERE user_id = :user_id GROUP BY symbol HAVING total_shares > 0",
        user_id=session["user_id"],
    )

    # If the user submits the form
    if request.method == "POST":
        symbol = request.form.get("symbol").upper()
        shares_to_sell = int(request.form.get("shares"))

        # Validate symbol and shares
        if not symbol:
            return apology("please provide a symbol")
        elif shares_to_sell <= 0:
            return apology("number of shares must be a positive number")

        # Find the stock in user's portfolio
        stock_to_sell = next(
            (stock for stock in stocks if stock["symbol"] == symbol), None
        )

        if stock_to_sell:
            total_shares_owned = stock_to_sell["total_shares"]

            # Validate the number of shares to sell
            if shares_to_sell > total_shares_owned:
                return apology("not enough shares")

            # Get the current price of the stock
            quote = lookup(symbol)
            if quote is None:
                return apology("symbol not found")

            price_per_share = quote["price"]
            total_sale = shares_to_sell * price_per_share

            # Update user's cash balance
            db.execute(
                "UPDATE users SET cash = cash + :total_sale WHERE id = :user_id",
                total_sale=total_sale,
                user_id=session["user_id"],
            )

            # Update the user's stock portfolio
            db.execute(
                "INSERT INTO transactions (user_id, symbol, shares, price, timestamp) VALUES (:user_id, :symbol, :shares, :price, :timestamp)",
                user_id=session["user_id"],
                symbol=symbol,
                shares=-shares_to_sell,
                price=price_per_share,
                timestamp=datetime.now(),
            )

            flash(f"Sold {shares_to_sell} shares of {symbol} for {usd(total_sale)}")
            return redirect("/")
        else:
            return apology("Symbol not found")

    else:
        return render_template("sell.html", stocks=stocks)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    # optional function
    if request.method == "POST":
        # Validate the current password
        current_hash = db.execute(
            "SELECT hash FROM users WHERE id = :user_id", user_id=session["user_id"]
        )[0]["hash"]
        current_password = request.form.get("current_password")
        confirm_password = request.form.get("confirm_password")

        new_password = request.form.get("new_password")
        if not check_password_hash(current_hash, current_password):
            return apology("Current password is incorrect", 400)

        # Validate the new password and confirmation
        if new_password != confirm_password:
            return apology("New password and confirmation do not match")
        # proceeding with the PW update

        new_hash = generate_password_hash(new_password)

        # update pw in the database
        db.execute(
            "UPDATE users SET hash = :new_hash WHERE id = :user_id",
            new_hash=new_hash,
            user_id=session["user_id"],
        )

        # feedback to the user
        flash("Password changed successfully!")
        return redirect("/")

    return render_template("change_password.html")
