-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT id, description, day FROM crime_scene_reports WHERE month = 7 AND year = 2020 AND street = 'Chamberlin Street'; -- find id and description of theft

SELECT name, transcript FROM interviews WHERE day = 28 AND month = 7 AND year = 2020; -- find courthouse robbery wintness interviews per description

SELECT people.name 
FROM people
INNER JOIN bank_accounts
    ON people.id = bank_accounts.person_id
WHERE bank_accounts.account_number IN
    (SELECT account_number FROM atm_transactions 
    WHERE atm_location = 'Fifer Street' 
    AND transaction_type = 'withdraw' 
    AND day = 28 AND month = 7 AND year = 2020);-- find atm records and associated people early morning same day of theft to check withdraws per eugenes interview (theif)
    
SELECT airports.full_name, airports.city, flights.hour, flights.minute
FROM airports
INNER JOIN flights
    ON flights.id = airports.id
WHERE airports.id IN (
    SELECT destination_airport_id
    FROM flights
    WHERE year = 2020 AND month = 7 AND day = 29 AND origin_airport_id = (
        SELECT id
        FROM airports
        WHERE abbreviation = 'CSF'))
ORDER BY flights.hour ASC, flights.minute ASC; -- find flight records for earilest flight out of fiftyville on 7-29-2020 per raymonds interview (theif location)

    
SELECT peopleCaller.name, peopleReceiver.name
FROM people as peopleCaller, people as peopleReceiver
WHERE (peopleCaller.phone_number, peopleReceiver.phone_number) IN
    (SELECT caller, receiver
    FROM phone_calls
    WHERE id IN
        (SELECT id
        FROM phone_calls 
        WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60)); -- check phone call records and return names of callers/receivers

SELECT name
FROM people
WHERE license_plate IN
    (SELECT license_plate
    FROM courthouse_security_logs
    WHERE day = 28 AND month = 7 AND year = 2020 AND hour = 10 AND minute <= 25 AND activity = 'exit');-- find license number of cars within 10m of theft (10:15am) per ruth interview (accomplice)

SELECT peopleCaller.name, peopleReceiver.name
FROM people as peopleCaller, people as peopleReceiver
WHERE (peopleCaller.phone_number, peopleReceiver.phone_number) IN
    (SELECT caller, receiver
    FROM phone_calls
    WHERE id IN
        (SELECT id
        FROM phone_calls 
        WHERE day = 28 AND month = 7 AND year = 2020 AND duration < 60)
        AND caller IN (
            SELECT phone_number
            FROM people
            WHERE name IN ('Ernest', 'Elizabeth', 'Danielle'))); -- cross reference call logs with results that match from bank search and plate search