SELECT name FROM PEOPLE JOIN stars ON stars.person_id = people.id JOIN movies ON stars.movie_id = movies.id WHERE movies.title LIKE "Toy Story";
