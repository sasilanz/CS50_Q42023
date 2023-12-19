SELECT COUNT(title) FROM movies INNER JOIN ratings ON ratings.movie_id = movies.id WHERE rating = "10.0";
