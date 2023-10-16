-- SQL query that returns the average energy of songs that are by Drake

SELECT avg(energy)
FROM songs
INNER JOIN artists ON songs.artist_id = artists.id
WHERE artists.name = "Drake";