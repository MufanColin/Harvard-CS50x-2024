-- Keep a log of any SQL queries you execute as you solve the mystery.

-- 1. Check the crime scene reports

SELECT * FROM crime_scene_reports WHERE year = 2023 AND month = 7 AND day = 28;

-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  | year | month | day |     street      |                                                                                                       description                                                                                                        |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 293 | 2023 | 7     | 28  | Axmark Road     | Vandalism took place at 12:04. No known witnesses.                                                                                                                                                                       |
-- | 294 | 2023 | 7     | 28  | Boyce Avenue    | Shoplifting took place at 03:01. Two people witnessed the event.                                                                                                                                                         |
-- | 295 | 2023 | 7     | 28  | Humphrey Street | Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery. |
-- | 296 | 2023 | 7     | 28  | Widenius Street | Money laundering took place at 20:30. No known witnesses.                                                                                                                                                                |
-- | 297 | 2023 | 7     | 28  | Humphrey Street | Littering took place at 16:36. No known witnesses.                                                                                                                                                                       |
-- +-----+------+-------+-----+-----------------+--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+

-- 2. Check the interviews

SELECT * FROM interviews WHERE year = 2023 AND month = 7 AND day = 28 AND transcript LIKE "%bakery%";

-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | id  |  name   | year | month | day |                                                                                                                                                     transcript                                                                                                                                                      |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+
-- | 161 | Ruth    | 2023 | 7     | 28  | Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.                                                          |
-- | 162 | Eugene  | 2023 | 7     | 28  | I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.                                                                                                 |
-- | 163 | Raymond | 2023 | 7     | 28  | As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket. |
-- +-----+---------+------+-------+-----+---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------+


-- 3. Check the ATM

SELECT name, id FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
    (SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"));

-- +---------+--------+
-- |  name   |   id   |
-- +---------+--------+
-- | Kenny   | 395717 |
-- | Iman    | 396669 |
-- | Benista | 438727 |
-- | Taylor  | 449774 |
-- | Brooke  | 458378 |
-- | Luca    | 467400 |
-- | Diana   | 514354 |
-- | Bruce   | 686048 |
-- +---------+--------+

-- 4. Check the flight

SELECT * FROM flights WHERE year = 2023 AND month = 7 AND day = 29 AND
    origin_airport_id IN
    (SELECT id FROM airports WHERE city = "Fiftyville")
    ORDER BY hour ASC;

-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+
-- | 36 | 8                 | 4                      | 2023 | 7     | 29  | 8    | 20     |
-- | 43 | 8                 | 1                      | 2023 | 7     | 29  | 9    | 30     |
-- | 23 | 8                 | 11                     | 2023 | 7     | 29  | 12   | 15     |
-- | 53 | 8                 | 9                      | 2023 | 7     | 29  | 15   | 20     |
-- | 18 | 8                 | 6                      | 2023 | 7     | 29  | 16   | 0      |
-- +----+-------------------+------------------------+------+-------+-----+------+--------+

-- 5. Compound query

SELECT name, id FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)
    AND passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- +--------+--------+
-- |  name  |   id   |
-- +--------+--------+
-- | Sofia  | 398010 |
-- | Luca   | 467400 |
-- | Kelsey | 560886 |
-- | Bruce  | 686048 |
-- +--------+--------+

-- 6. Narrowing down

SELECT name, id FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
    (SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))
INTERSECT
SELECT name, id FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)
    AND passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id = 36);

-- +-------+--------+
-- | name  |   id   |
-- +-------+--------+
-- | Bruce | 686048 |
-- | Luca  | 467400 |
-- +-------+--------+

-- 7. Idenfity the thief

SELECT name, id, phone_number FROM people WHERE id IN
    (SELECT person_id FROM bank_accounts WHERE account_number IN
    (SELECT account_number FROM atm_transactions WHERE year = 2023 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw"))
INTERSECT
SELECT name, id, phone_number FROM people WHERE license_plate IN
    (SELECT license_plate FROM bakery_security_logs WHERE year = 2023 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25)
    AND passport_number IN
    (SELECT passport_number FROM passengers WHERE flight_id = 36)
INTERSECT
SELECT name, id, phone_number FROM people WHERE phone_number IN
    (SELECT caller FROM phone_calls WHERE
    year = 2023 AND month = 7 AND day = 28 AND duration <= 60);

-- +-------+--------+----------------+
-- | name  |   id   |  phone_number  |
-- +-------+--------+----------------+
-- | Bruce | 686048 | (367) 555-5533 |
-- +-------+--------+----------------+

-- 8. Identify the accomplice

SELECT name, id FROM people WHERE phone_number IN
    (SELECT receiver FROM phone_calls WHERE
    year = 2023 AND month = 7 AND day = 28 AND duration <= 60 AND caller = "(367) 555-5533");

-- +-------+--------+
-- | name  |   id   |
-- +-------+--------+
-- | Robin | 864400 |
-- +-------+--------+

-- 9. Identify the destinationcheck50 cs50/problems/2024/x/fiftyville

SELECT city FROM airports WHERE id IN
    (SELECT destination_airport_id FROM flights WHERE id = 36);

-- +---------------+
-- |     city      |
-- +---------------+
-- | New York City |
-- +---------------+
