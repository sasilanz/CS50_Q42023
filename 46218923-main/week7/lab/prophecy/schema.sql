CREATE TABLE houses
(house TEXT NOT NULL, head TEXT, PRIMARY KEY(house));

CREATE TABLE assignments
(student_id INTEGER NOT NULL, house_id TEXT NOT NULL,
FOREIGN KEY(student_id) REFERENCES students(id),
FOREIGN KEY(house_id) REFERENCES houses(house),
PRIMARY KEY (student_id, house_id));

CREATE TABLE students
(id INTEGER NOT NULL, student_name TEXT, PRIMARY KEY (id));
