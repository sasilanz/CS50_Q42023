import csv
import sys


def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py database_name.csv sequence_name.txt")
        return
    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as db_file:
        db = list(csv.DictReader(db_file))

    # TODO: Read DNA sequence txt file into a variable
    with open(sys.argv[2], "r") as seq_file:
        seq = seq_file.read()
    # get STRs, reading the dict of db, converting the dictionary keys to a list
    # taking the 2nd until EOL, because 1st is "name"
    STRs = list(db[0].keys())[1:]

    # TODO: Find longest match of each STR in DNA sequence
    # using the fiven function "longest_match" if STR is in our list
    matches = {STR: str(longest_match(seq, STR)) for STR in STRs}

    # TODO: Check database for matching profiles
    for person_data in db:
        # copy the name of the person
        person_name = person_data["name"]
        # delete the key "name" as in matches there is no key "name"
        del person_data["name"]
        # if matches are equal to our person's data then its the same person
        if matches == person_data:
            print(person_name)
            return
    # if no match was found
    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):
        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:
            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
