import csv
import sys


def dna_test(rows, fields, sq_data):
    m, n = len(rows), len(fields)
    for i in range(m):
        flag = True
        for j in range(1, n):
            if longest_match(sq_data, fields[j]) != int(rows[i][fields[j]]):
                flag = False
                break
        if flag:
            return rows[i]["name"]


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Error! Incorrect number of command-line arguments.")

    # TODO: Read database file into a variable
    rows = []

    with open(sys.argv[1]) as dbfile:
        reader = csv.DictReader(dbfile)
        fields = reader.fieldnames
        for row in reader:
            rows.append(row)

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2]) as sqfile:
        sq_data = sqfile.read()

    # TODO: Find longest match of each STR in DNA sequence
    # TODO: Check database for matching profiles

    result = dna_test(rows, fields, sq_data)
    if result:
        print(result)
    else:
        print("No match")


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
