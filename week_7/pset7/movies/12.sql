SELECT movies.title
FROM movies
JOIN stars
    ON movies.id = stars.movie_id
JOIN people
    ON people.id = stars.person_id
WHERE people.name IN ('Helena Bonham Carter', 'Johnny Depp')
GROUP BY movies.title HAVING COUNT(*) = 2;