-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT description
FROM crime_scene_reports
WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street"

-- OUTPUT:
-- Theft of the CS50 duck took place at 10:15am at the Chamberlin Street courthouse. Interviews were conducted today with three witnesses who were present at the time — each of their interview transcripts mentions the courthouse.

SELECT transcript
FROM interviews
WHERE year = 2020 AND month = 7 AND day = 28

-- OUTPUT:
-- “Ah,” said he, “I forgot that I had not seen you for some weeks. It is a little souvenir from the King of Bohemia in return for my assistance in the case of the Irene Adler papers.”
-- “I suppose,” said Holmes, “that when Mr. Windibank came back from France he was very annoyed at your having gone to the ball.”
-- “You had my note?” he asked with a deep harsh voice and a strongly marked German accent. “I told you that I would call.” He looked from one to the other of us, as if uncertain which to address.
-- Sometime within ten minutes of the theft, I saw the thief get into a car in the courthouse parking lot and drive away. If you have security footage from the courthouse parking lot, you might want to look for cars that left the parking lot in that time frame.
-- I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at the courthouse, I was walking by the ATM on Fifer Street and saw the thief there withdrawing some money.
-- As the thief was leaving the courthouse, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the fli...

SELECT DISTINCT people.name
FROM people
INNER JOIN phone_calls ON people.phone_number = phone_calls.caller
INNER JOIN passengers ON people.passport_number = passengers.passport_number
INNER JOIN flights ON passengers.flight_id = flights.id
INNER JOIN airports ON flights.origin_airport_id = airports.id
INNER JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
INNER JOIN crime_scene_reports ON phone_calls.day = crime_scene_reports.day
INNER JOIN bank_accounts ON people.id = bank_accounts.person_id
INNER JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
INNER JOIN interviews ON phone_calls.day = interviews.day
WHERE phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.year = 2020
AND airports.city = "Fiftyville"
AND courthouse_security_logs.year = 2020 AND courthouse_security_logs.month = 7 AND courthouse_security_logs.day = 28 AND courthouse_security_logs.hour = 10 AND courthouse_security_logs.minute > 15 AND courthouse_security_logs.minute < 25 AND courthouse_security_logs.activity = "exit"
AND crime_scene_reports.year = 2020 AND crime_scene_reports.month = 7 AND crime_scene_reports.day = 28 AND crime_scene_reports.street = "Chamberlin Street" AND crime_scene_reports.description LIKE "Theft of the CS50 duck%"
AND atm_transactions.year = 2020 AND atm_transactions.month = 7 AND atm_transactions.day = 28 AND atm_transactions.transaction_type = "withdraw" AND atm_transactions.atm_location = "Fifer Street"
AND phone_calls.duration < 60
AND flights.year = 2020 AND flights.month = 7 AND flights.day = 29
ORDER BY flights.hour;

-- OUTPUT:
-- Ernest
-- Russell

SELECT passport_number
FROM people
WHERE name LIKE "Ernest"

-- OUTPUT:
-- 5773159633

SELECT flight_id
FROM passengers
WHERE passport_number = 5773159633

-- OUTPUT:
-- 36

SELECT destination_airport_id
FROM flights
WHERE id = 36

-- OUTPUT:
-- 4

SELECT city
FROM airports
WHERE id = 4

-- OUTPUT:
-- London

SELECT phone_number
FROM people
WHERE name LIKE "Ernest"

-- OUTPUT:
-- (367) 555-5533

SELECT name
FROM people
INNER JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.year = 2020 AND phone_calls.duration < 60 AND phone_calls.caller = "(367) 555-5533"

-- OUTPUT:
-- Berthold




















