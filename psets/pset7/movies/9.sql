-- SQL query to list the names of all people who starred in a movie released in 2004, ordered by birth year

SELECT name
FROM people
INNER JOIN stars ON people.id = stars.person_id
INNER JOIN movies ON stars.movie_id = movies.id
WHERE movies.year = 2004
ORDER BY people.birth