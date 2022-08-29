# VCSolver #
## Description ##
Framework for finding a maximum vertex cover.

## Usage ##
`vc_solver FILE [options]`.

### Options ###
This is a brief overview of the most important options.
For a full description, please take a look at the user guide.

`FILE`
Path to graph file that you want the maximum independent set for.

`--help`
Print help.

`--console_log`
Write the log to the console.

`--seed=<int>`
Seed to use for the random number generator.

`--time_limit=<double>`
Time limit until the algorithm terminates.


### File format
```
p 7 10
7 1
7 3
7 4
1 2
1 4
1 6
2 6
3 4
4 5
5 6
```
