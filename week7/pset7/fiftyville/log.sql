-- Keep a log of any SQL queries you execute as you solve the mystery.
-- get an overview of the database
.schema
-- check content of the crime_scene_reports table at the theft time and date  ==> theft took place at 10:15am
 SELECT id, description from crime_scene_reports WHERE month = 7 AND day = 28 AND street = 'Humphrey Street' AND year = 2021;
-- crime_scene_report id = 295 ==> refers to 3 interviews with witnesses and the bakery
-- check out the interviews table for more infos  by using ".schema interviews"
-- search for interviews at the same day(unfortunately no FK to the crime_scene_reports table)
SELECT id, name, transcript FROM interviews WHERE year = 2021 AND month = 7 AND day = 28;
-- witnesses: Ruth, Eugene, Raymond Interview IDs: 161, 162 and 163
-- Ruth (Interview ID 161): check security footage from the bakery parking lot time within 10 min after theft
SELECT hour, minute, license_plate FROM bakery_security_logs WHERE activity = 'exit' AND year = 2021 AND month = 7 AND day
= 28 AND hour = 10 ORDER BY minute;   -- too many results, need to be narrowed down to the theft time 10.15 plus 10mins

-- Eugene (INterview ID 162) saw the thief at the ATM on Leggett Street
SELECT transaction_type, amount, account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND year = 2021
 AND month = 7 AND day = 28;  -- too many transactions, as there is no timestamp

-- Raymond (Interview ID 163) says thief was having a phonecall and is planning to leave with the earliest flight next day (29th)
-- friend is byuing the tickets (for the earliest flight next morning)
-- checking the phone_calls table ==> duration less than a minute
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60; -- too many results
-- now checking the flights from fiftyville
-- checking the airports infos
SELECT * FROM airports WHERE city LIKE 'FIFTYVILLE';
-- fiftyville has id 8 abbr CSF
-- checking flights from fiftyville in flights
sqlite> SELECT * FROM flights WHERE day = 29 ORDER BY hour;  -- flights.id = 36  destination airport id = 4
-- now checking the destination in airports
SELECT id, full_name, city FROM airports WHERE id = 4;  -- LaGuardia NYC at 8:20 am
-- checking passengers
SELECT * FROM passengers WHERE flight_id = 36; -- a bunch of passport numbers
-- checking the people table with the information from above on flight, passport license plate
SELECT * FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id = 36 AND passport_number IN(SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute >= 15 AND minute <= 25 ) ) );
-- some supects Sofia, Luca, Kelsey and Bruce
-- checking again the phone calls on that day using the phone number of people
SELECT * FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE name IN ('Sofia', 'Luca', 'Kelsey', 'Bruce')) AND year = 2021 AND month = 7 AND day = 28;
-- finding the names from people and phone numbers using the query before
SELECT name FROM people WHERE phone_number IN (SELECT caller FROM phone_calls WHERE caller IN (
    SELECT phone_number FROM people WHERE name IN ('Sofia', 'Luca', 'Kelsey', 'Bruce')) AND year = 2021 AND month = 7 AND day = 28);
-- now we have 3 suspects: Sofia, Kelsay and Bruce
-- now check the ATM who withdraw money
SELECT account_number FROM atm_transactions WHERE atm_location = 'Leggett Street' AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = 'withdraw';
SELECT name FROM people
JOIN bank_accounts ON bank_accounts.person_id = people.id
WHERE account_number IN (
  SELECT account_number FROM atm_transactions
  WHERE atm_location = 'Leggett Street' AND year = 2021 AND month = 7 AND day = 28 AND transaction_type = 'withdraw');
-- ==> BANG, only Bruce is on the list , get all his information from people
SELECT * FROM people WHERE name = 'Bruce';
-- now lets check, who Bruce talked to from phone calls query with Bruce as caller or receiver
SELECT caller, receiver, duration FROM phone_calls WHERE year = 2021 AND month = 7 AND day = 28 AND duration < 60 AND (caller = '(367) 555-5533' OR receiver = '(367) 555-5533)'); -- too many results
-- check who the receiver number (375 555-8161) belongs to
SELECT * FROM people WHERE phone_number ='(375) 555-8161';
-- BANG ==> it's Robin


