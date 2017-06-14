# LI3
University project for LI3 in C and Java.

## What is it about?
It parses wikipedia-like xml snapshots and extracts some information:
- Total number of articles
- Number of unique articles
- Total number of revisions
- Top 10 contributors
- Contributor username given his ID
- Top 20 largest articles
- Article title given its ID
- Top N articles with more words
- List of titles with a certain prefix
- Article timestamp given its ID and revision ID

## How do I install it?
For the C version, simply use `make`.
For the Java version just sit back and relax, we've done the work for you.

## How do I use it?
### In C
To run it simply do:
```
$ ./program path_to_snap/mySnapshot1 path_to_Nsnap/mySnapshotN
```
It will autimatically extract all of the information and present it to you.
If you want to see the information one query at a time you might want to try the interpretor mode:
```
$ ./program -i path_to_snap/mySnapshot1 path_to_Nsnap/mySnapshotN
```
### In Java
You just have to do:
```
$ ./run.sh path_to_snap/mySnapshot1 path_to_Nsnap/mySnapshotN
```
It will extract all of the information and present it in `results.txt` along with a file `times.txt` with the time analysis of the project.

## Contributors
Thank you:

[Gil Cunha](https://github.com/Nexturn)

[Nuno Faria](https://github.com/nuno-faria)

[Tânia Silva](https://github.com/p3rsephone)
