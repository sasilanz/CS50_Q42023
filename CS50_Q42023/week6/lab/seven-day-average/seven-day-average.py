import csv
import requests



def main():
    # Read NYTimes Covid Database
    download = requests.get(
        "https://raw.githubusercontent.com/nytimes/covid-19-data/master/us-states.csv"
    )
    decoded_content = download.content.decode("utf-8")
    file = decoded_content.splitlines()
    reader = csv.DictReader(file)

    # Construct 14 day lists of new cases for each states
    new_cases = calculate(reader)

    # Create a list to store selected states
    states = []
    print("Choose one or more states to view average COVID cases.")
    print("Press enter when done.\n")

    while True:
        state = input("State: ")
        if state in new_cases:
            states.append(state)
        if len(state) == 0:
            break

    print(f"\nSeven-Day Averages")

    # Print out 7-day averages for this week vs last week
    comparative_averages(new_cases, states)


#  TODO: Create a dictionary to store 14 most recent days of new cases by state
def calculate(reader):
    cumulative_cases = dict()
    new_cases = dict()

    # Create a dictionay of lists where each state has its 14-day values list
    for value in reader:
        state = str(value("state"))
        cases = int(value("cases"))
        # initialize dictionary value
        if state not in cumulative_cases:
            cumulative_cases[state] = cases
            new_cases[state] = []
        else:
            new_case = cases - cumulative_cases[state]
            cumulative_cases[state] = cases

        # append the first 14 values
        if state not in new_cases:
            new_cases[state] = []
        if len(new_cases[state]) >= 14:
            new_cases[state].pop(0)
        else:
            new_cases[state].append(cases)

    return new_cases


# TODO: Calculate and print out seven day average for given state
def comparative_averages(new_cases, states):
    for state in states:
        avg_thisweek = round(sum(new_cases[state][7:]) / 7)
        avg_lastweek = round(sum(new_cases[state][:7]) / 7)

        diff = avg_thisweek - avg_lastweek
        if diff > 0:
            msg = "an inclrease"
        else:
            msg = "a decrease"

        try:
            d = diff / avg_lastweek
            p = round(d * 100)
        except ZeroDivisionError:
            raise ZeroDivisionError

        print(f"{state} had  a 7-day average of {avg_thisweek} and {msg} of {p}%.")

main()
