SELECT title, rating FROM movies JOIN ratings ON movie_id = movies.id WHERE movies.year = "2010" ORDER BY rating DESC, title ASC;
