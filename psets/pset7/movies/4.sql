-- SQL query to determine the number of movies with an IMDb rating of 10.0

SELECT count(title)
FROM movies
INNER JOIN ratings ON movies.id = ratings.movie_id
WHERE ratings.rating = 10.0;