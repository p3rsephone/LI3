# LI3
First phase of the project for LI3.

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
Use `make`.

## How do I use it?
To run it simply do:
```
$ ./program path_to_snap/mySnapshot1 path_to_Nsnap/mySnapshotN
```
It will autimatically extract all information and present it to you.
If you want to see the information one query at a time you might want to try the interpretor mode:
```
$ ./program -i path_to_snap/mySnapshot1 path_to_Nsnap/mySnapshotN
```

## Contributors
Thank you:

[Gil Cunha](https://github.com/Nexturn)

[Nuno Faria](https://github.com/nuno-faria)

[Tânia Silva](https://github.com/p3rsephone)
