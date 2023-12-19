import csv
from cs50 import SQL
from os import path
import sys

FILENAME = "students.csv"
DBNAME = "roster.db"


students = list()

# open csv file

with open(FILENAME, "r") as file:
    reader = csv.DictReader(file)

    # iterate over csv file store students in list
    for row in reader:
        students.append(row)



# open database
if path.exists(DBNAME):
    db = SQL("sqlite:///roster.db")
else:
    print("The database does not exist.")

# insert data to database
for student in students:
    db.execute(
        "INSERT OR IGNORE INTO students (id, student_name) VALUES (?, ?)",
        student["id"],
        student["student_name"],
    )
    db.execute(
        "INSERT OR IGNORE INTO houses (house, head) VALUES (?, ?)",
        student["house"],
        student["head"],
    )
    db.execute(
        "INSERT OR IGNORE INTO assignments (student_id, house_id) VALUES (?, ?)",
        student["id"],
        student["house"],
    )



