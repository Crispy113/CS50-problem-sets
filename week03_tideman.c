#include <cs50.h>
#include <stdio.h>
#include <strings.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
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
int find_loop(void); // Custom

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

    // Clear graph of locked-in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
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

        // Flush ranks
        for (int j = 0; j < candidate_count + 1; j++)
        {
            ranks[j] = 0;
        }
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote. Next, the program loops over all of
// the voters and collects their preferences in an array called ranks
// (via a call to vote), where ranks[i] is the index of the candidate
// who is the ith preference for the voter.

bool vote(int rank, string name, int ranks[])
{
    // Compare vote name to candidate names

    for (int i = 0; i < candidate_count; i++)
    {
        if (strcasecmp(candidates[i], name) == 0)
        {
            // Check if vote was already registered for candidate
            for (int j = 0; j < rank; j++)
            {
                if (strcasecmp(candidates[ranks[j]], name) == 0)
                {
                    return false;
                }
            }

            // Register vote
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // Visit each point in matrix; preferences.

    for (int i = 0; i < candidate_count - 1; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    pair_count = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count++;
            }
        }
    }

    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{

    bool sorted;

    do
    {
        sorted = true;

        // Do one sweep for each loop, start from i
        for (int i = 0; i < pair_count; i++)
        {
            int mem_margin = 0;
            int mem_pos = 0;

            // For each iteration, get win margin of pair j and compare with mem_margin. If margin is larger than any previous found
            // in sweep, record position
            for (int j = i; j < pair_count; j++)
            {

                int j_margin = (preferences[pairs[j].winner][pairs[j].loser]) - (preferences[pairs[j].loser][pairs[j].winner]);

                if (j_margin > mem_margin)
                {
                    mem_margin = j_margin;
                    mem_pos = j;
                }
            }

            if (mem_pos != i)
            {
                int mem_win = pairs[i].winner;
                int mem_los = pairs[i].loser;

                pairs[i].winner = pairs[mem_pos].winner;
                pairs[i].loser = pairs[mem_pos].loser;

                pairs[mem_pos].winner = mem_win;
                pairs[mem_pos].loser = mem_los;

                sorted = false;
            }
        }
    }
    while (sorted == false);

    return;
}

void lock_pairs(void)
{

    for (int i = 0; i < pair_count; i++)
    {
        // Add a pair to the graph locked[i][j]. Edge i --> j, i.e. i is the winner of the two
        locked[pairs[i].winner][pairs[i].loser] = true;

        // Scan each NODE for loops. If looped, delete the pair again
        if (find_loop() == 1)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }

        // Repeat from top
    }
}

// Print the winner of the election
void print_winner(void)
{

    // Find the candidate with no edges pointing towards them.

    for (int y = 0; y < candidate_count + 1; y++)
    {
        int sum = 0;

        for (int x = 0; x < candidate_count + 1; x++)
        {
            sum = sum + locked[x][y];
        }

        if (sum == 0)
        {
            printf("%s\n", candidates[y]);
            return;
        }
    }

    printf("No winner\n");

    return;
}

// Scan array locked for loops
int find_loop(void)
{

    for (int k = 0; k < candidate_count; k++)
    {
        int path[36] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};
        int queue[36] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

        queue[0] = k;

        while (queue[0] != -1)
        {

            // create a queue for node
            for (int i = 0; i < candidate_count; i++)
            {
                if (locked[queue[0]][i] == true)
                {
                    for (int j = 0; j < 36; j++)
                    {
                        if (queue[j] == -1)
                        {
                            queue[j] = i;
                            break;
                        }
                    }
                }
            }

            // mark node as visited
            for (int i = 0; i < 36; i++)
            {
                if (path[i] == -1)
                {
                    path[i] = queue[0];
                    break;
                }
            }

            // Shift queue towards left, removing queue[0] in the process
            for (int i = 0; i < 36 - 1; i++)
            {
                queue[i] = queue[i + 1];
            }
            queue[35] = -1;

            // check: if path contains dublicate, break and return 1
            for (int i = 0; i < 36 - 1; i++)
            {
                for (int j = i + 1; i < 36; i++)
                {
                    if (path[j] == -1)
                    {
                        break;
                    }
                    if (path[i] == path[j] && i != j)
                    {

                        printf("Loop found!\n");
                        return 1;
                    }
                }
            }
        }
    }
    // else return 0
    printf("No loop\n");
    return 0;
}
