# ./ft_ls

./ft_ls list directorys and files (like the command ls).

### Installation

ft_ls has been tested on Darwin 16.7.0, Ubuntu 14.0LTS / 16.0LTS. Here are the requirements to install ft_ls on your machine :
Here are the requirements to install ft_ls on your machine :

```sh
$ make
```

### Handled options

| Option | Description |
| ------ | ------ |
| -1 | (The numeric digit 'one'.)  Force output to be one entry per line. This is the default when output is not to a terminal. |
| -a | List all entries including those starting with a dot . |
| -d, --directory | List directories themselves, not their contents. |
| -g | Like -l, but do not list owner |
| -i | For each file, print the file's file serial number (inode number). |
| -l | List in long format. Ownership, Date/Time etc (See below) For terminal output, a total sum of all the file sizes is output on a line before the long listing. If the file is a symbolic link the pathname of the linked-to file is preceded by -> |
| -m | Fill width with a comma separated list of entries |
| -r | Reverse the order of the sort to get reverse lexicographical order or the oldest entries first. (or largest files last, if combined with sort by size) |
| -R | Recursively list subdirectories encountered. |
| -S | Sort by file size. |
| -U | Do not sort |
| -@ | (ONLY ON OSX) Display extended attribute keys and sizes in long (-l) output. |
| -e | (ONLY ON OSX) Print the Access Control List (ACL) associated with the file, if present, in long (-l) output. |

### Fixes done
- Total size with ./ft_ls -l on directory with links
- Sort when ./ft_ls -r -t or ./ft_ls -t -r
- Sort when ./ft_ls -r is not alphabetic reversed
- ./ft_ls -1 -l should disable -l
- Unable to access link where we have no rights, but we are not in nested mode, and wrong total
When ls have, no rights on a link, it must just display the link path
ex :
ls -l ~/Library/Application\ Support
lrwxr-xr-x  1 aemilien  2016_paris  59 Nov  9 18:49 /Users/aemilien/Library/Application Support -> /Volumes/Storage/cache/aemilien/Library/Application Support

ls -l ~/Library/Application\ Support/
total 8
drwx------   6 aemilien  2016_paris   204 Nov  7 21:03 AddressBook
drwxr-xr-x   3 aemilien  2016_paris   102 Nov  9 18:50 App Store
...

ls -l ~/Library/Fonts/
lrwxr-xr-x  1 aemilien  2016_paris  16 Oct 27 16:25 /Users/aemilien/Library/Fonts -> ../goinfre/Fonts

ls -l ~/Library/Fonts
lrwxr-xr-x  1 aemilien  2016_paris  16 Oct 27 16:25 /Users/aemilien/Library/Fonts -> ../goinfre/Fonts
- Rewrite error messages for OSX

### To fix

- Fail on ./ft_ls -lR ~/Library at school, maybe related to total With links and link access, nned to test fix on OSX,
issue due to print_total access NULL link when no rights
- Use size_t for indexing, not int

### Todos

 - Bufferize output
 - -X sort alphabetically by entry extension
 - -x list entries by lines instead of by columns
 - -I, --ignore=PATTERN do not list implied entries matching shell PATTERN (need to change parser)
