SELECT DISTINCT people.name 
FROM people 
JOIN directors
    ON people.id = directors.person_id 
JOIN movies
    ON movies.id = directors.movie_id
WHERE movies.id IN (SELECT movie_id FROM ratings WHERE rating >= 9.0);