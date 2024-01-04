#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
// if locked[i][j] is true then there is a "directed" edge from i to j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
} pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void dfs(int start, int visited[]);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false; // initialization
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference (maybe it's better to say ranks[j] is voter's jth preference)
        // notice that we only use 1d array here, not 2d because we record preferences for each voter directly
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();  // tally step
    sort_pairs(); // sort step

    // Debug:
    // for (int i = 0; i < pair_count; i++) {
    //     printf("Winner is: %s, votes is: %d, loser is: %s, votes is: %d\n", candidates[pairs[i].winner],
    //     preferences[pairs[i].winner][pairs[i].loser], candidates[pairs[i].loser], preferences[pairs[i].loser][pairs[i].winner]);
    // }

    lock_pairs(); // lock step

    // Debug:
    // for (int i = 0; i < pair_count; i++) {
    //     if (locked[pairs[i].winner][pairs[i].loser]) {
    //         printf("Winner is: %s, votes is: %d, loser is: %s, votes is: %d\n", candidates[pairs[i].winner],
    //         preferences[pairs[i].winner][pairs[i].loser], candidates[pairs[i].loser],
    //         preferences[pairs[i].loser][pairs[i].winner]);
    //     }
    // }

    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j]) == 0)
        {
            ranks[rank] = j;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++; // not preferences[i][j]++, but preferences[ranks[i]][ranks[j]]++
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // A pair of candidates who are tied (one is not preferred over the other) should not be added to the array
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // The following sorting strategy may not be the best though.
    for (int i = 0; i < pair_count - 1; i++)
    {
        int maxVotes = preferences[pairs[i].winner][pairs[i].loser];
        int flag = i;
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > maxVotes)
            {
                flag = j;
                maxVotes = preferences[pairs[j].winner][pairs[j].loser];
            }
        }
        // Do a swap here
        int winnerCopy = pairs[i].winner;
        int loserCopy = pairs[i].loser;
        pairs[i].winner = pairs[flag].winner;
        pairs[i].loser = pairs[flag].loser;
        pairs[flag].winner = winnerCopy;
        pairs[flag].loser = loserCopy;
    }
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    int visited[MAX] = {0};
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;
        dfs(pairs[i].winner, visited);
        if (visited[pairs[i].winner] > 1)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
        memset(visited, 0, sizeof(visited));
    }
    return;
}

void dfs(int start, int visited[])
{
    visited[start]++;
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[start][i] && visited[i] == 0)
        {
            dfs(i, visited);
        }
        else if (locked[start][i] && visited[i] > 0)
        { // we don't want to get stuck in a loop
            visited[i]++;
        }
    }
}

// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        bool flag = true;
        for (int j = 0; j < candidate_count; j++)
        {
            if (locked[j][i])
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            // We can't use new global array called inDegree in this problem, this is an alternative way to do so.
            // I borrowed this idea from the Ed discussion group!
            printf("%s\n", candidates[i]);
            return;
        }
    }
}
